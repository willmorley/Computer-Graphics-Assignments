// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{

  float height;
  float noise = 0.2 * improved_perlin_noise(9 * s);

  if(is_moon){
    height = 0.8 * noise;
  }
  else{
    height = noise;
  }

  return height;
}
