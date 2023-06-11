#include "ShaperComponent.h"

//constructor
ShaperComponent::ShaperComponent(juce::AudioProcessorValueTreeState& apvts, juce::String ShaperDriveId, juce::String ShaperTrimId)
:
        drivetrimknob("knobred.png")
{
    ShaperDriveSlider.setLookAndFeel(&drivetrimknob);
    ShaperTrimSlider.setLookAndFeel(&drivetrimknob);
    // making sliders, linking labels, setting text and colour in a function
    setSliderWithLabel(ShaperDriveSlider,ShaperDrivelabel,apvts,ShaperDriveId,ShaperDriveAttachment);
    setSliderWithLabel(ShaperTrimSlider,ShaperTrimlabel,apvts,ShaperTrimId,ShaperTrimAttachment);
    // background panel
    File customDirectory("/Volumes/SSD Kasper 1/HKU/Jaar_2/CSD2/Juce_Projects/Projects/Midi_Synth/UI/backgrounds");
    File backgroundimage = customDirectory.getChildFile("backgroundpanel.png");
    background = ImageCache::getFromFile(backgroundimage);
}
// destructor
ShaperComponent::~ShaperComponent()
{
    setLookAndFeel (nullptr);
}
void ShaperComponent::paint(juce::Graphics& g)
{
    g.drawImageAt(background,0,0);
//    g.fillAll(Colours::purple);
    g.setColour (juce::Colours::deeppink);
    g.setFont (30.0f);
    g.drawFittedText ("Distortion", getLocalBounds(), juce::Justification::topLeft, 1);
    g.setColour (juce::Colours::powderblue);
    g.setFont (32.0f);
    g.drawFittedText ("Distortion", getLocalBounds(), juce::Justification::topLeft, 1);
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