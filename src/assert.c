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

#include "src/assert.h"

#include <stdio.h>

#include "src/unreachable.h"

void radiant_assert(const char* file,
                    uint32_t line,
                    const char* func,
                    const char* msg,
                    const char* expr) {
  fprintf(stderr, "ASSERT: %s:%d:%s: %s", file, line, func, expr);
  if (msg) {
    fprintf(stderr, ": %s", msg);
  }
  fprintf(stderr, "\n");

  RADIANT_UNREACHABLE();
}
