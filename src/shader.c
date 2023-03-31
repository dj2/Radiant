#include "src/shader.h"

#include <stdio.h>
#include <stdlib.h>

radiant_shader_t radiant_shader_create(radiant_engine_t engine,
                                       const char* label,
                                       const char* data) {
  WGPUShaderModuleWGSLDescriptor wgsl_desc = {
      .chain =
          {
              .sType = WGPUSType_ShaderModuleWGSLDescriptor,
          },
      .source = data,
  };
  WGPUShaderModuleDescriptor desc = {
      .nextInChain = (WGPUChainedStruct*)&wgsl_desc,
      .label = label,
  };

  return (radiant_shader_t){
      .mod = wgpuDeviceCreateShaderModule(engine.device, &desc),
  };
}

void radiant_shader_destroy(radiant_shader_t shader) {
  wgpuShaderModuleRelease(shader.mod);
}

radiant_shader_create_result_t radiant_shader_create_from_file(
    radiant_engine_t engine,
    radiant_resource_manager_t manager,
    const char* label,
    const char* path) {
  radiant_shader_create_result_t result = {
      .shader = {0},
      .succeeded = true,
  };

  radiant_file_result_t shader_file_result =
      radiant_resource_manager_open(manager, path);
  if (!shader_file_result.succeeded) {
    fprintf(stderr, "Unable to load %s shader", path);
    result.succeeded = false;
    return result;
  }

  radiant_file_t shader_file = shader_file_result.file;
  uint64_t shader_file_size = radiant_file_size(shader_file);

  char* shader_data = (char*)malloc((uint32_t)shader_file_size);
  if (!radiant_file_read(shader_file, shader_data, shader_file_size)) {
    fprintf(stderr, "Failed to read %s shader", path);
    result.succeeded = false;
    goto cleanup;
  }

  result.shader = radiant_shader_create(engine, label, shader_data);

cleanup:
  radiant_file_close(shader_file);
  free(shader_data);

  return result;
}
