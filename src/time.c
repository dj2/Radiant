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

#include "src/time.h"

#include <time.h>

static const double NS_TO_MS = 1.0 / 1000000.0;

radiant_time_t radiant_time(void) {
  return clock_gettime_nsec_np(CLOCK_UPTIME_RAW);
}

radiant_time_diff_t radiant_time_sub(radiant_time_t mark1,
                                     radiant_time_t mark2) {
  return (mark2 > mark1) ? (mark2 - mark1) : (mark1 - mark2);
}

double radiant_time_diff_to_ms(radiant_time_diff_t diff) {
  return NS_TO_MS * (double)diff;
}
