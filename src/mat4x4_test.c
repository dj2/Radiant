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
#include "src/constants.h"
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
  radiant_mat4x4_t m =
      radiant_mat4x4_look_at((radiant_point3_t){2.0f, 2.0f, -2.0f},
                             (radiant_point3_t){-1.0f, -1.0f, 1.0f},
                             (radiant_vec3_t){0.0f, 1.0f, 0.0f});

  RADIANT_EXPECT_FLOAT_EQ(-0.707107f, radiant_mat4x4_get(m, 0));
  RADIANT_EXPECT_FLOAT_EQ(-0.40824831f, radiant_mat4x4_get(m, 1));
  RADIANT_EXPECT_FLOAT_EQ(0.577350f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 4));
  RADIANT_EXPECT_FLOAT_EQ(0.81649661f, radiant_mat4x4_get(m, 5));
  RADIANT_EXPECT_FLOAT_EQ(0.577350f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(-0.707107f, radiant_mat4x4_get(m, 8));
  RADIANT_EXPECT_FLOAT_EQ(0.40824831f, radiant_mat4x4_get(m, 9));
  RADIANT_EXPECT_FLOAT_EQ(-0.577350f, radiant_mat4x4_get(m, 10));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 11));

  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 12));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 13));
  RADIANT_EXPECT_FLOAT_EQ(-3.464102f, radiant_mat4x4_get(m, 14));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 15));
  return true;
}

