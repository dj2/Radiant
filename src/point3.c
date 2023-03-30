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

#include "src/point3.h"

#include "src/assert.h"
#include "src/vec3.h"

radiant_point3_t radiant_point3_negate(radiant_point3_t a) {
  return (radiant_point3_t){
      .x = -a.x,
      .y = -a.y,
      .z = -a.z,
  };
}

radiant_point3_t radiant_point3_add(radiant_point3_t a, radiant_vec3_t b) {
  return (radiant_point3_t){
      .x = a.x + b.x,
      .y = a.y + b.y,
      .z = a.z + b.z,
  };
}

radiant_vec3_t radiant_point3_sub_point(radiant_point3_t a,
                                        radiant_point3_t b) {
  return (radiant_vec3_t){
      .x = a.x - b.x,
      .y = a.y - b.y,
      .z = a.z - b.z,
  };
}

radiant_point3_t radiant_point3_sub_vec3(radiant_point3_t a, radiant_vec3_t b) {
  return (radiant_point3_t){
      .x = a.x - b.x,
      .y = a.y - b.y,
      .z = a.z - b.z,
  };
}

radiant_point3_t radiant_point3_mul(radiant_point3_t a, float s) {
  return (radiant_point3_t){
      .x = a.x * s,
      .y = a.y * s,
      .z = a.z * s,
  };
}

radiant_point3_t radiant_point3_div(radiant_point3_t a, float s) {
  RADIANT_ASSERT(s != 0.0f);
  float inv = 1.0f / s;
  return radiant_point3_mul(a, inv);
}

radiant_point3_t radiant_point3_lerp(radiant_point3_t a,
                                     radiant_point3_t b,
                                     float t) {
  RADIANT_ASSERT(!(t < 0.0f));
  RADIANT_ASSERT(!(t > 1.0f));

  float sub = 1.0f - t;
  return (radiant_point3_t){
      .x = (sub * a.x) + (t * b.x),
      .y = (sub * a.y) + (t * b.y),
      .z = (sub * a.z) + (t * b.z),
  };
}
