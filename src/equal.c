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

#include "src/equal.h"

static const double DOUBLE_EPSILON = 0.00001;
static const float FLOAT_EPSILON = 0.00001f;

bool radiant_equal_double(double left, double right) {
  double diff = left - right;
  diff = diff < 0.0 ? -diff : diff;
  return diff < DOUBLE_EPSILON;
}

bool radiant_equal_float(float left, float right) {
  float diff = left - right;
  diff = diff < 0.0f ? -diff : diff;
  return diff < FLOAT_EPSILON;
}
