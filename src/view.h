#pragma once

typedef struct radiant_view_t {
  struct {
    float width;
    float height;
  } size;
  float fov_y_radians;
  struct {
    float near;
    float far;
  } planes;
} radiant_view_t;
