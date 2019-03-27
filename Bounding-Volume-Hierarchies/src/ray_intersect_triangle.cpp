#include "ray_intersect_triangle.h"
#include <Eigen/Geometry>

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  t = 0;

  Eigen::Vector3d edge1 = B - A;
  Eigen::Vector3d edge2 = C - A;

  // Using Crammer's rule, solve the system of equations for t, alpha, and beta
  Eigen::Vector3d pdir = ray.direction.cross(edge2);
  double determinant = edge1.dot(pdir);

  // if determinant is 0, plane is parallel and therefore never intersect
  if(std::abs(determinant) < 1e-5) return false;

  // Check coefficient constraints (alpha, beta < 0 && alpha + beta < 1)
  Eigen::Vector3d tdir = ray.origin.transpose() - A;
  double alpha = tdir.dot(pdir) / determinant;
  if (alpha < 0 || alpha > 1) return false;

  Eigen::Vector3d qdir = tdir.cross(edge1);
  double beta = ray.direction.dot(qdir) / determinant;
  if(beta < 0 || alpha + beta > 1) return false;

  // if satisfied, the ray intersects the triangle, so calculate t and n and return
  t = edge2.dot(qdir) / determinant;
  if(t < min_t || t > max_t) return false;

  return true;
}
