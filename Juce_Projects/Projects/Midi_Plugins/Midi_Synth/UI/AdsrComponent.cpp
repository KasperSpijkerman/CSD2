#include "AdsrComponent.h"

//constructor
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // setting the sliders
    setSliderParams(attackSlider,apvts,"attack",attackAttachment);
    setSliderParams(decaySlider,apvts,"decay",decayAttachment);
    setSliderParams(sustainSlider,apvts,"sustain",sustainAttachment);
    setSliderParams(releaseSlider,apvts,"release",releaseAttachment);
    // background panel
    background = ImageFileFormat::loadFrom(BinaryData::backgroundpanel_png, BinaryData::backgroundpanel_pngSize);;
}
// destructor
AdsrComponent::~AdsrComponent()
{
    setLookAndFeel (nullptr);
}
void AdsrComponent::paint(juce::Graphics& g)
{
    /// Background
    g.fillAll(juce::Colour::fromRGBA(0, 0, 0, 20)); // Adjust the alpha value for opacity

    // Draw pink shadow for the title
    g.setColour(juce::Colour::fromRGBA(255, 105, 180, 80)); // Increased pink shadow opacity
    g.setFont(34.0f);
    g.drawFittedText("Shape", getLocalBounds().translated(4, 4), juce::Justification::centredTop, 1);

    // Draw the title with the adjusted light blue color
    g.setColour(juce::Colours::cyan); // Lighter blue color
    g.setFont(34.0f);
    g.drawFittedText("Shape", getLocalBounds(), juce::Justification::centredTop, 1);

    // Draw more prominent pink glow
    g.setColour(juce::Colour::fromRGBA(255, 105, 180, 60)); // Increased pink glow opacity
    for (int i = 0; i < 3; ++i)
    {
        g.drawFittedText("Shape", getLocalBounds().translated(-i, -i), juce::Justification::centredTop, 1);
    }

}
// layout slider positions
void AdsrComponent::resized()
{
    //making the layout flexible calculated
    const auto bounds = getLocalBounds().reduced (10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight()-20;
    const auto sliderStartX = 0;
    const auto sliderStartY = 30;
    attackSlider.setBounds(sliderStartX,sliderStartY,sliderWidth,sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding,sliderStartY,sliderWidth,sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding,sliderStartY,sliderWidth,sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding,sliderStartY,sliderWidth,sliderHeight);
    attackSlider.getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::deeppink);
}
// different from the other components so a seperate function
void AdsrComponent::setSliderParams(juce::Slider& slider,juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow,true, 50, 25);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts,paramID,slider);
    addAndMakeVisible(slider);
}