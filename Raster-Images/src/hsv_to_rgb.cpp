#include "hsv_to_rgb.h"
#include <algorithm>
#include <cmath>
#include <iostream>

// HSV to RGB algorithm based off HSV/HSL wikipedia article:
// https://en.wikipedia.org/wiki/HSL_and_HSV

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{

  double chroma = v * s;
  double h_prime = std::fmod(h/60, 6);
  //double h_prime = h/60;
  double x = chroma * (1 - std::fabs(std::fmod(h/60 , 2) - 1));
  double m = v - chroma;

  r = 0;
  g = 0;
  b = 0;

  if(h_prime > 0 && h_prime <= 1){
    //std::cout << h_prime << ": " << chroma << " " << x << std::endl;
    r = chroma;
    g = x;
  }
  else if(h_prime > 1 && h_prime <= 2){
    //std::cout << h_prime << ": " << chroma << " " << x << std::endl;
    r = x;
    g = chroma;
  }
  else if(h_prime > 2 && h_prime <= 3){
    //std::cout << h_prime << ": " << chroma << " " << x << std::endl;
    g = chroma;
    b = x;
  }
  else if(h_prime > 3 && h_prime <= 4){
    //std::cout << h_prime << ": " << chroma << " " << x << std::endl;
    g = x;
    b = chroma;
  }
  else if(h_prime > 4 && h_prime <= 5){
    //std::cout << h_prime << ": " << chroma << " " << x << std::endl;
    r = chroma;
    b = x;
  }
  else if(h_prime > 5 && h_prime <= 6){
    //std::cout << h_prime << ": " << chroma << " " << x << std::endl;
    r = x;
    b = chroma;
  }

  // else h == NAN, so do nothing

  r = std::round(255*(r+m));
  g = std::round(255*(g+m));
  b = std::round(255*(b+m));
}
