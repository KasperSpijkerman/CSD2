#include "FilterData.h"

void FilterData::prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels)
{
    filter.reset();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    filter.prepare(spec);

    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block { buffer };
    // replacing content in audioblock to filter the played sound
    filter.process(juce::dsp::ProcessContextReplacing<float> {block});
}

void FilterData::updateParameters(const int filterType, const float frequency, const float resonance)
{
    // switching between different filtertypes
    switch (filterType) {
        case 0:
            filter.setType(dsp::StateVariableTPTFilterType::lowpass);
            break;
        case 1:
            filter.setType(dsp::StateVariableTPTFilterType::bandpass);
            break;
        case 2:
            filter.setType(dsp::StateVariableTPTFilterType::highpass);
            break;
    }
    // setting cutoff and resonance
    filter.setCutoffFrequency(frequency);
    filter.setResonance(resonance);
}

void FilterData::reset()
{
    filter.reset();
}
