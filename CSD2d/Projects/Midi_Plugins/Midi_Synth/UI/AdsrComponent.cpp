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
    File customDirectory("/Volumes/SSD Kasper 1/HKU/Jaar_2/CSD2/Juce_Projects/Projects/Midi_Synth/UI/backgrounds");
    File backgroundimage = customDirectory.getChildFile("backgroundpanel.png");
    background = ImageCache::getFromFile(backgroundimage);
}
// destructor
AdsrComponent::~AdsrComponent()
{
    setLookAndFeel (nullptr);
}
void AdsrComponent::paint(juce::Graphics& g)
{
    g.drawImageAt(background,0,0);
    g.setColour (juce::Colours::deeppink);
    g.setFont (30.0f);
    g.drawFittedText ("Shape", getLocalBounds(), juce::Justification::topLeft, 1);
    g.setColour (juce::Colours::powderblue);
    g.setFont (32.0f);
    g.drawFittedText ("Shape", getLocalBounds(), juce::Justification::topLeft, 1);

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
    attackSlider.getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::deeppink);


}

void AdsrComponent::setSliderParams(juce::Slider& slider,juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow,true, 50, 25);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts,paramID,slider);
    addAndMakeVisible(slider);
}