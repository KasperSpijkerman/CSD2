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
    //creating the sliders with labels for parameter control
    // dry wet L
    juce::Slider drywetLSlider;
    juce::Label  drywetLLabel{"drywetL", "Drywet L"};
    std::unique_ptr<Attachment> drywetLSliderAttachment;
    // dry wet R
    juce::Slider drywetRSlider;
    juce::Label  drywetRLabel{"drywetR", "Drywet R"};
    std::unique_ptr<Attachment> drywetRSliderAttachment;
    // dry wet C
    juce::Slider drywetCSlider;
    juce::Label  drywetCLabel{"drywetC", "Drywet C"};
    std::unique_ptr<Attachment> drywetCSliderAttachment;
    // feedback L
    juce::Slider feedbackLSlider;
    juce::Label  feedbackLLabel{"feedbackR", "Feedback L"};
    std::unique_ptr<Attachment> feedbackLSliderAttachment;
    // feedback R
    juce::Slider feedbackRSlider;
    juce::Label  feedbackRLabel{"feedbackR", "Feedback R"};
    std::unique_ptr<Attachment> feedbackRSliderAttachment;
    // feedback C
    juce::Slider feedbackCSlider;
    juce::Label  feedbackCLabel{"feedbackC", "Feedback C"};
    std::unique_ptr<Attachment> feedbackCSliderAttachment;
    // delaytime L
    juce::Slider delayTimeLSlider;
    juce::Label  delayTimeLLabel{"delaytimeL", "Delay time L"};
    std::unique_ptr<Attachment> delayTimeLSliderAttachment;
    // delaytime R
    juce::Slider delayTimeRSlider;
    juce::Label  delayTimeRLabel{"delaytimeR", "Delay time R"};
    std::unique_ptr<Attachment> delayTimeRSliderAttachment;
    // delaytime C
    juce::Slider delayTimeCSlider;
    juce::Label  delayTimeCLabel{"delaytimeC", "Delay time C"};
    std::unique_ptr<Attachment> delayTimeCSliderAttachment;
private:
    myLookAndFeelV1 delayknobs;
    myLookAndFeelV1 delayknobsDT;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};




