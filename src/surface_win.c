#include "src/surface_win.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

radiant_surface_descriptor_t radiant_engine_create_win_surface_descriptor(
    GLFWwindow* window) {
  return (radiant_surface_descriptor_t){
      .chain =
          (WGPUChainedStruct){
              .sType = WGPUSType_SurfaceDescriptorFromWindowsHWND,
          },
      .hwnd = glfwGetWin32Window(window),
      .hinstance = glfwGetWin32Window(window),
  };
  return desc;
}
