#include "GeneralComponent.h"
using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void GeneralComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment)
{
    // Slider style, textbox and making visible
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 47, 20);

    addAndMakeVisible(slider);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts,paramID,slider);

// Creating the label, textfont, and colour.
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}



// Function to set bounds for a Slider and its Label based on row and column.
void GeneralComponent::positionSliderAndLabel(juce::Slider& slider, juce::Label& label, int x, int y, int width, int height, int labelYOffset)
{
    slider.setBounds(x, y, width, height);
    label.setBounds(x, y - labelYOffset, width, 20); // Adjust label height as needed
}

void GeneralComponent::positionSliderComboBoxAndLabel(Slider& slider, Label& label, ComboBox& comboBox,
                                    int x, int y,
                                    int sliderWidth, int sliderHeight,
                                    int labelYOffset, int comboBoxSpacing)
{
    // Position the slider
    slider.setBounds(x, y + labelYOffset, sliderWidth+20, sliderHeight+10);

    // Position the label above the slider
    label.setBounds(x, y, sliderWidth, labelYOffset);

    // Position the combobox to the right of the slider, with some spacing
    comboBox.setBounds(x + sliderWidth + comboBoxSpacing, y + labelYOffset, sliderWidth-15, sliderHeight-30);
}