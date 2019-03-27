#include "cube.h"
#include "sphere.h"
#include "write_obj.h"
#include "QuadViewer.h"
#include "set_texture_from_png.h"
#include <igl/readOBJ.h>
#include <Eigen/Core>
#include <vector>
#include <iostream>
#include <memory>
#include <limits>
#include <functional>


int main(int argc, char * argv[])
{
//#if 0
  {
    // Create mesh of a cube
    Eigen::MatrixXd V,UV,NV;
    Eigen::MatrixXi F,UF,NF;
    cube(V,F,UV,UF,NV,NF);
    write_obj("cube.obj",V,F,UV,UF,NV,NF);
    igl::readOBJ("cube.obj",V,UV,NV,F,UF,NF);
    {
      QuadViewer v;
      v.set_mesh(V,F,UV,UF,NV,NF);
      set_texture_from_png("../data/rubiks-cube.png", v.viewer.data());
      v.launch();
    }
  }
//#else
  {
    // Create mesh of a sphere
    Eigen::MatrixXd V,UV,NV;
    Eigen::MatrixXi F,UF,NF;
    sphere(60,40,V,F,UV,UF,NV,NF);
    write_obj("sphere.obj",V,F,UV,UF,NV,NF);
    igl::readOBJ("sphere.obj",V,UV,NV,F,UF,NF);
    {
      QuadViewer v;
      //std::cout << V << std::endl;
      //std::cout << F << std::endl;
      //std::cout << UV << std::endl;
      //std::cout << UF << std::endl;
      //std::cout << NV << std::endl;
      //std::cout << NF << std::endl;
      v.set_mesh(V,F,UV,UF,NV,NF);
      set_texture_from_png("../shared/data/earth-square.png", v.viewer.data());
      v.launch();
    }
  }
//#endif
}
