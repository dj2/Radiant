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

/// A 3 element vector.
typedef struct radiant_vec3_t {
  float x;
  float y;
  float z;
} radiant_vec3_t;

/// Returns |a| + |b|
radiant_vec3_t radiant_vec3_add(const radiant_vec3_t a, const radiant_vec3_t b);

/// Returns |a| - |b|
radiant_vec3_t radiant_vec3_sub(const radiant_vec3_t a, const radiant_vec3_t b);

/// Returns |A| * |B|
#define radiant_vec3_mul(A, B)           \
  _Generic((B),                          \
      signed: radiant_vec3_mul_scalar,   \
      unsigned: radiant_vec3_mul_scalar, \
      float: radiant_vec3_mul_scalar,    \
      radiant_vec3_t: radiant_vec3_mul_vec3)(A, B)

/// Returns |a| * |b| component-wise
radiant_vec3_t radiant_vec3_mul_vec3(const radiant_vec3_t a,
                                     const radiant_vec3_t b);

/// Returns |a| * |b|
radiant_vec3_t radiant_vec3_mul_scalar(const radiant_vec3_t a, const float b);

/// Returns |a| / |b|
radiant_vec3_t radiant_vec3_div(const radiant_vec3_t a, const float b);

/// Returns -|a|
radiant_vec3_t radiant_vec3_negate(const radiant_vec3_t a);

/// Retruns the length of |a|.
float radiant_vec3_length(const radiant_vec3_t a);

/// Returns the length^2 of |a|.
float radiant_vec3_length_squared(const radiant_vec3_t a);

/// Returns the dot product of |a|.
float radiant_vec3_dot(const radiant_vec3_t a, const radiant_vec3_t b);

/// Returns the cross product of |a| and |b|
radiant_vec3_t radiant_vec3_cross(const radiant_vec3_t a,
                                  const radiant_vec3_t b);

/// Returns a normalized copy of |a|.
radiant_vec3_t radiant_vec3_normalize(const radiant_vec3_t a);
