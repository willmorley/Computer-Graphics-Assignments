#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);

  int new_width = height;
  int new_height = width;
  int new_x, new_y;

  for(size_t y = 0;  y < height; y++){
    new_x = y;
    for(size_t x = 0; x < width; x++){
        new_y = new_height - x - 1;
        for(size_t j = 0; j < num_channels; j++)
            rotated[num_channels*(new_x + new_y * new_width)+ j]
                    = input[num_channels*(x + y * width)+ j];
    }
  }
}
