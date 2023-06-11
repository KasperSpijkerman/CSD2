#pragma once
#include <JuceHeader.h>
// works together with Synth voice and just exists
class Synth_Sound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override
    {
        return true;
        ignoreUnused(midiNoteNumber);
    }
    bool appliesToChannel (int midiChannel) override
    {
        return true;
        ignoreUnused(midiChannel);
    }
};



