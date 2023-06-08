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
                                   juce::String SmoothId,
                                   juce::String ShortId,
                                   juce::String LongId)
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
    createButton(shortTextButton,apvts,ShortId);
    createButton(longTextButton,apvts,LongId);

}
// destructor
ControlComponent::~ControlComponent()
{

}
void ControlComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::purple);
    g.setColour (juce::Colours::deeppink);
    g.setFont (35.0f);
    g.drawFittedText ("The Teleporter", getLocalBounds(), juce::Justification::centredTop, 1);
    g.setColour (juce::Colours::powderblue);
    g.setFont (37.0f);
    g.drawFittedText ("The Teleporter", getLocalBounds(), juce::Justification::centredTop, 1);
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
    fastTextButton.setColour(TextButton::buttonColourId, Colours::green);
    fastTextButton.setColour(TextButton::textColourOffId, Colours::yellow);
    slowTextButton.setColour(TextButton::buttonColourId, Colours::lightgoldenrodyellow);
    slowTextButton.setColour(TextButton::textColourOffId, Colours::black);
    roughTextButton.setColour(TextButton::buttonColourId, Colours::blue);
    roughTextButton.setColour(TextButton::textColourOffId, Colours::red);
    smoothTextButton.setColour(TextButton::buttonColourId, Colours::orange);
    smoothTextButton.setColour(TextButton::textColourOffId, Colours::yellow);
    shortTextButton.setColour(TextButton::buttonColourId, Colours::lightsteelblue);
    shortTextButton.setColour(TextButton::textColourOffId, Colours::salmon);
    longTextButton.setColour(TextButton::buttonColourId, Colours::lightgreen);
    longTextButton.setColour(TextButton::textColourOffId, Colours::lightyellow);
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
    shortTextButton.setBounds(0, buttonPosY + 250, buttonWidth, buttonHeigth);
    longTextButton.setBounds(shortTextButton.getRight(), buttonPosY + 250, buttonWidth, buttonHeigth);

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





    LightTextButton.onClick = [&]()
            {

                counterDark -= 2;
                stepLight += 50;
                // decreasing dark counter
                stepDark -= 50;
                counterLight++;
                // making sure it doesn't go out of range
                if (stepLight <= 0)
                {
                    stepLight = 50;
                }
                if (counterLight <= 0)
                {
                    counterLight = 1;
                }
                // setting cutoff based on counter position and stepsize.
                filterCutoffnew = filterCutoffnew + stepLight*counterLight;
                // protecting the range
                protectRange(0,20000,filterCutoffnew);
                slider.setValue(filterCutoffnew);

            };


    DarkTextButton.onClick = [&]()
            {

                counterLight -=2;
                stepDark += 50;
                // decreasing light counter
                stepLight -= 50;
                // making sure it doesn't go out of range
                if (stepDark <= 0)
                {
                    stepDark = 50;
                }
                if (counterDark <= 0)
                {
                    counterDark = 1;
                }

                // setting cutoff based on counter position and stepsize.
                filterCutoffnew = filterCutoffnew - stepDark*counterDark;
                protectRange(0,20000,filterCutoffnew);
                slider.setValue(filterCutoffnew);
            };
}

