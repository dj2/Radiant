// Copyright 2023 The Radiant Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/angle.h"
#include "src/array_element_count.h"
#include "src/buffer.h"
#include "src/camera.h"
#include "src/colour3.h"
#include "src/constants.h"
#include "src/engine.h"
#include "src/mat4x4.h"
#include "src/point3.h"
#include "src/resource_manager.h"
#include "src/shader.h"
#include "src/texture.h"
#include "src/view.h"
#include "src/window.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Uniforms {
  radiant_mat4x4_t model_view_projection_matrix;
  uint32_t frame;
  float frame_radians;
  uint32_t image_width;
  uint32_t image_height;
  // Pad size in order to get correct size for WGSL buffer
  RADIANT_PAD(sizeof(radiant_mat4x4_t) - (3 * sizeof(uint32_t)) -
              sizeof(float));
} Uniforms;

typedef struct Vertex {
  radiant_point3_t pos;
  radiant_colour3_t colour;
} Vertex;

typedef struct RenderBundle {
  WGPURenderPipeline pipeline;
  WGPUBindGroup uniform_bind_group;
  radiant_buffer_t vertex_buffer;
  radiant_buffer_t index_buffer;
  uint32_t index_count;
  uint32_t instance_count;
} RenderBundle;

static Vertex pyramid_vertex_data[] = {
    {
        // 0
        .pos = (radiant_point3_t){.0f, .5f, .0f},
        .colour = (radiant_colour3_t){1.f, 0.f, 0.f},
    },
    {
        // 1
        .pos = (radiant_point3_t){.5f, -.5f, -.5f},
        .colour = (radiant_colour3_t){0.f, 1.f, 0.f},
    },
    {
        // 2
        .pos = (radiant_point3_t){-.5f, -.5f, -.5f},
        .colour = (radiant_colour3_t){0.f, 0.f, 1.f},
    },
    {
        // 3
        .pos = (radiant_point3_t){.0f, -.5f, .5f},
        .colour = (radiant_colour3_t){1.f, 1.f, 0.f},
    },
};

static uint16_t pyramid_index_data[] = {
    // clang-format off
    // Face 1
    0, 1, 2,
    // Face 2
    0, 3, 1,
    // Face 3
    0, 2, 3,
    // Face 4
    3, 2, 1,
    // clang-format on
};

static radiant_point3_t plane_vertex_data[] = {
    (radiant_point3_t){-50.f, -10.f, -100.f},
    (radiant_point3_t){50.f, -10.f, -100.f},
    (radiant_point3_t){-50.f, -10.f, 100.f},
    (radiant_point3_t){50.f, -10.f, 100.f},
};

static uint16_t plane_index_data[] = {
    // clang-format off
    0, 1, 2,
    1, 3, 2
    // clang-format on
};

