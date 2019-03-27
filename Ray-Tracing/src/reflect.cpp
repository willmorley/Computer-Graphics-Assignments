#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  // Assumming n is normalized
  return -(in.dot(n)) * n + (in - (in.dot(n)) * n);

  // What about case where in is more than 90 deg from n?
  // for now its undefined
}

#ifdef TEST
#include "catch.hpp"
TEST_CASE( "reflects across normal", "[reflect]" ){
    SECTION( "test 1" ){
        Eigen::Vector3d in = Eigen::Vector3d(1, -1, 0);
        Eigen::Vector3d n = Eigen::Vector3d(0, 1, 0).normalized();
        Eigen::Vector3d out = reflect(in, n);
        REQUIRE( out[0] == 1 );
        REQUIRE( out[1] == 1 );
        REQUIRE( out[2] == 0 );
    }
    SECTION( "test 2" ){
        Eigen::Vector3d in = Eigen::Vector3d(0, 0, 1);
        Eigen::Vector3d n = Eigen::Vector3d(0, 1, -1).normalized();
        Eigen::Vector3d out = reflect(in, n);
        REQUIRE( out[0] == 0 );
        REQUIRE( std::abs(out[1] - 1) < 1e-5);
        REQUIRE( std::abs(out[2] - 0) < 1e-5);
    }
    SECTION( "test 3" ){
        Eigen::Vector3d in = Eigen::Vector3d(0, -1, 0);
        Eigen::Vector3d n = Eigen::Vector3d(1, 1, 0).normalized();
        Eigen::Vector3d out = reflect(in, n);
        REQUIRE( std::abs(out[0] - 1) < 1e-5);
        REQUIRE( std::abs(out[1] - 0) < 1e-5);
        REQUIRE( std::abs(out[2] - 0) < 1e-5);
    }
    SECTION( "test 4" ){
        Eigen::Vector3d in = Eigen::Vector3d(10, -1, 0);
        Eigen::Vector3d n = Eigen::Vector3d(0, 1, 0).normalized();
        Eigen::Vector3d out = reflect(in, n);
        REQUIRE( out[0] == 10 );
        REQUIRE( out[1] == 1 );
        REQUIRE( out[2] == 0 );
    }

}
#endif
