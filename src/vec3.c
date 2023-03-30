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

#include "src/vec3.h"

#include <math.h>

#include "src/assert.h"

radiant_vec3_t radiant_vec3_add(radiant_vec3_t a, radiant_vec3_t b) {
  return (radiant_vec3_t){
      .x = a.x + b.x,
      .y = a.y + b.y,
      .z = a.z + b.z,
  };
}

radiant_vec3_t radiant_vec3_sub(const radiant_vec3_t a,
                                const radiant_vec3_t b) {
  return (radiant_vec3_t){
      .x = a.x - b.x,
      .y = a.y - b.y,
      .z = a.z - b.z,
  };
}

radiant_vec3_t radiant_vec3_mul_vec3(const radiant_vec3_t a,
                                     const radiant_vec3_t b) {
  return (radiant_vec3_t){
      .x = a.x * b.x,
      .y = a.y * b.y,
      .z = a.z * b.z,
  };
}

radiant_vec3_t radiant_vec3_mul_scalar(const radiant_vec3_t a, const float b) {
  return (radiant_vec3_t){
      .x = a.x * b,
      .y = a.y * b,
      .z = a.z * b,
  };
}

radiant_vec3_t radiant_vec3_div(const radiant_vec3_t a, const float b) {
  RADIANT_ASSERT(b != 0.0f);

  return radiant_vec3_mul(a, 1.0f / b);
}

radiant_vec3_t radiant_vec3_negate(const radiant_vec3_t a) {
  return (radiant_vec3_t){
      .x = -a.x,
      .y = -a.y,
      .z = -a.z,
  };
}

float radiant_vec3_length(const radiant_vec3_t a) {
  return sqrtf(radiant_vec3_length_squared(a));
}

float radiant_vec3_length_squared(const radiant_vec3_t a) {
  return radiant_vec3_dot(a, a);
}

float radiant_vec3_dot(const radiant_vec3_t a, const radiant_vec3_t b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

radiant_vec3_t radiant_vec3_cross(const radiant_vec3_t a,
                                  const radiant_vec3_t b) {
  return (radiant_vec3_t){
      .x = (a.y * b.z) - (a.z * b.y),
      .y = (a.z * b.x) - (a.x * b.z),
      .z = (a.x * b.y) - (a.y * b.x),
  };
}

radiant_vec3_t radiant_vec3_normalize(const radiant_vec3_t a) {
  float len = radiant_vec3_length(a);
  if (len == 0.0f) {
    return (radiant_vec3_t){
        .x = 0.0f,
        .y = 0.0f,
        .z = 0.0f,
    };
  }
  return radiant_vec3_div(a, len);
}
