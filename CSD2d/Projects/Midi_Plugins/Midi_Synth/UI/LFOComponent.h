#pragma once

#include <JuceHeader.h>

class LFOComponent : public juce::Component
{
public:
    LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String LFOFreqId, juce::String LFODepthId);
    ~LFOComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
private:
    // Freq & Depth
    juce::Slider LFOFreqSlider;
    juce::Slider LFODepthSlider;
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> LFOFreqAttachment;
    juce::Label LFOFreqlabel {"LFOFreq", "Freq"};
    std::unique_ptr<Attachment> LFODepthAttachment;
    juce::Label LFODepthlabel {"LFODepth", "Depth"};


    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComponent)
};