static RenderBundle setup_plane_bundle(radiant_engine_t engine,
                                       radiant_resource_manager_t manager,
                                       radiant_buffer_t uniform_buffer) {
  RenderBundle bundle;

  // Create shader
  radiant_shader_create_result_t shader_result =
      radiant_shader_create_from_file(engine, manager, "Checker shader",
                                      "shaders/checker.wgsl");
  if (!shader_result.succeeded) {
    return (RenderBundle){0};
  }
  radiant_shader_t shader = shader_result.shader;

  WGPUVertexAttribute vert_attrs[] = {
      {
          .format = WGPUVertexFormat_Float32x3,
          .offset = offsetof(Vertex, pos),
          .shaderLocation = 0,
      },
  };
  WGPUVertexBufferLayout vert_buf_layout[] = {
      {
          .arrayStride = sizeof(radiant_point3_t),
          .attributeCount = RADIANT_ARRAY_ELEMENT_COUNT(vert_attrs),
          .attributes = vert_attrs,
      },
  };
  WGPUColorTargetState target[] = {
      {
          .format = WGPUTextureFormat_BGRA8Unorm,
          .writeMask = WGPUColorWriteMask_All,
      },
  };
  WGPUFragmentState frag_state = {
      .module = shader.mod,
      .entryPoint = "fs_main",
      .targetCount = RADIANT_ARRAY_ELEMENT_COUNT(target),
      .targets = target,
  };

  WGPUDepthStencilState depth_stencil = {
      .format = WGPUTextureFormat_Depth24Plus,
      .depthWriteEnabled = true,
      .depthCompare = WGPUCompareFunction_Less,
      .stencilFront =
          {
              .compare = WGPUCompareFunction_Always,
              .failOp = WGPUStencilOperation_Keep,
              .depthFailOp = WGPUStencilOperation_Keep,
              .passOp = WGPUStencilOperation_Keep,
          },
      .stencilBack =
          {
              .compare = WGPUCompareFunction_Always,
              .failOp = WGPUStencilOperation_Keep,
              .depthFailOp = WGPUStencilOperation_Keep,
              .passOp = WGPUStencilOperation_Keep,
          },
      .stencilReadMask = 0xffffffff,
      .stencilWriteMask = 0xffffffff,
  };

  WGPURenderPipelineDescriptor pipeline_desc = {
      .label = "Plane Render Pipeline",
      .primitive =
          {
              .topology = WGPUPrimitiveTopology_TriangleList,
              .frontFace = WGPUFrontFace_CW,
              .cullMode = WGPUCullMode_Back,
          },
      .vertex =
          {
              .module = shader.mod,
              .entryPoint = "vs_main",
              .bufferCount = RADIANT_ARRAY_ELEMENT_COUNT(vert_buf_layout),
              .buffers = vert_buf_layout,
          },
      .fragment = &frag_state,
      .depthStencil = &depth_stencil,
      .multisample =
          {
              .count = 4,
              .mask = 0xffffffff,
          },
  };

  bundle.pipeline =
      wgpuDeviceCreateRenderPipeline(engine.device, &pipeline_desc);

  radiant_buffer_create_request_t vertex_buffer_req = {
      .engine = engine,
      .usage = radiant_buffer_usage_vertex,
      .label = "Plane vertex data",
      .size_in_bytes = sizeof(plane_vertex_data),
  };
  bundle.vertex_buffer =
      radiant_buffer_create_with_data(vertex_buffer_req, plane_vertex_data);

  radiant_buffer_create_request_t index_buffer_req = {
      .engine = engine,
      .usage = radiant_buffer_usage_index,
      .label = "Plane index buffer",
      .size_in_bytes = sizeof(plane_index_data),
  };
  bundle.index_buffer =
      radiant_buffer_create_with_data(index_buffer_req, plane_index_data);
  bundle.index_count = RADIANT_ARRAY_ELEMENT_COUNT(plane_index_data);
  bundle.instance_count = 1;

  WGPUBindGroupEntry bind_entries[] = {
      {
          .binding = 0,
          .buffer = uniform_buffer.buffer,
          .size = sizeof(Uniforms),
      },
  };

  WGPUBindGroupLayout bind_group_layout =
      wgpuRenderPipelineGetBindGroupLayout(bundle.pipeline, 0);
  WGPUBindGroupDescriptor bind_group_desc = {
      .label = "Uniform bind group",
      .layout = bind_group_layout,
      .entryCount = RADIANT_ARRAY_ELEMENT_COUNT(bind_entries),
      .entries = bind_entries,
  };
  bundle.uniform_bind_group =
      wgpuDeviceCreateBindGroup(engine.device, &bind_group_desc);

  wgpuBindGroupLayoutRelease(bind_group_layout);
  radiant_shader_destroy(shader);

  return bundle;
}

