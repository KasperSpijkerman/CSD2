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


    DarkTextButton.setBounds(0, buttonPosY, buttonWidth, buttonHeigth);
    LightTextButton.setBounds(DarkTextButton.getRight(), buttonPosY, buttonWidth, buttonHeigth);
    condensedTextButton.setBounds(0, buttonPosY + 50, buttonWidth, buttonHeigth);
    spaciousTextButton.setBounds(condensedTextButton.getRight(), buttonPosY + 50, buttonWidth, buttonHeigth);
    predictableTextButton.setBounds(0, buttonPosY + 100, buttonWidth, buttonHeigth);
    experimentalTextButton.setBounds(predictableTextButton.getRight(), buttonPosY + 100, buttonWidth, buttonHeigth);
    slowTextButton.setBounds(0, buttonPosY + 150, buttonWidth, buttonHeigth);
    fastTextButton.setBounds(slowTextButton.getRight(), buttonPosY + 150, buttonWidth, buttonHeigth);
    smoothTextButton.setBounds(0, buttonPosY + 200, buttonWidth, buttonHeigth);
    roughTextButton.setBounds(smoothTextButton.getRight(), buttonPosY + 200, buttonWidth, buttonHeigth);

}

void ControlComponent::createButton (juce::TextButton& textButton, juce::AudioProcessorValueTreeState& apvts, juce::String paramID)
{
    // button text and making visible
    textButton.setButtonText(paramID);
    addAndMakeVisible(textButton);
}

void ControlComponent::protectRange(float min, float max, std::atomic<float> &value)
{
    if (value >= max)
    {
        value = max;
    }
    if (value <= min)
    {
        value = min;
    }
}

void ControlComponent::changeFilter(juce::AudioProcessorValueTreeState& apvts, juce::Slider& slider)
{
    // retrieve current parameter value
    auto& filterCutoffnew = *apvts.getRawParameterValue("filtercutoff");
    // making sure parameters don't go out of range
    protectRange(0,20000,filterCutoffnew);
    LightTextButton.onClick = [&]()
            {
               // and adjust the slider
                stepDark = 1;
                stepLight++;
                // making sure it doesn't go out of range

                filterCutoffnew = filterCutoffnew + 50*stepLight;
                slider.setValue(filterCutoffnew);

            };


    DarkTextButton.onClick = [&]()
            {
            // and adjust the slider
                stepLight = 1;
                stepDark++;
                // making sure it doesn't go out of range

                filterCutoffnew = filterCutoffnew - 50*stepDark;
                slider.setValue(filterCutoffnew);
            };
}

void ControlComponent::changeSpace(juce::AudioProcessorValueTreeState& apvts,
                                   juce::Slider& slider1,
                                   juce::Slider& slider2,
                                   juce::Slider& slider3,
                                   juce::Slider& slider4,
                                   juce::Slider& slider5,
                                   juce::Slider& slider6)
{
    // retrieving current parameter values
    auto& drywetLnew = *apvts.getRawParameterValue("drywetL");
    auto& drywetRnew = *apvts.getRawParameterValue("drywetR");
    auto& drywetCnew = *apvts.getRawParameterValue("drywetC");
    auto& delaytimeLnew = *apvts.getRawParameterValue("delaytimeL");
    auto& delaytimeRnew = *apvts.getRawParameterValue("delaytimeR");
    auto& delaytimeCnew = *apvts.getRawParameterValue("delaytimeC");
    // making sure parameters don't go out of range.
    protectRange(0,1,drywetLnew);
    protectRange(0,1,drywetCnew);
    protectRange(0,1,drywetRnew);
    protectRange(0,3000,drywetLnew);
    protectRange(0,3000,drywetCnew);
    protectRange(0,3000,drywetRnew);
    condensedTextButton.onClick = [&]()
            {
                counterCond ++;
                counterSpac = 0;
                drywetLnew = drywetLnew - 0.1;
                drywetRnew = drywetRnew - 0.1;
                drywetCnew = drywetCnew - 0.1;

                delaytimeLnew = delaytimeLnew - 50;
                delaytimeRnew = delaytimeRnew - 50;
                delaytimeCnew = delaytimeCnew - 50;
                // updating the slider values
                slider1.setValue(drywetLnew);
                slider2.setValue(drywetRnew);
                slider3.setValue(drywetCnew);
                slider4.setValue(delaytimeLnew);
                slider5.setValue(delaytimeRnew);
                slider6.setValue(delaytimeCnew);

            };
    spaciousTextButton.onClick = [&]()
            {
                counterSpac ++;
                counterCond = 0;
                // adjusting dry wet
                drywetLnew = drywetLnew + 0.1;
                drywetRnew = drywetRnew + 0.1;
                drywetCnew = drywetCnew + 0.1;
                // adjusting delay time
                delaytimeLnew = delaytimeLnew + 50;
                delaytimeRnew = delaytimeRnew + 50;
                delaytimeCnew = delaytimeCnew + 50;
                // setting sliders
                slider1.setValue(drywetLnew);
                slider2.setValue(drywetRnew);
                slider3.setValue(drywetCnew);
                slider4.setValue(delaytimeLnew);
                slider5.setValue(delaytimeRnew);
                slider6.setValue(delaytimeCnew);

            };
}
// Algorithm for changing the predictablity
void ControlComponent::changePredict(juce::AudioProcessorValueTreeState& apvts, juce::Slider& slider1,juce::Slider& slider2,juce::Slider& slider3)
{
    auto& fmDepthNew = *apvts.getRawParameterValue("fmdepth");
    auto& fmSpeedNew = *apvts.getRawParameterValue("fmfreq");
    auto& resNew = *apvts.getRawParameterValue("filterresonance");
    protectRange(0,1000,fmDepthNew);
    protectRange(0,1000,fmSpeedNew);
    protectRange(0,3,resNew);
    predictableTextButton.onClick = [&]()
    {
        counterExp = 0;
        stepExp = 0.5;
        fmDepthNew = fmDepthNew - stepPred;
        fmSpeedNew = fmSpeedNew - stepPred;
        resNew = resNew - stepRes;
        counterPred ++;
        stepPred +=0.5;
        slider1.setValue(fmDepthNew);
        slider2.setValue(fmSpeedNew);
        slider3.setValue(resNew);

    };
    experimentalTextButton.onClick = [&]()
    {
        counterPred = 0;
        stepPred = 0.5f;
        counterExp ++;
        fmDepthNew = fmDepthNew + stepExp;
        fmSpeedNew = fmSpeedNew + stepExp;
        resNew = resNew + stepRes;
        stepExp += 0.5;
        slider1.setValue(fmDepthNew);
        slider2.setValue(fmSpeedNew);
        slider3.setValue(resNew);
    };
}

