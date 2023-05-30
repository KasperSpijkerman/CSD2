#include "ControlComponent.h"
#include <iostream>

//constructor
ControlComponent::ControlComponent(juce::AudioProcessorValueTreeState& apvts,
                                   juce::String LightId,
                                   juce::String DarkId,
                                   juce::String CondId,
                                   juce::String SpacId,
                                   juce::String PredId,
                                   juce::String ExpId,
                                   juce::String FastId,
                                   juce::String SlowId,
                                   juce::String RoughId,
                                   juce::String SmoothId)
{

    // making buttons, linking labels, setting text and colour in a function
    createButton(LightTextButton,apvts,LightId);
    createButton(DarkTextButton,apvts,DarkId);
    createButton(condensedTextButton,apvts,CondId);
    createButton(spaciousTextButton,apvts,SpacId);
    createButton(predictableTextButton,apvts,PredId);
    createButton(experimentalTextButton,apvts,ExpId);
    createButton(fastTextButton,apvts,FastId);
    createButton(slowTextButton,apvts,SlowId);
    createButton(roughTextButton,apvts,RoughId);
    createButton(smoothTextButton,apvts,SmoothId);

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
    // colours per button
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
    fastTextButton.setColour(TextButton::buttonColourId, Colours::grey);
    fastTextButton.setColour(TextButton::textColourOffId, Colours::white);
    slowTextButton.setColour(TextButton::buttonColourId, Colours::blue);
    slowTextButton.setColour(TextButton::textColourOffId, Colours::black);
    roughTextButton.setColour(TextButton::buttonColourId, Colours::blue);
    roughTextButton.setColour(TextButton::textColourOffId, Colours::red);
    smoothTextButton.setColour(TextButton::buttonColourId, Colours::orange);
    smoothTextButton.setColour(TextButton::textColourOffId, Colours::yellow);
}
// layout button positions
void ControlComponent::resized() {
    // creating variables to make it easier to read and adjust everything all at once.
    const auto buttonPosY = 55;
    const auto buttonWidth = 100;
    const auto buttonHeigth = 40;

    LightTextButton.setBounds(0, buttonPosY, buttonWidth, buttonHeigth);
    DarkTextButton.setBounds(LightTextButton.getRight(), buttonPosY, buttonWidth, buttonHeigth);
    condensedTextButton.setBounds(0, buttonPosY + 50, buttonWidth, buttonHeigth);
    spaciousTextButton.setBounds(condensedTextButton.getRight(), buttonPosY + 50, buttonWidth, buttonHeigth);
    predictableTextButton.setBounds(0, buttonPosY + 100, buttonWidth, buttonHeigth);
    experimentalTextButton.setBounds(predictableTextButton.getRight(), buttonPosY + 100, buttonWidth, buttonHeigth);
    fastTextButton.setBounds(0, buttonPosY + 150, buttonWidth, buttonHeigth);
    slowTextButton.setBounds(fastTextButton.getRight(), buttonPosY + 150, buttonWidth, buttonHeigth);
    roughTextButton.setBounds(0, buttonPosY + 200, buttonWidth, buttonHeigth);
    smoothTextButton.setBounds(roughTextButton.getRight(), buttonPosY + 200, buttonWidth, buttonHeigth);

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
        stepPred = 0.5f;
        counterExp ++;
        fmDepth += stepExp;
        fmSpeed += stepExp;
        reso +=stepRes;
        stepExp += 0.5;
    };
}

// Algorithm for changing the predictablity
void ControlComponent::changeSpeed()
{
    fastTextButton.onClick = [&]()
    {
        counterSlow = 0;
        stepSlowAm = 0.5f;
        stepSlowAtt = 0.1f;
        attackTime += stepFastAtt;
        amSpeed += stepFastAm;
        counterFast ++;
        stepFastAtt +=0.1f;
        stepFastAm += 0.5f;
    };
    slowTextButton.onClick = [&]()
    {
        counterFast = 0;
        stepFastAm = 0.5;
        stepFastAtt = 0.1f;
        attackTime -= stepSlowAtt;
        amSpeed -= stepSlowAm;
        counterSlow ++;
        stepSlowAtt += 0.5f;
        stepSlowAm += 0.1f;
    };
}

// Algorithm for changing the predictablity
void ControlComponent::changeTexture()
{
    roughTextButton.onClick = [&]()
    {
        counterSmooth = 0;
        stepSmoothDr = 0.5;
        stepSmoothtrim = 0.5;
        driveShaper += stepRoughDr;
        trim -= stepRoughtrim;
        counterRough ++;
        stepRoughDr +=0.5f;
        stepRoughtrim += 0.1f;

    };
    smoothTextButton.onClick = [&]()
    {
        counterRough = 0;
        stepRoughDr = 0.5;
        stepRoughtrim = 0.2;
        counterSmooth ++;
        driveShaper -= stepRoughDr;
        trim += stepRoughtrim;
        stepSmoothDr += 0.5;
        stepSmoothtrim +=0.05f;
    };
}