void ControlComponent::changeSpace(juce::AudioProcessorValueTreeState& apvts,
                                   juce::Slider& slider1,
                                   juce::Slider& slider2,
                                   juce::Slider& slider3)
{
    // retrieving current parameter values
    auto& drywetLnew = *apvts.getRawParameterValue("drywetL");
    auto& drywetRnew = *apvts.getRawParameterValue("drywetR");
    auto& drywetCnew = *apvts.getRawParameterValue("drywetC");

    // making sure parameters don't go out of range.


    condensedTextButton.onClick = [&]()
            {
                counterCond ++;
                counterSpac = 0;
                drywetLnew = drywetLnew - stepCondDW;
                drywetRnew = drywetRnew - stepCondDW;
                drywetCnew = drywetCnew - stepCondDW;
                protectRange(0,1,drywetLnew);
                protectRange(0,1,drywetCnew);
                protectRange(0,1,drywetRnew);
                // updating the slider values
                slider1.setValue(drywetLnew);
                slider2.setValue(drywetRnew);
                slider3.setValue(drywetCnew);


            };
    spaciousTextButton.onClick = [&]()
            {
                counterSpac ++;
                counterCond = 0;
                // adjusting dry wet
                drywetLnew = drywetLnew + stepSpacDW;
                drywetRnew = drywetRnew + stepSpacDW;
                drywetCnew = drywetCnew + stepSpacDW;
                protectRange(0,1,drywetLnew);
                protectRange(0,1,drywetCnew);
                protectRange(0,1,drywetRnew);
                // setting sliders
                slider1.setValue(drywetLnew);
                slider2.setValue(drywetRnew);
                slider3.setValue(drywetCnew);


            };
}
// Algorithm for changing the predictablity
void ControlComponent::changePredict(juce::AudioProcessorValueTreeState& apvts, juce::Slider& slider1,juce::Slider& slider2,juce::Slider& slider3,juce::Slider& slider4)
{
    auto& fmDepthNew = *apvts.getRawParameterValue("fmdepth");
    auto& fmSpeedNew = *apvts.getRawParameterValue("fmfreq");
    auto& resNew = *apvts.getRawParameterValue("filterresonance");
    auto& amDepthNew = *apvts.getRawParameterValue("lfodepth");

    predictableTextButton.onClick = [&]()
    {
        counterExp = 0;
        stepExp = 0.5;
        fmDepthNew = fmDepthNew - stepPred*0.890780568956;
        fmSpeedNew = fmSpeedNew - stepPred*0.76249634987;
        amDepthNew = amDepthNew - stepPredamDepth ;
        if (fmDepthNew >= 150)
        {
            stepPredamDepth = 0;
        }
        else
        {
            stepPredamDepth = 0.1;
        }
        resNew = resNew - stepRes;
        counterPred ++;
        stepPred +=0.5;
        protectRange(0,1000,fmDepthNew);
        protectRange(0,1000,fmSpeedNew);
        protectRange(1,3,resNew);
        protectRange(0,1,amDepthNew);
        slider1.setValue(fmDepthNew);
        slider2.setValue(fmSpeedNew);
        slider3.setValue(resNew);
        slider4.setValue(amDepthNew);

    };
    experimentalTextButton.onClick = [&]()
    {
        counterPred = 0;
        stepPred = 0.5f;
        counterExp ++;
        amDepthNew = amDepthNew + stepFastAmd ;
        fmDepthNew = fmDepthNew + stepExp*0.67852547957;
        fmSpeedNew = fmSpeedNew + stepExp*0.5639;
        resNew = resNew + stepRes;
        stepExp += 0.5;
        protectRange(0,1000,fmDepthNew);
        protectRange(0,1000,fmSpeedNew);
        protectRange(1,3,resNew);
        protectRange(0,1,amDepthNew);
        slider1.setValue(fmDepthNew);
        slider2.setValue(fmSpeedNew);
        slider3.setValue(resNew);
        slider4.setValue(amDepthNew);
    };
}

// Algorithm for changing the predictablity
void ControlComponent::changeSpeed(juce::AudioProcessorValueTreeState& apvts,juce::Slider& slider2,juce::Slider& slider3,juce::Slider& slider4)
{
    auto& amSpeedNew = *apvts.getRawParameterValue("lfofreq");
    auto& attackNew = *apvts.getRawParameterValue("attack");
    auto& amDepthNew = *apvts.getRawParameterValue("lfodepth");

    fastTextButton.onClick = [&]()
    {
        if (amDepthNew == 0)
        {
           amDepthNew = 0.3;
        }
        counterSlow = 1;
        stepSlowAmf = 0.5f;
        stepSlowAtt = 0.1f;
        amSpeedNew = amSpeedNew + stepFastAmf*(counterFast/2);
        attackNew = attackNew - 0.005;
        counterFast ++;
        stepFastAtt +=0.1f;
        stepFastAmf += 0.5f;
        protectRange(0,60,amSpeedNew);
        protectRange(0,1,attackNew);
        slider2.setValue(amSpeedNew);
        slider3.setValue(attackNew);
        slider4.setValue(amDepthNew);
    };
    slowTextButton.onClick = [&]()
    {
        counterFast = 1;
        stepFastAmf = 0.5;
        stepFastAmd = 0.1;
        stepFastAtt = 0.1f;
        amSpeedNew = amSpeedNew - stepFastAmf*(counterSlow/2);
        attackNew = attackNew + 0.005;
        counterSlow ++;
        stepSlowAtt += 0.5f;
        stepSlowAmf += 0.1f;
        protectRange(0,60,amSpeedNew);
        protectRange(0,1,attackNew);
        slider2.setValue(amSpeedNew);
        slider3.setValue(attackNew);
    };
}

