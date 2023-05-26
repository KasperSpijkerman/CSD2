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
    control(audioProcessor.apvts,"light","dark")

{
    setSize (1000, 750);
    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
    addAndMakeVisible(LFO);
    addAndMakeVisible(shaper);
    addAndMakeVisible(control);
    startTimer(100);

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
    const auto objectWidth = 300;
    const auto objectHeight = 200;
    const auto moveRight = 400;
    osc.setBounds(paddingX,paddingY,objectWidth,objectHeight);
    adsr.setBounds(osc.getRight()+moveRight,paddingY,objectWidth, objectHeight);
    filter.setBounds(paddingX,paddingY2,objectWidth,objectHeight);
    LFO.setBounds(osc.getRight()+moveRight,paddingY2,objectWidth,objectHeight);
    shaper.setBounds(osc.getRight()+moveRight,paddingY3,objectWidth,objectHeight);
    control.setBounds(getWidth()/3,getHeight()/3,objectWidth,objectHeight);
}

void AudioPluginAudioProcessorEditor::updateControlData()
{
    control.changeFilter();
    filter.filterCutoffSlider.setValue(juce::jlimit (0.0f, 20000.0f,control.value) );
}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    updateControlData();
}