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

#include "src/mat4x4.h"
#include "src/test.h"

static bool identity() {
  radiant_mat4x4_t m = radiant_mat4x4_identity();

  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 0));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 1));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 4));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 5));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 8));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 9));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 10));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 11));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 12));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 13));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 14));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 15));
  return true;
}

static bool look_at() {
  radiant_mat4x4_t m = radiant_mat4x4_look_at(
      (radiant_vec3_t){2.0f, 2.0f, -2.0f}, (radiant_vec3_t){-1.0f, -1.0f, 1.0f},
      (radiant_vec3_t){0.0f, 1.0f, 0.0f});

  RADIANT_EXPECT_FLOAT_EQ(-0.707107f, radiant_mat4x4_get(m, 0));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 1));
  RADIANT_EXPECT_FLOAT_EQ(-0.707107f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(-2.000000f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(-0.40824831f, radiant_mat4x4_get(m, 4));
  RADIANT_EXPECT_FLOAT_EQ(0.81649661f, radiant_mat4x4_get(m, 5));
  RADIANT_EXPECT_FLOAT_EQ(0.40824831f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(-2.000000f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(-0.577350f, radiant_mat4x4_get(m, 8));
  RADIANT_EXPECT_FLOAT_EQ(-0.577350f, radiant_mat4x4_get(m, 9));
  RADIANT_EXPECT_FLOAT_EQ(0.577350f, radiant_mat4x4_get(m, 10));
  RADIANT_EXPECT_FLOAT_EQ(2.000000f, radiant_mat4x4_get(m, 11));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 12));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 13));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 14));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 15));
  return true;
}

static bool perspective() {
  radiant_mat4x4_t m = radiant_mat4x4_perspective(45.0f, 0.75f, 0.1f, 1.5f);

  RADIANT_EXPECT_FLOAT_EQ(0.74380231f, radiant_mat4x4_get(m, 0));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 1));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 4));
  RADIANT_EXPECT_FLOAT_EQ(0.55785173f, radiant_mat4x4_get(m, 5));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 8));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 9));
  RADIANT_EXPECT_FLOAT_EQ(1.142857f, radiant_mat4x4_get(m, 10));
  RADIANT_EXPECT_FLOAT_EQ(0.21428572f, radiant_mat4x4_get(m, 11));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 12));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 13));
  RADIANT_EXPECT_FLOAT_EQ(-1.0f, radiant_mat4x4_get(m, 14));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 15));
  return true;
}

static bool rotate_x() {
  radiant_mat4x4_t m = radiant_mat4x4_rotate_x(45.0f);

  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 0));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 1));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 4));
  RADIANT_EXPECT_FLOAT_EQ(0.52532196f, radiant_mat4x4_get(m, 5));
  RADIANT_EXPECT_FLOAT_EQ(-0.85090351f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 8));
  RADIANT_EXPECT_FLOAT_EQ(0.85090351f, radiant_mat4x4_get(m, 9));
  RADIANT_EXPECT_FLOAT_EQ(0.52532196f, radiant_mat4x4_get(m, 10));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 11));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 12));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 13));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 14));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 15));
  return true;
}

static bool rotate_y() {
  radiant_mat4x4_t m = radiant_mat4x4_rotate_y(45.0f);

  RADIANT_EXPECT_FLOAT_EQ(0.52532196f, radiant_mat4x4_get(m, 0));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 1));
  RADIANT_EXPECT_FLOAT_EQ(0.85090351f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 4));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 5));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(-0.85090351f, radiant_mat4x4_get(m, 8));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 9));
  RADIANT_EXPECT_FLOAT_EQ(0.52532196f, radiant_mat4x4_get(m, 10));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 11));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 12));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 13));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 14));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 15));
  return true;
}

static bool rotate_z() {
  radiant_mat4x4_t m = radiant_mat4x4_rotate_z(45.0f);

  RADIANT_EXPECT_FLOAT_EQ(0.52532196f, radiant_mat4x4_get(m, 0));
  RADIANT_EXPECT_FLOAT_EQ(-0.85090351f, radiant_mat4x4_get(m, 1));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(0.85090351f, radiant_mat4x4_get(m, 4));
  RADIANT_EXPECT_FLOAT_EQ(0.52532196f, radiant_mat4x4_get(m, 5));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 8));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 9));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 10));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 11));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 12));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 13));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 14));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 15));
  return true;
}

