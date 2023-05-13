#include "LFOComponent.h"

//constructor
LFOComponent::LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String LFOFreqId, juce::String LFODepthId)
{

    // making sliders, linking labels, setting text and colour in a function
    setSliderWithLabel(LFOFreqSlider,LFOFreqlabel,apvts,LFOFreqId,LFOFreqAttachment);
    setSliderWithLabel(LFODepthSlider,LFODepthlabel,apvts,LFODepthId,LFODepthAttachment);

}
// destructor
LFOComponent::~LFOComponent()
{

}
void LFOComponent::paint(juce::Graphics& g)
{
g.fillAll(juce::Colours::purple);
}
// layout slider positions
void LFOComponent::resized()
{
    // creating variables to make it easier to read and adjust everything all at once.
    const auto sliderPosY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeigth = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    LFOFreqSlider.setBounds(0,sliderPosY,sliderWidth,sliderHeigth);
    LFOFreqlabel.setBounds(LFOFreqSlider.getX(),LFOFreqSlider.getY()- labelYOffset,LFOFreqSlider.getWidth(),labelHeight);

    LFODepthSlider.setBounds(LFOFreqSlider.getRight(),sliderPosY,sliderWidth,sliderHeigth);
    LFODepthlabel.setBounds(LFODepthSlider.getX(),LFODepthSlider.getY()-labelYOffset,LFODepthSlider.getWidth(),labelHeight);

}
using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void LFOComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment)
{
    // Slider style, textbox and making visible
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true,50,25);
    addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts,paramID,slider);

    // creating the label, textfont, and colour.
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

}