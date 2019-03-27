#include "cube.h"
#include "iostream"

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  // Vertices
  V.resize(8,3);
  V <<  -1,  1,  1,
         1,  1,  1,
        -1,  1, -1,
         1,  1, -1,
        -1, -1,  1,
         1, -1,  1,
        -1, -1, -1,
         1, -1, -1;

  // Faces
  F.resize(6,4);
  F <<  1, 3, 2, 0,
        3, 1, 5, 7,
        4, 5, 1, 0,
        6, 4, 0, 2,
        7, 6, 2, 3,
        6, 7, 5, 4;


  // 2D Paramterization Vertices
  UV.resize(14,2);
  UV << 1, 3,
        2, 3,
        0, 2,
        1, 2,
        2, 2,
        3, 2,
        4, 2,
        0, 1,
        1, 1,
        2, 1,
        3, 1,
        4, 1,
        1, 0,
        2, 0;
  UV = (UV.array()/4.0).matrix();

  // 2D Faces
  UF.resize(6,4);
  UF << 12, 13, 9, 8,
        7, 8, 3, 2,
        8, 9, 4, 3,
        9, 10, 5, 4,
        10, 11, 6, 5,
        0, 3, 4, 1;

  // Normal Vectors
  NV.resize(6,3);
  NV << 0, 1, 0,
        1, 0, 0,
        0, 0, 1,
        -1, 0, 0,
        0, 0, -1,
        0, -1, 0;

  NF.resize(6,4);
  NF << 0, 0, 0, 0,
        1, 1, 1, 1,
        2, 2, 2, 2,
        3, 3, 3, 3,
        4, 4, 4, 4,
        5, 5, 5, 5;
}