static bool transpose() {
  radiant_mat4x4_t m = {0};
  radiant_mat4x4_set(&m, 0, 1.f);
  radiant_mat4x4_set(&m, 1, 2.f);
  radiant_mat4x4_set(&m, 2, 3.f);
  radiant_mat4x4_set(&m, 3, 4.f);
  radiant_mat4x4_set(&m, 4, 5.f);
  radiant_mat4x4_set(&m, 5, 6.f);
  radiant_mat4x4_set(&m, 6, 7.f);
  radiant_mat4x4_set(&m, 7, 8.f);
  radiant_mat4x4_set(&m, 8, 9.f);
  radiant_mat4x4_set(&m, 9, 10.f);
  radiant_mat4x4_set(&m, 10, 11.f);
  radiant_mat4x4_set(&m, 11, 12.f);
  radiant_mat4x4_set(&m, 12, 13.f);
  radiant_mat4x4_set(&m, 13, 14.f);
  radiant_mat4x4_set(&m, 14, 15.f);
  radiant_mat4x4_set(&m, 15, 16.f);

  radiant_mat4x4_t t = radiant_mat4x4_transpose(m);
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(t, 0));
  RADIANT_EXPECT_FLOAT_EQ(5.0f, radiant_mat4x4_get(t, 1));
  RADIANT_EXPECT_FLOAT_EQ(9.0f, radiant_mat4x4_get(t, 2));
  RADIANT_EXPECT_FLOAT_EQ(13.0f, radiant_mat4x4_get(t, 3));
  RADIANT_EXPECT_FLOAT_EQ(2.0f, radiant_mat4x4_get(t, 4));
  RADIANT_EXPECT_FLOAT_EQ(6.0f, radiant_mat4x4_get(t, 5));
  RADIANT_EXPECT_FLOAT_EQ(10.0f, radiant_mat4x4_get(t, 6));
  RADIANT_EXPECT_FLOAT_EQ(14.0f, radiant_mat4x4_get(t, 7));
  RADIANT_EXPECT_FLOAT_EQ(3.0f, radiant_mat4x4_get(t, 8));
  RADIANT_EXPECT_FLOAT_EQ(7.0f, radiant_mat4x4_get(t, 9));
  RADIANT_EXPECT_FLOAT_EQ(11.0f, radiant_mat4x4_get(t, 10));
  RADIANT_EXPECT_FLOAT_EQ(15.0f, radiant_mat4x4_get(t, 11));
  RADIANT_EXPECT_FLOAT_EQ(4.0f, radiant_mat4x4_get(t, 12));
  RADIANT_EXPECT_FLOAT_EQ(8.0f, radiant_mat4x4_get(t, 13));
  RADIANT_EXPECT_FLOAT_EQ(12.0f, radiant_mat4x4_get(t, 14));
  RADIANT_EXPECT_FLOAT_EQ(16.0f, radiant_mat4x4_get(t, 15));
  return true;
}

static bool mul() {
  radiant_mat4x4_t a = {0};
  radiant_mat4x4_set(&a, 0, 1.f);
  radiant_mat4x4_set(&a, 1, 2.f);
  radiant_mat4x4_set(&a, 2, 3.f);
  radiant_mat4x4_set(&a, 3, 4.f);
  radiant_mat4x4_set(&a, 4, 5.f);
  radiant_mat4x4_set(&a, 5, 6.f);
  radiant_mat4x4_set(&a, 6, 7.f);
  radiant_mat4x4_set(&a, 7, 8.f);
  radiant_mat4x4_set(&a, 8, 9.f);
  radiant_mat4x4_set(&a, 9, 10.f);
  radiant_mat4x4_set(&a, 10, 11.f);
  radiant_mat4x4_set(&a, 11, 12.f);
  radiant_mat4x4_set(&a, 12, 13.f);
  radiant_mat4x4_set(&a, 13, 14.f);
  radiant_mat4x4_set(&a, 14, 15.f);
  radiant_mat4x4_set(&a, 15, 16.f);

  radiant_mat4x4_t b = {0};
  radiant_mat4x4_set(&b, 0, 1.f);
  radiant_mat4x4_set(&b, 1, 2.f);
  radiant_mat4x4_set(&b, 2, 3.f);
  radiant_mat4x4_set(&b, 3, 4.f);
  radiant_mat4x4_set(&b, 4, 5.f);
  radiant_mat4x4_set(&b, 5, 6.f);
  radiant_mat4x4_set(&b, 6, 7.f);
  radiant_mat4x4_set(&b, 7, 8.f);
  radiant_mat4x4_set(&b, 8, 9.f);
  radiant_mat4x4_set(&b, 9, 10.f);
  radiant_mat4x4_set(&b, 10, 11.f);
  radiant_mat4x4_set(&b, 11, 12.f);
  radiant_mat4x4_set(&b, 12, 13.f);
  radiant_mat4x4_set(&b, 13, 14.f);
  radiant_mat4x4_set(&b, 14, 15.f);
  radiant_mat4x4_set(&b, 15, 16.f);

  radiant_mat4x4_t t = radiant_mat4x4_mul(a, b);
  RADIANT_EXPECT_FLOAT_EQ((1 * 1) + (2 * 5) + (3 * 9) + (4 * 13),
                          radiant_mat4x4_get(t, 0));
  RADIANT_EXPECT_FLOAT_EQ((1 * 2) + (2 * 6) + (3 * 10) + (4 * 14),
                          radiant_mat4x4_get(t, 1));
  RADIANT_EXPECT_FLOAT_EQ((1 * 3) + (2 * 7) + (3 * 11) + (4 * 15),
                          radiant_mat4x4_get(t, 2));
  RADIANT_EXPECT_FLOAT_EQ((1 * 4) + (2 * 8) + (3 * 12) + (4 * 16),
                          radiant_mat4x4_get(t, 3));

  RADIANT_EXPECT_FLOAT_EQ((5 * 1) + (6 * 5) + (7 * 9) + (8 * 13),
                          radiant_mat4x4_get(t, 4));
  RADIANT_EXPECT_FLOAT_EQ((5 * 2) + (6 * 6) + (7 * 10) + (8 * 14),
                          radiant_mat4x4_get(t, 5));
  RADIANT_EXPECT_FLOAT_EQ((5 * 3) + (6 * 7) + (7 * 11) + (8 * 15),
                          radiant_mat4x4_get(t, 6));
  RADIANT_EXPECT_FLOAT_EQ((5 * 4) + (6 * 8) + (7 * 12) + (8 * 16),
                          radiant_mat4x4_get(t, 7));

  RADIANT_EXPECT_FLOAT_EQ((9 * 1) + (10 * 5) + (11 * 9) + (12 * 13),
                          radiant_mat4x4_get(t, 8));
  RADIANT_EXPECT_FLOAT_EQ((9 * 2) + (10 * 6) + (11 * 10) + (12 * 14),
                          radiant_mat4x4_get(t, 9));
  RADIANT_EXPECT_FLOAT_EQ((9 * 3) + (10 * 7) + (11 * 11) + (12 * 15),
                          radiant_mat4x4_get(t, 10));
  RADIANT_EXPECT_FLOAT_EQ((9 * 4) + (10 * 8) + (11 * 12) + (12 * 16),
                          radiant_mat4x4_get(t, 11));

  RADIANT_EXPECT_FLOAT_EQ((13 * 1) + (14 * 5) + (15 * 9) + (16 * 13),
                          radiant_mat4x4_get(t, 12));
  RADIANT_EXPECT_FLOAT_EQ((13 * 2) + (14 * 6) + (15 * 10) + (16 * 14),
                          radiant_mat4x4_get(t, 13));
  RADIANT_EXPECT_FLOAT_EQ((13 * 3) + (14 * 7) + (15 * 11) + (16 * 15),
                          radiant_mat4x4_get(t, 14));
  RADIANT_EXPECT_FLOAT_EQ((13 * 4) + (14 * 8) + (15 * 12) + (16 * 16),
                          radiant_mat4x4_get(t, 15));
  return true;
}

