#include "ControlComponent.h"
#include <iostream>

//constructor
ControlComponent::ControlComponent(juce::AudioProcessorValueTreeState& apvts, juce::String LightId, juce::String DarkId)
{

    // making buttons, linking labels, setting text and colour in a function
    createButton(LightTextButton,apvts,LightId);
    createButton(DarkTextButton,apvts,DarkId);

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
g.drawFittedText ("Modes", getLocalBounds(), juce::Justification::topLeft, 1);
}
// layout button positions
void ControlComponent::resized() {
    // creating variables to make it easier to read and adjust everything all at once.
    const auto buttonPosY = 55;
    const auto buttonWidth = 100;
    const auto buttonHeigth = 90;

    LightTextButton.setBounds(0, buttonPosY, buttonWidth, buttonHeigth);
    DarkTextButton.setBounds(LightTextButton.getRight(), buttonPosY, buttonWidth, buttonHeigth);

}

void ControlComponent::createButton (juce::TextButton& textButton, juce::AudioProcessorValueTreeState& apvts, juce::String paramID)
{
    // button text and making visible
    textButton.setButtonText(paramID);
    addAndMakeVisible(textButton);
}

void ControlComponent::changeFilter()
{
    LightTextButton.onClick = [&](){value += stepLight; counterLight ++; counterDark = 0; };
    DarkTextButton.onClick = [&](){value -= stepDark; counterDark ++; counterLight = 0; };

    if (counterLight == 0)
    {
        stepLight = 50;
    }
    if(counterLight == 1)
    {
        stepLight = 100;
    }

    else if(counterLight == 2)
    {
        stepLight = 200;
    }
    else if(counterLight == 3 )
    {
        stepLight = 500;
    }

    if (counterDark == 0)
    {
        stepDark = 50;
    }
    else if(counterDark == 1)
    {
        stepDark = 100;
    }

    else if(counterDark == 2)
    {
        stepDark = 200;
    }
    else if(counterDark == 3 )
    {
        stepDark = 500;
    }
}