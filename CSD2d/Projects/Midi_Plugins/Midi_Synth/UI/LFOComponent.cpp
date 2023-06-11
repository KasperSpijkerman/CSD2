#include "LFOComponent.h"

//constructor
LFOComponent::LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String LFOFreqId, juce::String LFODepthId)
:
        lfofreqknob("knobblue.png"),
        lfodepthknob("knobblue.png")
{
    LFOFreqSlider.setLookAndFeel(&lfofreqknob);
    LFODepthSlider.setLookAndFeel(&lfodepthknob);
    // making sliders, linking labels, setting text and colour in a function
    setSliderWithLabel(LFOFreqSlider,LFOFreqlabel,apvts,LFOFreqId,LFOFreqAttachment);
    setSliderWithLabel(LFODepthSlider,LFODepthlabel,apvts,LFODepthId,LFODepthAttachment);
    // background panel

    background = ImageFileFormat::loadFrom(BinaryData::backgroundpanel_png, BinaryData::backgroundpanel_pngSize);
}
// destructor
LFOComponent::~LFOComponent()
{
    setLookAndFeel (nullptr);
}
void LFOComponent::paint(juce::Graphics& g)
{
    g.drawImageAt(background,0,0);
    g.setColour (juce::Colours::deeppink);
    g.setFont (30.0f);
    g.drawFittedText ("Movement", getLocalBounds(), juce::Justification::topLeft, 1);
    g.setColour (juce::Colours::powderblue);
    g.setFont (32.0f);
    g.drawFittedText ("Movement", getLocalBounds(), juce::Justification::topLeft, 1);
}
// layout slider positions
void LFOComponent::resized()
{
    // creating variables to make it easier to read and adjust everything all at once.
    const auto sliderPosY = 55;
    const auto sliderWidth = 130;
    const auto sliderHeigth = 110;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    LFOFreqSlider.setBounds(30,sliderPosY,sliderWidth,sliderHeigth);
    LFOFreqlabel.setBounds(LFOFreqSlider.getX(),LFOFreqSlider.getY()- labelYOffset,LFOFreqSlider.getWidth(),labelHeight);

    LFODepthSlider.setBounds(LFOFreqSlider.getRight()+60,sliderPosY,sliderWidth,sliderHeigth);
    LFODepthlabel.setBounds(LFODepthSlider.getX(),LFODepthSlider.getY()-labelYOffset,LFODepthSlider.getWidth(),labelHeight);
}