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

#include "src/point3.h"
#include "src/test.h"
#include "src/vec3.h"

static bool negate() {
  radiant_point3_t a = {
      .x = 2.3f,
      .y = -4.2f,
      .z = 5.9f,
  };
  radiant_point3_t c = radiant_point3_negate(a);

  RADIANT_EXPECT_FLOAT_EQ(-2.3f, c.x);
  RADIANT_EXPECT_FLOAT_EQ(4.2f, c.y);
  RADIANT_EXPECT_FLOAT_EQ(-5.9f, c.z);
  return true;
}

static bool sub() {
  radiant_point3_t a = {
      .x = 2.7f,
      .y = -4.2f,
      .z = 0.7f,
  };
  radiant_point3_t b = {
      .x = 5.0f,
      .y = -2.0f,
      .z = 3.7f,
  };

  radiant_vec3_t v = radiant_point3_sub(a, b);
  RADIANT_EXPECT_FLOAT_EQ(-2.3f, v.x);
  RADIANT_EXPECT_FLOAT_EQ(-2.2f, v.y);
  RADIANT_EXPECT_FLOAT_EQ(-3.0f, v.z);
  return true;
}

static bool add_vec3() {
  radiant_point3_t a = {
      .x = 2.3f,
      .y = -0.4f,
      .z = 2.7f,
  };
  radiant_vec3_t v = {
      .x = 1.7f,
      .y = 2.4f,
      .z = 5.0f,
  };

  radiant_point3_t b = radiant_point3_add(a, v);
  RADIANT_EXPECT_FLOAT_EQ(4.0f, b.x);
  RADIANT_EXPECT_FLOAT_EQ(2.0f, b.y);
  RADIANT_EXPECT_FLOAT_EQ(7.7f, b.z);
  return true;
}

static bool sub_vec3() {
  radiant_point3_t a = {
      .x = 2.7f,
      .y = -4.2f,
      .z = 0.7f,
  };
  radiant_vec3_t v = {
      .x = 5.0f,
      .y = -2.0f,
      .z = 3.7f,
  };
  radiant_point3_t b = radiant_point3_sub(a, v);
  RADIANT_EXPECT_FLOAT_EQ(-2.3f, b.x);
  RADIANT_EXPECT_FLOAT_EQ(-2.2f, b.y);
  RADIANT_EXPECT_FLOAT_EQ(-3.0f, b.z);
  return true;
}

static bool mul() {
  radiant_point3_t a = {
      .x = 2.7f,
      .y = -4.2f,
      .z = 0.7f,
  };
  radiant_point3_t b = radiant_point3_mul(a, 2.0f);
  RADIANT_EXPECT_FLOAT_EQ(5.4f, b.x);
  RADIANT_EXPECT_FLOAT_EQ(-8.4f, b.y);
  RADIANT_EXPECT_FLOAT_EQ(1.4f, b.z);
  return true;
}

static bool div() {
  radiant_point3_t a = {
      .x = 2.7f,
      .y = -4.2f,
      .z = 0.7f,
  };
  radiant_point3_t b = radiant_point3_div(a, 2.0f);
  RADIANT_EXPECT_FLOAT_EQ(1.35f, b.x);
  RADIANT_EXPECT_FLOAT_EQ(-2.1f, b.y);
  RADIANT_EXPECT_FLOAT_EQ(0.35f, b.z);
  return true;
}

static bool lerp() {
  radiant_point3_t a = {
      .x = 1.2f,
      .y = 2.4f,
      .z = -2.4f,
  };
  radiant_point3_t b = {
      .x = 0.4f,
      .y = -4.5f,
      .z = 22.9f,
  };

  radiant_point3_t c = radiant_point3_lerp(a, b, 0.0f);
  RADIANT_EXPECT_FLOAT_EQ(1.2f, c.x);
  RADIANT_EXPECT_FLOAT_EQ(2.4f, c.y);
  RADIANT_EXPECT_FLOAT_EQ(-2.4f, c.z);

  c = radiant_point3_lerp(a, b, 1.0);
  RADIANT_EXPECT_FLOAT_EQ(0.4f, c.x);
  RADIANT_EXPECT_FLOAT_EQ(-4.5f, c.y);
  RADIANT_EXPECT_FLOAT_EQ(22.9f, c.z);

  c = radiant_point3_lerp(a, b, 0.5);
  RADIANT_EXPECT_FLOAT_EQ(0.8f, c.x);
  RADIANT_EXPECT_FLOAT_EQ(-1.05f, c.y);
  RADIANT_EXPECT_FLOAT_EQ(10.25f, c.z);
  return true;
}

int main() {
  radiant_suite_begin("point3");
  RADIANT_TEST(negate);
  RADIANT_TEST(sub);
  RADIANT_TEST(sub_vec3);
  RADIANT_TEST(add_vec3);
  RADIANT_TEST(mul);
  RADIANT_TEST(div);
  RADIANT_TEST(lerp);
  return radiant_suite_end();
}
