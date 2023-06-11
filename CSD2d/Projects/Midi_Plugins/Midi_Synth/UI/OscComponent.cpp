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
    File customDirectory("/Volumes/SSD Kasper 1/HKU/Jaar_2/CSD2/Juce_Projects/Projects/Midi_Synth/UI/backgrounds");
    File backgroundimage = customDirectory.getChildFile("backgroundpanel.png");
    background = ImageCache::getFromFile(backgroundimage);
}
// destructor
OscComponent::~OscComponent()
{
    // protection
    setLookAndFeel (nullptr);
}
void OscComponent::paint(juce::Graphics& g)
{
    // background
    g.drawImageAt(background,0,0);
    // Title
    g.setColour (juce::Colours::deeppink);
    g.setFont (30.0f);
    g.drawFittedText ("State", getLocalBounds(), juce::Justification::topLeft, 1);
    g.setColour (juce::Colours::powderblue);
    g.setFont (32.0f);
    g.drawFittedText ("State", getLocalBounds(), juce::Justification::topLeft, 1);
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
    oscWaveSelector.setBounds(getWidth()/3-10,50,90,20);

    fmFreqSlider.setBounds(30,sliderPosY,sliderWidth,sliderHeigth);
    fmFreqlabel.setBounds(fmFreqSlider.getX(),fmFreqSlider.getY()- labelYOffset,fmFreqSlider.getWidth(),labelHeight);

    fmDepthSlider.setBounds(fmFreqSlider.getRight()+30,sliderPosY,sliderWidth,sliderHeigth);
    fmDepthlabel.setBounds(fmDepthSlider.getX(),fmDepthSlider.getY()-labelYOffset,fmDepthSlider.getWidth(),labelHeight);

}