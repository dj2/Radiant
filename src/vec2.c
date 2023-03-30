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

#include "src/vec2.h"

#include <math.h>

#include "src/assert.h"

radiant_vec2_t radiant_vec2_add(radiant_vec2_t a, radiant_vec2_t b) {
  return (radiant_vec2_t){
      .x = a.x + b.x,
      .y = a.y + b.y,
  };
}

radiant_vec2_t radiant_vec2_sub(const radiant_vec2_t a,
                                const radiant_vec2_t b) {
  return (radiant_vec2_t){
      .x = a.x - b.x,
      .y = a.y - b.y,
  };
}

radiant_vec2_t radiant_vec2_mul_vec2(const radiant_vec2_t a,
                                     const radiant_vec2_t b) {
  return (radiant_vec2_t){
      .x = a.x * b.x,
      .y = a.y * b.y,
  };
}

radiant_vec2_t radiant_vec2_mul_scalar(const radiant_vec2_t a, const float b) {
  return (radiant_vec2_t){
      .x = a.x * b,
      .y = a.y * b,
  };
}

radiant_vec2_t radiant_vec2_div(const radiant_vec2_t a, const float b) {
  RADIANT_ASSERT(b != 0.0f);
  return radiant_vec2_mul(a, 1.0f / b);
}

radiant_vec2_t radiant_vec2_negate(const radiant_vec2_t a) {
  return (radiant_vec2_t){
      .x = -a.x,
      .y = -a.y,
  };
}

float radiant_vec2_length(const radiant_vec2_t a) {
  return sqrtf(radiant_vec2_length_squared(a));
}

float radiant_vec2_length_squared(const radiant_vec2_t a) {
  return radiant_vec2_dot(a, a);
}

float radiant_vec2_dot(const radiant_vec2_t a, const radiant_vec2_t b) {
  return (a.x * b.x) + (a.y * b.y);
}

radiant_vec2_t radiant_vec2_normalize(const radiant_vec2_t a) {
  float len = radiant_vec2_length(a);
  if (len == 0.0f) {
    return (radiant_vec2_t){
        .x = 0.0f,
        .y = 0.0f,
    };
  }

  return radiant_vec2_div(a, len);
}
