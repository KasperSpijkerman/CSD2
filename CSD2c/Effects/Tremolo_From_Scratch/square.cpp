#include "square.h"
#include "math.h"

Square::Square(float frequency, float amplitude) : Oscillator(frequency, amplitude)
{
#if DEBUG
  std::cout << "Square::Square constructor\n";
#endif
}

float Square::calculate()
{
  sample = amplitude;
  if (phase > 0.5)
  {
    sample *= -1.0f;
  }
  return sample;
}