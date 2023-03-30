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

#pragma once

#include <stdint.h>

#include "src/point3.h"
#include "src/vec3.h"

/// A 4x4 matrix in row-major order.
typedef struct radiant_mat4x4_t {
  /// Matrix data.
  ///
  /// | a b c d |
  /// | e f g h |
  /// | i j k l |
  /// | m n o p |
  ///
  /// Stored as:
  /// [a b c d e f g h i j k l m n o p]
  ///
  float data[16];
} radiant_mat4x4_t;

/// Returns the identity matrix.
radiant_mat4x4_t radiant_mat4x4_identity(void);

/// Returns the view matrix for given |eye| looking at |centre| with |up|.
radiant_mat4x4_t radiant_mat4x4_look_at(radiant_vec3_t eye,
                                        radiant_vec3_t centre,
                                        radiant_vec3_t up);

/// Returns the perspective matrix with a field of view |fov_y_radians|,
/// |aspect| ratio and a given |near| and |far| planes.
radiant_mat4x4_t radiant_mat4x4_perspective(float fov_y_radians,
                                            float aspect,
                                            float near,
                                            float far);

/// Returns the matrix to rotate around the X axis by |angle_radians|.
radiant_mat4x4_t radiant_mat4x4_rotate_x(float angle_radians);

/// Returns the matrix to rotate around the Y axis by |angle_radians|.
radiant_mat4x4_t radiant_mat4x4_rotate_y(float angle_radians);

/// Returns the matrix to rotate around the Z axis by |angle_radians|.
radiant_mat4x4_t radiant_mat4x4_rotate_z(float angle_radians);

/// Returns matrix translated by |v|
radiant_mat4x4_t radiant_mat4x4_translate(radiant_vec3_t v);

/// Returns a matrix set to scale by (|x|, |y|, |z|)
radiant_mat4x4_t radiant_mat4x4_scale(float x, float y, float z);

/// Returns the transpose of |m|
radiant_mat4x4_t radiant_mat4x4_transpose(radiant_mat4x4_t m);

/// Returns |A| * |B|
#define radiant_mat4x4_mul(A, B)                   \
  _Generic((B),                                    \
      radiant_mat4x4_t: radiant_mat4x4_mul_mat4x4, \
      radiant_point3_t: radiant_mat4x4_mul_point3, \
      radiant_vec3_t: radiant_mat4x4_mul_vec3)(A, B)

/// Returns |m| * |b|
radiant_mat4x4_t radiant_mat4x4_mul_mat4x4(radiant_mat4x4_t m,
                                           radiant_mat4x4_t b);

/// Returns |m| * |p|
radiant_point3_t radiant_mat4x4_mul_point3(radiant_mat4x4_t m,
                                           radiant_point3_t p);

/// Returns |m| * |v|
radiant_vec3_t radiant_mat4x4_mul_vec3(radiant_mat4x4_t m, radiant_vec3_t v);

/// Returns the value of |m| at |idx|
float radiant_mat4x4_get(radiant_mat4x4_t m, uint32_t idx);

/// Sets the value of |m| at |idx| to |val|
void radiant_mat4x4_set(radiant_mat4x4_t* m, uint32_t idx, float val);
