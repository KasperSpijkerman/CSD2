
#pragma once

#include <JuceHeader.h>
#include "GeneralComponent.h"
class AdsrComponent : public GeneralComponent
{
public:
    AdsrComponent(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    juce::Slider attackSlider;
    juce::Label  attackLabel;

    juce::Slider decaySlider;
    juce::Label  decayLabel;

    juce::Slider sustainSlider;
    juce::Label  sustainLabel;

    juce::Slider releaseSlider;
    juce::Label  releaseLabel;
private:
    //==============================================================================
    // ADSR Sliders and labels for Parameter control
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderParams(juce::Slider& slider,juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment);

    // attachments for ADSR parameters
    std::unique_ptr<Attachment> attackAttachment;
    std::unique_ptr<Attachment> decayAttachment;
    std::unique_ptr<Attachment> sustainAttachment;
    std::unique_ptr<Attachment> releaseAttachment;
    Image background;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};




