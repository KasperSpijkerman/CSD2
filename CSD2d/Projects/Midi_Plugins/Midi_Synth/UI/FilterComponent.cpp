#include "FilterComponent.h"

//constructor
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeID, juce::String filterCutoffId, juce::String filterResonanceId)
:
filterknob("knobgreenorange.png"),
resknob("knobpurple.png")
{
    juce::StringArray choices {"Lowpass","Bandpass", "Highpass"};
    filterTypeSelector.addItemList(choices,1);
    addAndMakeVisible(filterTypeSelector);
    // linking combobox
    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts,filterTypeID,filterTypeSelector);
    // making sliders, linking labels, setting text and colour in a function
    setSliderWithLabel(filterCutoffSlider,filterCutofflabel,apvts,filterCutoffId,filterCutoffAttachment);
    setSliderWithLabel(filterResonanceSlider,filterResonancelabel,apvts,filterResonanceId,filterResonanceAttachment);
    filterCutoffSlider.setLookAndFeel(&filterknob);
    filterResonanceSlider.setLookAndFeel(&resknob);
}
// destructor
FilterComponent::~FilterComponent()
{

}
void FilterComponent::paint(juce::Graphics& g)
{

g.fillAll(juce::Colours::purple);
    g.setColour (juce::Colours::white);
    g.setFont (30.0f);
    g.drawFittedText ("Filter", getLocalBounds(), juce::Justification::centredTop, 1);
}
// layout slider positions
void FilterComponent::resized() {
    // creating variables to make it easier to read and adjust everything all at once.
    const auto sliderPosY = 100;
    const auto sliderWidth = 100;
    const auto sliderHeigth = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    // setting positions of sliders and labels
    filterTypeSelector.setBounds(0, 50, 90, 20);

    filterCutoffSlider.setBounds(0, sliderPosY, sliderWidth, sliderHeigth);
    filterCutofflabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - labelYOffset,
                                filterCutoffSlider.getWidth(), labelHeight);

    filterResonanceSlider.setBounds(filterCutoffSlider.getRight(), sliderPosY, sliderWidth, sliderHeigth);
    filterResonancelabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - labelYOffset,
                                   filterResonanceSlider.getWidth(), labelHeight);

}
