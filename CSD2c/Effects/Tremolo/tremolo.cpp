#include "effect.h"
#include "sine.h"
#include "tremolo.h"

void Tremolo::prepareToPlay (double sampleRate) {
    osc.prepareToPlay (sampleRate);
}

float Tremolo::output (float input) {
    auto modSignal = osc.output();
    modSignal *= amp;
    modSignal += 1.0f - amp;
    return input * modSignal;
}

void Tremolo::setAmplitude (float amplitude) {
    amp = amplitude;
}

void Tremolo::setRate (float rate) {
    osc.setDelta (rate);
}