// Algorithm for changing the predictablity
void ControlComponent::changeSpeed(juce::AudioProcessorValueTreeState& apvts, juce::Slider& slider1,juce::Slider& slider2,juce::Slider& slider3)
{
    auto& amDepthNew = *apvts.getRawParameterValue("lfodepth");
    auto& amSpeedNew = *apvts.getRawParameterValue("lfofreq");
    auto& attackNew = *apvts.getRawParameterValue("attack");
    protectRange(0,1,amDepthNew);
    protectRange(0,60,amSpeedNew);
    protectRange(0,1,attackNew);
    fastTextButton.onClick = [&]()
    {
        counterSlow = 0;
        stepSlowAmf = 0.5f;
        stepSlowAtt = 0.1f;
        amDepthNew = amDepthNew + stepFastAmd ;
        amSpeedNew = amDepthNew + stepFastAmf;
        attackNew = attackNew - 0.1;
        counterFast ++;
        stepFastAtt +=0.1f;
        stepFastAmf += 0.5f;
        slider1.setValue(amDepthNew);
        slider2.setValue(amSpeedNew);
        slider3.setValue(attackNew);
    };
    slowTextButton.onClick = [&]()
    {
        counterFast = 0;
        stepFastAmf = 0.5;
        stepFastAmd = 0.1;
        stepFastAtt = 0.1f;
        amDepthNew = amDepthNew - stepFastAmd ;
        amSpeedNew = amDepthNew - stepFastAmf;
        attackNew = attackNew + 0.1;
        counterSlow ++;
        stepSlowAtt += 0.5f;
        stepSlowAmf += 0.1f;
        slider1.setValue(amDepthNew);
        slider2.setValue(amSpeedNew);
        slider3.setValue(attackNew);
    };
}

// Algorithm for changing the predictablity
void ControlComponent::changeTexture(juce::AudioProcessorValueTreeState& apvts, juce::Slider& slider1,juce::Slider& slider2)
{
    auto& driveNew  = *apvts.getRawParameterValue("drive");
    auto& trimNew  = *apvts.getRawParameterValue("trim");
    protectRange(1,100,driveNew);
    protectRange(0.01,1.0,trimNew);
    roughTextButton.onClick = [&]()
    {
        counterSmooth = 0;
        stepSmoothDr = 0.5;
        stepSmoothtrim = 0.05;
        driveNew = driveNew + stepRoughDr;
        trimNew = trimNew - stepRoughtrim;
        counterRough ++;
        stepRoughDr +=0.5f;
        stepRoughtrim += 0.005f;
        slider1.setValue(driveNew);
        slider2.setValue(trimNew);

    };
    smoothTextButton.onClick = [&]()
    {
        counterRough = 0;
        stepRoughDr = 0.005;
        stepRoughtrim = 0.1;
        counterSmooth ++;
        driveNew = driveNew - stepSmoothDr;
        trimNew = trimNew + stepSmoothtrim;
        stepSmoothDr += 0.5;
        stepSmoothtrim +=0.005f;
        slider1.setValue(driveNew);
        slider2.setValue(trimNew);
    };
}