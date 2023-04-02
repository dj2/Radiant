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

#include "src/window.h"

#include <stdio.h>

static void glfw_error_callback(int code, const char* message) {
  fprintf(stderr, "GLFW error: %d: %s\n", code, message);
}

bool radiant_windows_initialize() {
  glfwSetErrorCallback(glfw_error_callback);

  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize glfw\n");
    return false;
  }
  return true;
}

void radiant_windows_shutdown() {
  glfwTerminate();
}

void radiant_windows_poll_events() {
  glfwPollEvents();
}

radiant_window_create_result_t radiant_window_create(radiant_view_t view) {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);

  radiant_window_create_result_t result = {
      .window = {0},
      .succeeded = true,
  };
  radiant_window_t* window = &result.window;
  window->glfw_window =
      glfwCreateWindow((int32_t)view.size.width, (int32_t)view.size.height,
                       "radiant", NULL, NULL);
  if (!window->glfw_window) {
    fprintf(stderr, "Failed to create window\n");
    result.succeeded = false;
    return result;
  }
  return result;
}

void radiant_window_destroy(radiant_window_t window) {
  glfwDestroyWindow(window.glfw_window);
}

bool radiant_window_should_close(radiant_window_t window) {
  return glfwWindowShouldClose(window.glfw_window);
}
