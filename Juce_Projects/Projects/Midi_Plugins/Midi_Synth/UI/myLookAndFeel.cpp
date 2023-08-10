// This code belongs to Stefan Remberg I used it to experiment with custom knobs -> Will later make my own knobs
#include "myLookAndFeel.h"

//==============================================================================
knobsLookAndFeel::knobsLookAndFeel(juce::String colour)
{
    // loading image
    File customDirectory("/Volumes/SSD Kasper 1/HKU/Jaar_2/CSD2/Juce_Projects/Projects/Midi_Synth/UI/knobs");
    File knobImageFile2 = customDirectory.getChildFile(colour);
    if(colour == "knobbrightness.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobbrightness_png, BinaryData::knobbrightness_pngSize);
    }
    else if(colour == "knobdistortion.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobdistortion_png, BinaryData::knobdistortion_pngSize);
    }
    else if(colour == "knobduration.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobduration_png, BinaryData::knobduration_pngSize);
    }
    else if(colour == "knobmovement.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobmovement_png, BinaryData::knobmovement_pngSize);
    }
    else if(colour == "knobspace.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobspace_png, BinaryData::knobspace_pngSize);
    }
    else if(colour == "knobstate.png")
    {
        img1 = ImageFileFormat::loadFrom(BinaryData::knobstate_png, BinaryData::knobstate_pngSize);
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
void labelLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
{
    auto labelArea { label.getLocalBounds().toFloat() };
    const float cornerSize { 2.0f };

    // Obtain the attached component (if any) which we assume is the slider
    auto attachedComponent = label.getAttachedComponent();
    if (attachedComponent != nullptr)
    {
        // Get the bounds of the attached component (assumed to be a slider)
        auto sliderBounds = attachedComponent->getBounds();

        // Calculate the position for the labelArea to be centered above the attached component
        labelArea = juce::Rectangle<float>(sliderBounds.getX() + (sliderBounds.getWidth() - label.getWidth()) / 2 - 10,  // Expanded width slightly by adjusting the starting X
                                           sliderBounds.getY() - label.getHeight() - 10,  // Adjust the offset as needed
                                           label.getWidth() + 20, // Expanded width slightly
                                           label.getHeight());
    }
    else
    {
        labelArea.setWidth((labelArea.getWidth() + 20) / 2.5f);
        labelArea.setX(labelArea.getX() + 15); // Adjusted due to increased width
    }

    // Drop shadow for the label's background (reduced intensity)
    juce::DropShadow shadow(juce::Colours::purple.withAlpha(0.4f), 4, juce::Point<int>(0, 0));
    shadow.drawForRectangle(g, labelArea.toNearestInt());

    // Change the background color to a darker shade of cyan for better contrast and reduced intensity
    g.setColour(juce::Colours::lightblue.darker(0.1f).withAlpha(0.9f));
    g.fillRoundedRectangle(labelArea, cornerSize);

    // Drawing the text's "shadow" first with a slight offset (reduced intensity)
    g.setColour(juce::Colours::orange.withAlpha(0.4f));  // further reduced transparency for softer shadow
    g.setFont(label.getFont());
    g.drawFittedText(label.getText(), labelArea.translated(1, 1).toNearestInt(), juce::Justification::centred, 1);

    // Then draw the main text over it
    g.setColour(juce::Colours::deeppink);
    g.drawFittedText(label.getText(), labelArea.toNearestInt(), juce::Justification::centred, 1);
}


// This draws the ComboBox itself
void boxLookAndFeel::drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown,
                  int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box)
{
    // Background
    g.setColour(juce::Colours::lightblue.withAlpha(0.9f));
    g.fillRoundedRectangle(box.getLocalBounds().toFloat(), 5.0f);

// Arrow
    juce::Path arrowPath;
    const float arrowScaleFactor = 0.5f; // Determines the size of the arrow. Smaller values = smaller arrow.
    const float arrowCenterX = buttonX + buttonW / 2.0f;
    const float arrowCenterY = buttonY + buttonH / 2.0f;
    const float arrowWidth = buttonW * arrowScaleFactor;
    const float arrowHeight = buttonH * arrowScaleFactor;

    arrowPath.startNewSubPath(arrowCenterX - arrowWidth / 2.0f, arrowCenterY - arrowHeight / 2.0f);
    arrowPath.lineTo(arrowCenterX + arrowWidth / 2.0f, arrowCenterY - arrowHeight / 2.0f);
    arrowPath.lineTo(arrowCenterX, arrowCenterY + arrowHeight / 2.0f);
    arrowPath.closeSubPath();

// Shadow
    juce::DropShadow shadow(juce::Colours::grey, 3, juce::Point<int>(0,1));
    shadow.drawForPath(g, arrowPath);

    g.setColour(juce::Colours::deeppink);
    g.fillPath(arrowPath);
}

// This draws the text in the ComboBox
void boxLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
{
    g.setColour(juce::Colours::deeppink);
    g.setFont(label.getFont());
    g.drawFittedText(label.getText(), label.getBounds(), juce::Justification::centredLeft, 1);
}

// This changes the popup menu background color
void boxLookAndFeel::drawPopupMenuBackground(juce::Graphics& g, int width, int height)
{
    g.setColour(juce::Colours::lightblue);
    g.fillRect(0, 0, width, height);
}

// This changes the popup menu text color
void boxLookAndFeel::drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
                       const bool isSeparator, const bool isActive, const bool isHighlighted,
                       const bool isTicked, const bool hasSubMenu, const juce::String& text,
                       const juce::String& shortcutKeyText, const juce::Drawable* icon,
                       const juce::Colour* const textColour)
{
    if (isHighlighted)
        g.fillAll(juce::Colours::deeppink.withAlpha(0.5f));

    if (!isActive)
        g.setColour(juce::Colours::grey);
    else if (isHighlighted)
        g.setColour(juce::Colours::black);
    else
        g.setColour(juce::Colours::deeppink);

    g.drawText(text, area.getX() + 10, area.getY(), area.getWidth() - 20, area.getHeight(),
               juce::Justification::centredLeft, true);
}

// Suppress drawing of the text when nothing is selected
void boxLookAndFeel::drawComboBoxTextWhenNothingSelected(juce::Graphics&, juce::ComboBox&, juce::Label&)
{ /* Do nothing */ }

