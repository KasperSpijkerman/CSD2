#pragma once

#include <JuceHeader.h>
#include "GeneralComponent.h"
#include "myLookAndFeel.h"
class OscComponent : public GeneralComponent
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts,juce::String wavetypeID, juce::String fmFreqId, juce::String fmDepthId);
    ~OscComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    knobsLookAndFeel fmknobs;
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    juce::ComboBox oscWaveSelector;
private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    juce::Label fmFreqlabel {"fmfreq", "Mod Speed"};
    juce::Label fmDepthlabel {"fmdepth", "Mod Depth"};
    std::unique_ptr<Attachment> fmFreqAttachment;
    std::unique_ptr<Attachment> fmdepthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;


    Image background;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};




