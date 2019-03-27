#include "blinn_phong_shading.h"
#include <algorithm>
#include "first_hit.h"
#include <cmath>
#include "Sphere.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Object.h"
#include "Light.h"

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id,
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  Eigen::Vector3d rgb = Eigen::Vector3d(0, 0, 0);

  Eigen::Vector3d half;
  Eigen::Vector3d dir;
  Eigen::Vector3d lamb;
  Eigen::Vector3d spec;
  Eigen::Vector3d norm_check;

  Eigen::Vector3d point = ray.origin + t * ray.direction;
  double max_t;
  Ray check;
  check.origin = point;
  int hit_check;
  double t_check;

  // set ambient component
  rgb += ((objects[hit_id]->material->ka).array() * 0.1).matrix();


  for(auto & light : lights){
    // Check for shadow from light source
    light->direction(point, dir, max_t);
    check.direction = dir;

    if(first_hit(check, 1e-6, objects, hit_check, t_check, norm_check)){
        if(t_check < max_t) continue;
    }

    // Calc half vector
    half = (-ray.direction.normalized() + dir).normalized();

    // Calc Lambertian
    rgb += (((objects[hit_id]->material->kd).array() * std::max(0.0, n.dot(dir)))
                    * (light->I).array()).matrix();

    // Calc Specular
    double exp = objects[hit_id]->material->phong_exponent;
    Eigen::Vector3d temp = Eigen::Vector3d(
            objects[hit_id]->material->ks[0] * std::pow(std::max(0.0, n.dot(half)), exp),
            objects[hit_id]->material->ks[1] * std::pow(std::max(0.0, n.dot(half)), exp),
            objects[hit_id]->material->ks[2] * std::pow(std::max(0.0, n.dot(half)), exp));

    rgb += (temp.array() * (light->I).array()).matrix();
  }

  return rgb;
}

#ifdef TEST
#include "catch.hpp"
TEST_CASE( "Testing shading model", "[shading]" ){

    Ray ray;
    ray.origin = Eigen::Vector3d(0, 0, -1);
    ray.direction = Eigen::Vector3d(0, 0, 1);

    std::vector< std::shared_ptr<Object> > objects;
    std::vector< std::shared_ptr<Light> > lights;

    objects.clear();
    std::shared_ptr<Sphere> sphere(new Sphere());
    sphere->center = Eigen::Vector3d(0, 0, 1);
    sphere->radius = 1.0;
    objects.push_back(sphere);
    int hit_id;
    double t;
    Eigen::Vector3d normal;
    first_hit(ray, 1.0, objects, hit_id, t, normal);

/*    SECTION( "test directional light" ){
        lights.clear();
        std::shared_ptr<DirectionalLight> light(new DirectionalLight());
        light->d = Eigen::Vector3d(0, -2, 0);
        light->I = Eigen::Vector3d(0.2, 0.1, 0.4);
        lights.push_back(light);
        Eigen::Vector3d color = blinn_phong_shading(ray, 0, t, normal, objects, lights);
        Eigen::Vector3d expected = Eigen::Vector3d(0, 0, 0);
        REQUIRE(std::abs(color[0] - expected[0]) < 1e-5);
        REQUIRE(std::abs(color[1] - expected[1]) < 1e-5);
        REQUIRE(std::abs(color[2] - expected[2]) < 1e-5);
    }
    SECTION( "test point light" ){
        lights.clear();
        std::shared_ptr<PointLight> light(new PointLight());
        light->p = Eigen::Vector3d(2, 2, 2);
        light->I = Eigen::Vector3d(0, 0, 0);
        lights.push_back(light);
        Eigen::Vector3d color = blinn_phong_shading(ray, 0, t, normal, objects, lights);
        Eigen::Vector3d expected = Eigen::Vector3d(0, 0, 0);
        REQUIRE(std::abs(color[0] - expected[0]) < 1e-5);
        REQUIRE(std::abs(color[1] - expected[1]) < 1e-5);
        REQUIRE(std::abs(color[2] - expected[2]) < 1e-5);
    }
 */   SECTION( "test object blocking light source" ){

    }
    SECTION( "test ambient light" ){

    }
    SECTION( "test lambertian light" ){

    }
    SECTION( "test specular light" ){
        lights.clear();
        std::shared_ptr<DirectionalLight> light(new DirectionalLight());
        light->d = Eigen::Vector3d(0, 0, 1);
        light->I = Eigen::Vector3d(0.8, 0.8, 0.8);
        lights.push_back(light);

        std::shared_ptr<Material> material(new Material());
        material->ka = Eigen::Vector3d(0, 0, 0);
        material->kd = Eigen::Vector3d(0, 0, 0);
        material->ks = Eigen::Vector3d(0.8, 0, 0);
        material->km = Eigen::Vector3d(0, 0, 0);
        material->phong_exponent = 1000.0;
        objects[0]->material = material;
        Eigen::Vector3d rgb = blinn_phong_shading(ray, hit_id, t, normal, objects, lights);
        Eigen::Vector3d expected = Eigen::Vector3d(0.64, 0, 0);
        REQUIRE(std::abs(rgb[0] - expected[0]) < 1e-4);
    }
}
#endif
