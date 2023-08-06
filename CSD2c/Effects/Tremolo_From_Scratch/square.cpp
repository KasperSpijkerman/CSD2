#include "square.h"
#include "math.h"

Square::Square(float frequency, float amplitude) : Oscillator(frequency, amplitude)
{
#if DEBUG
  std::cout << "Square::Square constructor\n";
#endif
}
void Square::calculate()
{
  sample = amplitude +1.0f;
  if (phase > 0.5)
  {
    sample *= -1.0f;
  }
}