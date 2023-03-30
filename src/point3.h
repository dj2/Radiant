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

#include <stdbool.h>

typedef struct radiant_vec3_t radiant_vec3_t;

/// A point in 3 space.
typedef struct radiant_point3_t {
  float x;
  float y;
  float z;
} radiant_point3_t;

/// Returns -|a|.
radiant_point3_t radiant_point3_negate(radiant_point3_t a);

/// Returns |a| + |b|.
radiant_point3_t radiant_point3_add(radiant_point3_t a, radiant_vec3_t b);

/// Subtracts a value from a point
#define radiant_point3_sub(A, B)                  \
  _Generic((B),                                   \
      radiant_point3_t: radiant_point3_sub_point, \
      radiant_vec3_t: radiant_point3_sub_vec3)(A, B)

/// Returns |a| - |b|
radiant_vec3_t radiant_point3_sub_point(radiant_point3_t a, radiant_point3_t b);

/// Returns |a| - |b|.
radiant_point3_t radiant_point3_sub_vec3(radiant_point3_t a, radiant_vec3_t b);

/// Returns |a| * |s|
radiant_point3_t radiant_point3_mul(radiant_point3_t a, float s);

/// Returns |a| / |s|
radiant_point3_t radiant_point3_div(radiant_point3_t a, float s);

/// Linear interpolation between |a| and |b| based on time |t|.
radiant_point3_t radiant_point3_lerp(radiant_point3_t a,
                                     radiant_point3_t b,
                                     float t);
