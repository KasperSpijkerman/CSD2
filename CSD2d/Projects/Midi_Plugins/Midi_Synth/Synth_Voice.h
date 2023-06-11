#pragma once
#include <JuceHeader.h>
#include "Synth_Sound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"
// A lot of this is from this tutorial and JUCE reference : https://www.youtube.com/watch?v=ADG6Rsd3ekg&list=PLLgJJsrdwhPwJimt5vtHtNmu63OucmPck
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
    void updateParameters(const float attack, const float decay, const float sustain, const float release);
    // returning oscillator object
    OscData& getOscillator() { return osc; }
private:
    // ADSR object
    AdsrData adsr;
    // buffer for synth to avoid clicks
    juce::AudioBuffer<float> synthBuffer;
    // Oscillator object
    OscData osc;
    juce::dsp::Gain<float> gain;
    bool isPrepared {false};


};



