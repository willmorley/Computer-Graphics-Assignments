#ifndef CONVERSION_H
#define CONVERSION_H

#include "hue_shift.h"
#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void rgb_to_hsv_image(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<double> & hsv);

void hsv_to_rgb_image(
  const std::vector<double> & hsv,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb);

#endif //CONVERSION_H
