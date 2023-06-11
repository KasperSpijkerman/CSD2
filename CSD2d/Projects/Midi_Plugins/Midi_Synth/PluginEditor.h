#pragma once

#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"
#include "UI/LFOComponent.h"
#include "UI/ShaperComponent.h"
#include "UI/ControlComponent.h"
#include "UI/DelayComponent.h"
#include "UI/visualiserComponent.h"

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                         public AudioPluginAudioProcessor,
                                         private juce::Timer
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void updateControlData();

private:
    // Oscillator combobox select
    juce::ComboBox oscillatorSelect;
    // attachment for comboBox
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelectAttachment;
    // reference to processor
    AudioPluginAudioProcessor& audioProcessor;
    // ADSR object UI
    AdsrComponent adsr;
    // oscillator component UI
    OscComponent osc;
    // filter component UI
    FilterComponent filter;
    //LFO component UI
    LFOComponent LFO;
    // Waveshaper UI Component
    ShaperComponent shaper;
    // Control UI
    ControlComponent control;
    // Delay UI
    DelayComponent delay;
    // Visualiser UI
    visualiserComponent visualiser;
    Image background;

    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
