#include "src/angle.h"

#include "src/constants.h"

static const float kPiBy180 = RADIANT_PI / 180.f;
static const float k180ByPi = 180.f / RADIANT_PI;

float radiant_deg_to_rad(float degrees) {
  return degrees * kPiBy180;
}

float radiant_rad_to_deg(float radians) {
  return radians * k180ByPi;
}
