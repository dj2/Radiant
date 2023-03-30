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
#include <stdio.h>

#include "src/equal.h"

/// Begins a test suite of |name|
void radiant_suite_begin(const char* name);

/// Ends a test suite returning 0 if the suite passed
int radiant_suite_end();

/// Prototype of a test method
typedef bool (*radiant_test_t)(void);

/// Runs the |name| test
#define RADIANT_TEST(name) radiant_run_test(name, #name)

/// Runs |test| with |name|
void radiant_run_test(radiant_test_t test, const char* name);

/// ANSI escape red
#define RADIANT_RED "\033[0;31m"
/// ANSI escape gree
#define RADIANT_GREEN "\033[0;32m"
/// ANSI escape Reset
#define RADIANT_RESET "\033[0m"

/// Emits a test failure prefix with various bits of test information
#define RADIANT_FAIL_PREFIX()                      \
  printf(RADIANT_RED "FAILED" RADIANT_RESET "\n"); \
  printf("  %s:%d\n  EXPECTED: ", __FILE__, __LINE__)

/// Logs an error and sets the context to failed if |a| is not true.
#define RADIANT_EXPECT_TRUE(a)    \
  do {                            \
    if (!(a)) {                   \
      RADIANT_FAIL_PREFIX();      \
      printf(#a " to be true\n"); \
      return false;               \
    }                             \
  } while (0)

/// Logs an error and sets the context to failed if |a| is true.
#define RADIANT_EXPECT_FALSE(a)    \
  do {                             \
    if ((a)) {                     \
      RADIANT_FAIL_PREFIX();       \
      printf(#a " to be false\n"); \
      return false;                \
    }                              \
  } while (0)

/// Logs an error and sets the context to failed if |a| != |b|.
#define RADIANT_EXPECT_EQ(a, b)                                \
  do {                                                         \
    if ((a) != (b)) {                                          \
      RADIANT_FAIL_PREFIX();                                   \
      printf(#a " (0x%x) to equal " #b " (0x%x)\n", (a), (b)); \
      return false;                                            \
    }                                                          \
  } while (0)

/// Logs an error and sets the context to failed if |a| != NULL.
#define RADIANT_EXPECT_NOT_NULL(a)    \
  do {                                \
    if ((a) == NULL) {                \
      RADIANT_FAIL_PREFIX();          \
      printf(#a " to not be null\n"); \
      return false;                   \
    }                                 \
  } while (0)

/// Logs an error and sets the context to failed if |a| == NULL.
#define RADIANT_EXPECT_NULL(a)    \
  do {                            \
    if ((a) != NULL) {            \
      RADIANT_FAIL_PREFIX();      \
      printf(#a " to be null\n"); \
      return false;               \
    }                             \
  } while (0)

/// Logs an error and sets the context to failed if |a| != |b|.
#define RADIANT_EXPECT_DOUBLE_EQ(a, b)                     \
  do {                                                     \
    if (!radiant_equal((a), (b))) {                        \
      RADIANT_FAIL_PREFIX();                               \
      printf(#a " (%f) to equal " #b " (%f)\n", (a), (b)); \
      return false;                                        \
    }                                                      \
  } while (0)

/// Logs an error and sets the context to failed if |a| != |b|.
#define RADIANT_EXPECT_FLOAT_EQ(a, b)                                      \
  do {                                                                     \
    if (!radiant_equal((a), (b))) {                                        \
      RADIANT_FAIL_PREFIX();                                               \
      printf(#a " (%f) to equal " #b " (%f)\n", (double)(a), (double)(b)); \
      return false;                                                        \
    }                                                                      \
  } while (0)
