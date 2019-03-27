#include "viewing_ray.h"
#include <iostream>

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
    Eigen::Vector3d cam_dir;

    // Calculate ray in camera frame
    cam_dir[0] = -(((width-1)/2.0) - j) * (camera.width/(double)width);   // u
    cam_dir[1] = (((height-1)/2.0) - i) * (camera.height/(double)height); // v
    cam_dir[2] = -camera.d;                                               // w

    // Transform to world frame
    Eigen::Matrix3d cam_to_world;
    cam_to_world << camera.u, camera.v, camera.w;

    ray.direction = cam_to_world * cam_dir;
    ray.origin = camera.e;
}

