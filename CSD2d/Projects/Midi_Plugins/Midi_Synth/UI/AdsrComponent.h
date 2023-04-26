
#pragma once

#include <JuceHeader.h>

class AdsrComponent : public juce::Component
{
public:
    AdsrComponent(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
private:
    //==============================================================================
    // ADSR Sliders and labels for Parameter control
    void setSliderParams(juce::Slider& slider);

    juce::Slider attackSlider;
    juce::Label  attackLabel;

    juce::Slider decaySlider;
    juce::Label  decayLabel;

    juce::Slider sustainSlider;
    juce::Label  sustainLabel;

    juce::Slider releaseSlider;
    juce::Label  releaseLabel;

    // short
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // attachments for ADSR parameters
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};




