// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
//
// algorithm based on definitions at:
// https://en.wikipedia.org/wiki/Perlin_noise
float perlin_noise( vec3 st)
{
  ////////////////////
  //1. Grid Definition
  ////////////////////

  //split into integer and fractional parts
  vec3 i = floor(st);
  vec3 f = fract(st);

  //setup unit cube around point st
  vec3 x0_y0_z0 = i;
  vec3 x1_y0_z0 = vec3(1 + i.x, i.y, i.z);
  vec3 x0_y1_z0 = vec3(i.x, 1 + i.y, i.z);
  vec3 x0_y0_z1 = vec3(i.x, i.y, 1 + i.z);
  vec3 x1_y1_z0 = vec3(1 + i.x, 1 + i.y, i.z);
  vec3 x1_y0_z1 = vec3(1 + i.x, i.y, 1 + i.z);
  vec3 x0_y1_z1 = vec3(i.x, 1 + i.y, 1 + i.z);
  vec3 x1_y1_z1 = i + vec3(1);

  //////////////////////////////////////////////////
  //2. Gradients, dot products, and distance vectors
  //////////////////////////////////////////////////

  //pseudorandom gradients at each corner
  vec3 grad1 = random_direction(x0_y0_z0);
  vec3 grad2 = random_direction(x1_y0_z0);
  vec3 grad3 = random_direction(x0_y1_z0);
  vec3 grad4 = random_direction(x0_y0_z1);
  vec3 grad5 = random_direction(x1_y1_z0);
  vec3 grad6 = random_direction(x1_y0_z1);
  vec3 grad7 = random_direction(x0_y1_z1);
  vec3 grad8 = random_direction(x1_y1_z1);

  //distance from point to grid coords
  vec3 dist_0_0_0 = f;
  vec3 dist_1_0_0 = vec3(1 - f.x, f.y, f.z);
  vec3 dist_0_1_0 = vec3(f.x, 1 - f.y, f.z);
  vec3 dist_0_0_1 = vec3(1 + f.x, f.y, 1 - f.z);
  vec3 dist_1_1_0 = vec3(1 - f.x, 1 - f.y, f.z);
  vec3 dist_1_0_1 = vec3(1 - f.x, f.y, 1 - f.z);
  vec3 dist_0_1_1 = vec3(f.x, 1 - f.y, 1 - f.z);
  vec3 dist_1_1_1 = f - vec3(1);

  //dot product between grad and dist
  float d1 = dot(grad1, dist_0_0_0);
  float d2 = dot(grad2, dist_1_0_0);
  float d3 = dot(grad3, dist_0_1_0);
  float d4 = dot(grad4, dist_0_0_1);
  float d5 = dot(grad5, dist_1_1_0);
  float d6 = dot(grad6, dist_1_0_1);
  float d7 = dot(grad7, dist_0_1_1);
  float d8 = dot(grad8, dist_1_1_1);

  //////////////////
  //3. Interpolation
  //////////////////

  vec3 smoothed = smooth_step(f);

  float interp1x = mix(d1, d2, smoothed.x);
  float interp2x = mix(d3, d4, smoothed.x);
  float interp3x = mix(d5, d6, smoothed.x);
  float interp4x = mix(d7, d8, smoothed.x);
  float interp1y = mix(interp1x, interp2x, smoothed.y);
  float interp2y = mix(interp3x, interp4x, smoothed.y);
  float interp1z = mix(interp1y, interp2y, smoothed.z);



  return 2 * interp1z - 1;
}

