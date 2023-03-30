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

#include "src/pad.h"

#include <stdbool.h>
#include <stdint.h>

/// A file handle
typedef struct radiant_file_t {
  /// Opqaue file handle
  uint64_t handle;
  /// True if the file is open
  bool open;
  /// Unused padding
  RADIANT_PAD(7);
} radiant_file_t;

/// The result of opening a file.
typedef struct radiant_file_result_t {
  /// The file handle. Only valid if |succeeded| is true.
  radiant_file_t file;
  /// True if the file was successfully opened. False otherwise.
  bool succeeded;
  /// Unused padding
  RADIANT_PAD(7);
} radiant_file_result_t;

/// Teturns the result of opening the file at |path|.
/// Note: |path| must not be a nullptr.
radiant_file_result_t radiant_file_open(const char* path);

/// Returns the result of opening |buf| of |len| as a file stream.
/// Note: |buf| must not be a nullptr. |len| must be greater then 0.
radiant_file_result_t radiant_file_mem_open(void* buf, uint32_t len);

/// Closes the |file| handle.
/// Note: |file| must not be used after closed.
void radiant_file_close(radiant_file_t file);

/// Seeks |file| to |pos|.
void radiant_file_seek(radiant_file_t file, int32_t pos);

/// Returns the size of |file|.
uint64_t radiant_file_size(radiant_file_t file);

/// Reads |size| bytes from |file| into |buffer|. Returning true if |size| bytes
/// were read. Note: |buffer| must not be a nullptr.
bool radiant_file_read(radiant_file_t file,
                       void* buffer,
                       uint64_t size_in_bytes);

/// Writes |size| bytes from |buffer| to |file|.
void radiant_file_write(radiant_file_t file,
                        const void* buffer,
                        uint64_t size_in_bytes);

/// Writes |msg| with arguments to |file|.
void radiant_file_printf(radiant_file_t file, const char* msg, ...);
