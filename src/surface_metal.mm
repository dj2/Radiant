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

#include "src/surface_metal.h"

#import <AppKit/AppKit.h>
#import <QuartzCore/CAMetalLayer.h>

#include "src/glfw.h"
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

radiant_surface_descriptor_t radiant_engine_create_metal_surface_descriptor(
    GLFWwindow* window) {
  NSWindow* nsWin = glfwGetCocoaWindow(window);
  NSView* view = [nsWin contentView];

  [view setWantsLayer:YES];
  [view setLayer:[CAMetalLayer layer]];

  // Use retina if requested by the window
  [[view layer] setContentsScale:[nsWin backingScaleFactor]];

  return (radiant_surface_descriptor_t){
    .chain =
      (WGPUChainedStruct){
        .sType = WGPUSType_SurfaceDescriptorFromMetalLayer,
      },
    .layer = [view layer],
  };
}

