#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");

  // Open file and fstream
  std::ofstream file;
  file.open(filename, std::ios::trunc);
  if(!file.is_open())   // ensure file opened
    return false;

  // list vertices
  for(int i = 0; i < V.rows(); i++){
    file << "v " << V.row(i) << "\n";
  }

  // list 2D vertices
  for(int i = 0; i < UV.rows(); i++)
    file << "vt " << UV.row(i) << "\n";

  // list normal vectors
  for(int i = 0; i < NV.rows(); i++)
    file << "vn " << NV.row(i) << "\n";

  // list faces
  for(int i = 0; i < F.rows(); i++){
    file << "f ";
    for(int j = 0; j < 4; j++)
#if 0
        file << F.row(i)[j] + 1 << "/" << UF.row(i)[j] + 1 << "/" << NF.row(i)[j] + 1 << " ";
#else
        file << F.row(i)[j] + 1 << " ";
#endif
    file << "\n";
  }

  file.close(); //TODO: test for success
  return true;
}
