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

    void setOscillatorGains(float gain1, float gain2,float gain3);

    void setOscillatorOffsets(float offset1, float offset2,float offset3);
    // returning oscillator object
    OscData& getOscillator1() { return osc; }
    OscData& getOscillator2() { return osc2; }
    OscData& getOscillator3() { return osc3; }
private:
    // ADSR object
    AdsrData adsr;
    // buffer for synth to avoid clicks
    juce::AudioBuffer<float> synthBuffer;
    // Oscillator objects
    OscData osc;
    OscData osc2;
    OscData osc3;
    juce::dsp::Gain<float> gainOsc1;
    juce::dsp::Gain<float> gainOsc2;
    juce::dsp::Gain<float> gainOsc3;

    float osc1GainValue = 0.5f;
    float osc2GainValue = 0.5f;
    float osc3GainValue = 0.5f;

    float offset1osc = 0;
    float offset2osc = 0;
    float offset3osc = 0;
    bool isPrepared {false};


};



