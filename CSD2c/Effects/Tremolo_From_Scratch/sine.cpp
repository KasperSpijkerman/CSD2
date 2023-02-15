#include "sine.h"
#include "math.h"

Sine::Sine(float frequency, float amplitude) : Oscillator(frequency, amplitude)
{
#if DEBUG
  std::cout << "Sine::Sine constructor" << frequency << "\n";
#endif
}

float Sine::calculate()
{
  return sin(M_PI * 2 * phase) * amplitude;
}

