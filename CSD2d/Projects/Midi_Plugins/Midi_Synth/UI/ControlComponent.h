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
                     juce::String SmoothId,
                     juce::String ShortId,
                     juce::String LongId);
    ~ControlComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void protectRange(float min, float max, std::atomic<float> &value);
    // functions for changing the sliders
    void changeFilter(juce::AudioProcessorValueTreeState& apvts,juce::Slider& slider);
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
    // buttons for different opposites
    juce::TextButton LightTextButton;
    juce::TextButton DarkTextButton;
    juce::TextButton condensedTextButton;
    juce::TextButton spaciousTextButton;
    // names got changed to earthlier and weirder
    juce::TextButton predictableTextButton;
    juce::TextButton experimentalTextButton;
    juce::TextButton fastTextButton;
    juce::TextButton slowTextButton;
    juce::TextButton roughTextButton;
    juce::TextButton smoothTextButton;
    juce::TextButton shortTextButton;
    juce::TextButton longTextButton;
    // counter for how many times user has pressed Light or Dark in a row
    int counterLight{5};
    int counterDark {5};
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
    // counter 6th set
    int counterShort{0};
    int counterLong {0};
    // Stepsize for Dark and Light increasing when user pressed a button more times.
    int stepLight {50};
    int stepDark {50};
    // Stepsize dry wet
    float stepCondDW {0.1f};
    float stepSpacDW {0.1f};
    // Stepsize delaytime
    float stepCondDT {30.0f};
    float stepSpacDT {30.0f};
    // FM amount
    float stepPred {0.5f};
    float stepExp {0.5};
    // Resonance step
    float stepRes {static_cast<float>(0.1)};
    // AM amount
    float stepFastAmf {0.5f};
    float stepFastAmd {0.1f};
    float stepSlowAmf {0.5};
    float stepSlowAmd {static_cast<float>(0.1)};
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


    void createButton (juce::TextButton& button, juce::AudioProcessorValueTreeState& apvts, juce::String paramID);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlComponent)
};




