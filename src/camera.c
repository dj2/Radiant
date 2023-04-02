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
  radiant_mat4x4_t rot_x = radiant_mat4x4_identity();
  radiant_mat4x4_t rot_y = radiant_mat4x4_identity();
  radiant_mat4x4_t rot_z = radiant_mat4x4_identity();

  if (radians.x != 0.f) {
    rot_x = radiant_mat4x4_rotate_x(radians.x);
  }
  if (radians.y != 0.f) {
    rot_y = radiant_mat4x4_rotate_y(radians.y);
  }
  if (radians.z != 0.f) {
    rot_z = radiant_mat4x4_rotate_z(radians.x);
  }

  radiant_mat4x4_t rot_yz = radiant_mat4x4_mul(rot_y, rot_z);
  radiant_mat4x4_t rot = radiant_mat4x4_mul(rot_x, rot_yz);
  cam->position.current = radiant_mat4x4_mul(rot, cam->position.initial);

  radiant_camera_update_look_at(cam);
}

void radiant_camera_update_look_at(radiant_camera_t* cam) {
  cam->look_at_matrix =
      radiant_mat4x4_look_at(cam->position.current, cam->aim_point, cam->up);
  radiant_camera_update_view_projection_matrix(cam);
}

void radiant_camera_update_view_projection_matrix(radiant_camera_t* cam) {
  cam->view_projection_matrix =
      radiant_mat4x4_mul(cam->projection_matrix, cam->look_at_matrix);
}
