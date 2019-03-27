#include "sphere.h"
#include <iostream>
#include <math.h>
#include <Eigen/Geometry>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  // add vertex data
  V.resize(num_faces_u * (num_faces_v - 1) + 2, 3);
  UV.resize((1 + num_faces_u) * (num_faces_v - 1) + 2, 2);
  NV.resize(num_faces_u * (num_faces_v - 1) + 2, 3);

  V.row(0) << 0, 1, 0;
  UV.row(0) << 0.5, 1;

  double increment = M_PI/num_faces_v; // size of latitude jump each line
  double long_inc = 2*M_PI / num_faces_u;
  int row = 1;
  int u_row = 1;

  for(int i = num_faces_v/2.0 - increment; i > -num_faces_v/2.0 + increment; i--){
    // calc parallel coord
    double lat = i * increment;
    bool first = false;
    double final_v;
    for(int j = num_faces_u/2.0; j > -num_faces_u/2.0; j--){
        // calc meridian coord
        double lon = j * long_inc;
        double z = cos(lat) * cos(lon);
        double x = cos(lat) * sin(lon);
        double y = sin(lat);
        V.row(row) << x, y, z;

        // calc uv coord
        double u = atan2(x, z) / (2*M_PI) + 0.5;
        double v = y * 0.5 + 0.5;
        UV.row(u_row) << u, v;

        final_v = v;
        row++;
        u_row++;
    }
    UV.row(u_row++) << 0, final_v;
  }
  V.row(row) << 0, -1, 0;
  UV.row(row) << 0.5, 0;

  // Add face data
  int end = num_faces_u * num_faces_v;
  int last_V = num_faces_u * (num_faces_v - 1) + 1;
  int last_U = (num_faces_u+1) * (num_faces_v - 1) + 1;

  F.resize(end, 4);
  UF.resize(end, 4);
  NF.resize(end, 4);

  int depth = 0;
  row = 0;

  for(int i = 0; i < num_faces_v; i++){
    for(int j = 1; j <= num_faces_u; j++){
        F.row(row) << ((i==0)?0:((i-1)*num_faces_u + j)),
                        ((i==num_faces_v-1)?last_V:i*num_faces_u + j),
                        ((i==num_faces_v-1)?last_V:((j==num_faces_u)?
                                i*num_faces_u + 1:i*num_faces_u + j+1)),
                        ((i==0)?0:((j==num_faces_u)?
                                (i-1)*num_faces_u + 1:(i-1)*num_faces_u + j + 1));

        UF.row(row++) << ((i==0)?0:((i-1)*(num_faces_u+1) + j)),
                        ((i==num_faces_v-1)?last_U:i*(num_faces_u+1) + j),
                        ((i==num_faces_v-1)?last_U:i*(num_faces_u+1) + j + 1),
                        ((i==0)?0:(i-1)*(num_faces_u+1) + j+ 1);
    }
  }

  NV = V.normalized();
  NF = F;
}
