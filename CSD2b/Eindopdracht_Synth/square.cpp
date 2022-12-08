#include "square.h"
#include "math.h"

Square::Square(float frequency, float samplerate) : Oscillators(frequency,samplerate)
{
  std::cout << "Square - constructor " << frequency << "\n";
}



Square::~Square() {
  std::cout << "Square - destructor\n";
}

void Square::tick() {
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  phase += frequency / samplerate;
  if(phase > 1.0f) {
    phase -= 1.0f;
  }
  if(phase < 0.5f)
  {
  sample = amplitude;
  }
  if(phase > 0.5f)
  {
  sample = -amplitude;
  }


}