#pragma once
#include <JuceHeader.h>
#include "Synth_Sound.h"

class Synth_Voice : public juce::SynthesiserVoice
{
public:
    // inheriting functions from synthesizer voice class from JUCE
    bool canPlaySound (SynthesiserSound *) override;
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    // function updatind ADSR
    void updateADSR(const float attack, const float decay, const float sustain, const float release);


private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    // buffer for synth to avoid clicks
    juce::AudioBuffer<float> synthBuffer;
    juce::dsp::Oscillator<float> osc {  [](float x) {return sin(x);} };
    juce::dsp::Gain<float> gain;
    bool isPrepared {false};

};



