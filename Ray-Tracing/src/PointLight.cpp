#include "PointLight.h"
#include <random>
#include <limits>
#include <iostream>

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
    d = this->p - q;
    max_t = d.norm();
    d.normalize();
}


#ifdef TEST
#include "catch.hpp"
TEST_CASE( "Point light direction works for different query points", "[pointlight]" ) {
    PointLight pointlight;
    pointlight.p = Eigen::Vector3d(5, 2, 9);
    Eigen::Vector3d d;
    double max_t;

    SECTION( "querying from origin works" ){
        Eigen::Vector3d origin = Eigen::Vector3d(0, 0, 0);
        pointlight.direction(origin, d, max_t);
        REQUIRE( d == pointlight.p.normalized());
        REQUIRE( max_t == pointlight.p.norm());
    }

    SECTION( "querying from same point works" ){
        Eigen::Vector3d origin = pointlight.p;
        pointlight.direction(origin, d, max_t);
        REQUIRE( d == Eigen::Vector3d(0, 0, 0) );
        REQUIRE( max_t == 0);
    }

    SECTION( "querying from random point works" ){
        int x, y, z;
        x = (rand() % 20) - 10;
        y = (rand() % 20) - 10;
        z = (rand() % 20) - 10;
        //std::cout << x << " " << y << " " << z << std::endl;
        Eigen::Vector3d origin = Eigen::Vector3d(x, y, z);
        pointlight.direction(origin, d, max_t);
        //REQUIRE( d == pointlight.p-origin ); // needs to be normalized
    }

    /*
    SECTION( "pointlight works at infinity" ){
        Eigen::Vector3d origin = Eigen::Vector3d(1, 2, 3);
        PointLight infLight;

        SECTION( "x is infinity" ){
            infLight.p = Eigen::Vector3d(std::numeric_limits<double>::infinity(), 4, 3);
            infLight.direction(origin, d, max_t);
            //REQUIRE( d == Eigen::Vector3d(0, 0, 0));
            //REQUIRE( max_t == std::numeric_limits<double>::infinity());
        }
    }
    */
}
#endif
