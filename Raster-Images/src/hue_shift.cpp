#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <iostream>
#include <cmath>

void rgb_to_hsv_image(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<double> & hsv)
{
    for(size_t i = 0; i < rgb.size(); i += 3)
        rgb_to_hsv(static_cast<double>(rgb[i])/255.0,
                   static_cast<double>(rgb[i+1])/255.0,
                   static_cast<double>(rgb[i+2])/255.0,
                    hsv[i], hsv[i+1], hsv[i+2]);
}

void hsv_to_rgb_image(
  const std::vector<double> & hsv,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
    double r, g, b;
    for(size_t i = 0; i < rgb.size(); i += 3){
        hsv_to_rgb(hsv[i], hsv[i+1], hsv[i+2], r, g, b);
        rgb[i] = static_cast<unsigned char>(r);
        rgb[i + 1] = static_cast<unsigned char>(g);
        rgb[i + 2] = static_cast<unsigned char>(b);
    }
}

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());

  // Convert to hsv format
  std::vector<double> hsv(rgb.size());
  rgb_to_hsv_image(rgb, width, height, hsv);

  // Perform Hue shift
  for(size_t i = 0; i < hsv.size(); i += 3){
    hsv[i] += shift;
  }

  // Convert back to RGB
  hsv_to_rgb_image(hsv, width, height, shifted);
}
