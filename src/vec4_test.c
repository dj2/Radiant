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

#include "src/vec4.h"
#include "src/test.h"

#include <math.h>

static bool add() {
  radiant_vec4_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
      .w = 1.3f,
  };
  radiant_vec4_t b = {
      .x = 1.2f,
      .y = 2.4f,
      .z = 3.9f,
      .w = 2.4f,
  };
  radiant_vec4_t c = radiant_vec4_add(a, b);

  RADIANT_EXPECT_FLOAT_EQ(3.5f, c.x);
  RADIANT_EXPECT_FLOAT_EQ(-1.8f, c.y);
  RADIANT_EXPECT_FLOAT_EQ(9.8f, c.z);
  RADIANT_EXPECT_FLOAT_EQ(3.7f, c.w);
  return true;
}

static bool sub() {
  radiant_vec4_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
      .w = 1.3f,
  };
  radiant_vec4_t b = {
      .x = 1.2f,
      .y = 2.4f,
      .z = 3.9f,
      .w = 2.4f,
  };
  radiant_vec4_t c = radiant_vec4_sub(a, b);

  RADIANT_EXPECT_FLOAT_EQ(1.1f, c.x);
  RADIANT_EXPECT_FLOAT_EQ(-6.6f, c.y);
  RADIANT_EXPECT_FLOAT_EQ(2.0f, c.z);
  RADIANT_EXPECT_FLOAT_EQ(-1.1f, c.w);
  return true;
}

static bool mul() {
  radiant_vec4_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
      .w = 1.3f,
  };
  radiant_vec4_t b = {
      .x = 1.2f,
      .y = 2.4f,
      .z = 3.9f,
      .w = 2.4f,
  };
  radiant_vec4_t c = radiant_vec4_mul(a, b);

  RADIANT_EXPECT_FLOAT_EQ(2.76f, c.x);
  RADIANT_EXPECT_FLOAT_EQ(-10.08f, c.y);
  RADIANT_EXPECT_FLOAT_EQ(23.01f, c.z);
  RADIANT_EXPECT_FLOAT_EQ(3.12f, c.w);
  return true;
}

static bool div() {
  radiant_vec4_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
      .w = 1.3f,
  };
  radiant_vec4_t b = radiant_vec4_div(a, 2.0f);

  RADIANT_EXPECT_FLOAT_EQ(1.15f, b.x);
  RADIANT_EXPECT_FLOAT_EQ(-2.1f, b.y);
  RADIANT_EXPECT_FLOAT_EQ(2.95f, b.z);
  RADIANT_EXPECT_FLOAT_EQ(0.65f, b.w);
  return true;
}

static bool scale() {
  radiant_vec4_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
      .w = 1.3f,
  };
  radiant_vec4_t b = radiant_vec4_mul(a, 2.0f);

  RADIANT_EXPECT_FLOAT_EQ(4.6f, b.x);
  RADIANT_EXPECT_FLOAT_EQ(-8.4f, b.y);
  RADIANT_EXPECT_FLOAT_EQ(11.8f, b.z);
  RADIANT_EXPECT_FLOAT_EQ(2.6f, b.w);
  return true;
}

static bool negate() {
  radiant_vec4_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
      .w = 1.3f,
  };
  radiant_vec4_t b = radiant_vec4_negate(a);

  RADIANT_EXPECT_FLOAT_EQ(-2.3f, b.x);
  RADIANT_EXPECT_FLOAT_EQ(4.2f, b.y);
  RADIANT_EXPECT_FLOAT_EQ(-5.9f, b.z);
  RADIANT_EXPECT_FLOAT_EQ(-1.3f, b.w);
  return true;
}

static bool length() {
  radiant_vec4_t a = {
      .x = 2.3f,
      .y = -4.8f,
      .z = 2.8f,
      .w = 1.3f,
  };

  float len =
      sqrtf((2.3f * 2.3f) + (-4.8f * -4.8f) + (2.8f * 2.8f) + (1.3f * 1.3f));
  RADIANT_EXPECT_FLOAT_EQ(len, radiant_vec4_length(a));
  return true;
}

static bool length_squared() {
  radiant_vec4_t a = {
      .x = 2.3f,
      .y = -4.8f,
      .z = 2.8f,
      .w = 1.3f,
  };

  float len = (2.3f * 2.3f) + (-4.8f * -4.8f) + (2.8f * 2.8f) + (1.3f * 1.3f);
  RADIANT_EXPECT_FLOAT_EQ(len, radiant_vec4_length_squared(a));
  return true;
}

static bool dot() {
  radiant_vec4_t a = {
      .x = 1.f,
      .y = 2.f,
      .z = 3.f,
      .w = 4.f,
  };
  radiant_vec4_t b = {
      .x = 2.f,
      .y = 3.f,
      .z = 4.f,
      .w = 5.f,
  };

  RADIANT_EXPECT_FLOAT_EQ(40.0f, radiant_vec4_dot(a, b));
  return true;
}

static bool normalize() {
  radiant_vec4_t a = {
      .x = 2.3f,
      .y = -4.8f,
      .z = 2.8f,
  };
  radiant_vec4_t b = radiant_vec4_normalize(a);

  float len = radiant_vec4_length(a);
  RADIANT_EXPECT_FLOAT_EQ(2.3f / len, b.x);
  RADIANT_EXPECT_FLOAT_EQ(-4.8f / len, b.y);
  RADIANT_EXPECT_FLOAT_EQ(2.8f / len, b.z);
  return true;
}

static bool normalize_zero() {
  radiant_vec4_t a = {
      .x = 0.f,
      .y = 0.f,
      .z = 0.f,
      .w = 0.f,
  };
  radiant_vec4_t b = radiant_vec4_normalize(a);

  RADIANT_EXPECT_FLOAT_EQ(0.f, b.x);
  RADIANT_EXPECT_FLOAT_EQ(0.f, b.y);
  RADIANT_EXPECT_FLOAT_EQ(0.f, b.z);
  return true;
}

int main() {
  radiant_suite_begin("vec4");
  RADIANT_TEST(add);
  RADIANT_TEST(sub);
  RADIANT_TEST(mul);
  RADIANT_TEST(div);
  RADIANT_TEST(scale);
  RADIANT_TEST(negate);
  RADIANT_TEST(length);
  RADIANT_TEST(length_squared);
  RADIANT_TEST(dot);
  RADIANT_TEST(normalize);
  RADIANT_TEST(normalize_zero);
  return radiant_suite_end();
}
