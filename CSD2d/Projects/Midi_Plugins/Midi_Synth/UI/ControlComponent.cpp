#include "ControlComponent.h"
#include <iostream>

//constructor
ControlComponent::ControlComponent(juce::AudioProcessorValueTreeState& apvts, juce::String LightId, juce::String DarkId, juce::String CondId,juce::String SpacId)
{

    // making buttons, linking labels, setting text and colour in a function
    createButton(LightTextButton,apvts,LightId);
    createButton(DarkTextButton,apvts,DarkId);
    createButton(condensedTextButton,apvts,CondId);
    createButton(spaciousTextButton,apvts,SpacId);

}
// destructor
ControlComponent::~ControlComponent()
{

}
void ControlComponent::paint(juce::Graphics& g)
{
g.fillAll(juce::Colours::purple);
g.setColour (juce::Colours::white);
g.setFont (30.0f);
g.drawFittedText ("Modes", getLocalBounds(), juce::Justification::centredTop, 1);
}
// layout button positions
void ControlComponent::resized() {
    // creating variables to make it easier to read and adjust everything all at once.
    const auto buttonPosY = 55;
    const auto buttonWidth = 100;
    const auto buttonHeigth = 90;

    LightTextButton.setBounds(0, buttonPosY, buttonWidth, buttonHeigth);
    DarkTextButton.setBounds(LightTextButton.getRight(), buttonPosY, buttonWidth, buttonHeigth);
    condensedTextButton.setBounds(0, buttonPosY + 100, buttonWidth, buttonHeigth);
    spaciousTextButton.setBounds(condensedTextButton.getRight(), buttonPosY + 100, buttonWidth, buttonHeigth);

}

void ControlComponent::createButton (juce::TextButton& textButton, juce::AudioProcessorValueTreeState& apvts, juce::String paramID)
{
    // button text and making visible
    textButton.setButtonText(paramID);
    addAndMakeVisible(textButton);
}

void ControlComponent::changeFilter()
{
    LightTextButton.onClick = [&](){brightness += stepLight; counterLight ++; counterDark = 0; stepLight +=50; stepDark = 50; };
    DarkTextButton.onClick = [&](){brightness-= stepDark; counterDark ++; counterLight = 0; stepDark += 50; stepLight = 50;  };




}

void ControlComponent::changeSpace()
{
    condensedTextButton.onClick = [&]()
            {
                distance -= stepCondDW;
                length -= stepCondDT;
                counterCond ++;
                counterSpac = 0;
                // increase stepsize
                stepCondDT += 100;
                stepSpacDT = 50;
            };
    spaciousTextButton.onClick = [&]()
            {
                distance += stepSpacDW;
                length += stepSpacDT;
                counterSpac ++;
                counterCond = 0;
                stepSpacDT += 100;
                stepCondDT = 50;
            };
}