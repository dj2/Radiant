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

#include "src/glfw.h"
#include "src/pad.h"

#include <stdbool.h>

/// A window
typedef struct radiant_window_t {
  GLFWwindow* glfw_window;
} radiant_window_t;

/// Results of creating a window
typedef struct radiant_window_create_result_t {
  /// The window handle. Only valid if |succeeded| is true.
  radiant_window_t window;
  /// True if the window was successfully created. False otherwise.
  bool succeeded;
  /// Unused padding
  RADIANT_PAD(7);
} radiant_window_create_result_t;

/// Initializes the window system
bool radiant_windows_initialize(void);
/// Shuts down the window system
void radiant_windows_shutdown(void);

/// Polls the window system for new events
void radiant_windows_poll_events(void);

/// Creates a new window
radiant_window_create_result_t radiant_window_create(void);
/// Destroys a window
void radiant_window_destroy(radiant_window_t window);

/// Returns true if |window| should close
bool radiant_window_should_close(radiant_window_t window);
