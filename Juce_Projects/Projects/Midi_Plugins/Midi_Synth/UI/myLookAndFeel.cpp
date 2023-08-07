// This code belongs to Stefan Remberg I used it to experiment with custom knobs -> Will later make my own knobs
#include "myLookAndFeel.h"

//==============================================================================
knobsLookAndFeel::knobsLookAndFeel(juce::String colour)
{
    // loading image
    File customDirectory("/Volumes/SSD Kasper 1/HKU/Jaar_2/CSD2/Juce_Projects/Projects/Midi_Synth/UI/knobs");
    File knobImageFile2 = customDirectory.getChildFile(colour);
    if(colour == "knobblue.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobblue_png, BinaryData::knobblue_pngSize);
    }
    else if(colour == "knobgreenorange.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobgreenorange_png, BinaryData::knobgreenorange_pngSize);
    }
    else if(colour == "knobpink.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobpink_png, BinaryData::knobpink_pngSize);
    }
    else if(colour == "knobbgrey.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobgrey_png, BinaryData::knobgrey_pngSize);
    }
    else if(colour == "knobpurple.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobpurple_png, BinaryData::knobpurple_pngSize);
    }
    else if(colour == "knoblightpurple.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knoblightpurple_png, BinaryData::knoblightpurple_pngSize);
    }
    else if(colour == "knobbrightpurple.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobbrightpurple_png, BinaryData::knobbrightpurple_pngSize);
    }
    else if(colour == "knobred.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobred_png, BinaryData::knobred_pngSize);
    }

}

//==============================================================================
void knobsLookAndFeel::drawRotarySlider(Graphics& g,
    int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    // checking if image is loaded
    if (img1.isValid())
    {
        const double rotation = (slider.getValue()
            - slider.getMinimum())
            / (slider.getMaximum()
                - slider.getMinimum());
        // specifying rotation
        const int frames = img1.getHeight() / img1.getWidth();
        const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float radius = jmin(width / 2.0f, height / 2.0f);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;
        // actually drawing the knob
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
    // debug if files are not there
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

void buttonsLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button,
                                              const juce::Colour& backgroundColour,
                                              bool, bool isButtonDown)
{
    auto buttonArea = button.getBounds();
    auto edge = 4; // Reduce the edge value for a less extreme effect

    auto offset = isButtonDown ? -edge / 2 : -edge;

    // Draw the texture with modified randomness and probabilistic variations
    for (int i = 0; i < 40; ++i) // Reduce the number of iterations
    {
        if (juce::Random::getSystemRandom().nextFloat() < 0.8f) // 80% probability for lines
        {
            g.setColour(backgroundColour.withAlpha(juce::Random::getSystemRandom().nextFloat() * 0.3f)); // Increase opacity
            g.drawLine(juce::Random::getSystemRandom().nextInt(buttonArea.getWidth()) + buttonArea.getX(),
                       juce::Random::getSystemRandom().nextInt(buttonArea.getHeight()) + buttonArea.getY(),
                       juce::Random::getSystemRandom().nextInt(buttonArea.getWidth()) + buttonArea.getX(),
                       juce::Random::getSystemRandom().nextInt(buttonArea.getHeight()) + buttonArea.getY(),
                       juce::Random::getSystemRandom().nextInt(3) + 1); // Reduce line thickness
        }
        else
        {
            auto sphereX = juce::Random::getSystemRandom().nextInt(buttonArea.getWidth()) + buttonArea.getX();
            auto sphereY = juce::Random::getSystemRandom().nextInt(buttonArea.getHeight()) + buttonArea.getY();

            sphereX = juce::jlimit(buttonArea.getX(), buttonArea.getRight(), sphereX);
            sphereY = juce::jlimit(buttonArea.getY(), buttonArea.getBottom(), sphereY);

            g.setColour(backgroundColour.withAlpha(juce::Random::getSystemRandom().nextFloat() * 0.3f)); // Increase opacity
            g.fillEllipse(juce::Rectangle<float>(sphereX,
                                                 sphereY,
                                                 juce::Random::getSystemRandom().nextInt(12) + 5, // Increase sphere size
                                                 juce::Random::getSystemRandom().nextInt(12) + 5));
        }
    }
}



void buttonsLookAndFeel::drawButtonText(juce::Graphics& g, juce::TextButton& button, bool isMouseOverButton, bool isButtonDown)
{
    auto font = getTextButtonFont(button, button.getHeight());
    font.setHeight(18.0f); // Increase the font size

    g.setFont(font);

    // Set the text color with a soft and subtle shadow
    g.setColour(juce::Colour::fromRGBA(0, 0, 0, 40)); // Shadow color and opacity
    auto textBounds = button.getLocalBounds();
    g.drawFittedText(button.getButtonText(), textBounds.translated(2, 2), juce::Justification::centred, false);

    // Set the text color for the actual text
    g.setColour(button.findColour(button.getToggleState() ? juce::TextButton::textColourOnId
                                                          : juce::TextButton::textColourOffId)
                        .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.7f));

    // Draw the text with bolder style
    g.setFont(font.boldened());
    auto yIndent = juce::jmin(5, button.proportionOfHeight(0.3f));
    auto edge = 4;
    auto offset = isButtonDown ? edge / 2 : 0;
    auto textWidth = button.getWidth();
    if (textWidth > 0)
    {
        if (isButtonDown)
        {
            g.drawFittedText(button.getButtonText(),
                             offset + 2, yIndent + offset + 2, textWidth, button.getHeight() - yIndent * 2 - edge,
                             juce::Justification::centred, 2);
        }
        else
        {
            g.drawFittedText(button.getButtonText(),
                             offset, yIndent + offset, textWidth, button.getHeight() - yIndent * 2 - edge,
                             juce::Justification::centred, 2);
        }
    }
    g.setOpacity(0.9f); // Set the opacity to 90%
}

labelLookAndFeel::labelLookAndFeel()
{

}
void labelLookAndFeel::drawLabel (juce::Graphics& g, juce::Label& label)
{
    auto labelArea { label.getLocalBounds().toFloat() };
    const float cornerSize { 2.0f };

    // Calculate the width of the rectangle to be approximately one-third of it
    labelArea.setWidth(labelArea.getWidth() / 2.5f);

    // Adjust the x-coordinate to move the rectangle and text to the left
    labelArea.setX(labelArea.getX() + 26);

    // Draw rounded rectangle with light blue color
    g.setColour (juce::Colours::lightblue);
    g.fillRoundedRectangle (labelArea, cornerSize);

    // Draw text with slightly lighter deeppink color and more glow
    g.setColour (label.findColour (juce::Label::textColourId).brighter(0.1f).withAlpha(0.8f));
    g.setFont (label.getFont());

    // Draw the label text with centred alignment
    g.setColour (juce::Colours::deeppink);
    g.drawFittedText (label.getText(), labelArea.toNearestInt(), juce::Justification::centred, 1);
}