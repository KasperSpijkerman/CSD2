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

class boxLookAndFeel : public LookAndFeel_V4
{
public:
    void drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown,
                                      int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box) override;

    void drawLabel(juce::Graphics& g, juce::Label& label) override;
    void drawPopupMenuBackground(juce::Graphics& g, int width, int height) override;
    void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
    const bool isSeparator, const bool isActive, const bool isHighlighted,
    const bool isTicked, const bool hasSubMenu, const juce::String& text,
    const juce::String& shortcutKeyText, const juce::Drawable* icon,
    const juce::Colour* const textColour) override;
    void drawComboBoxTextWhenNothingSelected(juce::Graphics&, juce::ComboBox&, juce::Label&) override;
};