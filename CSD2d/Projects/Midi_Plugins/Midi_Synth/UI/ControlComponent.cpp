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
    // style of buttons
    setLookAndFeel(&buttonStyle);
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
    // background panel
    File customDirectory("/Volumes/SSD Kasper 1/HKU/Jaar_2/CSD2/Juce_Projects/Projects/Midi_Synth/UI/backgrounds");
    File backgroundimage = customDirectory.getChildFile("backgroundpanelbig.png");
    background = ImageCache::getFromFile(backgroundimage);

}
// destructor
ControlComponent::~ControlComponent()
{
    setLookAndFeel (nullptr);
}
void ControlComponent::paint(juce::Graphics& g)
{
    // background
    g.drawImageAt(background,0,0);
    g.setColour (juce::Colours::deeppink);
    // title
    g.setFont (43.0f);
    g.drawFittedText ("The TeleSynth", getLocalBounds(), juce::Justification::centredTop, 1);
    g.setColour (juce::Colours::powderblue);
    g.setFont (45.0f);
    g.drawFittedText ("The TeleSynth", getLocalBounds(), juce::Justification::centredTop, 1);
    // colours per button first the background and 2nd the Text
    // 1st set
    buttonStyle.drawButtonBackground(g,LightTextButton,juce::Colours::white,LightTextButton.buttonNormal,LightTextButton.buttonDown);
    LightTextButton.setColour(TextButton::textColourOffId, Colours::darkgrey);
    buttonStyle.drawButtonBackground(g,DarkTextButton,juce::Colours::black,DarkTextButton.buttonNormal,DarkTextButton.buttonDown);
    DarkTextButton.setColour(TextButton::textColourOffId, Colours::lightgrey);
    // 2nd set
    buttonStyle.drawButtonBackground(g,condensedTextButton,juce::Colours::blue,condensedTextButton.buttonNormal,condensedTextButton.buttonDown);
    condensedTextButton.setColour(TextButton::textColourOffId, Colours::lightsalmon);
    buttonStyle.drawButtonBackground(g,spaciousTextButton,juce::Colours::deeppink,spaciousTextButton.buttonNormal,spaciousTextButton.buttonDown);
    spaciousTextButton.setColour(TextButton::textColourOffId, Colours::greenyellow);
    // 3rd set names got changed to earthlier and weirder
    buttonStyle.drawButtonBackground(g,predictableTextButton,juce::Colours::lightgreen,predictableTextButton.buttonNormal,predictableTextButton.buttonDown);
    predictableTextButton.setColour(TextButton::textColourOffId, Colours::lightsalmon);
    buttonStyle.drawButtonBackground(g,experimentalTextButton,juce::Colours::yellow,experimentalTextButton.buttonNormal,experimentalTextButton.buttonDown);
    experimentalTextButton.setColour(TextButton::textColourOffId, Colours::green);
    // 4th set
    buttonStyle.drawButtonBackground(g,fastTextButton,juce::Colours::green,fastTextButton.buttonNormal,fastTextButton.buttonDown);
    fastTextButton.setColour(TextButton::textColourOffId, Colours::yellow);
    buttonStyle.drawButtonBackground(g,slowTextButton,juce::Colours::lightgoldenrodyellow,slowTextButton.buttonNormal,slowTextButton.buttonDown);
    slowTextButton.setColour(TextButton::textColourOffId, Colours::black);
    // 5th set
    buttonStyle.drawButtonBackground(g,roughTextButton,juce::Colours::blue,roughTextButton.buttonNormal,roughTextButton.buttonDown);
    roughTextButton.setColour(TextButton::textColourOffId, Colours::red);
    buttonStyle.drawButtonBackground(g,smoothTextButton,juce::Colours::orange,smoothTextButton.buttonNormal,smoothTextButton.buttonDown);
    smoothTextButton.setColour(TextButton::textColourOffId, Colours::lightcyan);
    // 6th set
    buttonStyle.drawButtonBackground(g,shortTextButton,juce::Colours::lightsteelblue,shortTextButton.buttonNormal,shortTextButton.buttonDown);
    shortTextButton.setColour(TextButton::textColourOffId, Colours::lightsalmon);
    buttonStyle.drawButtonBackground(g,longTextButton,juce::Colours::grey,longTextButton.buttonNormal,longTextButton.buttonDown);
    longTextButton.setColour(TextButton::textColourOffId, Colours::white);
}
// layout button positions
void ControlComponent::resized()
{
    // creating variables to make it easier to read and adjust everything all at once.
    // with some offsets
    const auto buttonPosY = 55;
    const auto buttonWidth = 150;
    const auto buttonHeigth = 45;
    DarkTextButton.setBounds(0, buttonPosY, buttonWidth, buttonHeigth);
    LightTextButton.setBounds(DarkTextButton.getRight(), buttonPosY, buttonWidth, buttonHeigth);
    condensedTextButton.setBounds(0, buttonPosY + 60, buttonWidth, buttonHeigth);
    spaciousTextButton.setBounds(condensedTextButton.getRight(), buttonPosY + 60, buttonWidth, buttonHeigth);
    predictableTextButton.setBounds(0, buttonPosY + 120, buttonWidth, buttonHeigth);
    experimentalTextButton.setBounds(predictableTextButton.getRight(), buttonPosY + 120, buttonWidth, buttonHeigth);
    slowTextButton.setBounds(0, buttonPosY + 180, buttonWidth, buttonHeigth);
    fastTextButton.setBounds(slowTextButton.getRight(), buttonPosY + 180, buttonWidth, buttonHeigth);
    smoothTextButton.setBounds(0, buttonPosY + 240, buttonWidth, buttonHeigth);
    roughTextButton.setBounds(smoothTextButton.getRight(), buttonPosY + 240, buttonWidth, buttonHeigth);
    shortTextButton.setBounds(0, buttonPosY + 300, buttonWidth, buttonHeigth);
    longTextButton.setBounds(shortTextButton.getRight(), buttonPosY + 300, buttonWidth, buttonHeigth);
}

