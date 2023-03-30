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
typedef struct radiant_vec4_t {
  float x;
  float y;
  float z;
  float w;
} radiant_vec4_t;

/// Returns |a| + |b|
radiant_vec4_t radiant_vec4_add(radiant_vec4_t a, radiant_vec4_t b);

/// Returns |a| - |b|
radiant_vec4_t radiant_vec4_sub(radiant_vec4_t a, radiant_vec4_t b);

/// Returns |A| * |B|
#define radiant_vec4_mul(A, B)           \
  _Generic((B),                          \
      signed: radiant_vec4_mul_scalar,   \
      unsigned: radiant_vec4_mul_scalar, \
      float: radiant_vec4_mul_scalar,    \
      radiant_vec4_t: radiant_vec4_mul_vec4)(A, B)

/// Returns |a| * |b| component-wise
radiant_vec4_t radiant_vec4_mul_vec4(radiant_vec4_t a, radiant_vec4_t b);

/// Returns |a| * |b|
radiant_vec4_t radiant_vec4_mul_scalar(radiant_vec4_t a, float b);

/// Returns |a| / |b|
radiant_vec4_t radiant_vec4_div(radiant_vec4_t a, float b);

/// Returns -|a|
radiant_vec4_t radiant_vec4_negate(radiant_vec4_t a);

/// Returns the length of |a|.
float radiant_vec4_length(radiant_vec4_t a);

/// Returns the length^2 of |a|.
float radiant_vec4_length_squared(radiant_vec4_t a);

/// Returns the dot product of |a|.
float radiant_vec4_dot(radiant_vec4_t a, radiant_vec4_t b);

/// Returns a normalized copy of |a|.
radiant_vec4_t radiant_vec4_normalize(radiant_vec4_t a);
