#pragma once

#include <JuceHeader.h>
#include "GeneralComponent.h"
#include "myLookAndFeel.h"
class LFOComponent : public GeneralComponent
{
public:
    LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String LFOFreqId, juce::String LFODepthId);
    ~LFOComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    knobsLookAndFeel lfofreqknob;
    knobsLookAndFeel lfodepthknob;
    // Freq & Depth
    juce::Slider LFOFreqSlider;
    juce::Slider LFODepthSlider;
private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // labels
    juce::Label LFOFreqlabel {"LFOFreq", "Speed"};
    juce::Label LFODepthlabel {"LFODepth", "Intensity"};
    std::unique_ptr<Attachment> LFOFreqAttachment;
    std::unique_ptr<Attachment> LFODepthAttachment;
    // background
    Image background;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComponent)
};




