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

/// A 2-element vector.
typedef struct radiant_vec2_t {
  /// The x component
  float x;
  /// The y component
  float y;
} radiant_vec2_t;

/// Returns |a| + |b|
radiant_vec2_t radiant_vec2_add(const radiant_vec2_t a, const radiant_vec2_t b);

/// Returns |a| - |b|
radiant_vec2_t radiant_vec2_sub(const radiant_vec2_t a, const radiant_vec2_t b);

/// Returns |A| * |B|
#define radiant_vec2_mul(A, B)           \
  _Generic((B),                          \
      signed: radiant_vec2_mul_scalar,   \
      unsigned: radiant_vec2_mul_scalar, \
      float: radiant_vec2_mul_scalar,    \
      radiant_vec2_t: radiant_vec2_mul_vec2)(A, B)

/// Returns |a| * |b|
radiant_vec2_t radiant_vec2_mul_vec2(const radiant_vec2_t a,
                                     const radiant_vec2_t b);

/// Returns |a| * |b|
radiant_vec2_t radiant_vec2_mul_scalar(const radiant_vec2_t a, const float b);

/// Returns |a| / |b|
radiant_vec2_t radiant_vec2_div(const radiant_vec2_t a, const float b);

/// Returns -|a|
radiant_vec2_t radiant_vec2_negate(const radiant_vec2_t a);

/// Returns the length of |a|
float radiant_vec2_length(const radiant_vec2_t a);

/// Returns the squared length of |a|
float radiant_vec2_length_squared(const radiant_vec2_t a);

/// Returns the dot product of |a| with |b|.
float radiant_vec2_dot(const radiant_vec2_t a, const radiant_vec2_t b);

/// Returns a normalized copy of |a|.
radiant_vec2_t radiant_vec2_normalize(const radiant_vec2_t a);
