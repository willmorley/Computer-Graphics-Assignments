// Generate a pseudorandom unit 3D vector
//
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
  vec2 rand1 = random2(4 * seed);
  vec2 rand2 = random2(seed);
  vec2 rand3 = random2(2 * seed);
  vec3 rand = vec3(rand1.x, rand2.y, rand3.y);
  rand = normalize(rand);
  return rand;
}
