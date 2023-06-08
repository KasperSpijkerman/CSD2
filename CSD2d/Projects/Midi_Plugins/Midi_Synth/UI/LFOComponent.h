#pragma once

#include <JuceHeader.h>

class LFOComponent : public juce::Component
{
public:
    LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String LFOFreqId, juce::String LFODepthId);
    ~LFOComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    // Freq & Depth
    juce::Slider LFOFreqSlider;
    juce::Slider LFODepthSlider;
private:

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    juce::Label LFOFreqlabel {"LFOFreq", "Freq"};
    juce::Label LFODepthlabel {"LFODepth", "Depth"};
    std::unique_ptr<Attachment> LFOFreqAttachment;
    std::unique_ptr<Attachment> LFODepthAttachment;

    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComponent)
};




