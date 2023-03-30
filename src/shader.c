#include "src/shader.h"

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
