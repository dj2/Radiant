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

#include "src/texture.h"

radiant_texture_t radiant_texture_create(radiant_texture_create_request_t req) {
  WGPUTextureDescriptor texture_desc = {
      .label = req.label,
      .usage = WGPUTextureUsage_RenderAttachment,
      .dimension = WGPUTextureDimension_2D,
      .format = req.format,
      .size =
          {
              .width = req.size.width,
              .height = req.size.height,
              .depthOrArrayLayers = 1,
          },
      .mipLevelCount = 1,
      .sampleCount = req.samples > 0 ? req.samples : 1,
  };
  return (radiant_texture_t){
      .texture = wgpuDeviceCreateTexture(req.engine.device, &texture_desc),
  };
}

void radiant_texture_destroy(radiant_texture_t texture) {
  wgpuTextureDestroy(texture.texture);
}

radiant_texture_view_t radiant_texture_view_create(radiant_texture_t texture) {
  return (radiant_texture_view_t){
      .view = wgpuTextureCreateView(texture.texture, NULL),
  };
}

void radiant_texture_view_destroy(radiant_texture_view_t view) {
  wgpuTextureViewRelease(view.view);
}
