#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);

  int colour = 2;
  double r, g, b;

  // TODO: add black border around bayer image to prevent problems along edges.


  auto coord = [width](int x, int y){
          return( x + y * width);
  };

  auto naive_interp = [&](int c, int x, int y){
    if(c == 0){ // Red
        r = bayer[coord(x, y)];
        g = bayer[coord(x - 1, y)] + bayer[coord(x + 1, y)]
                + bayer[coord(x, y - 1)] + bayer[coord(x, y + 1)];
        g /= 4;
        b = bayer[coord(x - 1, y - 1)] + bayer[coord(x + 1, y - 1)]
                + bayer[coord(x - 1, y + 1)] + bayer[coord(x + 1, y + 1)];
        b /= 4;
    }
    else if(c == 1){ // Green #1
        r = bayer[coord(x, y - 1)] + bayer[coord(x, y + 1)];
        r /= 2;
        g = bayer[coord(x, y)];
        b = bayer[coord(x - 1, y)] + bayer[coord(x + 1, y)];
        b /= 2;
    }
    else if(c == 2){ // Blue
        r = bayer[coord(x - 1, y - 1)] + bayer[coord(x + 1, y - 1)]
                + bayer[coord(x - 1, y + 1)] + bayer[coord(x + 1, y + 1)];
        r /= 4;
        g = bayer[coord(x - 1, y)] + bayer[coord(x + 1, y)]
                + bayer[coord(x, y - 1)] + bayer[coord(x, y + 1)];
        g /= 4;
        b = bayer[coord(x, y)];
    }
    else{ // colour == 4 (Green #2)
        b = bayer[coord(x, y - 1)] + bayer[coord(x, y + 1)];
        b /= 2;
        g = bayer[coord(x, y)];
        r = bayer[coord(x - 1, y)] + bayer[coord(x + 1, y)];
        r /= 2;
    }
  };

  for(int y = 0; y < height; y++){
    for(int x = 0; x < width; x++){
        // 1. perform relevant interpolation for r, g, b
        naive_interp(colour, x, y);

        // 2. set rgb array to those values
        rgb[0 + 3*coord(x, y)] = static_cast<unsigned char>(r);
        rgb[1 + 3*coord(x, y)] = static_cast<unsigned char>(g);
        rgb[2 + 3*coord(x, y)] = static_cast<unsigned char>(b);

        // 3. update pixel colour
        if(y % 2 == 0){ // even  lines
            if(colour == 2) colour = 1;
            else colour = 2;
        }
        else{ // odd lines
            if(colour == 4) colour = 0;
            else colour = 4;
        }
    }
    if(y % 2 == 0) colour = 4;
    else colour = 2;
  }
}
