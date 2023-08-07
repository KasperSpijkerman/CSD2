// This code belongs to Stefan Remberg I used it to experiment with custom knobs and customized it
// this is the link of the code https://github.com/remberg/juceCustomSliderSample
#pragma once
#include <JuceHeader.h>

//==============================================================================
class knobsLookAndFeel : public LookAndFeel_V4
{
public:
    knobsLookAndFeel(juce::String colouro);
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
private:
    // knob image file
    Image img1;
};

class buttonsLookAndFeel : public LookAndFeel_V4
{
public:
    buttonsLookAndFeel();
    void drawButtonBackground (juce::Graphics& g, juce::Button& button,
                               const juce::Colour& backgroundColour,
                               bool, bool isButtonDown) override;
    void drawButtonText (juce::Graphics& g, juce::TextButton& button, bool isMouseOverButton, bool isButtonDown) override;
    // background button image file
    Image buttonBackground;

};

class labelLookAndFeel : public LookAndFeel_V4
{
public:
    labelLookAndFeel();
    void drawLabel(juce::Graphics& g, juce::Label& label) override;


};