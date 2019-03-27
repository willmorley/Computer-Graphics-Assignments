#include "over.h"

// Porter Duff over operator from Wikipedia's Alpha Compositing article
// https://en.wikipedia.org/wiki/Alpha_compositing

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  int rgb;
  double ca, aa, cb, ab;
  for(int i = 0; i < A.size(); i++){
    rgb = i % 4;
    cb = A[i]/255.0;
    ab = A[i + 3-rgb]/255.0;
    ca = B[i]/255.0;
    aa = B[i + 3-rgb]/255.0;
    if(rgb != 3){
      // colour pixel update
      C[i] = static_cast<unsigned char>(
                      255 * ((cb * ab + ca * aa * (1 - ab))
                            / (ab + aa * (1 - ab))));
    }
    else{
      // alpha update
      C[i] = static_cast<unsigned char>(255 * (ab + (aa * (1 - ab))));
    }
  }
}
