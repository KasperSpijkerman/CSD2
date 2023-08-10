#include "ShaperComponent.h"

//constructor
ShaperComponent::ShaperComponent(juce::AudioProcessorValueTreeState& apvts, juce::String ShaperDriveId, juce::String ShaperTrimId,juce::String ShaperDwId)
:
//drive
        drivetrimknob("knobdistortion.png")
{
    ShaperDriveSlider.setLookAndFeel(&drivetrimknob);
    ShaperTrimSlider.setLookAndFeel(&drivetrimknob);
    ShaperDwSlider.setLookAndFeel(&drivetrimknob);

    ShaperDrivelabel.setLookAndFeel(&labelLookAndFeel);
    ShaperTrimlabel.setLookAndFeel(&labelLookAndFeel);
    ShaperDwlabel.setLookAndFeel(&labelLookAndFeel);
    // making sliders, linking labels, setting text and colour in a function
    setSliderWithLabel(ShaperDriveSlider,ShaperDrivelabel,apvts,ShaperDriveId,ShaperDriveAttachment);
    setSliderWithLabel(ShaperTrimSlider,ShaperTrimlabel,apvts,ShaperTrimId,ShaperTrimAttachment);
    setSliderWithLabel(ShaperDwSlider,ShaperDwlabel,apvts,ShaperDwId,ShaperDwAttachment);
    // background panel
    background = ImageFileFormat::loadFrom(BinaryData::backgroundpanel_png, BinaryData::backgroundpanel_pngSize);

}
// destructor
ShaperComponent::~ShaperComponent()
{
    setLookAndFeel (nullptr);
}
void ShaperComponent::paint(juce::Graphics& g)
{
    /// Background
    g.fillAll(juce::Colour::fromRGBA(0, 0, 0, 20)); // Adjust the alpha value for opacity

    // Draw pink shadow for the title
    g.setColour(juce::Colour::fromRGBA(255, 105, 180, 80)); // Increased pink shadow opacity
    g.setFont(34.0f);
    g.drawFittedText("Distortion", getLocalBounds().translated(4, 4), juce::Justification::centredTop, 1);

    // Draw the title with the adjusted light blue color
    g.setColour(juce::Colours::cyan); // Lighter blue color
    g.setFont(34.0f);
    g.drawFittedText("Distortion", getLocalBounds(), juce::Justification::centredTop, 1);

    // Draw more prominent pink glow
    g.setColour(juce::Colour::fromRGBA(255, 105, 180, 60)); // Increased pink glow opacity
    for (int i = 0; i < 3; ++i)
    {
        g.drawFittedText("Distortion", getLocalBounds().translated(-i, -i), juce::Justification::centredTop, 1);
    }
}
// layout slider positions
void ShaperComponent::resized()
{
    // creating variables to make it easier to read and adjust everything all at once.
    const auto sliderPosY = 55;
    const auto sliderWidth = 130;
    const auto sliderHeigth = 110;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    ShaperDriveSlider.setBounds(30,sliderPosY,sliderWidth,sliderHeigth);
    ShaperDrivelabel.setBounds(ShaperDriveSlider.getX(),ShaperDriveSlider.getY()- labelYOffset,ShaperDriveSlider.getWidth(),labelHeight);

    ShaperTrimSlider.setBounds(ShaperDriveSlider.getRight()+50,sliderPosY,sliderWidth,sliderHeigth);
    ShaperTrimlabel.setBounds(ShaperTrimSlider.getX(),ShaperTrimSlider.getY()-labelYOffset,ShaperTrimSlider.getWidth(),labelHeight);

    ShaperDwSlider.setBounds(ShaperDriveSlider.getRight()-40,sliderPosY,sliderWidth,sliderHeigth);
    ShaperDwlabel.setBounds(ShaperDwSlider.getX(),ShaperTrimSlider.getY()-labelYOffset,ShaperTrimSlider.getWidth(),labelHeight);

}
using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void ShaperComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment)
{
    // Slider style, textbox and making visible
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true,50,25);
    // making visible
    addAndMakeVisible(slider);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts,paramID,slider);
    // creating the label, textfont, and colour.
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}