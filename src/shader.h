#pragma once

#include "src/engine.h"
#include "src/pad.h"
#include "src/resource_manager.h"

typedef struct radiant_shader_t {
  WGPUShaderModule mod;
} radiant_shader_t;

/// Results of a create call
typedef struct radiant_shader_create_result_t {
  /// The shader. Only valid if succeeded is true.
  radiant_shader_t shader;
  /// True if the file was successfully opened. False otherwise.
  bool succeeded;
  /// Unused padding
  RADIANT_PAD(7);
} radiant_shader_create_result_t;

radiant_shader_t radiant_shader_create(radiant_engine_t engine,
                                       const char* label,
                                       const char* data);
void radiant_shader_destroy(radiant_shader_t shader);

radiant_shader_create_result_t radiant_shader_create_from_file(
    radiant_engine_t engine,
    radiant_resource_manager_t manager,
    const char* label,
    const char* path);
