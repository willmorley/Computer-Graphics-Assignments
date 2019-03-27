#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  #ifdef INSIDE_OUT_TRI // NOTE: doesn't work with triangle soup
  // using inside-outside polygon method

  // preload relevant triangle data
  Eigen::Vector3d p0, p1, p2, edge1, edge2, norm;
  p0 = std::get<0>(this->corners);
  p1 = std::get<1>(this->corners);
  p2 = std::get<2>(this->corners);
  edge1 = p1 - p0;
  edge2 = p2 - p0;
  norm = edge1.cross(edge2);

  // Using equation for plane Ax + By + Cz = D
  // and recalling that norm = (A, B, C)
  double D = norm.dot(p0);

  // Check for parallel plane to eliminate potential div by 0 below
  double angle = norm.dot(ray.direction);
  if(std::abs(angle) < 1e-5) return false;

  // Combine with eq'n of ray to find intersection (t)
  t = -(norm.dot(ray.origin) + D) / angle;
  if(t < min_t) return false;

  //////////////////////////////////////////////////////////////////////////////////////
  // Determine if intersection with plane is inside triangle by computing cross product
  // between each edge and the intersection point. If dot product of that with the normal
  // is negative, point lies to the left of that edge and is therefore outside the triangle
  //////////////////////////////////////////////////////////////////////////////////////

  Eigen::Vector3d point = ray.origin + t * ray.direction; // intersection point

  Eigen::Vector3d edge = p1 - p0;
  Eigen::Vector3d lr = point - p0;
  Eigen::Vector3d test = edge.cross(lr);
  if(norm.dot(test) < 0) return false;

  edge = p2 - p1;
  lr = point - p1;
  test = edge.cross(lr);
  if(norm.dot(test) < 0) return false;

  edge = p0 - p2;
  lr = point - p2;
  test = edge.cross(lr);
  if(norm.dot(test) < 0) return false;

  // ray intersects with triangle, so set norm and return
  n = norm.normalized()
  return true;

  #else // NOTE: works with triangle soup
  // Moller-trumbore intersection algorithm

  // Preload relevant triangle data
  Eigen::Vector3d p0, p1, p2, edge1, edge2, pdir;
  p0 = std::get<0>(this->corners);
  p1 = std::get<1>(this->corners);
  p2 = std::get<2>(this->corners);
  edge1 = p1 - p0;
  edge2 = p2 - p0;

  // Using Crammer's rule, solve the system of equations for t, alpha, and beta
  pdir = ray.direction.cross(edge2);
  double determinant = edge1.dot(pdir);

  // if determinant is 0, plane is parallel and therefore never intersect
  if( std::abs(determinant) < 1e-5) return false;

  // Check coefficient constraints (alpha, beta < 0 && alpha + beta < 1)
  Eigen::Vector3d tdir = ray.origin - p0;
  double alpha = tdir.dot(pdir) / determinant;
  if (alpha < 0 || alpha > 1) return false;

  Eigen::Vector3d qdir = tdir.cross(edge1);
  double beta = ray.direction.dot(qdir) / determinant;
  if(beta < 0 || alpha + beta > 1) return false;

  // if satisfied, the ray intersects the triangle, so calculate t and n and return
  t = edge2.dot(qdir) / determinant;
  n = edge1.cross(edge2).normalized();

  return true;
  #endif
}
