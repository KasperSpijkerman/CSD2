#include "OscComponent.h"

//constructor
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String wavetypeID, juce::String fmFreqId, juce::String fmDepthId)
:
        fmknobs("knobblue.png")
{
    juce::StringArray choices {"Sine","Square", "Saw"};
    oscWaveSelector.addItemList(choices,2);
    addAndMakeVisible(oscWaveSelector);
    // linking combobox
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts,wavetypeID,oscWaveSelector);
    // custom knobs
    fmFreqSlider.setLookAndFeel(&fmknobs);
    fmDepthSlider.setLookAndFeel(&fmknobs);
    // making sliders, linking labels, setting text and colour in a function
    setSliderWithLabel(fmFreqSlider,fmFreqlabel,apvts,fmFreqId,fmFreqAttachment);
    setSliderWithLabel(fmDepthSlider,fmDepthlabel,apvts,fmDepthId,fmdepthAttachment);
    // background panel
    background = ImageFileFormat::loadFrom(BinaryData::backgroundpanel_png, BinaryData::backgroundpanel_pngSize);;
}
// destructor
OscComponent::~OscComponent()
{
    // protection
    setLookAndFeel (nullptr);
}
void OscComponent::paint(juce::Graphics& g)
{
    /// Background
    g.fillAll(juce::Colour::fromRGBA(0, 0, 0, 20)); // Adjust the alpha value for opacity

    // Draw pink shadow for the title
    g.setColour(juce::Colour::fromRGBA(255, 105, 180, 50)); // Increased pink shadow opacity
    g.setFont(34.0f);
    g.drawFittedText("State", getLocalBounds().translated(4, 4), juce::Justification::centredTop, 1);

    // Draw the title with the adjusted light blue color
    g.setColour(juce::Colour::fromRGBA(173, 216, 255, 255)); // Lighter blue color
    g.setFont(34.0f);
    g.drawFittedText("State", getLocalBounds(), juce::Justification::centredTop, 1);

    // Draw more prominent pink glow
    g.setColour(juce::Colour::fromRGBA(255, 105, 180, 60)); // Increased pink glow opacity
    for (int i = 0; i < 3; ++i)
    {
        g.drawFittedText("State", getLocalBounds().translated(-i, -i), juce::Justification::centredTop, 1);
    }
}
// layout slider positions
void OscComponent::resized()
{
    // creating variables to make it easier to read and adjust everything all at once.
    const auto sliderPosY = 90;
    const auto sliderWidth = 130;
    const auto sliderHeigth = 110;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    // setting positions of sliders and labels
    oscWaveSelector.setBounds(getWidth()/2.7,40,90,20);

    fmFreqSlider.setBounds(10,sliderPosY,sliderWidth,sliderHeigth);
    fmFreqlabel.setBounds(fmFreqSlider.getX(),fmFreqSlider.getY()- labelYOffset,fmFreqSlider.getWidth(),labelHeight);

    fmDepthSlider.setBounds(fmFreqSlider.getRight()+30,sliderPosY,sliderWidth,sliderHeigth);
    fmDepthlabel.setBounds(fmDepthSlider.getX(),fmDepthSlider.getY()-labelYOffset,fmDepthSlider.getWidth(),labelHeight);

}