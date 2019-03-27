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

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  std::vector<double> hsv(rgb.size());

  // Convert to HSV
  rgb_to_hsv_image(rgb, width, height, hsv);

  // Perform saturation
  for(size_t i = 1; i < hsv.size(); i += 3)
    hsv[i] *= (1 - factor);

  // Convert back to RGB
  hsv_to_rgb_image(hsv, width, height, desaturated);
}
