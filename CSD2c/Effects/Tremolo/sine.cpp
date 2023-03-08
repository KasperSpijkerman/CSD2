#include <cmath>
#include "sine.h"

void Sine::prepareToPlay (double sampleRate) {
    samplerate = sampleRate;
    resetPhase();
    setDelta (8);
}

float Sine::output() {
    phase += delta;
    if (phase > 1.0) phase -= 1.0f;
    return calculate();
}

float Sine::calculate() {
    return sin (phase * pi * 2.0f);
}

void Sine::setDelta (float frequency) {
    currentFrequency = frequency;
    this->delta = currentFrequency / samplerate;
}

double Sine::getFrequency() {
    return currentFrequency;
}

void Sine::resetPhase() {
    phase = 0;
}
