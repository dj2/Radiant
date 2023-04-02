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
#include "src/colour3.h"
#include "src/constants.h"
#include "src/engine.h"
#include "src/mat4x4.h"
#include "src/point3.h"
#include "src/resource_manager.h"
#include "src/shader.h"
#include "src/window.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Uniforms {
  radiant_mat4x4_t model_view_project_matrix;
} Uniforms;

static struct vertices {
  radiant_point3_t pos;
  radiant_colour3_t colour;
} vertex_data[] = {
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

static uint16_t index_data[] = {
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

  radiant_window_create_result_t window_result = radiant_window_create();
  if (!window_result.succeeded) {
    return 1;
  }
  radiant_window_t window = window_result.window;

  radiant_engine_create_result_t engine_result = radiant_engine_create(window);
  if (!engine_result.succeeded) {
    return 1;
  }
  radiant_engine_t engine = engine_result.engine;

  // Create shader
  radiant_shader_create_result_t shader_result =
      radiant_shader_create_from_file(engine, manager, "Passthrough shader",
                                      "shaders/pass_through.wgsl");
  if (!shader_result.succeeded) {
    return 1;
  }
  radiant_shader_t shader = shader_result.shader;

  WGPUVertexAttribute vert_attrs[] = {
      {
          .format = WGPUVertexFormat_Float32x3,
          .offset = offsetof(struct vertices, pos),
          .shaderLocation = 0,
      },
      {
          .format = WGPUVertexFormat_Float32x3,
          .offset = offsetof(struct vertices, colour),
          .shaderLocation = 1,
      },
  };
  WGPUVertexBufferLayout vert_buf_layout = {
      .arrayStride = sizeof(struct vertices),
      .attributeCount = 2,
      .attributes = vert_attrs,
  };
  WGPUColorTargetState target = {
      .format = WGPUTextureFormat_BGRA8Unorm,
      .writeMask = WGPUColorWriteMask_All,
  };
  WGPUFragmentState frag_state = {
      .module = shader.mod,
      .entryPoint = "fs_main",
      .targetCount = 1,
      .targets = &target,
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
      .label = "Main Render Pipeline",
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
              .bufferCount = 1,
              .buffers = &vert_buf_layout,
          },
      .fragment = &frag_state,
      .depthStencil = &depth_stencil,
      .multisample =
          {
              .count = 1,
              .mask = 0xffffffff,
          },
  };

  WGPURenderPipeline pipeline =
      wgpuDeviceCreateRenderPipeline(engine.device, &pipeline_desc);

  // Create Vertex Buffer
  radiant_buffer_create_request_t vertex_buffer_req = {
      .engine = engine,
      .usage = radiant_buffer_usage_vertex,
      .label = "Vertex data",
      .size_in_bytes = sizeof(vertex_data),
  };
  radiant_buffer_t vertex_buffer =
      radiant_buffer_create_with_data(vertex_buffer_req, vertex_data);

  radiant_buffer_create_request_t index_buffer_req = {
      .engine = engine,
      .usage = radiant_buffer_usage_index,
      .label = "Index buffer",
      .size_in_bytes = sizeof(index_data),
  };
  radiant_buffer_t index_buffer =
      radiant_buffer_create_with_data(index_buffer_req, index_data);

  // Create Uniform Buffer
  radiant_buffer_create_request_t uniform_buffer_req = {
      .engine = engine,
      .usage = (radiant_buffer_usage_t)(radiant_buffer_usage_uniform |
                                        radiant_buffer_usage_copy_dst),
      .label = "Uniform data",
      .size_in_bytes = sizeof(Uniforms),
  };
  radiant_buffer_t uniform_buffer = radiant_buffer_create(uniform_buffer_req);

  // Create depth texture
  WGPUTextureDescriptor texture_desc = {
      .label = "Depth texture",
      .usage = WGPUTextureUsage_RenderAttachment,
      .dimension = WGPUTextureDimension_2D,
      .format = WGPUTextureFormat_Depth24Plus,
      .size =
          {
              .width = 1024,
              .height = 768,
              .depthOrArrayLayers = 1,
          },
      .mipLevelCount = 1,
      .sampleCount = 1,
  };
  WGPUTexture depth_texture =
      wgpuDeviceCreateTexture(engine.device, &texture_desc);

  WGPUBindGroupEntry bind_entries[] = {{
      .binding = 0,
      .buffer = uniform_buffer.buffer,
      .size = sizeof(Uniforms),
  }};

  WGPUBindGroupLayout bind_group_layout =
      wgpuRenderPipelineGetBindGroupLayout(pipeline, 0);
  WGPUBindGroupDescriptor bind_group_desc = {
      .label = "Uniform bind group",
      .layout = bind_group_layout,
      .entryCount = 1,
      .entries = bind_entries,
  };
  WGPUBindGroup uniform_bind_group =
      wgpuDeviceCreateBindGroup(engine.device, &bind_group_desc);

  wgpuBindGroupLayoutRelease(bind_group_layout);

  radiant_shader_destroy(shader);

  uint64_t frame = 0;

  while (!radiant_window_should_close(window)) {
    radiant_windows_poll_events();
    wgpuInstanceProcessEvents(engine.instance);

    frame += 1;
    (void)frame;

    float aspect = 1024.f / 768.f;
    float fov_y_radians = (2.f * RADIANT_PI) / 5.f;
    radiant_mat4x4_t projection =
        radiant_mat4x4_perspective(fov_y_radians, aspect, 1.f, 100.f);

    radiant_vec3_t cam_initial_pos = {
        0.f,
        0.f,
        4.f,
    };
    radiant_mat4x4_t rot =
        radiant_mat4x4_rotate_y(radiant_deg_to_rad((float)(frame) / 2.f));
    radiant_vec3_t cam_pos = radiant_mat4x4_mul(rot, cam_initial_pos);

    radiant_mat4x4_t cam =
        radiant_mat4x4_look_at(cam_pos, (radiant_vec3_t){0.f, 0.f, 0.f},
                               (radiant_vec3_t){0.f, 1.f, 0.f});

    Uniforms uniforms = {
        .model_view_project_matrix = radiant_mat4x4_mul(projection, cam),
    };

    radiant_buffer_write(uniform_buffer, sizeof(Uniforms), &uniforms);

    WGPUCommandEncoderDescriptor cmd_desc = {
        .label = "Main encoder",
    };
    WGPUCommandEncoder encoder =
        wgpuDeviceCreateCommandEncoder(engine.device, &cmd_desc);

    {
      WGPUTextureView backbuffer =
          wgpuSwapChainGetCurrentTextureView(engine.swapchain);

      WGPURenderPassColorAttachment colour_attach = {
          .view = backbuffer,
          .loadOp = WGPULoadOp_Clear,
          .storeOp = WGPUStoreOp_Store,
          .clearValue =
              {
                  .r = .2,
                  .g = .2,
                  .b = .2,
                  .a = 1.,
              },
      };

      WGPUTextureView depth_view = wgpuTextureCreateView(depth_texture, NULL);
      WGPURenderPassDepthStencilAttachment depth_attach = {
          .view = depth_view,
          .depthClearValue = 1.f,
          .depthLoadOp = WGPULoadOp_Clear,
          .depthStoreOp = WGPUStoreOp_Store,
      };
      WGPURenderPassDescriptor pass_desc = {
          .label = "Render pass",
          .colorAttachmentCount = 1,
          .colorAttachments = &colour_attach,
          .depthStencilAttachment = &depth_attach,
      };

      WGPURenderPassEncoder pass =
          wgpuCommandEncoderBeginRenderPass(encoder, &pass_desc);

      wgpuRenderPassEncoderSetPipeline(pass, pipeline);
      wgpuRenderPassEncoderSetBindGroup(pass, 0, uniform_bind_group, 0, NULL);
      wgpuRenderPassEncoderSetVertexBuffer(pass, 0, vertex_buffer.buffer, 0,
                                           WGPU_WHOLE_SIZE);
      wgpuRenderPassEncoderSetIndexBuffer(pass, index_buffer.buffer,
                                          WGPUIndexFormat_Uint16, 0,
                                          WGPU_WHOLE_SIZE);
      wgpuRenderPassEncoderDrawIndexed(
          pass, RADIANT_ARRAY_ELEMENT_COUNT(index_data), 1, 0, 0, 0);
      wgpuRenderPassEncoderEnd(pass);

      wgpuRenderPassEncoderRelease(pass);
      wgpuTextureViewRelease(depth_view);
    }

    WGPUCommandBuffer commands = wgpuCommandEncoderFinish(encoder, NULL);
    wgpuCommandEncoderRelease(encoder);

    WGPUQueue queue = wgpuDeviceGetQueue(engine.device);
    wgpuQueueSubmit(queue, 1, &commands);
    wgpuCommandBufferRelease(commands);

    wgpuSwapChainPresent(engine.swapchain);
  }

  wgpuRenderPipelineRelease(pipeline);

  radiant_buffer_destroy(uniform_buffer);
  radiant_buffer_destroy(index_buffer);
  radiant_buffer_destroy(vertex_buffer);
  radiant_engine_destroy(engine);
  radiant_window_destroy(window);
  radiant_windows_shutdown();
  radiant_resource_manager_destroy(manager);

  return 0;
}
