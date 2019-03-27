#include "first_hit.h"

bool first_hit(
  const Ray & ray,
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id,
  double & t,
  Eigen::Vector3d & n)
{
  double temp_t = 0;
  t = 0;
  Eigen::Vector3d temp_n;
  unsigned i = 0;
  bool hit = false;

  for(const auto & ob : objects){
    if(ob->intersect(ray, min_t, temp_t, temp_n)){
        if(temp_t < t || t == 0){
            t = temp_t;
            n = temp_n;
            hit_id = i;
            hit = true;
        }
    }
    i++;
  }

  return hit;
}
