#pragma once

#include <JuceHeader.h>
#include "GeneralComponent.h"
#include "myLookAndFeel.h"
class OscComponent : public GeneralComponent
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts,
                               juce::String wavetypeID,
                               juce::String wavetypeID2,
                               juce::String wavetypeID3,
                               juce::String fmFreqId,
                               juce::String fmDepthId,
                               juce::String volumeID1,
                               juce::String volumeID2,
                               juce::String volumeID3);
    ~OscComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    // custrom knobs
    knobsLookAndFeel fmknobs;
    labelLookAndFeel labelLookAndFeel;
    boxLookAndFeel boxLookAndFeel;
    // sliders
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    // volume sliders per oscillator
    juce::Slider oscVolumeSlider1;
    juce::Slider oscVolumeSlider2;
    juce::Slider oscVolumeSlider3;
    // oscillator selection boxes
    juce::ComboBox oscWaveSelector;
    juce::ComboBox oscWaveSelector2;
    juce::ComboBox oscWaveSelector3;

    // Oscillator note offset sliders
    juce::Slider oscNoteOffsetSlider1;
    juce::Slider oscNoteOffsetSlider2;
    juce::Slider oscNoteOffsetSlider3;


private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // labels
    juce::Label fmFreqlabel {"fmfreq", "Mod Speed"};
    juce::Label fmDepthlabel {"fmdepth", "Mod Depth"};
    juce::Label oscVolumeLabel1 {"oscvol1", "Lvl 1"};
    juce::Label oscVolumeLabel2 {"oscvol2", "Lvl 2"};
    juce::Label oscVolumeLabel3 {"oscvol3", "Lvl 3"};
    // Labels for the sliders
    juce::Label oscNoteOffsetLabel1;
    juce::Label oscNoteOffsetLabel2;
    juce::Label oscNoteOffsetLabel3;
    // attachments
    std::unique_ptr<Attachment> fmFreqAttachment;
    std::unique_ptr<Attachment> fmdepthAttachment;

    // 3 attachments per oscillator
    std::unique_ptr<Attachment> oscVolumeAttachment1;
    std::unique_ptr<Attachment> oscVolumeAttachment2;
    std::unique_ptr<Attachment> oscVolumeAttachment3;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment2;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment3;

    // Slider attachments to link sliders with the corresponding audio parameters
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscNoteOffsetAttachment1;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscNoteOffsetAttachment2;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscNoteOffsetAttachment3;
    // background
    Image background;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};




