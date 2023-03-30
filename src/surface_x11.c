#include "src/surface_x11.h"
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

radiant_surface_descriptor_t radiant_engine_create_x11_surface_descriptor(
    GLFWwindow* window) {
  return (radiant_surface_descriptor_t){
      .chain =
          (WGPUChainedStruct){
              .sType = WGPUSType_SurfaceDescriptorFromXlibWindow,
          },
      .display = glfwGetX11Display(),
      .window = glfwGetX11Window(window),
  };
}
