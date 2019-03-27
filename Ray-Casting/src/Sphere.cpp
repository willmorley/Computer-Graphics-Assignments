#include "Sphere.h"
#include "Ray.h"
#include <cmath>
#include <math.h>
#include <iostream>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  // Using parametric equation of sphere, determine if there is a t that intersects
  // If 2, return smaller t.

  // Using quadratic formula to solve for real roots of at^2 + bt + c = 0
  Eigen::Vector3d line = ray.origin - this->center;// - ray.direction;
  double a = ray.direction.dot(ray.direction);
  double b = 2*ray.direction.dot(line);//ray.origin);
  double c = line.dot(line) - std::pow(this->radius, 2);
  double disc = std::pow(b, 2) - (4 * a * c);

  // Calculate appropriate t if intersection occurs
  if(disc < 0){
    // No intersection
    return false;
  }
  else if (disc > 0){
    // 2 intersections, choose smaller value of t
    t = (-b - std::sqrt(disc)) / (2 * a);
    if(t < min_t)
        t = (-b + std::sqrt(disc)) / (2 * a);
  }
  else{
    // 1 intersection
    t = - b / 2*a ;
  }

  // If t is far enough away from origin of ray, set normal and return true
  if( t >= min_t){
    n = (ray.origin + t * ray.direction) - this->center;
    n.normalize();
    return true;
  }

  return false;
}

