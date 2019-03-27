// Filter an input value to perform a smooth step. This function should be a
// cubic polynomial with smooth_step(0) = 0, smooth_step(1) = 1, and zero first
// derivatives at f=0 and f=1.
//
// Inputs:
//   f  input value
// Returns filtered output value
float smooth_step( float f)
{
  if(f <= 0)
    return 0;
  else if(f >= 1)
    return 1;

  return (-2*pow(f, 3) + 3*pow(f, 2));
}

vec3 smooth_step( vec3 f)
{
  vec3 ss = vec3(smooth_step(f.x), smooth_step(f.y), smooth_step(f.z));
  return ss;
}
