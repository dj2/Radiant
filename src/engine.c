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

#include "src/engine.h"
#include "src/glfw.h"
#include "src/no_return.h"

#include <stdio.h>

#if defined(__APPLE__)
#include "src/surface_metal.h"
#elif defined(__linux__)
#include "src/surface_x11.h"
#elif defined(_WIN32)
#include "src/surface_win.h"
#endif

/// Callback for uncaptured errors from WebGPU
static void uncaptured_error_callback(WGPUErrorType type,
                                      char const* message,
                                      void* /* userdata */) {
  switch (type) {
    case WGPUErrorType_NoError:
      break;
    case WGPUErrorType_Validation:
      fprintf(stderr, "Uncaptured error -- validation: %s", message);
      break;
    case WGPUErrorType_OutOfMemory:
      fprintf(stderr, "Uncaptured error -- out of memory: %s", message);
      break;
    case WGPUErrorType_Internal:
      fprintf(stderr, "Uncaptured error -- internal: %s", message);
      break;
    case WGPUErrorType_Unknown:
      fprintf(stderr, "Uncaptured error -- unknown: %s", message);
      break;
    case WGPUErrorType_DeviceLost:
      fprintf(stderr, "Uncaptured error -- device lost: %s", message);
      break;
    case WGPUErrorType_Force32:
      break;
  }
}

/// Callback when device is lost
static void device_lost_callback(WGPUDeviceLostReason reason,
                                 char const* message,
                                 void* /* userdata */) {
  switch (reason) {
    case WGPUDeviceLostReason_Destroyed:
      fprintf(stderr, "Device lost: destroyed: %s\n", message);
      break;

    case WGPUDeviceLostReason_Undefined:
      fprintf(stderr, "Device lost: undefined: %s\n", message);
      break;

    case WGPUDeviceLostReason_Force32:
      break;
  }
}

/// Logging callback
static void logging_callback(WGPULoggingType type,
                             char const* message,
                             void* /* userdata */) {
  switch (type) {
    case WGPULoggingType_Verbose:
      fprintf(stderr, "Log: verbose: %s\n", message);
      break;
    case WGPULoggingType_Info:
      fprintf(stderr, "Log: info: %s\n", message);
      break;
    case WGPULoggingType_Warning:
      fprintf(stderr, "Log: warning: %s\n", message);
      break;
    case WGPULoggingType_Error:
      fprintf(stderr, "Log: error: %s\n", message);
      break;
    case WGPULoggingType_Force32:
      break;
  }
}

/// Callback when requesting an adapter
static void adapter_request_callback(WGPURequestAdapterStatus status,
                                     WGPUAdapter adapter,
                                     char const* message,
                                     void* userdata) {
  radiant_engine_create_result_t* result =
      (radiant_engine_create_result_t*)userdata;
  result->engine.adapter = adapter;

  switch (status) {
    case WGPURequestAdapterStatus_Success:
      break;
    case WGPURequestAdapterStatus_Unavailable:
      fprintf(stderr, "WGPU adapter unavailable: %s\n", message);
      result->succeeded = false;
      break;

    case WGPURequestAdapterStatus_Error:
    case WGPURequestAdapterStatus_Unknown:
    case WGPURequestAdapterStatus_Force32:
      fprintf(stderr, "WGPU adapter error: %s\n", message);
      result->succeeded = false;
      break;
  }
}

static radiant_surface_descriptor_t create_surface_descriptor(
    GLFWwindow* window) {
#if defined(__APPLE__)
  return radiant_engine_create_metal_surface_descriptor(window);
#elif defined(__linux__)
  return radiant_engine_create_x11_surface_descriptor(window);
#elif defined(_WIN32)
  return radiant_engine_create_win_surface_descriptor(window);
#else
#error "Unknown surface to create"
#endif
}

radiant_engine_create_result_t radiant_engine_create(radiant_window_t window) {
  radiant_engine_create_result_t result = {
      .engine = {0},
      .succeeded = true,
  };
  radiant_engine_t* engine = &result.engine;

  WGPUInstanceDescriptor instance_descriptor = {0};
  engine->instance = wgpuCreateInstance(&instance_descriptor);

  WGPURequestAdapterOptions adapter_options = {0};
  wgpuInstanceRequestAdapter(engine->instance, &adapter_options,
                             adapter_request_callback, &result);
  if (!result.succeeded) {
    wgpuInstanceRelease(engine->instance);
    return result;
  }

  WGPUDeviceDescriptor device_descriptor = {
      .label = "Primary device",
  };
  engine->device = wgpuAdapterCreateDevice(engine->adapter, &device_descriptor);

  wgpuDeviceSetUncapturedErrorCallback(engine->device,
                                       uncaptured_error_callback, NULL);
  wgpuDeviceSetDeviceLostCallback(engine->device, device_lost_callback, NULL);
  wgpuDeviceSetLoggingCallback(engine->device, logging_callback, NULL);

  radiant_surface_descriptor_t chain_surface_descriptor =
      create_surface_descriptor(window.glfw_window);
  WGPUSurfaceDescriptor surface_descriptor = {
      .nextInChain = (WGPUChainedStruct*)&chain_surface_descriptor,
      .label = "Primary surface",
  };
  engine->surface =
      wgpuInstanceCreateSurface(engine->instance, &surface_descriptor);

  WGPUSwapChainDescriptor swapchain_descriptor = {
      .label = "Primary swapchain",
      .usage = WGPUTextureUsage_RenderAttachment,
      .format = WGPUTextureFormat_BGRA8Unorm,
      .width = 1024,
      .height = 768,
      .presentMode = WGPUPresentMode_Mailbox,
  };
  engine->swapchain = wgpuDeviceCreateSwapChain(engine->device, engine->surface,
                                                &swapchain_descriptor);

  return result;
}

void radiant_engine_destroy(radiant_engine_t engine) {
  wgpuSwapChainRelease(engine.swapchain);
  wgpuSurfaceRelease(engine.surface);
  // Remove the device lost callback as it will be lost when we release it.
  wgpuDeviceSetDeviceLostCallback(engine.device, NULL, NULL);
  wgpuDeviceRelease(engine.device);
  wgpuAdapterRelease(engine.adapter);
  wgpuInstanceRelease(engine.instance);
}
