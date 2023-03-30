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

#include "src/test.h"

static bool suite_passed = true;

void radiant_suite_begin(const char* name) {
  printf("Running suite: %s\n", name);
}

int radiant_suite_end() {
  return suite_passed ? 0 : 1;
}

void radiant_run_test(radiant_test_t test, const char* name) {
  printf("Running %s ... ", name);
  fflush(stdout);

  if (!test()) {
    suite_passed = false;
  } else {
    printf(RADIANT_GREEN "PASSED" RADIANT_RESET "\n");
  }
}
