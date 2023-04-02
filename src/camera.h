#pragma once

#include "src/mat4x4.h"
#include "src/point3.h"
#include "src/vec3.h"
#include "src/view.h"

typedef struct radiant_camera_t {
  struct {
    radiant_point3_t initial;
    radiant_point3_t current;
  } position;
  radiant_point3_t aim_point;
  radiant_vec3_t up;

  radiant_mat4x4_t projection_matrix;
  radiant_mat4x4_t look_at_matrix;
  radiant_mat4x4_t view_projection_matrix;
} radiant_camera_t;

radiant_camera_t radiant_camera_create(radiant_point3_t position,
                                       radiant_point3_t aim_point,
                                       radiant_vec3_t up,
                                       radiant_view_t view);
void radiant_camera_destroy(radiant_camera_t cam);

void radiant_camera_rotate(radiant_camera_t* cam, radiant_point3_t radians);

void radiant_camera_update_look_at(radiant_camera_t* cam);
void radiant_camera_update_view_projection_matrix(radiant_camera_t* cam);
