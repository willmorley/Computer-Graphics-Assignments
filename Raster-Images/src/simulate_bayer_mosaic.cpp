#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);

  int colour = 2;
  for(auto y = 0; y < height; y++){
    for(auto x = 0; x < width; x++){
        bayer[x + width*y] = rgb[colour + 3*(x + width*y)];
        if(y % 2 == 0){ // even  lines
            if(colour == 2) colour = 1;
            else colour = 2;
        }
        else{ // odd lines
            if(colour == 1) colour = 0;
            else colour = 1;
        }
    }
    if(y % 2 == 0) colour = 1;
    else colour = 2;
  }
}
