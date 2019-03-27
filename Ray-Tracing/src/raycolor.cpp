#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include "Sphere.h"
#include "PointLight.h"

bool raycolor(
  const Ray & ray,
  const double min_t, // should be sent in 1.0 for initial call
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  rgb = Eigen::Vector3d(0,0,0);

  int hit_id;
  double t;
  Eigen::Vector3d normal;

  // put this in loop,
  if(first_hit(ray, min_t, objects, hit_id, t, normal) && num_recursive_calls < 5){ // 10 = max_depth
    // find ray colour using blinn_phong
    rgb += blinn_phong_shading(ray, hit_id, t, normal, objects, lights);

    if(objects[hit_id]->material->km[0] > 1e-5
    && objects[hit_id]->material->km[1] > 1e-5
    && objects[hit_id]->material->km[2] > 1e-5){
        // Generate reflected ray
        Ray ray_reflect;
        ray_reflect.direction = reflect(ray.direction, normal.normalized());
        ray_reflect.origin = ray.origin + t * ray.direction;
        // Generate refracted ray
        //Ray ray_refract;

        // recursively call raycolor
        Eigen::Vector3d reflect;
        raycolor(ray_reflect, 1e-4, objects, lights, (num_recursive_calls + 1), reflect);
        rgb += (objects[hit_id]->material->km.array() * reflect.array()).matrix();
        return true;
    }


  }
  else if( num_recursive_calls > 0 )
    return true;

  return false;
}

#ifdef TEST
#include "catch.hpp"
TEST_CASE( "ray loop works", "[raycolor]" ){
    // setup object and ray

    Ray ray;
    ray.origin = Eigen::Vector3d(0, 0.5, -1);
    ray.direction = Eigen::Vector3d(0, 0, 1);

    std::vector< std::shared_ptr<Object> > objects;
    std::vector< std::shared_ptr<Light> > lights;

    objects.clear();
    std::shared_ptr<Sphere> sphere(new Sphere());
    sphere->center = Eigen::Vector3d(0, 0, 1);
    sphere->radius = 1.0;
/*
    sphere->material->ka = Eigen::Vector3d(1, 1, 1);
    sphere->material->kd = Eigen::Vector3d(1, 1, 1);
    sphere->material->ks = Eigen::Vector3d(1, 1, 1);
    sphere->material->km = Eigen::Vector3d(1, 1, 1);
    sphere->material->phong_exponent = 1;
*/
    objects.push_back(sphere);

    lights.clear();
    std::shared_ptr<PointLight> light(new PointLight());
    light->p = Eigen::Vector3d(2, 2, 2);
    light->I = Eigen::Vector3d(0, 0, 0);
    lights.push_back(light);

    std::shared_ptr<Material> material(new Material());
    material->ka = Eigen::Vector3d(0, 0, 0);
    material->kd = Eigen::Vector3d(0, 0, 0);
    material->ks = Eigen::Vector3d(0, 0, 0);
    material->km = Eigen::Vector3d(0, 0, 0);
    material->phong_exponent = 1000.0;
    objects[0]->material = material;

    double min_t = 1.0;
    int count = 0;
    Eigen::Vector3d rgb = Eigen::Vector3d(0, 0, 0);
    REQUIRE(raycolor(ray, min_t, objects, lights, count, rgb) == true);
}

#endif
