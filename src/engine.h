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

#pragma once

#include "src/pad.h"
#include "src/view.h"
#include "src/wgpu.h"
#include "src/window.h"

/// The engine data engine
typedef struct radiant_engine_t {
  WGPUInstance instance;
  WGPUAdapter adapter;
  WGPUDevice device;
  WGPUSurface surface;
  WGPUSwapChain swapchain;
} radiant_engine_t;

/// Results of creating an engine
typedef struct radiant_engine_create_result_t {
  /// The engine handle. Only valid if |succeeded| is true.
  radiant_engine_t engine;
  /// True if the engine was successfully created. False otherwise.
  bool succeeded;
  /// Unused padding
  RADIANT_PAD(7);
} radiant_engine_create_result_t;

/// Creates and initializes a new engine based on the given |window|.
radiant_engine_create_result_t radiant_engine_create(radiant_window_t window,
                                                     radiant_view_t view);

/// Destroys the |engine|.
void radiant_engine_destroy(radiant_engine_t engine);
