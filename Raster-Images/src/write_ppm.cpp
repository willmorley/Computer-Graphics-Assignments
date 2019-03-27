#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

// .PPM file header structure from wikipedia at:
// https://en.wikipedia.org/wiki/Netpbm_format

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels == 1 ) &&
    ".ppm only supports RGB or grayscale images");

  // Open file and fstream
  std::ofstream file;
  file.open(filename, std::ios::trunc);
  if(!file.is_open())   // ensure file opened
    return false;

  auto size = width*height*num_channels;

  // Write header
  if(num_channels == 1)
    file << "P5\n";
  else
    file << "P6\n";

  file << width << " " << height << "\n" << "255" << std::endl;

  // Write image
  for(auto i = 0; i < size; i++){
    file << data[i];
  }

  // Close file
  file.close();
  return true;
}
