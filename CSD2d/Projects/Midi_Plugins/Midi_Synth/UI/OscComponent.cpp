#include "OscComponent.h"

//constructor
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String wavetypeID, juce::String fmFreqId, juce::String fmDepthId)
:
        fmknobs("knobblue.png")
{
    juce::StringArray choices {"Sine","Saw", "Square"};
    oscWaveSelector.addItemList(choices,1);
    addAndMakeVisible(oscWaveSelector);
    // linking combobox
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts,wavetypeID,oscWaveSelector);
    // making sliders, linking labels, setting text and colour in a function
    setSliderWithLabel(fmFreqSlider,fmFreqlabel,apvts,fmFreqId,fmFreqAttachment);
    setSliderWithLabel(fmDepthSlider,fmDepthlabel,apvts,fmDepthId,fmdepthAttachment);
    fmFreqSlider.setLookAndFeel(&fmknobs);
    fmDepthSlider.setLookAndFeel(&fmknobs);
}
// destructor
OscComponent::~OscComponent()
{

}
void OscComponent::paint(juce::Graphics& g)
{
g.fillAll(juce::Colours::purple);
g.setColour (juce::Colours::white);
g.setFont (30.0f);
g.drawFittedText ("Waveform", getLocalBounds(), juce::Justification::centredTop, 1);
}
// layout slider positions
void OscComponent::resized()
{
    // creating variables to make it easier to read and adjust everything all at once.
    const auto sliderPosY = 90;
    const auto sliderWidth = 100;
    const auto sliderHeigth = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    // setting positions of sliders and labels
    oscWaveSelector.setBounds(0,50,90,20);

    fmFreqSlider.setBounds(0,sliderPosY,sliderWidth,sliderHeigth);
    fmFreqlabel.setBounds(fmFreqSlider.getX(),fmFreqSlider.getY()- labelYOffset,fmFreqSlider.getWidth(),labelHeight);

    fmDepthSlider.setBounds(fmFreqSlider.getRight(),sliderPosY,sliderWidth,sliderHeigth);
    fmDepthlabel.setBounds(fmDepthSlider.getX(),fmDepthSlider.getY()-labelYOffset,fmDepthSlider.getWidth(),labelHeight);

}