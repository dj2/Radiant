#include "src/camera.h"

radiant_camera_t radiant_camera_create(radiant_point3_t position,
                                       radiant_point3_t aim_point,
                                       radiant_vec3_t up,
                                       radiant_view_t view) {
  radiant_camera_t cam = {
      .position =
          {
              .initial = position,
              .current = position,
          },
      .aim_point = aim_point,
      .up = up,
  };

  float aspect = view.size.width / view.size.height;
  float fov_y_radians = view.fov_y_radians;
  cam.projection_matrix = radiant_mat4x4_perspective(
      fov_y_radians, aspect, view.planes.near, view.planes.far);

  radiant_camera_update_look_at(&cam);
  return cam;
}

void radiant_camera_destroy(radiant_camera_t /*cam*/) {}

void radiant_camera_rotate(radiant_camera_t* cam, radiant_point3_t radians) {
  cam->position.current =
      radiant_mat4x4_mul(radiant_mat4x4_rotate(radians), cam->position.initial);

  radiant_camera_update_look_at(cam);
}

void radiant_camera_update_look_at(radiant_camera_t* cam) {
  cam->look_at_matrix =
      radiant_mat4x4_look_at(cam->position.current, cam->aim_point, cam->up);

  radiant_camera_update_projection_view_matrix(cam);
}

void radiant_camera_update_projection_view_matrix(radiant_camera_t* cam) {
  cam->projection_view_matrix =
      radiant_mat4x4_mul(cam->projection_matrix, cam->look_at_matrix);
}
