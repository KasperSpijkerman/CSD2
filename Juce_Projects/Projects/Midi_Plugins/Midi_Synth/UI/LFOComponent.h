#pragma once

#include <JuceHeader.h>
#include "GeneralComponent.h"
#include "myLookAndFeel.h"
class LFOComponent : public GeneralComponent
{
public:
    LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String LFOFreqId, juce::String LFODepthId,juce::String bpmId);
    ~LFOComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    knobsLookAndFeel lfofreqknob;
    knobsLookAndFeel lfodepthknob;
    labelLookAndFeel labelLookAndFeel;
    // Freq & Depth
    juce::Slider LFOFreqSlider;
    juce::Slider LFODepthSlider;
    juce::Slider bpmSlider;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // labels
    juce::Label LFOFreqlabel {"LFOFreq", "Speed"};
    juce::Label LFODepthlabel {"LFODepth", "Intensity"};
    juce::Label bpmLabel {"bpm", "BPM"};
    std::unique_ptr<Attachment> LFOFreqAttachment;
    std::unique_ptr<Attachment> LFODepthAttachment;
    std::unique_ptr<Attachment> bpmAttachment;
    // LFO Sync
    juce::ToggleButton bpmSyncButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bpmSyncAttachment;
    // background
    Image background;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComponent)
};




