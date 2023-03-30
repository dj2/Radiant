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

#include "src/buffer.h"
#include "src/engine.h"
#include "src/resource_manager.h"
#include "src/shader.h"
#include "src/vec3.h"
#include "src/window.h"

#include <stdio.h>
#include <stdlib.h>

static struct vertices {
  radiant_vec3_t pos;
  radiant_vec3_t colour;
} vertex_data[] = {
    {
        .pos = (radiant_vec3_t){0.0f, 0.5f, 0.0f},
        .colour = (radiant_vec3_t){1.f, 0.f, 0.f},
    },
    {
        .pos = (radiant_vec3_t){-0.5f, -0.5f, 0.0f},
        .colour = (radiant_vec3_t){0.f, 1.f, 0.f},
    },
    {
        .pos = (radiant_vec3_t){0.5f, -0.5f, 0.0f},
        .colour = (radiant_vec3_t){0.f, 0.f, 1.f},
    },
};

int main() {
  // Set setderr to unbuffered
  setvbuf(stderr, NULL, _IONBF, 0);

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

  radiant_buffer_create_request_t vertex_buffer_req = {
      .engine = engine,
      .usage = radiant_buffer_usage_vertex,
      .label = "Vertex data",
      .size_in_bytes = sizeof(vertex_data),
  };
  radiant_buffer_t vertex_buffer =
      radiant_buffer_create_with_data(vertex_buffer_req, vertex_data);

  radiant_file_result_t shader_file_result =
      radiant_resource_manager_open(manager, "shaders/pass_through.wgsl");
  if (!shader_file_result.succeeded) {
    fprintf(stderr, "Unable to load pass_through shader");
    return 1;
  }

  radiant_file_t shader_file = shader_file_result.file;
  uint64_t shader_file_size = radiant_file_size(shader_file);

  char* shader_data = (char*)malloc((uint32_t)shader_file_size);
  if (!radiant_file_read(shader_file, shader_data, shader_file_size)) {
    fprintf(stderr, "Failed to read shader file");
    return 1;
  }

  radiant_shader_t shader =
      radiant_shader_create(engine, "Passthrough shader", shader_data);
  free(shader_data);
  radiant_file_close(shader_file);

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

  WGPURenderPipelineDescriptor pipeline_desc = {
      .label = "Main Render Pipeline",
      .primitive =
          {
              .topology = WGPUPrimitiveTopology_TriangleList,
              .frontFace = WGPUFrontFace_CCW,
              .cullMode = WGPUCullMode_None,
          },
      .vertex =
          {
              .module = shader.mod,
              .entryPoint = "vs_main",
              .bufferCount = 1,
              .buffers = &vert_buf_layout,
          },
      .fragment = &frag_state,
      .multisample =
          {
              .count = 1,
              .mask = 0xffffffff,
          },
  };

  WGPURenderPipeline pipeline =
      wgpuDeviceCreateRenderPipeline(engine.device, &pipeline_desc);

  radiant_shader_destroy(shader);

  while (!radiant_window_should_close(window)) {
    radiant_windows_poll_events();

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

      WGPURenderPassDescriptor pass_desc = {
          .label = "Render pass",
          .colorAttachmentCount = 1,
          .colorAttachments = &colour_attach,
      };

      WGPURenderPassEncoder pass =
          wgpuCommandEncoderBeginRenderPass(encoder, &pass_desc);

      wgpuRenderPassEncoderSetPipeline(pass, pipeline);
      wgpuRenderPassEncoderSetVertexBuffer(pass, 0, vertex_buffer.buffer, 0,
                                           WGPU_WHOLE_SIZE);
      wgpuRenderPassEncoderDraw(pass, 3, 1, 0, 0);
      wgpuRenderPassEncoderEnd(pass);

      wgpuRenderPassEncoderRelease(pass);
    }

    WGPUCommandBuffer commands = wgpuCommandEncoderFinish(encoder, NULL);
    wgpuCommandEncoderRelease(encoder);

    WGPUQueue queue = wgpuDeviceGetQueue(engine.device);
    wgpuQueueSubmit(queue, 1, &commands);
    wgpuCommandBufferRelease(commands);

    wgpuSwapChainPresent(engine.swapchain);
  }

  radiant_buffer_destroy(vertex_buffer);
  radiant_engine_destroy(engine);
  radiant_window_destroy(window);
  radiant_windows_shutdown();
  radiant_resource_manager_destroy(manager);

  return 0;
}
