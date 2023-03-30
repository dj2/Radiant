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
#include <stddef.h>
#include <stdint.h>

#include "src/no_return.h"

/// Log an assert if |x| is false.
#define RADIANT_ASSERT(x) \
  ((x) ? (void)0 : radiant_assert(__FILE__, __LINE__, __func__, NULL, #x))

/// Log an assert if |x| is false with |msg|.
#define RADIANT_ASSERT_MSG(x, msg) \
  ((x) ? (void)0 : radiant_assert(__FILE__, __LINE__, __func__, msg, #x))

/// Log an assert in |file| at |line| executing |func|. The assertion |msg| and
/// |expr| are also provided.
///
/// Note: does not return.
void radiant_assert(const char* file,
                    uint32_t line,
                    const char* func,
                    const char* msg,
                    const char* expr) RADIANT_NO_RETURN;
