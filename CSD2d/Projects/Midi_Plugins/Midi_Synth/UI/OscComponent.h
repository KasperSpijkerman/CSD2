#pragma once

#include <JuceHeader.h>

class OscComponent : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts,juce::String wavetypeID, juce::String fmFreqId, juce::String fmDepthId);
    ~OscComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
private:
    juce::ComboBox oscWaveSelector;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    juce::Label fmFreqlabel {"fmfreq", "FM Freq"};
    juce::Label fmDepthlabel {"fmdepth", "FM Depth"};
    std::unique_ptr<Attachment> fmFreqAttachment;
    std::unique_ptr<Attachment> fmdepthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};




