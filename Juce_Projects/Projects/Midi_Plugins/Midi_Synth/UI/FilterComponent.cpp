#include "FilterComponent.h"

//constructor
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts,
                                 juce::String filterTypeID,
                                 juce::String filterCutoffId,
                                 juce::String filterResonanceId)
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
    background = ImageFileFormat::loadFrom(BinaryData::backgroundpanel_png, BinaryData::backgroundpanel_pngSize);;
}
// destructor
FilterComponent::~FilterComponent()
{
    setLookAndFeel (nullptr);
}
void FilterComponent::paint(juce::Graphics& g)
{
    // Background
    g.fillAll(juce::Colour::fromRGBA(0, 0, 0, 20)); // Adjust the alpha value for opacity

    // Draw pink shadow for the title
    g.setColour(juce::Colour::fromRGBA(255, 105, 180, 80)); // Increased pink shadow opacity
    g.setFont(34.0f);
    g.drawFittedText("Brightness", getLocalBounds().translated(4, 4), juce::Justification::centredTop, 1);

    // Draw the title with the adjusted light blue color
    g.setColour(juce::Colour::fromRGBA(173, 216, 255, 255)); // Lighter blue color
    g.setFont(34.0f);
    g.drawFittedText("Brightness", getLocalBounds(), juce::Justification::centredTop, 1);

    // Draw more prominent pink glow
    g.setColour(juce::Colour::fromRGBA(255, 105, 180, 60)); // Increased pink glow opacity
    for (int i = 0; i < 3; ++i)
    {
        g.drawFittedText("Brightness", getLocalBounds().translated(-i, -i), juce::Justification::centredTop, 1);
    }
}
// layout slider positions
void FilterComponent::resized() {
    // creating variables to make it easier to read and adjust everything all at once.
    const auto sliderPosY = 80;
    const auto sliderWidth = 130;
    const auto sliderHeigth = 110;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    // setting positions of sliders and labels
    filterTypeSelector.setBounds(getWidth()/2.7, 40, 90, 20);

    filterCutoffSlider.setBounds(30, sliderPosY, sliderWidth, sliderHeigth);
    filterCutofflabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - labelYOffset,
                                filterCutoffSlider.getWidth(), labelHeight);

    filterResonanceSlider.setBounds(filterCutoffSlider.getRight()+30, sliderPosY, sliderWidth, sliderHeigth);
    filterResonancelabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - labelYOffset,
                                   filterResonanceSlider.getWidth(), labelHeight);
}
