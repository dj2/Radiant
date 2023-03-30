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

#include "src/vec4.h"

#include <math.h>

#include "src/assert.h"
#include "src/unreachable.h"

radiant_vec4_t radiant_vec4_add(radiant_vec4_t a, radiant_vec4_t b) {
  return (radiant_vec4_t){
      .x = a.x + b.x,
      .y = a.y + b.y,
      .z = a.z + b.z,
      .w = a.w + b.w,
  };
}

radiant_vec4_t radiant_vec4_sub(radiant_vec4_t a, radiant_vec4_t b) {
  return (radiant_vec4_t){
      .x = a.x - b.x,
      .y = a.y - b.y,
      .z = a.z - b.z,
      .w = a.w - b.w,
  };
}

radiant_vec4_t radiant_vec4_mul_vec4(radiant_vec4_t a, radiant_vec4_t b) {
  return (radiant_vec4_t){
      .x = a.x * b.x,
      .y = a.y * b.y,
      .z = a.z * b.z,
      .w = a.w * b.w,
  };
}

radiant_vec4_t radiant_vec4_mul_scalar(radiant_vec4_t a, float b) {
  return (radiant_vec4_t){
      .x = a.x * b,
      .y = a.y * b,
      .z = a.z * b,
      .w = a.w * b,
  };
}

radiant_vec4_t radiant_vec4_div(radiant_vec4_t a, float b) {
  RADIANT_ASSERT(b != 0.0f);

  if (b < 0.0f || b > 0.0f) {
    return radiant_vec4_mul(a, 1.0f / b);
  }

  RADIANT_UNREACHABLE();
}

radiant_vec4_t radiant_vec4_negate(radiant_vec4_t a) {
  return (radiant_vec4_t){
      .x = -a.x,
      .y = -a.y,
      .z = -a.z,
      .w = -a.w,
  };
}

float radiant_vec4_length(radiant_vec4_t a) {
  return sqrtf(radiant_vec4_length_squared(a));
}

float radiant_vec4_length_squared(radiant_vec4_t a) {
  return radiant_vec4_dot(a, a);
}

float radiant_vec4_dot(radiant_vec4_t a, radiant_vec4_t b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

radiant_vec4_t radiant_vec4_normalize(radiant_vec4_t a) {
  float len = radiant_vec4_length(a);
  if (len == 0.0f) {
    return (radiant_vec4_t){
        .x = 0.f,
        .y = 0.f,
        .z = 0.f,
        .w = 0.f,
    };
  }
  return radiant_vec4_div(a, radiant_vec4_length(a));
}
