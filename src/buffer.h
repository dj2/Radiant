#pragma once

#include <stdint.h>

#include "src/engine.h"
#include "src/pad.h"
#include "src/wgpu.h"

/// Buffer usage flags
typedef enum radiant_buffer_usage_t {
  radiant_buffer_usage_none = WGPUBufferUsage_None,
  radiant_buffer_usage_map_read = WGPUBufferUsage_MapRead,
  radiant_buffer_usage_map_write = WGPUBufferUsage_MapWrite,
  radiant_buffer_usage_copy_src = WGPUBufferUsage_CopySrc,
  radiant_buffer_usage_copy_dst = WGPUBufferUsage_CopyDst,
  radiant_buffer_usage_index = WGPUBufferUsage_Index,
  radiant_buffer_usage_vertex = WGPUBufferUsage_Vertex,
  radiant_buffer_usage_uniform = WGPUBufferUsage_Uniform,
  radiant_buffer_usage_stoage = WGPUBufferUsage_Storage,
  radiant_buffer_usage_indirect = WGPUBufferUsage_Indirect,
  radiant_buffer_usage_query_resolve = WGPUBufferUsage_QueryResolve,

  radiant_buffer_usage_enum_sizer = WGPUBufferUsage_Force32,
} radiant_buffer_usage_t;

/// A GPU buffer
typedef struct radiant_buffer_t {
  radiant_engine_t engine;
  WGPUBuffer buffer;
} radiant_buffer_t;

/// Structure for requesting a buffer
typedef struct radiant_buffer_create_request_t {
  /// The engine
  radiant_engine_t engine;
  /// The buffer usage
  radiant_buffer_usage_t usage;
  /// Padding
  RADIANT_PAD(4);
  /// The buffer label
  const char* label;
  /// The bytes size of the buffer
  uint64_t size_in_bytes;
} radiant_buffer_create_request_t;

/// Creates a buffer with the given |req.usage| and |req.label|.
radiant_buffer_t radiant_buffer_create(radiant_buffer_create_request_t req);
/// Creates a buffer with the given |req.usage| and |req.label|. The provided
/// |data| will be uploaded to the buffer. Assumes that the |data| is the same
/// length as the |req.size_in_bytes|.
///
/// The `radiant_buffer_usage_copy_dst` usage will be applied automatically.
radiant_buffer_t radiant_buffer_create_with_data(
    radiant_buffer_create_request_t req,
    const void* data);
/// Destroys the |buffer|
void radiant_buffer_destroy(radiant_buffer_t buffer);

/// Writes the given |data| into the |buffer|.
void radiant_buffer_write(radiant_buffer_t buffer,
                          uint64_t data_size_in_bytes,
                          const void* data);
