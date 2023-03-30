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

#include <stddef.h>

#include "src/test.h"
#include "src/vec2.h"

static bool add() {
  radiant_vec2_t v1 = {
      .x = 1.2f,
      .y = 2.3f,
  };
  radiant_vec2_t v2 = {
      .x = 3.4f,
      .y = -1.2f,
  };
  radiant_vec2_t v3 = radiant_vec2_add(v1, v2);

  RADIANT_EXPECT_FLOAT_EQ(4.6f, v3.x);
  RADIANT_EXPECT_FLOAT_EQ(1.1f, v3.y);
  return true;
}

static bool sub() {
  radiant_vec2_t v1 = {
      .x = 1.2f,
      .y = 2.3f,
  };
  radiant_vec2_t v2 = {
      .x = 3.4f,
      .y = -1.2f,
  };
  radiant_vec2_t v3 = radiant_vec2_sub(v1, v2);

  RADIANT_EXPECT_FLOAT_EQ(-2.2f, v3.x);
  RADIANT_EXPECT_FLOAT_EQ(3.5f, v3.y);
  return true;
}

static bool mul() {
  radiant_vec2_t v1 = {
      .x = 1.2f,
      .y = 2.3f,
  };
  radiant_vec2_t v2 = {
      .x = 3.4f,
      .y = -1.2f,
  };
  radiant_vec2_t v3 = radiant_vec2_mul(v1, v2);

  RADIANT_EXPECT_FLOAT_EQ(4.08f, v3.x);
  RADIANT_EXPECT_FLOAT_EQ(-2.76f, v3.y);
  return true;
}

static bool div() {
  radiant_vec2_t v1 = {
      .x = 1.2f,
      .y = 2.3f,
  };
  radiant_vec2_t v3 = radiant_vec2_div(v1, 2);

  RADIANT_EXPECT_FLOAT_EQ(0.6f, v3.x);
  RADIANT_EXPECT_FLOAT_EQ(1.15f, v3.y);
  return true;
}

static bool div_by_negative() {
  radiant_vec2_t v1 = {
      .x = 1.2f,
      .y = 2.3f,
  };
  radiant_vec2_t v3 = radiant_vec2_div(v1, -2);

  RADIANT_EXPECT_FLOAT_EQ(-0.6f, v3.x);
  RADIANT_EXPECT_FLOAT_EQ(-1.15f, v3.y);
  return true;
}

static bool scale() {
  radiant_vec2_t v1 = {
      .x = 1.2f,
      .y = 2.3f,
  };
  radiant_vec2_t v3 = radiant_vec2_mul(v1, 2);

  RADIANT_EXPECT_FLOAT_EQ(2.4f, v3.x);
  RADIANT_EXPECT_FLOAT_EQ(4.6f, v3.y);
  return true;
}

static bool negate() {
  radiant_vec2_t v1 = {
      .x = 1.2f,
      .y = 2.3f,
  };
  radiant_vec2_t v3 = radiant_vec2_negate(v1);

  RADIANT_EXPECT_FLOAT_EQ(-1.2f, v3.x);
  RADIANT_EXPECT_FLOAT_EQ(-2.3f, v3.y);
  return true;
}

static bool length() {
  radiant_vec2_t v1 = {
      .x = 1.2f,
      .y = 2.3f,
  };
  RADIANT_EXPECT_FLOAT_EQ(2.594224f, radiant_vec2_length(v1));
  return true;
}

static bool length_squared() {
  radiant_vec2_t v1 = {
      .x = 1.2f,
      .y = 2.3f,
  };
  RADIANT_EXPECT_FLOAT_EQ(6.73f, radiant_vec2_length_squared(v1));
  return true;
}

static bool dot() {
  radiant_vec2_t v1 = {
      .x = 1.2f,
      .y = 2.3f,
  };
  RADIANT_EXPECT_FLOAT_EQ(6.73f, radiant_vec2_length_squared(v1));
  return true;
}

static bool normalize() {
  radiant_vec2_t v1 = {
      .x = 1.2f,
      .y = 2.3f,
  };
  radiant_vec2_t v3 = radiant_vec2_normalize(v1);

  RADIANT_EXPECT_FLOAT_EQ(0.462566f, v3.x);
  RADIANT_EXPECT_FLOAT_EQ(0.886585f, v3.y);
  return true;
}

static bool normalize_zero_length() {
  radiant_vec2_t v1 = {
      .x = 0.0f,
      .y = 0.0f,
  };
  radiant_vec2_t v3 = radiant_vec2_normalize(v1);

  RADIANT_EXPECT_FLOAT_EQ(0.0f, v3.x);
  RADIANT_EXPECT_FLOAT_EQ(0.0f, v3.y);
  return true;
}

int main() {
  radiant_suite_begin("vec2");
  RADIANT_TEST(add);
  RADIANT_TEST(sub);
  RADIANT_TEST(mul);
  RADIANT_TEST(div);
  RADIANT_TEST(div_by_negative);
  RADIANT_TEST(scale);
  RADIANT_TEST(negate);
  RADIANT_TEST(length);
  RADIANT_TEST(length_squared);
  RADIANT_TEST(dot);
  RADIANT_TEST(normalize);
  RADIANT_TEST(normalize_zero_length);
  return radiant_suite_end();
}
