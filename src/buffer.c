#include "src/buffer.h"

#include <stdio.h>

radiant_buffer_t radiant_buffer_create(radiant_buffer_create_request_t req) {
  radiant_buffer_t buffer = {
      .engine = req.engine,
  };
  WGPUBufferDescriptor buffer_descriptor = {
      .label = req.label,
      .usage = req.usage,
      .size = req.size_in_bytes,
  };
  buffer.buffer = wgpuDeviceCreateBuffer(req.engine.device, &buffer_descriptor);
  return buffer;
}

radiant_buffer_t radiant_buffer_create_with_data(
    radiant_buffer_create_request_t req,
    const void* data) {
  req.usage |= radiant_buffer_usage_copy_dst;
  radiant_buffer_t buffer = radiant_buffer_create(req);
  radiant_buffer_write(buffer, req.size_in_bytes, data);
  return buffer;
}

void radiant_buffer_destroy(radiant_buffer_t buffer) {
  wgpuBufferDestroy(buffer.buffer);
}

void radiant_buffer_write(radiant_buffer_t buffer,
                          uint64_t data_size_in_bytes,
                          const void* data) {
  WGPUQueue queue = wgpuDeviceGetQueue(buffer.engine.device);
  wgpuQueueWriteBuffer(queue, buffer.buffer, 0, data, data_size_in_bytes);
}
