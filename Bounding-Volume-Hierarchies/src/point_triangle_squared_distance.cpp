#include "point_triangle_squared_distance.h"

double point_triangle_squared_distance(
  const Eigen::RowVector3d & query,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  Eigen::RowVector3d & bary)
{
  // precompute relevant values
  // calc args of gradient=0.
  // if inside triangle, return bary coords
  // else calc boundry point
  return 0;
}