static RenderBundle setup_pyramid_bundle(radiant_engine_t engine,
                                         radiant_resource_manager_t manager,
                                         radiant_buffer_t uniform_buffer) {
  RenderBundle bundle;

  // Create shader
  radiant_shader_create_result_t shader_result =
      radiant_shader_create_from_file(engine, manager, "Passthrough shader",
                                      "shaders/pass_through.wgsl");
  if (!shader_result.succeeded) {
    return (RenderBundle){0};
  }
  radiant_shader_t shader = shader_result.shader;

  WGPUVertexAttribute vert_attrs[] = {
      {
          .format = WGPUVertexFormat_Float32x3,
          .offset = offsetof(Vertex, pos),
          .shaderLocation = 0,
      },
      {
          .format = WGPUVertexFormat_Float32x3,
          .offset = offsetof(Vertex, colour),
          .shaderLocation = 1,
      },
  };
  WGPUVertexBufferLayout vert_buf_layout[] = {
      {
          .arrayStride = sizeof(Vertex),
          .attributeCount = RADIANT_ARRAY_ELEMENT_COUNT(vert_attrs),
          .attributes = vert_attrs,
      },
  };
  WGPUColorTargetState target[] = {
      {
          .format = WGPUTextureFormat_BGRA8Unorm,
          .writeMask = WGPUColorWriteMask_All,
      },
  };
  WGPUFragmentState frag_state = {
      .module = shader.mod,
      .entryPoint = "fs_main",
      .targetCount = RADIANT_ARRAY_ELEMENT_COUNT(target),
      .targets = target,
  };

  WGPUDepthStencilState depth_stencil = {
      .format = WGPUTextureFormat_Depth24Plus,
      .depthWriteEnabled = true,
      .depthCompare = WGPUCompareFunction_Less,
      .stencilFront =
          {
              .compare = WGPUCompareFunction_Always,
              .failOp = WGPUStencilOperation_Keep,
              .depthFailOp = WGPUStencilOperation_Keep,
              .passOp = WGPUStencilOperation_Keep,
          },
      .stencilBack =
          {
              .compare = WGPUCompareFunction_Always,
              .failOp = WGPUStencilOperation_Keep,
              .depthFailOp = WGPUStencilOperation_Keep,
              .passOp = WGPUStencilOperation_Keep,
          },
      .stencilReadMask = 0xffffffff,
      .stencilWriteMask = 0xffffffff,
  };

  WGPURenderPipelineDescriptor pipeline_desc = {
      .label = "Pyramid Render Pipeline",
      .primitive =
          {
              .topology = WGPUPrimitiveTopology_TriangleList,
              .frontFace = WGPUFrontFace_CW,
              .cullMode = WGPUCullMode_Back,
          },
      .vertex =
          {
              .module = shader.mod,
              .entryPoint = "vs_main",
              .bufferCount = RADIANT_ARRAY_ELEMENT_COUNT(vert_buf_layout),
              .buffers = vert_buf_layout,
          },
      .fragment = &frag_state,
      .depthStencil = &depth_stencil,
      .multisample =
          {
              .count = 4,
              .mask = 0xffffffff,
          },
  };

  bundle.pipeline =
      wgpuDeviceCreateRenderPipeline(engine.device, &pipeline_desc);

  radiant_buffer_create_request_t vertex_buffer_req = {
      .engine = engine,
      .usage = radiant_buffer_usage_vertex,
      .label = "Pyramid vertex data",
      .size_in_bytes = sizeof(pyramid_vertex_data),
  };
  bundle.vertex_buffer =
      radiant_buffer_create_with_data(vertex_buffer_req, pyramid_vertex_data);

  radiant_buffer_create_request_t index_buffer_req = {
      .engine = engine,
      .usage = radiant_buffer_usage_index,
      .label = "Pyramid index buffer",
      .size_in_bytes = sizeof(pyramid_index_data),
  };
  bundle.index_buffer =
      radiant_buffer_create_with_data(index_buffer_req, pyramid_index_data);
  bundle.index_count = RADIANT_ARRAY_ELEMENT_COUNT(pyramid_index_data);
  bundle.instance_count = 2;

  WGPUBindGroupEntry bind_entries[] = {
      {
          .binding = 0,
          .buffer = uniform_buffer.buffer,
          .size = sizeof(Uniforms),
      },
  };

  WGPUBindGroupLayout bind_group_layout =
      wgpuRenderPipelineGetBindGroupLayout(bundle.pipeline, 0);
  WGPUBindGroupDescriptor bind_group_desc = {
      .label = "Uniform bind group",
      .layout = bind_group_layout,
      .entryCount = RADIANT_ARRAY_ELEMENT_COUNT(bind_entries),
      .entries = bind_entries,
  };
  bundle.uniform_bind_group =
      wgpuDeviceCreateBindGroup(engine.device, &bind_group_desc);

  wgpuBindGroupLayoutRelease(bind_group_layout);
  radiant_shader_destroy(shader);

  return bundle;
}

