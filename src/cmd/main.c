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
#include "src/window.h"

int main() {
  if (!radiant_windows_initialize()) {
    return 1;
  }

  radiant_window_create_result_t window_result = radiant_window_create();
  if (!window_result.succeeded) {
    return 0;
  }
  radiant_window_t window = window_result.window;

  radiant_engine_create_result_t engine_result = radiant_engine_create(window);
  if (!engine_result.succeeded) {
    return 0;
  }
  radiant_engine_t engine = engine_result.engine;

  while (!radiant_window_should_close(window)) {
    radiant_windows_poll_events();
  }

  radiant_engine_destroy(engine);
  radiant_window_destroy(window);
  radiant_windows_shutdown();

  return 0;
}
