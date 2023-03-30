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

#include <stdint.h>

/// A time value
typedef uint64_t radiant_time_t;

/// The difference between two time values.
typedef uint64_t radiant_time_diff_t;

/// Returns a monotonic increasing time value. The timer does not increase
/// if the system is asleep.
radiant_time_t radiant_time(void);

/// Returns the time difference between |mark1| and |mark2|. This will always
/// subtract the smaller from the larger.
radiant_time_diff_t radiant_time_sub(radiant_time_t mark1,
                                     radiant_time_t mark2);

/// Returns the number of milliseconds represented by the given |diff|.
double radiant_time_diff_to_ms(radiant_time_diff_t diff);
