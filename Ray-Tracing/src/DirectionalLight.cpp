#include "DirectionalLight.h"
#include <limits>
#include <random>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
    max_t = std::numeric_limits<double>::infinity();
    d = -this->d.normalized();
}

#ifdef TEST
#include "catch.hpp"
TEST_CASE( "Directional Light returns same direction for any point", "[dirlight]"){
    DirectionalLight source;
    source.d = Eigen::Vector3d(3, -7, 1);
    int x, y, z;
    x = (int)(rand() % 50) - 24;
    y = (int)(rand() % 50) - 24;
    z = (int)(rand() % 50) - 24;
    Eigen::Vector3d test = Eigen::Vector3d(x, y, z);
    Eigen::Vector3d result;
    double max_t;
    source.direction(test, result, max_t);

    SECTION( "rand 1" ){

        REQUIRE( result == -source.d.normalized());
        REQUIRE( max_t == std::numeric_limits<double>::infinity());

    }

    SECTION( "rand 2" ){

        REQUIRE( result == -source.d.normalized());
        REQUIRE( max_t == std::numeric_limits<double>::infinity());

    }

    SECTION( "rand 3" ){

        REQUIRE( result == -source.d.normalized());
        REQUIRE( max_t == std::numeric_limits<double>::infinity());

    }
}
#endif
