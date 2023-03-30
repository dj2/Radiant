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

cmake_minimum_required(VERSION 3.21)

project(Radiant
  VERSION 0.0.1
  LANGUAGES C CXX OBJC
)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_C_STANDARD 23)

set(CMAKE_OSX_DEPLOYMENT_TARGET 13.0)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  message(STATUS "No build type selected, default to Debug")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

find_package(Doxygen)
if (Doxygen_FOUND)
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out/docs")
  doxygen_add_docs(docs "${PROJECT_SOURCE_DIR}/src")
else()
  message(STATUS "Doxygen not found, skipping docs")
endif()

if (NOT CLANG_FORMAT)
  find_program(CLANG_FORMAT "clang-format")
endif()
if (CLANG_FORMAT)
  message(STATUS "Found clang-format: ${CLANG_FORMAT}")
  file(GLOB_RECURSE
       ALL_C_SOURCE_FILES
       ${PROJECT_SOURCE_DIR}/src/*.h
       ${PROJECT_SOURCE_DIR}/src/*.c
  )

  add_custom_target(
      format
      COMMAND ${CLANG_FORMAT} -i ${ALL_C_SOURCE_FILES})
  add_custom_target(
      format-ci
      COMMAND
        ! ${CLANG_FORMAT} -output-replacements-xml ${ALL_C_SOURCE_FILES}
            | grep -q "replacement offset"
  )
endif()

find_package(glfw3 3.3 REQUIRED)

function(radiant_compile_options TARGET)
  target_include_directories(${TARGET} PRIVATE "${PROJECT_SOURCE_DIR}")
  target_include_directories(${TARGET} PRIVATE "${PROJECT_SOURCE_DIR}/third_party/dawn/include")

  target_compile_options(${TARGET} PRIVATE
    -fvisibility=hidden
    -Wall
    -Werror
    -Wextra
    -Wpedantic
    -pedantic-errors

    -Wno-declaration-after-statement
    -Wno-pre-c2x-compat
  )

  if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
      "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")
    target_compile_options(${TARGET} PRIVATE
      -Weverything
      -Wno-c99-extensions
      -Wno-documentation-unknown-command
      -Wno-pre-c++20-compat-pedantic
    )
  endif()
  if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${TARGET} PRIVATE
      -Wno-unsafe-buffer-usage
    )
  endif()
endfunction()

function(radiant_add_shader TARGET SHADER)
  add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/resources/shaders/${SHADER}
            ${PROJECT_BINARY_DIR}/resources/shaders/${SHADER})
endfunction()

add_subdirectory(third_party)
add_subdirectory(src)
add_subdirectory(src/cmd)