static bool perspective() {
  radiant_mat4x4_t m = radiant_mat4x4_perspective(45.0f * (RADIANT_PI / 180.f),
                                                  640.f / 480.f, 0.1f, 200.f);

  RADIANT_EXPECT_FLOAT_EQ(1.81066f, radiant_mat4x4_get(m, 0));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 1));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 4));
  RADIANT_EXPECT_FLOAT_EQ(2.414213f, radiant_mat4x4_get(m, 5));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 8));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 9));
  RADIANT_EXPECT_FLOAT_EQ(-1.001f, radiant_mat4x4_get(m, 10));
  RADIANT_EXPECT_FLOAT_EQ(-1.f, radiant_mat4x4_get(m, 11));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 12));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 13));
  RADIANT_EXPECT_FLOAT_EQ(-0.2001f, radiant_mat4x4_get(m, 14));
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
  RADIANT_EXPECT_FLOAT_EQ(0.85090351f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 8));
  RADIANT_EXPECT_FLOAT_EQ(-0.85090351f, radiant_mat4x4_get(m, 9));
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
  RADIANT_EXPECT_FLOAT_EQ(-0.85090351f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 4));
  RADIANT_EXPECT_FLOAT_EQ(1.0f, radiant_mat4x4_get(m, 5));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(0.85090351f, radiant_mat4x4_get(m, 8));
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
  RADIANT_EXPECT_FLOAT_EQ(0.85090351f, radiant_mat4x4_get(m, 1));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(0.0f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(-0.85090351f, radiant_mat4x4_get(m, 4));
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
  radiant_mat4x4_t m = {
      // clang-format off
       1.f,  2.f,  3.f,  4.f,
       5.f,  6.f,  7.f,  8.f,
       9.f, 10.f, 11.f, 12.f,
      13.f, 14.f, 15.f, 16.f,
      // clang-format on
  };

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
  // clang-format off
  // Matrix is column-major so in memory appears as:
  //  1 5  9 13
  //  2 6 10 14
  //  3 7 11 15
  //  4 8 12 16
  // clang-format on
  radiant_mat4x4_t a = {
      // clang-format off
      1.f, 5.f,  9.f, 13.f,
      2.f, 6.f, 10.f, 14.f,
      3.f, 7.f, 11.f, 15.f,
      4.f, 8.f, 12.f, 16.f,
      // clang-format on
  };

  radiant_mat4x4_t b = {
      // clang-format off
      1.f, 5.f,  9.f, 13.f,
      2.f, 6.f, 10.f, 14.f,
      3.f, 7.f, 11.f, 15.f,
      4.f, 8.f, 12.f, 16.f,
      // clang-format on
  };

  radiant_mat4x4_t t = radiant_mat4x4_mul(a, b);
  // Column-major so check results by column
  RADIANT_EXPECT_FLOAT_EQ((1 * 1) + (2 * 5) + (3 * 9) + (4 * 13),
                          radiant_mat4x4_get(t, 0));
  RADIANT_EXPECT_FLOAT_EQ((1 * 2) + (2 * 6) + (3 * 10) + (4 * 14),
                          radiant_mat4x4_get(t, 4));
  RADIANT_EXPECT_FLOAT_EQ((1 * 3) + (2 * 7) + (3 * 11) + (4 * 15),
                          radiant_mat4x4_get(t, 8));
  RADIANT_EXPECT_FLOAT_EQ((1 * 4) + (2 * 8) + (3 * 12) + (4 * 16),
                          radiant_mat4x4_get(t, 12));

  RADIANT_EXPECT_FLOAT_EQ((5 * 1) + (6 * 5) + (7 * 9) + (8 * 13),
                          radiant_mat4x4_get(t, 1));
  RADIANT_EXPECT_FLOAT_EQ((5 * 2) + (6 * 6) + (7 * 10) + (8 * 14),
                          radiant_mat4x4_get(t, 5));
  RADIANT_EXPECT_FLOAT_EQ((5 * 3) + (6 * 7) + (7 * 11) + (8 * 15),
                          radiant_mat4x4_get(t, 9));
  RADIANT_EXPECT_FLOAT_EQ((5 * 4) + (6 * 8) + (7 * 12) + (8 * 16),
                          radiant_mat4x4_get(t, 13));

  RADIANT_EXPECT_FLOAT_EQ((9 * 1) + (10 * 5) + (11 * 9) + (12 * 13),
                          radiant_mat4x4_get(t, 2));
  RADIANT_EXPECT_FLOAT_EQ((9 * 2) + (10 * 6) + (11 * 10) + (12 * 14),
                          radiant_mat4x4_get(t, 6));
  RADIANT_EXPECT_FLOAT_EQ((9 * 3) + (10 * 7) + (11 * 11) + (12 * 15),
                          radiant_mat4x4_get(t, 10));
  RADIANT_EXPECT_FLOAT_EQ((9 * 4) + (10 * 8) + (11 * 12) + (12 * 16),
                          radiant_mat4x4_get(t, 14));

  RADIANT_EXPECT_FLOAT_EQ((13 * 1) + (14 * 5) + (15 * 9) + (16 * 13),
                          radiant_mat4x4_get(t, 3));
  RADIANT_EXPECT_FLOAT_EQ((13 * 2) + (14 * 6) + (15 * 10) + (16 * 14),
                          radiant_mat4x4_get(t, 7));
  RADIANT_EXPECT_FLOAT_EQ((13 * 3) + (14 * 7) + (15 * 11) + (16 * 15),
                          radiant_mat4x4_get(t, 11));
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

  RADIANT_EXPECT_FLOAT_EQ(1.f, radiant_mat4x4_get(m, 0));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 1));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 2));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 3));

  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 4));
  RADIANT_EXPECT_FLOAT_EQ(1.f, radiant_mat4x4_get(m, 5));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 6));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 7));

  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 8));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 9));
  RADIANT_EXPECT_FLOAT_EQ(1.f, radiant_mat4x4_get(m, 10));
  RADIANT_EXPECT_FLOAT_EQ(0.f, radiant_mat4x4_get(m, 11));

  RADIANT_EXPECT_FLOAT_EQ(2.4f, radiant_mat4x4_get(m, 12));
  RADIANT_EXPECT_FLOAT_EQ(-3.4f, radiant_mat4x4_get(m, 13));
  RADIANT_EXPECT_FLOAT_EQ(10.9f, radiant_mat4x4_get(m, 14));
  RADIANT_EXPECT_FLOAT_EQ(1.f, radiant_mat4x4_get(m, 15));
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
