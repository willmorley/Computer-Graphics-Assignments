#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  for(auto y = 0; y < height; y++){
    for(auto x = 0; x < width; x++){
        gray[x + width*y] = static_cast<unsigned char>(
                        0.2126 * rgb[0 + 3*(x + width*y)]
                        + 0.7152 * rgb[1 + 3*(x + width*y)]
                        + 0.0722 * rgb[2 + 3*(x + width*y)]
                        );
    }
  }
}


