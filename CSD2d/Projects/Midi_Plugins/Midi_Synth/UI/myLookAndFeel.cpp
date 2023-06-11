// This code belongs to Stefan Remberg I used it to experiment with custom knobs -> Will later make my own knobs
#include "myLookAndFeel.h"

//==============================================================================
knobsLookAndFeel::knobsLookAndFeel(juce::String colour)
{
    File customDirectory("/Volumes/SSD Kasper 1/HKU/Jaar_2/CSD2/Juce_Projects/Projects/Midi_Synth/UI/knobs");
    File knobImageFile2 = customDirectory.getChildFile(colour);
    img1 = ImageCache::getFromFile(knobImageFile2);
}

//==============================================================================
void knobsLookAndFeel::drawRotarySlider(Graphics& g,
    int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{

    if (img1.isValid())
    {
        const double rotation = (slider.getValue()
            - slider.getMinimum())
            / (slider.getMaximum()
                - slider.getMinimum());

        const int frames = img1.getHeight() / img1.getWidth();
        const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float radius = jmin(width / 2.0f, height / 2.0f);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;

        g.drawImage(img1,
            (int)rx,
            (int)ry,
            2 * (int)radius,
            2 * (int)radius,
            0,
            frameId*img1.getWidth(),
            img1.getWidth(),
            img1.getWidth());
    }
    else
    {
        static const float textPpercent = 0.35f;
        Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f,
            0.5f * height, width * textPpercent, 0.5f * height);

        g.setColour(Colours::white);

        g.drawFittedText(String("No Image"), text_bounds.getSmallestIntegerContainer(),
            Justification::horizontallyCentred | Justification::centred, 1);
    }
}

buttonsLookAndFeel::buttonsLookAndFeel()
{
    File customDirectory("/Volumes/SSD Kasper 1/HKU/Jaar_2/CSD2/Juce_Projects/Projects/Midi_Synth/UI/knobs");
    File buttonBackgroundFile = customDirectory.getChildFile("backgroundpanel.png");
    buttonBackground = ImageCache::getFromFile(buttonBackgroundFile);
}

void buttonsLookAndFeel::drawButtonBackground (juce::Graphics& g, juce::Button& button,
                           const juce::Colour& backgroundColour,
                           bool, bool isButtonDown)
{
    auto buttonArea = button.getBounds();
    auto edge = 6;

    buttonArea.removeFromLeft (edge);
    buttonArea.removeFromTop (edge);

    // shadow
    g.setColour (backgroundColour.withAlpha(0.25f) );
    g.fillRect (buttonArea);

    auto offset = isButtonDown ? -edge / 2 : -edge;
    buttonArea.translate (offset, offset);

    g.setColour (backgroundColour);
    g.setOpacity(0.8f);
    g.fillRect (buttonArea);
    g.fillRect(buttonArea);
    g.drawImageAt(buttonBackground,button.getX(),button.getY());

}
void buttonsLookAndFeel::drawButtonText (juce::Graphics& g, juce::TextButton& button, bool isMouseOverButton, bool isButtonDown)
{
    // Took the standard template from JUCE reference site and added extra things
    auto font = getTextButtonFont (button, button.getHeight());
    g.setFont (font);
    juce::Font newFont("Elephant", 22.0f, juce::Font::plain);
    g.setFont(newFont);
    g.setColour (button.findColour (button.getToggleState() ? juce::TextButton::textColourOnId
                                                            : juce::TextButton::textColourOffId)
                         .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

    auto yIndent = juce::jmin (4, button.proportionOfHeight (0.3f));
    auto cornerSize = juce::jmin (button.getHeight(), button.getWidth()) / 2;

    auto fontHeight = juce::roundToInt (font.getHeight() * 0.6f);
    auto leftIndent  = juce::jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft()  ? 4 : 2));
    auto rightIndent = juce::jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
    auto textWidth = button.getWidth() - leftIndent - rightIndent;

    auto edge = 4;
    auto offset = isButtonDown ? edge / 2 : 0;

    if (textWidth > 0)
        g.drawFittedText (button.getButtonText(),
                          leftIndent + offset, yIndent + offset, textWidth, button.getHeight() - yIndent * 2 - edge,
                          juce::Justification::centred, 2);
    g.setOpacity(0.8f); // Set the opacity to 50%
}