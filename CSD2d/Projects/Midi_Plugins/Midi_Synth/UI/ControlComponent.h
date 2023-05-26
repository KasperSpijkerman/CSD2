#pragma once

#include <JuceHeader.h>

class ControlComponent : public juce::Component
{
public:
    ControlComponent(juce::AudioProcessorValueTreeState& apvts, juce::String LightId, juce::String DarkId);
    ~ControlComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    float value {200.0f};
    float step{50};
    void changeFilter();
private:
    // Dark And Light Buttons
    juce::TextButton LightTextButton;
    juce::TextButton DarkTextButton;
    // counter for how many times user has pressed Light or Dark in a row
    int counterLight{0};
    int counterDark {0};
    // Stepsize for Dark and Light increasing when user pressed a button more times.
    int stepLight {50};
    int stepDark {50};
    void createButton (juce::TextButton& button, juce::AudioProcessorValueTreeState& apvts, juce::String paramID);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlComponent)
};