static bool mul_point3() {
  radiant_mat4x4_t a = radiant_mat4x4_scale(2.f, 3.f, 4.f);
  radiant_point3_t b = (radiant_point3_t){2.f, 3.f, 4.f};

  radiant_point3_t t = radiant_mat4x4_mul(a, b);
  RADIANT_EXPECT_FLOAT_EQ(4.f, t.x);
  RADIANT_EXPECT_FLOAT_EQ(9.f, t.y);
  RADIANT_EXPECT_FLOAT_EQ(16.f, t.z);
  return true;
}

static bool mul_vec3() {
  radiant_mat4x4_t a = radiant_mat4x4_scale(2.f, 3.f, 4.f);
  radiant_vec3_t b = (radiant_vec3_t){2.f, 3.f, 4.f};

  radiant_vec3_t t = radiant_mat4x4_mul(a, b);
  RADIANT_EXPECT_FLOAT_EQ(4.f, t.x);
  RADIANT_EXPECT_FLOAT_EQ(9.f, t.y);
  RADIANT_EXPECT_FLOAT_EQ(16.f, t.z);
  return true;
}

static bool translate() {
  radiant_vec3_t a = (radiant_vec3_t){2.4f, -3.4f, 10.9f};
  radiant_mat4x4_t m = radiant_mat4x4_translate(a);

  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 0));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 1));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(2.4f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 4));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 5));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(-3.4f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 8));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 9));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 10));
  RADIANT_EXPECT_FLOAT_EQ(10.9f, radiant_mat4x4_get(m, 11));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 12));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 13));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 14));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 15));
  return true;
}

static bool scale() {
  radiant_mat4x4_t m = radiant_mat4x4_scale(2.0f, -3.4f, 4.5f);

  RADIANT_EXPECT_FLOAT_EQ(2.f, radiant_mat4x4_get(m, 0));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 1));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 4));
  RADIANT_EXPECT_FLOAT_EQ(-3.4f, radiant_mat4x4_get(m, 5));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 8));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 9));
  RADIANT_EXPECT_FLOAT_EQ(4.5f, radiant_mat4x4_get(m, 10));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 11));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 12));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 13));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 14));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 15));
  return true;
}

int main() {
  radiant_suite_begin("mat4x4");
  RADIANT_TEST(identity);
  RADIANT_TEST(look_at);
  RADIANT_TEST(perspective);
  RADIANT_TEST(rotate_x);
  RADIANT_TEST(rotate_y);
  RADIANT_TEST(rotate_z);
  RADIANT_TEST(transpose);
  RADIANT_TEST(mul);
  RADIANT_TEST(mul_point3);
  RADIANT_TEST(mul_vec3);
  RADIANT_TEST(translate);
  RADIANT_TEST(scale);
  return radiant_suite_end();
}
