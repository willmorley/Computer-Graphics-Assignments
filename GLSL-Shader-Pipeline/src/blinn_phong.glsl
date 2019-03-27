// Compute Blinn-Phong Shading given a material specification, a point on a
// surface and a light direction. Assume the light is white and has a low
// ambient intensity.
//
// Inputs:
//   ka  rgb ambient colour
//   kd  rgb diffuse colour
//   ks  rgb specular colour
//   p  specular exponent (shininess)
//   n  unit surface normal direction
//   v  unit direction from point on object to eye
//   l  unit light direction
// Returns rgb colour
vec3 blinn_phong(
  vec3 ka,
  vec3 kd,
  vec3 ks,
  float p,
  vec3 n,
  vec3 v,
  vec3 l)
{
  vec3 half_vec = (l + v) / length(l + v);
  vec3 spec = ks * pow(max(0, dot(n, half_vec)), p);
  vec3 ambient = ka;
  vec3 diff = kd * max(0, dot(n, l));

  vec3 colour = ambient + diff + spec;
  return colour;
}


