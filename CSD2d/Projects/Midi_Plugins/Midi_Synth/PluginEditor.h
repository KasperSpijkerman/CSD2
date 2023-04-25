#pragma once

#include "PluginProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                         public AudioPluginAudioProcessor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void setSliderParams(juce::Slider& slider);

private:


    // ADSR Sliders and labels for Parameter control
    juce::Slider attackSlider;
    juce::Label  attackLabel;

    juce::Slider decaySlider;
    juce::Label  decayLabel;

    juce::Slider sustainSlider;
    juce::Label  sustainLabel;

    juce::Slider releaseSlider;
    juce::Label  releaseLabel;

    // Oscillator combobox select
    juce::ComboBox oscillatorSelect;


    // short
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // attachments for ADSR parameters
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    // attachments for comboBox
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelectAttachment;
    // reference to processor
    AudioPluginAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
