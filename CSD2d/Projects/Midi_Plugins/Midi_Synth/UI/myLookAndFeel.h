// This code belongs to Stefan Remberg I used it to experiment with custom knobs and customized it
// this is the link of the code https://github.com/remberg/juceCustomSliderSample
#pragma once
#include <JuceHeader.h>

//==============================================================================
class myLookAndFeelV1 : public LookAndFeel_V4
{
public:
    myLookAndFeelV1(juce::String colour);
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
private:
    Image img1;
};
