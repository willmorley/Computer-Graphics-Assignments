#include "Plane.h"
#include "Ray.h"
#include <math.h>

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  // Using parametric equation of plane, calculate intersection
  double denom = this->normal.dot(ray.direction);

  if(std::abs(denom) > 1e-5){
    double num = this->normal.dot(this->point - ray.origin);
    t = num / denom;
    if(t >= min_t){
        n = this->normal;
        return true;
    }
  }

  // Note: if denominator = 0, ray runs parallel or along plane and so does not intersect
  return false;
}

