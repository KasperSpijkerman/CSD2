#pragma once

#include <JuceHeader.h>
#include "GeneralComponent.h"
#include "myLookAndFeel.h"
class DelayComponent : public GeneralComponent
{
public:
    DelayComponent(juce::AudioProcessorValueTreeState& apvts,
                   juce::String dWLid,
                   juce::String dwRid,
                   juce::String dWCid,
                   juce::String fbLid,
                   juce::String fbRid,
                   juce::String fbCid,
                   juce::String dtLid,
                   juce::String dtRid,
                   juce::String dtCid);
    ~DelayComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment Attachment;
    // custom knobs
    knobsLookAndFeel delayknobsDW;
    knobsLookAndFeel delayknobsFB;
    knobsLookAndFeel delayknobsDT;
    //creating the sliders with labels for parameter control
    // dry wet L
    juce::Slider drywetLSlider;
    juce::Label  drywetLLabel{"drywetL", "Mix L"};
    std::unique_ptr<Attachment> drywetLSliderAttachment;
    // dry wet R
    juce::Slider drywetRSlider;
    juce::Label  drywetRLabel{"drywetR", "Mix R"};
    std::unique_ptr<Attachment> drywetRSliderAttachment;
    // dry wet C
    juce::Slider drywetCSlider;
    juce::Label  drywetCLabel{"drywetC", "Mix C"};
    std::unique_ptr<Attachment> drywetCSliderAttachment;
    // feedback L
    juce::Slider feedbackLSlider;
    juce::Label  feedbackLLabel{"feedbackR", "FB L"};
    std::unique_ptr<Attachment> feedbackLSliderAttachment;
    // feedback R
    juce::Slider feedbackRSlider;
    juce::Label  feedbackRLabel{"feedbackR", "FB R"};
    std::unique_ptr<Attachment> feedbackRSliderAttachment;
    // feedback C
    juce::Slider feedbackCSlider;
    juce::Label  feedbackCLabel{"feedbackC", "FB C"};
    std::unique_ptr<Attachment> feedbackCSliderAttachment;
    // delaytime L
    juce::Slider delayTimeLSlider;
    juce::Label  delayTimeLLabel{"delaytimeL", "Time L"};
    std::unique_ptr<Attachment> delayTimeLSliderAttachment;
    // delaytime R
    juce::Slider delayTimeRSlider;
    juce::Label  delayTimeRLabel{"delaytimeR", "Time R"};
    std::unique_ptr<Attachment> delayTimeRSliderAttachment;
    // delaytime C
    juce::Slider delayTimeCSlider;
    juce::Label  delayTimeCLabel{"delaytimeC", "Time C"};
    std::unique_ptr<Attachment> delayTimeCSliderAttachment;
private:

    Image background;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};




