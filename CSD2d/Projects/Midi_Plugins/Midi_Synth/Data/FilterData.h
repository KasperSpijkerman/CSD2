#pragma once
#include <JuceHeader.h>


class FilterData
{
public:
    FilterData();
    ~FilterData();

    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters();
    void reset();
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
};