void ControlComponent::createButton (juce::TextButton& textButton, juce::AudioProcessorValueTreeState& apvts, juce::String paramID)
{
    // button text and making visible
    ignoreUnused(apvts);
    textButton.setButtonText(paramID);
    addAndMakeVisible(textButton);
}
// function for protecting range to making sure slider doesn't get stuck
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
// Changing Filter Frequency, filterttype and waveformtype.
void ControlComponent::changeFilter(juce::AudioProcessorValueTreeState& apvts, juce::Slider& slider,juce::ComboBox& combobox,juce::ComboBox& combobox2)
{
    // 3 variables being affected by these buttons. Loaded from APVTS.
    auto& filterCutoffnew = *apvts.getRawParameterValue("filtercutoff");
    auto& filterTypeNew = *apvts.getRawParameterValue("filtertype");
    auto& oscwaveTypeNew =*apvts.getRawParameterValue("oscwavetype1");
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
                // switching to different filtertype
                if (filterCutoffnew > 20000 && filterTypeNew != 2 && oscwaveTypeNew == 2)
                {
                    filterTypeNew = 2;
                    filterCutoffnew = 100;
                }
                // switching to different waveform type
                if (oscwaveTypeNew == 0 &&filterCutoffnew > 20000 && filterTypeNew == 0 )
                {
                    oscwaveTypeNew = 1;
                    filterCutoffnew = 1000;
                }
                if (oscwaveTypeNew == 1 &&filterCutoffnew > 20000 && filterTypeNew == 0 )
                {
                    oscwaveTypeNew = 2;
                    filterCutoffnew = 1000;
                }
                if (oscwaveTypeNew == 2 &&filterCutoffnew > 20000 && filterTypeNew == 0 )
                {
                    oscwaveTypeNew = 1;
                    filterCutoffnew = 1000;
                }
                // protecting the range
                protectRange(0,20000,filterCutoffnew);
                slider.setValue(filterCutoffnew);
                combobox.setSelectedItemIndex(static_cast<int>(filterTypeNew));
                combobox2.setSelectedItemIndex(static_cast<int>(oscwaveTypeNew));
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
                else if (counterDark <= 0)
                {
                    counterDark = 1;
                }
                // switching between oscillators if user is at the end of range
                if (filterTypeNew == 2 && filterCutoffnew <= 20)
                {
                    filterTypeNew = 0;
                    filterCutoffnew = 19000;
                }
                // setting cutoff based on counter position and stepsize.
                filterCutoffnew = filterCutoffnew - stepDark*counterDark;
                if (oscwaveTypeNew == 2 &&filterCutoffnew <= 20 && filterTypeNew == 0 )
                {
                    oscwaveTypeNew = 1;
                    filterCutoffnew = 3000;
                }
                if (oscwaveTypeNew == 1 &&filterCutoffnew <= 20 && filterTypeNew == 0 )
                {
                    oscwaveTypeNew = 0;
                    filterCutoffnew = 19000;
                }
                protectRange(0,20000,filterCutoffnew);
                slider.setValue(filterCutoffnew);
                combobox.setSelectedItemIndex(static_cast<int>(filterTypeNew));
                combobox2.setSelectedItemIndex(static_cast<int>(oscwaveTypeNew));
            };
}
// changing Dry Wet of the Delay
void ControlComponent::changeSpace(juce::AudioProcessorValueTreeState& apvts,
                                   juce::Slider& slider1,
                                   juce::Slider& slider2,
                                   juce::Slider& slider3)
{
    // retrieving current parameter values
    auto& drywetLnew = *apvts.getRawParameterValue("drywetL");
    auto& drywetRnew = *apvts.getRawParameterValue("drywetR");
    auto& drywetCnew = *apvts.getRawParameterValue("drywetC");

    condensedTextButton.onClick = [&]()
            {
                counterCond ++;
                counterSpac = 0;
                drywetLnew = drywetLnew - stepCondDW*0.83453459;
                drywetRnew = drywetRnew - stepCondDW*0.9275978;
                drywetCnew = drywetCnew - stepCondDW*0.9368304;
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
                drywetLnew = static_cast<float>(drywetLnew + stepSpacDW * 0.9234729384);
                drywetRnew = static_cast<float>(drywetRnew + stepSpacDW * 0.8923472349);
                drywetCnew = static_cast<float>(drywetCnew + stepSpacDW * 0.9458734697);
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
        fmDepthNew = static_cast<float>(fmDepthNew - stepPred * 0.890780568956);
        fmSpeedNew = static_cast<float>(fmSpeedNew - stepPred * 0.76249634987);
        amDepthNew = amDepthNew - stepPredamDepth ;
        if (fmDepthNew >= 90)
        {
            stepPredamDepth = 0;
        }
        else
        {
            stepPredamDepth = static_cast<float>(0.025);
        }
        resNew = resNew - stepRes;
        counterPred ++;
        stepPred += static_cast<float>(0.5);
        protectRange(0,100,fmDepthNew);
        protectRange(0,100,fmSpeedNew);
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
        if(fmDepthNew <= 60 && amDepthNew >= 0.5)
        {
            stepExpAmd = 0;
        }
        else
        {
            stepExpAmd = static_cast<float>(0.025);
        }
        amDepthNew = amDepthNew + stepExpAmd ;
        fmDepthNew = static_cast<float>(fmDepthNew + stepExp * 0.67852547957);
        fmSpeedNew = static_cast<float>(fmSpeedNew + stepExp * 0.5639);
        resNew = resNew + stepRes;
        stepExp += static_cast<float>(0.5);

        protectRange(0,100,fmDepthNew);
        protectRange(0,100,fmSpeedNew);
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
           amDepthNew = static_cast<float>(0.3);
        }
        counterSlow = 1;
        stepSlowAmf = 0.05f;
        stepSlowAtt = 0.01f;
        amSpeedNew = amSpeedNew + stepFastAmf*(counterFast/2);
        attackNew = static_cast<float>(attackNew - 0.005);
        counterFast ++;
        stepFastAtt +=0.1f;
        stepFastAmf += 0.015f;
        protectRange(0,60,amSpeedNew);
        protectRange(0,1,attackNew);
        slider2.setValue(amSpeedNew);
        slider3.setValue(attackNew);
        slider4.setValue(amDepthNew);
    };
    slowTextButton.onClick = [&]()
    {
        counterFast = 1;
        stepFastAmf = static_cast<float>(0.05);
        stepFastAtt = 0.1f;
        amSpeedNew = amSpeedNew - stepSlowAmf*(static_cast<float>(counterSlow / 2));
        attackNew = static_cast<float>(attackNew + 0.005);
        counterSlow ++;
        stepSlowAtt += 0.025f;
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
            stepRoughtrim = {static_cast<float>(0.1)};
        }
        // after 6 it will make smaller steps
        else
        {
            stepRoughtrim = static_cast<float>(0.05);
        }
        counterSmooth = 2;
        stepSmoothDr = 0.5;
        stepSmoothtrim = static_cast<float>(0.05);
        driveNew = driveNew + stepRoughDr;

        if (driveNew >= 100)
        {
            if(trimNew < 0.666)
            {
                trimNew = trimNew +stepRoughtrim;
            }
        }
        else
        {
            trimNew = trimNew - stepRoughtrim;
        }
        counterRough ++;
        stepRoughDr +=0.5f;
        stepRoughtrim += 0.005f;
        protectRange(1,100,driveNew);
        protectRange(static_cast<float>(0.2), 1.0, trimNew);
        slider1.setValue(driveNew);
        slider2.setValue(trimNew);

    };
    smoothTextButton.onClick = [&]()
    {
        if(driveNew >= 20)
        {
            stepSmoothtrim = {static_cast<float>(0.005)};
        }
        else
        {
            stepSmoothtrim = static_cast<float>(0.1);
        }

        counterRough = 0;
        stepRoughDr = static_cast<float>(0.005);
        stepRoughtrim = static_cast<float>(0.1);
        counterSmooth ++;
        driveNew = driveNew - stepSmoothDr;
        trimNew = trimNew + stepSmoothtrim;
        stepSmoothDr += static_cast<float>(0.5);
        stepSmoothtrim +=0.005f;
        protectRange(1,100,driveNew);
        protectRange(static_cast<float>(0.2), 1.0, trimNew);
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
        stepLongFb = static_cast<float>(0.005);
        stepLongR = static_cast<float>(0.05);
        counterShort ++;
        releaseNew = releaseNew - stepLongR;
        feedbackLNew = static_cast<float>(feedbackLNew - stepShortFb * 0.82094567);
        feedbackRNew = static_cast<float>(feedbackRNew - stepShortFb * 0.66724569);
        feedbackCNew = static_cast<float>(feedbackCNew - stepShortFb * 0.74587934567);
        stepShortFb += static_cast<float>(0.0005);
        stepShortR +=0.005f;
        // adjusting delay time
        delaytimeLnew = static_cast<float>(delaytimeLnew - counterShort * 10.92385637);
        delaytimeRnew = static_cast<float>(delaytimeRnew - counterShort * 10.890567985);
        delaytimeCnew = static_cast<float>(delaytimeCnew - counterShort * 10.32572946);
        //protecting ranges
        protectRange(0,3000,delaytimeLnew);
        protectRange(0,3000,delaytimeCnew);
        protectRange(0,3000,delaytimeRnew);
        // setting sliders
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
        stepShortFb = static_cast<float>(0.005);
        stepShortR = static_cast<float>(0.05);
        counterLong ++;
        releaseNew = releaseNew + stepLongR;
        feedbackLNew = static_cast<float>(feedbackLNew + stepLongFb * 0.987673342);
        feedbackRNew = static_cast<float>(feedbackRNew + stepLongFb * 0.789834);
        feedbackCNew = static_cast<float>(feedbackCNew + stepLongFb * 0.674634596);
        if (counterLong <= 20)
        {
            protectRange(0, static_cast<float>(0.60), feedbackLNew);
            protectRange(0, static_cast<float>(0.60), feedbackRNew);
            protectRange(0, static_cast<float>(0.60), feedbackCNew);
        }
        else
        {
            protectRange(0,1,feedbackLNew);
            protectRange(0,1,feedbackRNew);
            protectRange(0,1,feedbackCNew);
        }
        // adjusting delay time
        delaytimeLnew = static_cast<float>(delaytimeLnew + counterLong * 5.92385637);
        delaytimeRnew = static_cast<float>(delaytimeRnew + counterLong * 5.890567985);
        delaytimeCnew = static_cast<float>(delaytimeCnew + counterLong * 5.32572946);
        // protecting ranges
        protectRange(0,3000,delaytimeLnew);
        protectRange(0,3000,delaytimeCnew);
        protectRange(0,3000,delaytimeRnew);
        stepLongFb += static_cast<float>(0.005);
        stepLongR += 0.005f;
        // setting sliders
        slider1.setValue(releaseNew);
        slider2.setValue(feedbackLNew);
        slider3.setValue(feedbackRNew);
        slider4.setValue(feedbackCNew);
        slider5.setValue(delaytimeLnew);
        slider6.setValue(delaytimeRnew);
        slider7.setValue(delaytimeCnew);
    };
}