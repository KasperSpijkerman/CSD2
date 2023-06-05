#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p),
    audioProcessor (p) ,
    osc(audioProcessor.apvts,"oscwavetype1","fmfreq","fmdepth"),
    adsr (audioProcessor.apvts),
    filter(audioProcessor.apvts, "filtertype", "filtercutoff", "filterresonance"),
    LFO(audioProcessor.apvts,"lfofreq","lfodepth"),
    shaper(audioProcessor.apvts,"drive","trim"),
    control(audioProcessor.apvts,"Light","Dark","Condensed","Atmospheric","Predictable","Experimental","Fast","Slow","Rough","Smooth"),
    delay(audioProcessor.apvts,"drywetL","drywetR","drywetC","feedbackL","feedbackR","feedbackC","delaytimeL","delaytimeR","delaytimeC")

{
    setSize (1000, 800);
    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
    addAndMakeVisible(LFO);
    addAndMakeVisible(shaper);
    addAndMakeVisible(control);
    addAndMakeVisible(delay);
    startTimer(10);

}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{

    g.fillAll(juce::Colours::purple);
    g.setColour(juce::Colours::green);
    g.setFont (30.0f);
//    g.drawFittedText ("The Teleporter", getLocalBounds(), juce::Justification::centredTop, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    const auto paddingX = 5;
    const auto paddingY = 35;
    const auto paddingY2 = 400;
    const auto paddingY3 = 550;
    // standard formats
    const auto objectWidth = 300;
    const auto objectHeight = 200;
    // bigger format
    const auto objectWidthBig = 300;
    const auto objectHeightBig = 600;
    const auto moveRight = 400;
    // placing objects on screen
    osc.setBounds(paddingX,paddingY,objectWidth,objectHeight);
    adsr.setBounds(osc.getRight()+moveRight,paddingY,objectWidth, objectHeight);
    filter.setBounds(paddingX,paddingY2,objectWidth,objectHeight);
    LFO.setBounds(osc.getRight()+moveRight,paddingY2,objectWidth,objectHeight);
    shaper.setBounds(osc.getRight()+moveRight,paddingY3,objectWidth,objectHeight);
    control.setBounds(getWidth()/2.7,getHeight()/500,objectWidthBig,objectHeightBig);
    delay.setBounds(getWidth()/3,getHeight()/2,objectWidthBig,objectHeightBig);
}
// updating the data based on buttons
void AudioPluginAudioProcessorEditor::updateControlData()
{
    // passing audio parameters and the right sliders to adjust
    // changing cutoff frequency
    control.changeFilter(audioProcessor.apvts,
                         filter.filterCutoffSlider);
    // changing Delay dry wet and delay times
    control.changeSpace(audioProcessor.apvts,
                        delay.drywetLSlider,
                        delay.drywetRSlider,
                        delay.drywetCSlider,
                        delay.delayTimeLSlider,
                        delay.delayTimeRSlider,
                        delay.delayTimeCSlider);
    // changing FM params and Resonance
    control.changePredict(audioProcessor.apvts,
                          osc.fmDepthSlider,
                          osc.fmFreqSlider,
                          filter.filterResonanceSlider);
    // changing AM and Attack time
    control.changeSpeed(audioProcessor.apvts,
                        LFO.LFODepthSlider,
                        LFO.LFOFreqSlider,
                        adsr.attackSlider);
    // changing Drive and trim
    control.changeTexture(audioProcessor.apvts,
                          shaper.ShaperDriveSlider,
                          shaper.ShaperTrimSlider);
}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    updateControlData();
}