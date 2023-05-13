#pragma once

#include <JuceHeader.h>

class ShaperComponent : public juce::Component
{
public:
    ShaperComponent(juce::AudioProcessorValueTreeState& apvts, juce::String ShaperDriveId, juce::String ShaperTrimId);
    ~ShaperComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
private:
    // Drive & Trim
    juce::Slider ShaperDriveSlider;
    juce::Slider ShaperTrimSlider;
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> ShaperDriveAttachment;
    juce::Label ShaperDrivelabel {"ShaperDrive", "Drive"};
    std::unique_ptr<Attachment> ShaperTrimAttachment;
    juce::Label ShaperTrimlabel {"ShaperTrim", "Trim"};


    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShaperComponent)
};




