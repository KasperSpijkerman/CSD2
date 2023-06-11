#pragma once

#include <JuceHeader.h>
#include "myLookAndFeel.h"
class ShaperComponent : public juce::Component
{
public:
    ShaperComponent(juce::AudioProcessorValueTreeState& apvts, juce::String ShaperDriveId, juce::String ShaperTrimId);
    ~ShaperComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    // custom knobs
    knobsLookAndFeel drivetrimknob;
    // Drive & Trim
    juce::Slider ShaperDriveSlider;
    juce::Slider ShaperTrimSlider;
private:

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    juce::Label ShaperDrivelabel {"ShaperDrive", "Drive"};
    juce::Label ShaperTrimlabel {"ShaperTrim", "Level"};
    std::unique_ptr<Attachment> ShaperDriveAttachment;
    std::unique_ptr<Attachment> ShaperTrimAttachment;
    // background
    Image background;
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShaperComponent)
};




