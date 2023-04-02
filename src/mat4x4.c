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

  radiant_vec3_t eye_pos = {
      -(x.x * eye.x + x.y * eye.y + x.z * eye.z),
      -(y.x * eye.x + y.y * eye.y + y.z * eye.z),
      -(z.x * eye.x + z.y * eye.y + z.z * eye.z),
  };

  return (radiant_mat4x4_t){
      // clang-format off
      .data = {
               x.x,       y.x,       z.x, 0.f,
               x.y,       y.y,       z.y, 0.f,
               x.z,       y.z,       z.z, 0.f,
         eye_pos.x, eye_pos.y, eye_pos.z, 1.f,
      },
      // clang-format on
  };
}

radiant_mat4x4_t radiant_mat4x4_perspective(float fov_y_radians,
                                            float aspect,
                                            float near,
                                            float far) {
  float tan_half_fov_y = 1.f / tanf(fov_y_radians / 2);
  float nf = 1.f / (near - far);

  return (radiant_mat4x4_t){
      // clang-format off
      .data = {
          tan_half_fov_y / aspect, 0.f, 0.f, 0.f,
          0.f, tan_half_fov_y, 0.f, 0.f,
          0.f, 0.f, (far + near) * nf, -1,
          0.f, 0.f, 2 * far * near * nf, 0.f,
      },
      // clang-format on
  };
}

radiant_mat4x4_t radiant_mat4x4_rotate_x(float angle_radians) {
  return (radiant_mat4x4_t){
      // clang-format off
      .data = {
          1.f, 0.f, 0.f, 0.f,
          0.f, cosf(angle_radians), sinf(angle_radians), 0.f,
          0.f, -sinf(angle_radians), cosf(angle_radians), 0.f,
          0.f, 0.f, 0.f, 1.f,
      },
      // clang-format on
  };
}

radiant_mat4x4_t radiant_mat4x4_rotate_y(float angle_radians) {
  return (radiant_mat4x4_t){
      // clang-format off
      .data = {
          cosf(angle_radians), 0.f, -sinf(angle_radians), 0.f,
          0.f, 1.f, 0.f, 0.f,
          sinf(angle_radians), 0.f, cosf(angle_radians), 0.f,
          0.f, 0.f, 0.f, 1.f,
      },
      // clang-format on
  };
}

radiant_mat4x4_t radiant_mat4x4_rotate_z(float angle_radians) {
  return (radiant_mat4x4_t){
      // clang-format off
      .data = {
          cosf(angle_radians), sinf(angle_radians), 0.f, 0.f,
          -sinf(angle_radians), cosf(angle_radians), 0.f, 0.f,
          0.f, 0.f, 1.f, 0.f,
          0.f, 0.f, 0.f, 1.f,
      },
      // clang-format on
  };
}

radiant_mat4x4_t radiant_mat4x4_translate(radiant_vec3_t v) {
  radiant_mat4x4_t m = radiant_mat4x4_identity();
  m.data[12] = v.x;
  m.data[13] = v.y;
  m.data[14] = v.z;
  return m;
}

radiant_mat4x4_t radiant_mat4x4_scale(float x, float y, float z) {
  radiant_mat4x4_t m = radiant_mat4x4_identity();
  m.data[0] = x;
  m.data[5] = y;
  m.data[10] = z;
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
  radiant_mat4x4_t r = radiant_mat4x4_identity();
  for (uint32_t i = 0; i < 4; ++i) {
    for (uint32_t j = 0; j < 4; ++j) {
      uint32_t row = j * 4;
      r.data[i + (j * 4)] = (m.data[i + 0] * b.data[row + 0]) +
                            (m.data[i + 4] * b.data[row + 1]) +
                            (m.data[i + 8] * b.data[row + 2]) +
                            (m.data[i + 12] * b.data[row + 3]);
    }
  }
  return r;
}

radiant_point3_t radiant_mat4x4_mul_point3(radiant_mat4x4_t m,
                                           radiant_point3_t p) {
  float x = m.data[0] * p.x + m.data[4] * p.y + m.data[8] * p.z + m.data[12];
  float y = m.data[1] * p.x + m.data[5] * p.y + m.data[9] * p.z + m.data[13];
  float z = m.data[2] * p.x + m.data[6] * p.y + m.data[10] * p.z + m.data[14];
  float w = m.data[3] * p.x + m.data[7] * p.y + m.data[11] * p.z + m.data[15];

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
      .x = m.data[0] * v.x + m.data[4] * v.y + m.data[8] * v.z,
      .y = m.data[1] * v.x + m.data[5] * v.y + m.data[9] * v.z,
      .z = m.data[2] * v.x + m.data[6] * v.y + m.data[10] * v.z,
  };
}

float radiant_mat4x4_get(radiant_mat4x4_t m, uint32_t idx) {
  return m.data[idx];
}

void radiant_mat4x4_set(radiant_mat4x4_t* m, uint32_t idx, float val) {
  m->data[idx] = val;
}
