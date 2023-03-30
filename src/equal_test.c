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

#include "src/equal.h"
#include "src/test.h"

static bool equal_float() {
  RADIANT_EXPECT_FALSE(radiant_equal(2.3f, 3.4f));
  RADIANT_EXPECT_FALSE(radiant_equal(4.2f, 1.2f));
  RADIANT_EXPECT_TRUE(radiant_equal(2.0f, 2.0f));
  return true;
}

int main() {
  radiant_suite_begin("equal");
  RADIANT_TEST(equal_float);
  return radiant_suite_end();
}