static void render_bundle(WGPURenderPassEncoder pass, RenderBundle b) {
  wgpuRenderPassEncoderSetPipeline(pass, b.pipeline);
  wgpuRenderPassEncoderSetBindGroup(pass, 0, b.uniform_bind_group, 0, NULL);
  wgpuRenderPassEncoderSetVertexBuffer(pass, 0, b.vertex_buffer.buffer, 0,
                                       WGPU_WHOLE_SIZE);
  wgpuRenderPassEncoderSetIndexBuffer(
      pass, b.index_buffer.buffer, WGPUIndexFormat_Uint16, 0, WGPU_WHOLE_SIZE);
  wgpuRenderPassEncoderDrawIndexed(pass, b.index_count, b.instance_count, 0, 0,
                                   0);
}

int main() {
  // TODO(dsinclair): This should probably pull from the build or something
  // instead of using a hard coded `resources` folder.
  radiant_resource_manager_create_result_t manager_result =
      radiant_resource_manager_create("./resources");
  if (!manager_result.succeeded) {
    fprintf(stderr, "Failed to create resource manager");
    return 1;
  }
  radiant_resource_manager_t manager = manager_result.manager;

  if (!radiant_windows_initialize()) {
    return 1;
  }

  radiant_view_t view = {
      .size =
          {
              .width = 1024.f,
              .height = 768.f,
          },
      .fov_y_radians = (2.f * RADIANT_PI) / 5.f,
      .planes =
          {
              .near = 1.f,
              .far = 100.f,
          },
  };

  radiant_window_create_result_t window_result = radiant_window_create(view);
  if (!window_result.succeeded) {
    return 1;
  }
  radiant_window_t window = window_result.window;

  radiant_engine_create_result_t engine_result =
      radiant_engine_create(window, view);
  if (!engine_result.succeeded) {
    return 1;
  }
  radiant_engine_t engine = engine_result.engine;

  // Create Uniform Buffer
  Uniforms uniforms = {
      .model_view_projection_matrix = radiant_mat4x4_identity(),
      .frame = 0,
      .frame_radians = radiant_deg_to_rad(0),
      .image_width = (uint32_t)view.size.width,
      .image_height = (uint32_t)view.size.height,
  };
  radiant_buffer_create_request_t uniform_buffer_req = {
      .engine = engine,
      .usage = radiant_buffer_usage_uniform,
      .label = "Uniform data",
      .size_in_bytes = sizeof(uniforms),
  };
  radiant_buffer_t uniform_buffer =
      radiant_buffer_create_with_data(uniform_buffer_req, &uniforms);

  // Setup pipelines
  RenderBundle pyramid_bundle =
      setup_pyramid_bundle(engine, manager, uniform_buffer);

  RenderBundle plane_bundle =
      setup_plane_bundle(engine, manager, uniform_buffer);

  // Create depth texture
  radiant_texture_create_request_t depth_texture_req = {
      .engine = engine,
      .label = "Depth Texture",
      .format = WGPUTextureFormat_Depth24Plus,
      .size =
          {
              .width = (uint32_t)view.size.width,
              .height = (uint32_t)view.size.height,
          },
      .samples = 4,
  };
  radiant_texture_t depth_texture = radiant_texture_create(depth_texture_req);

  // Create render texture
  radiant_texture_create_request_t render_texture_req = {
      .engine = engine,
      .label = "Render Texture",
      .format = WGPUTextureFormat_BGRA8Unorm,
      .size =
          {
              .width = (uint32_t)view.size.width,
              .height = (uint32_t)view.size.height,
          },
      .samples = 4,
  };
  radiant_texture_t render_texture = radiant_texture_create(render_texture_req);

  radiant_texture_view_t render_view =
      radiant_texture_view_create(render_texture);

  radiant_camera_t cam = radiant_camera_create(
      (radiant_point3_t){0.f, 0.f, 4.f}, (radiant_point3_t){0.f, 0.f, 0.f},
      (radiant_vec3_t){0.f, 1.f, 0.f}, view);

  uint32_t frame = 0;

  while (!radiant_window_should_close(window)) {
    radiant_windows_poll_events();
    wgpuInstanceProcessEvents(engine.instance);

    frame += 1;

    WGPUCommandEncoderDescriptor cmd_desc = {
        .label = "Main encoder",
    };
    WGPUCommandEncoder encoder =
        wgpuDeviceCreateCommandEncoder(engine.device, &cmd_desc);

    {
      WGPUTextureView backbuffer =
          wgpuSwapChainGetCurrentTextureView(engine.swapchain);

      WGPURenderPassColorAttachment colour_attach[] = {
          {
              .view = render_view.view,
              .resolveTarget = backbuffer,
              .loadOp = WGPULoadOp_Clear,
              .storeOp = WGPUStoreOp_Store,
              .clearValue =
                  {
                      .r = .2,
                      .g = .2,
                      .b = .2,
                      .a = 1.,
                  },
          },
      };

      radiant_texture_view_t depth_view =
          radiant_texture_view_create(depth_texture);
      WGPURenderPassDepthStencilAttachment depth_attach = {
          .view = depth_view.view,
          .depthClearValue = 1.f,
          .depthLoadOp = WGPULoadOp_Clear,
          .depthStoreOp = WGPUStoreOp_Store,
      };
      WGPURenderPassDescriptor pass_desc = {
          .label = "Render pass",
          .colorAttachmentCount = RADIANT_ARRAY_ELEMENT_COUNT(colour_attach),
          .colorAttachments = colour_attach,
          .depthStencilAttachment = &depth_attach,
      };

      WGPURenderPassEncoder pass =
          wgpuCommandEncoderBeginRenderPass(encoder, &pass_desc);

      // Update uniforms
      {
        float frame_deg = radiant_deg_to_rad((float)(frame % 360));
        // Rotate camera
        radiant_camera_rotate(&cam, (radiant_point3_t){0.f, frame_deg, 0.f});

        // Object rotation
        radiant_mat4x4_t model_matrix = radiant_mat4x4_translate(
            (radiant_vec3_t){0.f, sinf(frame_deg), 0.f});

        uniforms.frame = frame;
        uniforms.frame_radians = frame_deg;
        uniforms.model_view_projection_matrix =
            radiant_mat4x4_mul(cam.projection_view_matrix, model_matrix);
        radiant_buffer_write(uniform_buffer, sizeof(uniforms), &uniforms);
      }
      render_bundle(pass, pyramid_bundle);

      // Update uniforms
      {
        // Object rotation
        // radiant_mat4x4_t model_matrix = radiant_mat4x4_identity();
        // uniforms.model_view_projection_matrix =
        //    radiant_mat4x4_mul(cam.projection_view_matrix, model_matrix);
        // radiant_buffer_write(uniform_buffer, sizeof(uniforms), &uniforms);
      }

      render_bundle(pass, plane_bundle);

      wgpuRenderPassEncoderEnd(pass);
      wgpuRenderPassEncoderRelease(pass);

      radiant_texture_view_destroy(depth_view);
    }

    WGPUCommandBuffer commands = wgpuCommandEncoderFinish(encoder, NULL);
    wgpuCommandEncoderRelease(encoder);

    WGPUQueue queue = wgpuDeviceGetQueue(engine.device);
    wgpuQueueSubmit(queue, 1, &commands);
    wgpuCommandBufferRelease(commands);

    wgpuSwapChainPresent(engine.swapchain);
  }

  radiant_texture_view_destroy(render_view);
  radiant_texture_destroy(render_texture);
  radiant_texture_destroy(depth_texture);

  wgpuRenderPipelineRelease(pyramid_bundle.pipeline);
  wgpuRenderPipelineRelease(plane_bundle.pipeline);

  radiant_camera_destroy(cam);
  radiant_buffer_destroy(uniform_buffer);
  radiant_buffer_destroy(plane_bundle.index_buffer);
  radiant_buffer_destroy(plane_bundle.vertex_buffer);
  radiant_buffer_destroy(pyramid_bundle.index_buffer);
  radiant_buffer_destroy(pyramid_bundle.vertex_buffer);
  radiant_engine_destroy(engine);
  radiant_window_destroy(window);
  radiant_windows_shutdown();
  radiant_resource_manager_destroy(manager);

  return 0;
}
