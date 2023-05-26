#include "AdsrComponent.h"

//constructor
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    // linkin parameters
    attackAttachment = std::make_unique<SliderAttachment>(apvts, "attack",attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "decay",decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "sustain",sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "release",releaseSlider);

    // setting the sliders
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);
}
// destructor
AdsrComponent::~AdsrComponent()
{

}
void AdsrComponent::paint(juce::Graphics& g)
{
g.fillAll(juce::Colours::purple);
g.setColour (juce::Colours::white);
g.setFont (20.0f);
g.drawFittedText ("ADSR", getLocalBounds(), juce::Justification::topLeft, 1);
}
// layout slider positions
void AdsrComponent::resized()
{
    //making the layout flexible calculated
    const auto bounds = getLocalBounds().reduced (10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 20;

    attackSlider.setBounds(sliderStartX,sliderStartY,sliderWidth,sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding,sliderStartY,sliderWidth,sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding,sliderStartY,sliderWidth,sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding,sliderStartY,sliderWidth,sliderHeight);
}

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow,true, 50, 25);
    addAndMakeVisible(slider);
}