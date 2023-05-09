#pragma once
#include <JuceHeader.h>


class OscData : public juce::dsp::Oscillator<float>
{
public:
    void setWaveType(const int choice);
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setWaveFrequency(const int midiNoteNumber);
    void setFMParams(const float depth, const float frequency);

private:
    // FM Oscillator with frequency and depth
    juce::dsp::Oscillator<float> fmOsc{[](float x) {return  std::sin(x);}};
    float fmMod {0.0f};
    float fmDepth {0.0f};
    int lastMidiNote;
};


