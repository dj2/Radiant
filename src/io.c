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

#include "src/io.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>

#include "src/assert.h"
#include "src/unreachable.h"

radiant_file_result_t radiant_file_open(const char* path) {
  RADIANT_ASSERT(path);

  FILE* file = fopen(path, "r+");
  if (!file) {
    return (radiant_file_result_t){0};
  }
  return (radiant_file_result_t){.succeeded = true,
                                 .file = (radiant_file_t){
                                     .open = true,
                                     .handle = (uint64_t)file,
                                 }};
}

radiant_file_result_t radiant_file_mem_open(void* buf, uint32_t len) {
  RADIANT_ASSERT(buf);
  RADIANT_ASSERT(len > 0);

  FILE* dest = fmemopen(buf, len, "r+");
  if (!dest) {
    return (radiant_file_result_t){0};
  }

  return (radiant_file_result_t){.succeeded = true,
                                 .file = (radiant_file_t){
                                     .open = true,
                                     .handle = (uint64_t)dest,
                                 }};
}

void radiant_file_close(radiant_file_t file) {
  RADIANT_ASSERT(file.open);

  FILE* handle = (FILE*)file.handle;
  if (fclose(handle) != 0) {
    RADIANT_UNREACHABLE();
  }
}

void radiant_file_seek(radiant_file_t file, int32_t pos) {
  RADIANT_ASSERT(file.open);

  FILE* handle = (FILE*)file.handle;
  if (fseek(handle, SEEK_SET, pos) != 0) {
    RADIANT_UNREACHABLE();
  }
}

uint64_t radiant_file_size(radiant_file_t file) {
  RADIANT_ASSERT(file.open);

  FILE* handle = (FILE*)file.handle;
  fpos_t cur = {0};
  if (fgetpos(handle, &cur) != 0) {
    RADIANT_UNREACHABLE();
  }
  if (fseek(handle, 0, SEEK_END) != 0) {
    RADIANT_UNREACHABLE();
  }

  int64_t s = ftell(handle);
  if (s < 0) {
    RADIANT_UNREACHABLE();
  }

  uint64_t size = (uint64_t)s;
  if (fsetpos(handle, &cur) != 0) {
    RADIANT_UNREACHABLE();
  }

  return size;
}

bool radiant_file_read(radiant_file_t file, void* buffer, uint64_t size) {
  RADIANT_ASSERT(file.open);
  RADIANT_ASSERT(buffer);

  FILE* handle = (FILE*)file.handle;
  if (fread(buffer, 1, size, handle) != size) {
    RADIANT_UNREACHABLE();
  }
  return true;
}

void radiant_file_write(radiant_file_t file,
                        const void* buffer,
                        uint64_t size) {
  RADIANT_ASSERT(file.open);
  RADIANT_ASSERT(buffer);

  FILE* handle = (FILE*)file.handle;
  if (fwrite(buffer, 1, size, handle) != size) {
    RADIANT_UNREACHABLE();
  }
}

__attribute__((format(printf, 2, 3)))  //
 void radiant_file_printf(radiant_file_t file, const char* msg, ...) {
  RADIANT_ASSERT(file.open);
  RADIANT_ASSERT(msg);

  FILE* handle = (FILE*)file.handle;
  va_list args = {0};
  va_start(args, msg);
  if (vfprintf(handle, msg, args) < 0) {
    RADIANT_UNREACHABLE();
  }
  va_end(args);
}
