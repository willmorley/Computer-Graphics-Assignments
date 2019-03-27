#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);

  auto end = (width * num_channels) - num_channels;
  for(auto i = 0; i < height; i++){
    auto first = 0;
    auto last = end;
    while(first <= end && last >= 0){
        for(auto j = 0; j < num_channels; j++)
            reflected[i*width*num_channels + first + j] = input[i*width*num_channels + last + j];
        first += num_channels;
        last -= num_channels;
    }
  }
}
