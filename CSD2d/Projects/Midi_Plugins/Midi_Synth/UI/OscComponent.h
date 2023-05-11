#pragma once

#include <JuceHeader.h>

class OscComponent : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts,juce::String wavetypeID, juce::String fmFreqId, juce::String fmDepthId);
    ~OscComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
private:
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;


    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> fmFreqAttachment;
    juce::Label fmFreqlabel {"fmfreq", "FM Freq"};
    std::unique_ptr<Attachment> fmdepthAttachment;
    juce::Label fmDepthlabel {"fmdepth", "FM Depth"};


    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};




