#include "sine.h"
#include "math.h"

Sine::Sine(float frequency, float amplitude) : Oscillator(frequency, amplitude)
{
}

void Sine::calculate()
{
sample = sin(M_PI * 2 * phase) * amplitude;
}

