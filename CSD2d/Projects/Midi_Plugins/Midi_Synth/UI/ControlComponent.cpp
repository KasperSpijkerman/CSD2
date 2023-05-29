#include "ControlComponent.h"
#include <iostream>

//constructor
ControlComponent::ControlComponent(juce::AudioProcessorValueTreeState& apvts,
                                   juce::String LightId,
                                   juce::String DarkId,
                                   juce::String CondId,
                                   juce::String SpacId,
                                   juce::String PredId,
                                   juce::String ExpId)
{

    // making buttons, linking labels, setting text and colour in a function
    createButton(LightTextButton,apvts,LightId);
    createButton(DarkTextButton,apvts,DarkId);
    createButton(condensedTextButton,apvts,CondId);
    createButton(spaciousTextButton,apvts,SpacId);
    createButton(predictableTextButton,apvts,PredId);
    createButton(experimentalTextButton,apvts,ExpId);

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
    LightTextButton.setColour(TextButton::buttonColourId, Colours::white);
    LightTextButton.setColour(TextButton::textColourOffId, Colours::black);
    DarkTextButton.setColour(TextButton::buttonColourId, Colours::black);
    DarkTextButton.setColour(TextButton::textColourOffId, Colours::white);
    condensedTextButton.setColour(TextButton::buttonColourId, Colours::blue);
    condensedTextButton.setColour(TextButton::textColourOffId, Colours::lightsalmon);
    spaciousTextButton.setColour(TextButton::buttonColourId, Colours::deeppink);
    spaciousTextButton.setColour(TextButton::textColourOffId, Colours::greenyellow);
    predictableTextButton.setColour(TextButton::buttonColourId, Colours::grey);
    predictableTextButton.setColour(TextButton::textColourOffId, Colours::white);
    experimentalTextButton.setColour(TextButton::buttonColourId, Colours::yellow);
    experimentalTextButton.setColour(TextButton::textColourOffId, Colours::red);
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
    predictableTextButton.setBounds(0, buttonPosY + 200, buttonWidth, buttonHeigth);
    experimentalTextButton.setBounds(predictableTextButton.getRight(), buttonPosY + 200, buttonWidth, buttonHeigth);

}

void ControlComponent::createButton (juce::TextButton& textButton, juce::AudioProcessorValueTreeState& apvts, juce::String paramID)
{
    // button text and making visible
    textButton.setButtonText(paramID);
    addAndMakeVisible(textButton);
}

void ControlComponent::changeFilter()
{
    LightTextButton.onClick = [&]()
            {
                counterDark = 0;
                stepDark = 50;
                brightness += stepLight;
                counterLight ++;
                stepLight +=50;
            };
    DarkTextButton.onClick = [&]()
            {
                counterLight = 0;
                stepLight = 50;
                brightness-= stepDark;
                counterDark ++;
                stepDark += 50;
            };




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
// Algorithm for changing the predictablity
void ControlComponent::changePredict()
{
    predictableTextButton.onClick = [&]()
    {
        counterExp = 0;
        stepExp = 0.5;
        fmDepth -= stepPred;
        fmSpeed -= stepPred;
        reso -=stepRes;
        counterPred ++;
        stepPred +=0.5;

    };
    experimentalTextButton.onClick = [&]()
    {
        counterPred = 0;
        stepPred = 0.5;
        counterExp ++;
        fmDepth += stepExp;
        fmSpeed += stepExp;
        reso +=stepRes;
        stepExp += 0.5;
    };
}