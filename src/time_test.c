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

#include "src/time.h"
#include "src/test.h"

static bool sub() {
  radiant_time_t first = 123;
  radiant_time_t second = 234;
  RADIANT_EXPECT_EQ((uint32_t)radiant_time_sub(first, second), 111);
  RADIANT_EXPECT_EQ((uint32_t)radiant_time_sub(second, first), 111);
  return true;
}

static bool to_ms() {
  radiant_time_t mark1 = 1;
  radiant_time_t mark2 = 1000001;
  radiant_time_diff_t diff = radiant_time_sub(mark1, mark2);
  RADIANT_EXPECT_DOUBLE_EQ(radiant_time_diff_to_ms(diff), 1.0);
  return true;
}

int main() {
  radiant_suite_begin("time");
  RADIANT_TEST(sub);
  RADIANT_TEST(to_ms);
  return radiant_suite_end();
}