// Algorithm for changing the predictablity
void ControlComponent::changeTexture(juce::AudioProcessorValueTreeState& apvts, juce::Slider& slider1,juce::Slider& slider2)
{
    auto& driveNew  = *apvts.getRawParameterValue("drive");
    auto& trimNew  = *apvts.getRawParameterValue("trim");


    roughTextButton.onClick = [&]()
    {

        if(driveNew < 6)
        {
            stepRoughtrim = {0.1};
        }
        // after 6 it will make smaller steps
        else
        {
            stepRoughtrim = 0.05;
        }
        counterSmooth = 2;
        stepSmoothDr = 0.5;
        stepSmoothtrim = 0.05;
        driveNew = driveNew + stepRoughDr;
        trimNew = trimNew - stepRoughtrim;
        counterRough ++;
        stepRoughDr +=0.5f;
        stepRoughtrim += 0.005f;
        protectRange(1,100,driveNew);
        protectRange(0.2,1.0,trimNew);
        slider1.setValue(driveNew);
        slider2.setValue(trimNew);

    };
    smoothTextButton.onClick = [&]()
    {
        if(driveNew >= 20)
        {
            stepSmoothtrim = {0.005};
        }
        else
        {
            stepSmoothtrim = 0.1;
        }

        counterRough = 0;
        stepRoughDr = 0.005;
        stepRoughtrim = 0.1;
        counterSmooth ++;
        driveNew = driveNew - stepSmoothDr;
        trimNew = trimNew + stepSmoothtrim;
        stepSmoothDr += 0.5;
        stepSmoothtrim +=0.005f;
        protectRange(1,100,driveNew);
        protectRange(0.2,1.0,trimNew);
        slider1.setValue(driveNew);
        slider2.setValue(trimNew);
    };
}

void ControlComponent::changeLength(juce::AudioProcessorValueTreeState& apvts,
                                    juce::Slider& slider1,
                                    juce::Slider& slider2,
                                    juce::Slider& slider3,
                                    juce::Slider& slider4,
                                    juce::Slider& slider5,
                                    juce::Slider& slider6,
                                    juce::Slider& slider7)
{
    auto& releaseNew  = *apvts.getRawParameterValue("release");
    auto& feedbackLNew  = *apvts.getRawParameterValue("feedbackL");
    auto& feedbackRNew  = *apvts.getRawParameterValue("feedbackR");
    auto& feedbackCNew  = *apvts.getRawParameterValue("feedbackC");
    auto& delaytimeLnew = *apvts.getRawParameterValue("delaytimeL");
    auto& delaytimeRnew = *apvts.getRawParameterValue("delaytimeR");
    auto& delaytimeCnew = *apvts.getRawParameterValue("delaytimeC");
    protectRange(0,3,releaseNew);

    shortTextButton.onClick = [&]()
    {
        counterLong = 0;
        stepLongFb = 0.05;
        stepLongR = 0.05;
        counterShort ++;
        releaseNew = releaseNew - stepLongR;
        feedbackLNew = feedbackLNew - stepShortFb*0.82094567;
        feedbackRNew = feedbackRNew - stepShortFb*0.66724569;
        feedbackCNew = feedbackCNew - stepShortFb*0.74587934567;
        stepShortFb += 0.005;
        stepShortR +=0.005f;

        // adjusting delay time
        delaytimeLnew = delaytimeLnew - counterShort*10.92385637;
        delaytimeRnew = delaytimeRnew - counterShort*10.890567985;
        delaytimeCnew = delaytimeCnew - counterShort*10.32572946;

        protectRange(0,3000,delaytimeLnew);
        protectRange(0,3000,delaytimeCnew);
        protectRange(0,3000,delaytimeRnew);
        slider1.setValue(releaseNew);
        slider2.setValue(feedbackLNew);
        slider3.setValue(feedbackRNew);
        slider4.setValue(feedbackCNew);
        slider5.setValue(delaytimeLnew);
        slider6.setValue(delaytimeRnew);
        slider7.setValue(delaytimeCnew);

    };
    longTextButton.onClick = [&]()
    {
        counterShort = 0;
        stepShortFb = 0.05;
        stepShortR = 0.05;
        counterLong ++;
        releaseNew = releaseNew + stepLongR;
        feedbackLNew = feedbackLNew + stepLongFb*0.987673342;
        feedbackRNew = feedbackRNew + stepLongFb*0.789834;
        feedbackCNew = feedbackCNew + stepLongFb*0.674634596;

        if (counterLong <= 30)
        {
            protectRange(0,0.75,feedbackLNew);
            protectRange(0,0.75,feedbackRNew);
            protectRange(0,0.75,feedbackCNew);
        }
        else
        {
            protectRange(0,1,feedbackLNew);
            protectRange(0,1,feedbackRNew);
            protectRange(0,1,feedbackCNew);
        }


        // adjusting delay time
        delaytimeLnew = delaytimeLnew + counterLong*5.92385637;
        delaytimeRnew = delaytimeRnew + counterLong*5.890567985;
        delaytimeCnew = delaytimeCnew + counterLong*5.32572946;

        protectRange(0,3000,delaytimeLnew);
        protectRange(0,3000,delaytimeCnew);
        protectRange(0,3000,delaytimeRnew);
        stepLongFb += 0.005;
        stepLongR += 0.005f;
        slider1.setValue(releaseNew);
        slider2.setValue(feedbackLNew);
        slider3.setValue(feedbackRNew);
        slider4.setValue(feedbackCNew);
        slider5.setValue(delaytimeLnew);
        slider6.setValue(delaytimeRnew);
        slider7.setValue(delaytimeCnew);
    };
}