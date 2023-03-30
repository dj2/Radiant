#pragma once

#include "src/engine.h"

typedef struct radiant_shader_t {
  WGPUShaderModule mod;
} radiant_shader_t;

radiant_shader_t radiant_shader_create(radiant_engine_t engine,
                                       const char* label,
                                       const char* data);
void radiant_shader_destroy(radiant_shader_t shader);
