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

#include <math.h>

#include "src/equal.h"

radiant_mat4x4_t radiant_mat4x4_identity(void) {
  return (radiant_mat4x4_t){
      // clang-format off
      .data = {
          1.f, 0.f, 0.f, 0.f,
          0.f, 1.f, 0.f, 0.f,
          0.f, 0.f, 1.f, 0.f,
          0.f, 0.f, 0.f, 1.f,
      },
      // clang-format on
  };
}

radiant_mat4x4_t radiant_mat4x4_look_at(radiant_vec3_t eye,
                                        radiant_vec3_t centre,
                                        radiant_vec3_t up) {
  radiant_vec3_t z = radiant_vec3_normalize(radiant_vec3_sub(eye, centre));
  radiant_vec3_t x = radiant_vec3_normalize(radiant_vec3_cross(up, z));
  radiant_vec3_t y = radiant_vec3_normalize(radiant_vec3_cross(z, x));

  return (radiant_mat4x4_t){
      // clang-format off
      .data = {
          x.x, x.y, x.z, -eye.x,
          y.x, y.y, y.z, -eye.y,
          -z.x, -z.y, -z.z, -eye.z,
          0.f, 0.f, 0.f, 1.f,
      },
      // clang-format on
  };
}

radiant_mat4x4_t radiant_mat4x4_perspective(float fov_y_radians,
                                            float aspect,
                                            float near,
                                            float far) {
  float tan_half_fov_y = tanf(fov_y_radians / 2);
  float dist = far - near;

  return (radiant_mat4x4_t){
      // clang-format off
      .data = {
          tan_half_fov_y / aspect, 0.f, 0.f, 0.f,
          0.f, tan_half_fov_y, 0.f, 0.f,
          0.f, 0.f, (far + near) / dist, (2.f * far * near) / dist,
          0.f, 0.f, -1.f, 0.f,
      },
      // clang-format on
  };
}

radiant_mat4x4_t radiant_mat4x4_rotate_x(float angle_radians) {
  return (radiant_mat4x4_t){
      // clang-format off
      .data = {
          1.f, 0.f, 0.f, 0.f,
          0.f, cosf(angle_radians), -sinf(angle_radians), 0.f,
          0.f, sinf(angle_radians), cosf(angle_radians), 0.f,
          0.f, 0.f, 0.f, 1.f,
      },
      // clang-format on
  };
}

radiant_mat4x4_t radiant_mat4x4_rotate_y(float angle_radians) {
  return (radiant_mat4x4_t){
      // clang-format off
      .data = {
          cosf(angle_radians), 0.f, sinf(angle_radians), 0.f,
          0.f, 1.f, 0.f, 0.f,
          -sinf(angle_radians), 0.f, cosf(angle_radians), 0.f,
          0.f, 0.f, 0.f, 1.f,
      },
      // clang-format on
  };
}

radiant_mat4x4_t radiant_mat4x4_rotate_z(float angle_radians) {
  return (radiant_mat4x4_t){
      // clang-format off
      .data = {
          cosf(angle_radians), -sinf(angle_radians), 0.f, 0.f,
          sinf(angle_radians), cosf(angle_radians), 0.f, 0.f,
          0.f, 0.f, 1.f, 0.f,
          0.f, 0.f, 0.f, 1.f,
      },
      // clang-format on
  };
}

radiant_mat4x4_t radiant_mat4x4_translate(radiant_vec3_t v) {
  radiant_mat4x4_t m = radiant_mat4x4_identity();
  m.data[3] = v.x;
  m.data[7] = v.y;
  m.data[11] = v.z;
  return m;
}

radiant_mat4x4_t radiant_mat4x4_scale(float x, float y, float z) {
  radiant_mat4x4_t m = {0};
  m.data[0] = x;
  m.data[5] = y;
  m.data[10] = z;
  m.data[15] = 1.0f;
  return m;
}

radiant_mat4x4_t radiant_mat4x4_transpose(radiant_mat4x4_t m) {
  // clang-format off
    return (radiant_mat4x4_t){
      .data = {
        m.data[0], m.data[4], m.data[8], m.data[12],
        m.data[1], m.data[5], m.data[9], m.data[13],
        m.data[2], m.data[6], m.data[10], m.data[14],
        m.data[3], m.data[7], m.data[11], m.data[15],
      }
    };
  // clang-format on
}

radiant_mat4x4_t radiant_mat4x4_mul_mat4x4(radiant_mat4x4_t m,
                                           radiant_mat4x4_t b) {
  radiant_mat4x4_t r = {0};
  for (uint32_t i = 0; i < 4; ++i) {
    uint32_t row = i * 4;
    for (uint32_t j = 0; j < 4; ++j) {
      r.data[row + j] = (m.data[row + 0] * b.data[j + 0]) +
                        (m.data[row + 1] * b.data[j + 4]) +
                        (m.data[row + 2] * b.data[j + 8]) +
                        (m.data[row + 3] * b.data[j + 12]);
    }
  }
  return r;
}

radiant_point3_t radiant_mat4x4_mul_point3(radiant_mat4x4_t m,
                                           radiant_point3_t p) {
  float x = m.data[0] * p.x + m.data[1] * p.y + m.data[2] * p.z + m.data[3];
  float y = m.data[4] * p.x + m.data[5] * p.y + m.data[6] * p.z + m.data[7];
  float z = m.data[8] * p.x + m.data[9] * p.y + m.data[10] * p.z + m.data[11];
  float w = m.data[12] * p.x + m.data[13] * p.y + m.data[14] * p.z + m.data[15];

  if (radiant_equal(w, 1.0f)) {
    return (radiant_point3_t){
        .x = x,
        .y = y,
        .z = z,
    };
  }

  float inv = 1.f / w;
  return (radiant_point3_t){
      .x = x * inv,
      .y = y * inv,
      .z = z * inv,
  };
}

radiant_vec3_t radiant_mat4x4_mul_vec3(radiant_mat4x4_t m, radiant_vec3_t v) {
  return (radiant_vec3_t){
      .x = m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z,
      .y = m.data[4] * v.x + m.data[5] * v.y + m.data[6] * v.z,
      .z = m.data[8] * v.x + m.data[9] * v.y + m.data[10] * v.z,
  };
}

float radiant_mat4x4_get(radiant_mat4x4_t m, uint32_t idx) {
  return m.data[idx];
}

void radiant_mat4x4_set(radiant_mat4x4_t* m, uint32_t idx, float val) {
  m->data[idx] = val;
}
