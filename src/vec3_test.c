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

#include <math.h>

#include "src/test.h"
#include "src/vec3.h"

static bool add() {
  radiant_vec3_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
  };
  radiant_vec3_t b = {
      .x = 1.2f,
      .y = 2.4f,
      .z = 3.9f,
  };
  radiant_vec3_t c = radiant_vec3_add(a, b);

  RADIANT_EXPECT_FLOAT_EQ(3.5f, c.x);
  RADIANT_EXPECT_FLOAT_EQ(-1.8f, c.y);
  RADIANT_EXPECT_FLOAT_EQ(9.8f, c.z);
  return true;
}

static bool sub() {
  radiant_vec3_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
  };
  radiant_vec3_t b = {
      .x = 1.2f,
      .y = 2.4f,
      .z = 3.9f,
  };
  radiant_vec3_t c = radiant_vec3_sub(a, b);

  RADIANT_EXPECT_FLOAT_EQ(1.1f, c.x);
  RADIANT_EXPECT_FLOAT_EQ(-6.6f, c.y);
  RADIANT_EXPECT_FLOAT_EQ(2.0f, c.z);
  return true;
}

static bool mul() {
  radiant_vec3_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
  };
  radiant_vec3_t b = {
      .x = 1.2f,
      .y = 2.4f,
      .z = 3.9f,
  };
  radiant_vec3_t c = radiant_vec3_mul(a, b);

  RADIANT_EXPECT_FLOAT_EQ(2.76f, c.x);
  RADIANT_EXPECT_FLOAT_EQ(-10.08f, c.y);
  RADIANT_EXPECT_FLOAT_EQ(23.01f, c.z);
  return true;
}

static bool div() {
  radiant_vec3_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
  };
  radiant_vec3_t b = radiant_vec3_div(a, 2.0f);

  RADIANT_EXPECT_FLOAT_EQ(1.15f, b.x);
  RADIANT_EXPECT_FLOAT_EQ(-2.1f, b.y);
  RADIANT_EXPECT_FLOAT_EQ(2.95f, b.z);
  return true;
}

static bool scale() {
  radiant_vec3_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
  };
  radiant_vec3_t b = radiant_vec3_mul(a, 2.0f);

  RADIANT_EXPECT_FLOAT_EQ(4.6f, b.x);
  RADIANT_EXPECT_FLOAT_EQ(-8.4f, b.y);
  RADIANT_EXPECT_FLOAT_EQ(11.8f, b.z);
  return true;
}

static bool negate() {
  radiant_vec3_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
  };
  radiant_vec3_t b = radiant_vec3_negate(a);

  RADIANT_EXPECT_FLOAT_EQ(-2.3f, b.x);
  RADIANT_EXPECT_FLOAT_EQ(4.2f, b.y);
  RADIANT_EXPECT_FLOAT_EQ(-5.9f, b.z);
  return true;
}

static bool length() {
  radiant_vec3_t a = {
      .x = 2.3f,
      .y = -4.8f,
      .z = 2.8f,
  };

  float len = sqrtf((2.3f * 2.3f) + (-4.8f * -4.8f) + (2.8f * 2.8f));
  RADIANT_EXPECT_FLOAT_EQ(len, radiant_vec3_length(a));
  return true;
}

static bool length_squared() {
  radiant_vec3_t a = {
      .x = 2.3f,
      .y = -4.8f,
      .z = 2.8f,
  };

  float len = (2.3f * 2.3f) + (-4.8f * -4.8f) + (2.8f * 2.8f);
  RADIANT_EXPECT_FLOAT_EQ(len, radiant_vec3_length_squared(a));
  return true;
}

static bool dot() {
  radiant_vec3_t a = {
      .x = 1.f,
      .y = 2.f,
      .z = 3.f,
  };
  radiant_vec3_t b = {
      .x = 2.f,
      .y = 3.f,
      .z = 4.f,
  };

  RADIANT_EXPECT_FLOAT_EQ(20.0f, radiant_vec3_dot(a, b));
  return true;
}

static bool cross() {
  radiant_vec3_t a = {
      .x = 1.0f,
      .y = 2.0f,
      .z = 3.0f,
  };
  radiant_vec3_t b = {
      .x = 2.0f,
      .y = 3.0f,
      .z = 4.0f,
  };

  radiant_vec3_t c = radiant_vec3_cross(a, b);
  RADIANT_EXPECT_FLOAT_EQ(-1.0f, c.x);
  RADIANT_EXPECT_FLOAT_EQ(2.0f, c.y);
  RADIANT_EXPECT_FLOAT_EQ(-1.0f, c.z);

  radiant_vec3_t d = radiant_vec3_cross(b, a);
  RADIANT_EXPECT_FLOAT_EQ(1.0f, d.x);
  RADIANT_EXPECT_FLOAT_EQ(-2.0f, d.y);
  RADIANT_EXPECT_FLOAT_EQ(1.0f, d.z);
  return true;
}

static bool normalize() {
  radiant_vec3_t a = {
      .x = 2.3f,
      .y = -4.8f,
      .z = 2.8f,
  };
  radiant_vec3_t b = radiant_vec3_normalize(a);

  float len = radiant_vec3_length(a);
  RADIANT_EXPECT_FLOAT_EQ(2.3f / len, b.x);
  RADIANT_EXPECT_FLOAT_EQ(-4.8f / len, b.y);
  RADIANT_EXPECT_FLOAT_EQ(2.8f / len, b.z);
  return true;
}

static bool normalize_zero() {
  radiant_vec3_t a = {
      .x = 0.0f,
      .y = 0.0f,
      .z = 0.0f,
  };
  radiant_vec3_t b = radiant_vec3_normalize(a);

  RADIANT_EXPECT_FLOAT_EQ(0.0f, b.x);
  RADIANT_EXPECT_FLOAT_EQ(0.0f, b.y);
  RADIANT_EXPECT_FLOAT_EQ(0.0f, b.z);
  return true;
}

int main() {
  radiant_suite_begin("vec3");
  RADIANT_TEST(add);
  RADIANT_TEST(sub);
  RADIANT_TEST(mul);
  RADIANT_TEST(div);
  RADIANT_TEST(scale);
  RADIANT_TEST(negate);
  RADIANT_TEST(length);
  RADIANT_TEST(length_squared);
  RADIANT_TEST(dot);
  RADIANT_TEST(cross);
  RADIANT_TEST(normalize);
  RADIANT_TEST(normalize_zero);
  return radiant_suite_end();
}
