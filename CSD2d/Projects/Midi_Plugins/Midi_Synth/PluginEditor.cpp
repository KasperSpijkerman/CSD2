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
    shaper(audioProcessor.apvts,"drive","trim")

{
    setSize (600, 500);
    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
    addAndMakeVisible(LFO);
    addAndMakeVisible(shaper);
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
    const auto paddingY2 = 235;
    const auto paddingY3 = 350;
    const auto objectWidth = 300;
    const auto objectHeight = 200;
    osc.setBounds(paddingX,paddingY,objectWidth,objectHeight);
    adsr.setBounds(osc.getRight(),paddingY,objectWidth, objectHeight);
    filter.setBounds(paddingX,paddingY2,objectWidth,objectHeight);
    LFO.setBounds(osc.getRight(),paddingY2,objectWidth,objectHeight);
    shaper.setBounds(osc.getRight(),paddingY3,objectWidth,objectHeight);

}

