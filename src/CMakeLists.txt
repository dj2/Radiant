# Copyright 2023 The Radiant Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

add_library(libradiant "")
target_sources(libradiant PRIVATE
  angle.c
  angle.h
  array_element_count.h
  assert.c
  assert.h
  buffer.c
  buffer.h
  colour3.h
  constants.h
  engine.c
  engine.h
  equal.c
  equal.h
  glfw.h
  io.c
  io.h
  mat4x4.c
  mat4x4.h
  no_return.h
  pad.h
  point3.c
  point3.h
  resource_manager.c
  resource_manager.h
  shader.c
  shader.h
  time.c
  time.h
  vec2.c
  vec2.h
  vec3.c
  vec3.h
  vec4.c
  vec4.h
  unreachable.h
  unreachable.h
  wgpu.h
  window.c
  window.h
)

if (APPLE)
  target_sources(libradiant PRIVATE
    surface_metal.h
    surface_metal.mm
  )
  target_link_libraries(libradiant PRIVATE
    "-framework Metal"
  )
endif()
if (UNIX AND !APPLE)
  target_sources(libradiant PRIVATE
    surface_x11.h
    surface_x11.c
  )
endif()
if (WIN32)
  target_sources(libradiant PRIVATE
    surface_win.h
    surface_win.c
  )
endif()

radiant_compile_options(libradiant)
target_link_libraries(libradiant PUBLIC
  webgpu_dawn
  webgpu_cpp
  glfw
)

add_library(radiant::lib ALIAS libradiant)

add_library(libradianttest "")
target_sources(libradianttest PRIVATE
  test.c
  test.h
)
radiant_compile_options(libradianttest)
target_link_libraries(libradianttest PUBLIC radiant::lib)
add_library(radiant::test ALIAS libradianttest)

set(TESTS
  equal_test
  mat4x4_test
  point3_test
  time_test
  vec2_test
  vec3_test
  vec4_test
)

foreach(TEST IN LISTS TESTS)
  add_executable(${TEST} ${TEST}.c)
  radiant_compile_options(${TEST})
  target_link_libraries(${TEST} radiant::test)
  add_test(${TEST} COMMAND ${PROJECT_BINARY_DIR}/${TEST})
endforeach()
