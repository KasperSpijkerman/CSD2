#pragma once

#include "PluginProcessor.h"

//==============================================================================
class LowpassHighpassFilterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit LowpassHighpassFilterAudioProcessorEditor (LowpassHighpassFilterAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~LowpassHighpassFilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LowpassHighpassFilterAudioProcessor& processorRef;
    juce::Slider cutoffFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        cutoffFrequencyAttachment;
    juce::Label cutoffFrequencyLabel;

    juce::ToggleButton highpassButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
    highpassAttachment;
    juce::Label highpassButtonLabel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowpassHighpassFilterAudioProcessorEditor)
};
