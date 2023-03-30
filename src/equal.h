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

#define radiant_equal(A, B) \
  _Generic((B), double: radiant_equal_double, float: radiant_equal_float)(A, B)

/// Returns true if |left| == |right| within some epsilon.
bool radiant_equal_double(double left, double right);

/// Returns true if |left| == |right| within some epsilon.
bool radiant_equal_float(float left, float right);
