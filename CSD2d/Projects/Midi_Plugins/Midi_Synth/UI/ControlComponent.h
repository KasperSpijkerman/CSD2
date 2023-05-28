#pragma once

#include <JuceHeader.h>

class ControlComponent : public juce::Component
{
public:
    ControlComponent(juce::AudioProcessorValueTreeState& apvts, juce::String LightId, juce::String DarkId,juce::String CondId, juce::String SpacId);
    ~ControlComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void changeFilter();
    void changeSpace();
    // cutoff value
    float brightness {1000.0f};
    // dry wet value
    float distance{0.0f};
    // delay time value
    float length{200.0f};
private:
    // Dark And Light Buttons
    juce::TextButton LightTextButton;
    juce::TextButton DarkTextButton;
    juce::TextButton condensedTextButton;
    juce::TextButton spaciousTextButton;
    juce::TextButton predictableTextButton;
    juce::TextButton experimentalTextButton;
    // counter for how many times user has pressed Light or Dark in a row
    int counterLight{0};
    int counterDark {0};
    int counterCond{0};
    int counterSpac {0};
    // Stepsize for Dark and Light increasing when user pressed a button more times.
    int stepLight {50};
    int stepDark {50};
    // Stepsize dry wet
    float stepCondDW {0.15f};
    float stepSpacDW {0.15f};
    // Stepsize delaytime
    float stepCondDT {30.0f};
    float stepSpacDT {30.0f};
    void createButton (juce::TextButton& button, juce::AudioProcessorValueTreeState& apvts, juce::String paramID);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlComponent)
};




