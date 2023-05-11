#include "FilterComponent.h"

//constructor
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeID, juce::String filterCutoffId, juce::String filterResonanceId)
{
    juce::StringArray choices {"Lowpass","Bandpass", "Highpass"};
    filterTypeSelector.addItemList(choices,1);
    addAndMakeVisible(filterTypeSelector);
    // linking combobox
    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts,filterTypeID,filterTypeSelector);
    // making sliders, linking labels, setting text and colour in a function
    setSliderWithLabel(filterCutoffSlider,filterCutofflabel,apvts,filterCutoffId,filterCutoffAttachment);
    setSliderWithLabel(filterResonanceSlider,filterResonancelabel,apvts,filterResonanceId,filterResonanceAttachment);

}
// destructor
FilterComponent::~FilterComponent()
{

}
void FilterComponent::paint(juce::Graphics& g)
{
g.fillAll(juce::Colours::purple);
}
// layout slider positions
void FilterComponent::resized()
{
    // creating variables to make it easier to read and adjust everything all at once.
    const auto sliderPosY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeigth = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    // setting positions of sliders and labels
    filterTypeSelector.setBounds(0,0,90,20);

    filterCutoffSlider.setBounds(0,sliderPosY,sliderWidth,sliderHeigth);
    filterCutofflabel.setBounds(filterCutoffSlider.getX(),filterCutoffSlider.getY()- labelYOffset,filterCutoffSlider.getWidth(),labelHeight);

    filterResonanceSlider.setBounds(filterCutoffSlider.getRight(),sliderPosY,sliderWidth,sliderHeigth);
    filterResonancelabel.setBounds(filterResonanceSlider.getX(),filterResonanceSlider.getY()-labelYOffset,filterResonanceSlider.getWidth(),labelHeight);

}
using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void FilterComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment)
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