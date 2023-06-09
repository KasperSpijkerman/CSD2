#include "LFOComponent.h"

//constructor
LFOComponent::LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String LFOFreqId, juce::String LFODepthId)
:
        lfofreqknob("knobblue.png"),
        lfodepthknob("knobblue.png")
{

    // making sliders, linking labels, setting text and colour in a function
    setSliderWithLabel(LFOFreqSlider,LFOFreqlabel,apvts,LFOFreqId,LFOFreqAttachment);
    setSliderWithLabel(LFODepthSlider,LFODepthlabel,apvts,LFODepthId,LFODepthAttachment);
    LFOFreqSlider.setLookAndFeel(&lfofreqknob);
    LFODepthSlider.setLookAndFeel(&lfodepthknob);
}
// destructor
LFOComponent::~LFOComponent()
{

}
void LFOComponent::paint(juce::Graphics& g)
{
g.fillAll(juce::Colours::purple);
g.setColour (juce::Colours::white);
g.setFont (30.0f);
g.drawFittedText ("AM", getLocalBounds(), juce::Justification::topLeft, 1);
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