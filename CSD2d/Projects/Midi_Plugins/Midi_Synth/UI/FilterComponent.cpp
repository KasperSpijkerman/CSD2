#include "FilterComponent.h"

//constructor
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeID, juce::String filterCutoffId, juce::String filterResonanceId)
:
knobsFilter("knobgreenorange.png")
{
    juce::StringArray choices {"Lowpass","Bandpass", "Highpass"};
    filterTypeSelector.addItemList(choices,1);
    addAndMakeVisible(filterTypeSelector);
    // linking combobox
    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts,filterTypeID,filterTypeSelector);
    filterCutoffSlider.setLookAndFeel(&knobsFilter);
    filterResonanceSlider.setLookAndFeel(&knobsFilter);
    // making sliders, linking labels, setting text and colour in a function
    setSliderWithLabel(filterCutoffSlider,filterCutofflabel,apvts,filterCutoffId,filterCutoffAttachment);
    setSliderWithLabel(filterResonanceSlider,filterResonancelabel,apvts,filterResonanceId,filterResonanceAttachment);

    // background panel
    File customDirectory("/Volumes/SSD Kasper 1/HKU/Jaar_2/CSD2/Juce_Projects/Projects/Midi_Synth/UI/backgrounds");
    File backgroundimage = customDirectory.getChildFile("backgroundpanel.png");
    background = ImageCache::getFromFile(backgroundimage);
}
// destructor
FilterComponent::~FilterComponent()
{
    setLookAndFeel (nullptr);
}
void FilterComponent::paint(juce::Graphics& g)
{

    g.drawImageAt(background,0,0);
    g.setColour (juce::Colours::deeppink);
    g.setFont (30.0f);
    g.drawFittedText ("Brightness", getLocalBounds(), juce::Justification::topLeft, 1);
    g.setColour (juce::Colours::powderblue);
    g.setFont (32.0f);
    g.drawFittedText ("Brightness", getLocalBounds(), juce::Justification::topLeft, 1);
}
// layout slider positions
void FilterComponent::resized() {
    // creating variables to make it easier to read and adjust everything all at once.
    const auto sliderPosY = 70;
    const auto sliderWidth = 130;
    const auto sliderHeigth = 110;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    // setting positions of sliders and labels
    filterTypeSelector.setBounds(getWidth()/3-10, 30, 90, 20);

    filterCutoffSlider.setBounds(30, sliderPosY, sliderWidth, sliderHeigth);
    filterCutofflabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - labelYOffset,
                                filterCutoffSlider.getWidth(), labelHeight);

    filterResonanceSlider.setBounds(filterCutoffSlider.getRight()+30, sliderPosY, sliderWidth, sliderHeigth);
    filterResonancelabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - labelYOffset,
                                   filterResonanceSlider.getWidth(), labelHeight);

}
