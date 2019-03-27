#include "rgba_to_rgb.h"
#include <iostream>
#include <algorithm>

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);

  unsigned long long i = 0;
  std::remove_copy_if(rgba.begin(), rgba.end(), rgb.begin(),
                            [&i](unsigned char c){ return(i++ % 4 == 3);}
                            );
}
