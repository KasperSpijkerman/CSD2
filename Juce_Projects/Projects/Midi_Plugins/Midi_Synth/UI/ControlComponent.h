#pragma once

#include <JuceHeader.h>
#include "myLookAndFeel.h"
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
                     juce::String SmoothId,
                     juce::String ShortId,
                     juce::String LongId);
    ~ControlComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void protectRange(float min, float max, std::atomic<float> &value);
    // functions for changing the sliders -> Which sliders can be seen at audioEditor or in CPP
    void changeFilter(juce::AudioProcessorValueTreeState& apvts,
                      juce::Slider& slider,
                      juce::ComboBox& combobox,
                      juce::ComboBox& combobox2);
    void changeSpace(juce::AudioProcessorValueTreeState& apvts,
                     juce::Slider& slider1,
                     juce::Slider& slider2,
                     juce::Slider& slider3);
    void changePredict(juce::AudioProcessorValueTreeState& apvts,
                       juce::Slider& slider1,
                       juce::Slider& slider2,
                       juce::Slider& slider3,
                       juce::Slider& slider4);
    void changeSpeed(juce::AudioProcessorValueTreeState& apvts,
                     juce::Slider& slider2,
                     juce::Slider& slider3,
                     juce::Slider& slider4);
    void changeTexture(juce::AudioProcessorValueTreeState& apvts,
                       juce::Slider& slider1,
                       juce::Slider& slider2);
    void changeLength(juce::AudioProcessorValueTreeState& apvts,
                       juce::Slider& slider1,
                       juce::Slider& slider2,
                       juce::Slider& slider3,
                       juce::Slider& slider4,
                       juce::Slider& slider5,
                       juce::Slider& slider6,
                       juce::Slider& slider7);

private:
    buttonsLookAndFeel buttonStyle;
    // buttons for different opposites
    // 1st set
    juce::TextButton LightTextButton;
    juce::TextButton DarkTextButton;
    // 2nd set
    juce::TextButton condensedTextButton;
    juce::TextButton spaciousTextButton;
    // 3rd set (names on display got changed to earthlier and weirder)
    juce::TextButton predictableTextButton;
    juce::TextButton experimentalTextButton;
    // 4th set
    juce::TextButton fastTextButton;
    juce::TextButton slowTextButton;
    // 5th set
    juce::TextButton roughTextButton;
    juce::TextButton smoothTextButton;
    // 6th set
    juce::TextButton shortTextButton;
    juce::TextButton longTextButton;
    // Counters For every set
    // 1st set
    int counterLight{5};
    int counterDark {5};
    // 2nd set
    int counterCond{0};
    int counterSpac {0};
    // 3rd set
    int counterPred{0};
    int counterExp {0};
    // 4th set
    int counterFast{0};
    int counterSlow {0};
    // 5th set
    int counterRough{0};
    int counterSmooth {0};
    // 6th set
    int counterShort{0};
    int counterLong {0};
    // Stepsize for Dark and Light increasing when user pressed a button more times.
    int stepLight {50};
    int stepDark {50};
    // Stepsize Dry-Wet Tighter Spacier (New Names)
    float stepCondDW {0.1f};
    float stepSpacDW {0.1f};
    // FM amount
    float stepPred {0.5f};
    float stepExp {0.5};
    // Resonance step
    float stepRes {static_cast<float>(0.1)};
    // AM / Tremolo amount
    float stepFastAmf {0.5f};
    float stepExpAmd {0.1f};
    float stepSlowAmf {0.5};
    float stepFastAtt {0.1f};
    float stepSlowAtt {static_cast<float>(0.1)};
    // Gain/trim amount
    float stepRoughDr {1.0f};
    float stepSmoothDr {1.0f};
    float stepRoughtrim {0.05f};
    float stepSmoothtrim {0.05f};
    // Step for feedback and release
    float stepShortR {static_cast<float>(0.05)};
    float stepShortFb {static_cast<float>(0.05)};
    float stepLongR {static_cast<float>(0.05)};
    float stepLongFb {static_cast<float>(0.05)};
    float stepPredamDepth{static_cast<float>(0.1)};
    // background
    Image background;
    // function for creating the buttons
    void createButton (juce::TextButton& button, juce::AudioProcessorValueTreeState& apvts, juce::String paramID);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlComponent)
};




