#pragma once

#include <JuceHeader.h>
#include "GeneralComponent.h"
#include "myLookAndFeel.h"
class DelayComponent : public GeneralComponent, public juce::Button::Listener
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
                   juce::String dtCid,
                   juce::String divLid,
                   juce::String divRid,
                   juce::String divCid,
                   juce::String syncid);
    ~DelayComponent() override;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment buttonAttachment;
    void setButton (juce::Button& button, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<buttonAttachment>& attachment);
    void buttonClicked(juce::ToggleButton* button);
    void paint(juce::Graphics&) override;
    void resized() override;
    void updateUI();
    void buttonClicked(juce::Button* button);
    typedef juce::AudioProcessorValueTreeState::SliderAttachment Attachment;

    // custom knobs
    knobsLookAndFeel delayknobsDW;
    knobsLookAndFeel delayknobsFB;
    knobsLookAndFeel delayknobsDT;
    //
    labelLookAndFeel labelLookAndFeel;
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
    juce::Label  delayTimeLLabel{"delaytimeL", "Dt L"};
    std::unique_ptr<Attachment> delayTimeLSliderAttachment;
    // delaytime R
    juce::Slider delayTimeRSlider;
    juce::Label  delayTimeRLabel{"delaytimeR", "Dt R"};
    std::unique_ptr<Attachment> delayTimeRSliderAttachment;
    // delaytime C
    juce::Slider delayTimeCSlider;
    juce::Label  delayTimeCLabel{"delaytimeC", "Dt C"};
    std::unique_ptr<Attachment> delayTimeCSliderAttachment;
    // division L
    juce::Slider divisionLSlider;
    juce::Label  divisionLLabel{"divisionL", "Div L"};
    std::unique_ptr<Attachment> divisionLSliderAttachment;
    // division R
    juce::Slider divisionRSlider;
    juce::Label  divisionRLabel{"divisionR", "Div R"};
    std::unique_ptr<Attachment> divisionRSliderAttachment;
    // division C
    juce::Slider divisionCSlider;
    juce::Label  divisionCLabel{"divisionC", "Div C"};
    std::unique_ptr<Attachment> divisionCSliderAttachment;

    juce::ToggleButton syncTogglebutton;
    std::unique_ptr<buttonAttachment> syncToggleAttachment;


private:
    // background
    Image background;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};




