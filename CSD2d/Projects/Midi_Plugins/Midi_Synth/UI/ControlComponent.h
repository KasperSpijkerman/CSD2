#pragma once

#include <JuceHeader.h>

class ControlComponent : public juce::Component
{
public:
    ControlComponent(juce::AudioProcessorValueTreeState& apvts,
                     juce::String LightId,
                     juce::String DarkId,
                     juce::String CondId,
                     juce::String SpacId,
                     juce::String PredId,
                     juce::String ExpID,
                     juce::String FastId,
                     juce::String SlowId,
                     juce::String RoughId,
                     juce::String SmoothId);
    ~ControlComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    // functions for changing the sliders
    void changeFilter();
    void changeSpace();
    void changePredict();
    void changeSpeed();
    void changeTexture();
    // cutoff value
    float brightness {1000.0f};
    // dry wet value
    float distance{0.0f};
    // delay time value
    float length{200.0f};
    // fm and resonance
    float fmDepth {0.0f};
    float fmSpeed {0.0f};
    float reso {0.0f};
    // AM
    float amSpeed{0.0f};
    float attackTime{0.0f};
    // Shaper variables
    float driveShaper{1.0f};
    float trim{1.0f};
private:
    // buttons for different opposites
    juce::TextButton LightTextButton;
    juce::TextButton DarkTextButton;
    juce::TextButton condensedTextButton;
    juce::TextButton spaciousTextButton;
    juce::TextButton predictableTextButton;
    juce::TextButton experimentalTextButton;
    juce::TextButton fastTextButton;
    juce::TextButton slowTextButton;
    juce::TextButton roughTextButton;
    juce::TextButton smoothTextButton;
    // counter for how many times user has pressed Light or Dark in a row
    int counterLight{0};
    int counterDark {0};
    // counters for 2nd set
    int counterCond{0};
    int counterSpac {0};
    // counter for 3rd set
    int counterPred{0};
    int counterExp {0};
    // counter for 4th set
    int counterFast{0};
    int counterSlow {0};
    // counter for 5th set
    int counterRough{0};
    int counterSmooth {0};
    // Stepsize for Dark and Light increasing when user pressed a button more times.
    int stepLight {50};
    int stepDark {50};
    // Stepsize dry wet
    float stepCondDW {0.2f};
    float stepSpacDW {0.2f};
    // Stepsize delaytime
    float stepCondDT {30.0f};
    float stepSpacDT {30.0f};
    // FM amount
    float stepPred {0.5f};
    float stepExp {0.5};
    // Resonance step
    float stepRes {0.1};
    // AM amount
    float stepFastAm {0.5f};
    float stepSlowAm {0.5};
    float stepFastAtt {0.1f};
    float stepSlowAtt {0.1};
    // Gain/trim amount
    float stepRoughDr {1.0f};
    float stepSmoothDr {1.0f};
    float stepRoughtrim {0.05f};
    float stepSmoothtrim {0.05f};

    void createButton (juce::TextButton& button, juce::AudioProcessorValueTreeState& apvts, juce::String paramID);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlComponent)
};




