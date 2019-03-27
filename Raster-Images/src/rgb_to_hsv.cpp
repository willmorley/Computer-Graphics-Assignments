#include "rgb_to_hsv.h"
#include <cmath>
#include <algorithm>

// HSV to RGB algorithm based off HSV/HSL wikipedia article:
// https://en.wikipedia.org/wiki/HSL_and_HSV

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  // Find min, max, and diff (chroma) between them
  double min = std::min({r, g, b});
  double max = std::max({r, g, b});
  double c = max - min;

  // Set the Value
  v = max;

  // Set the saturation
  if(v == 0){ // r = g = b = 0
    s = 0;
    h = 0;
    return;
  }
  else s = (c/v);// * 0.8;

  // Choose the hue region
  if(c == 0){
    s = 0;
    h = 0; // Undefined
  }
  else if(max == r)
    h = 60 * (std::fmod(((g-b)/c), 6));
  else if (max == g)
    h = 60 * (2 + (b-r)/c);
  else if (max == b)
    h = 60 * (4 + (r-g)/c);

  if(h < 0) h += 360; // make sure h is [0, 360)
}
