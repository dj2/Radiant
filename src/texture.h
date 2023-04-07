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

#include "src/engine.h"
#include "src/size.h"
#include "src/wgpu.h"

typedef struct radiant_texture_create_request_t {
  radiant_engine_t engine;
  const char* label;
  radiant_size_t size;
  uint32_t samples;
  WGPUTextureFormat format;
} radiant_texture_create_request_t;

typedef struct radiant_texture_t {
  WGPUTexture texture;
} radiant_texture_t;

typedef struct radiant_text_view_t {
  WGPUTextureView view;
} radiant_texture_view_t;

radiant_texture_t radiant_texture_create(radiant_texture_create_request_t req);
void radiant_texture_destroy(radiant_texture_t texture);

radiant_texture_view_t radiant_texture_view_create(radiant_texture_t texture);
void radiant_texture_view_destroy(radiant_texture_view_t view);
