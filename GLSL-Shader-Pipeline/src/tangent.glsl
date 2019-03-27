// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  // setup parameters
  float radius = sqrt(N.x * N.x + N.y * N.y + N.z * N.z);
  float theta = acos(N.z/radius);
  float phi = atan(N.y/N.x);

  // From
  T = vec3(1,0,0);
  B = vec3(0,1,0);
}
