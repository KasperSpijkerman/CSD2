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
    control(audioProcessor.apvts,"Light","Dark","Condensed","Spacious"),
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
    osc.setBounds(paddingX,paddingY,objectWidth,objectHeight);
    adsr.setBounds(osc.getRight()+moveRight,paddingY,objectWidth, objectHeight);
    filter.setBounds(paddingX,paddingY2,objectWidth,objectHeight);
    LFO.setBounds(osc.getRight()+moveRight,paddingY2,objectWidth,objectHeight);
    shaper.setBounds(osc.getRight()+moveRight,paddingY3,objectWidth,objectHeight);
    control.setBounds(getWidth()/2.7,getHeight()/500,objectWidthBig,objectHeightBig);
    delay.setBounds(getWidth()/3,getHeight()/2,objectWidthBig,objectHeightBig);
}

void AudioPluginAudioProcessorEditor::updateControlData()
{
    control.changeFilter();
    control.changeSpace();
    // changing filter cutoff
    filter.filterCutoffSlider.setValue(juce::jlimit (0.0f, 20000.0f,control.brightness) );
    // changing dry wet
    delay.drywetLSlider.setValue(juce::jlimit(0.1f,1.0f,control.distance));
    delay.drywetRSlider.setValue(juce::jlimit(0.1f,1.0f,control.distance));
    delay.drywetCSlider.setValue(juce::jlimit(0.1f,1.0f,control.distance));
    // changing delaytime
    delay.delayTimeLSlider.setValue(juce::jlimit(0.1f,3000.0f,control.length*0.897631f));
    delay.delayTimeRSlider.setValue(juce::jlimit(0.1f,3000.0f,control.length*0.912315715f));
    delay.delayTimeCSlider.setValue(juce::jlimit(0.1f,3000.0f,control.length*1.253456f));
}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    updateControlData();
}