#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p) , osc(audioProcessor.apvts, "oscwavetype1"), adsr (audioProcessor.apvts)
{
    setSize (400, 300);
    oscSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts,"osc",oscillatorSelect);
    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
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
    adsr.setBounds(getWidth()/2,0,getWidth() /2, getHeight());
    osc.setBounds(10,10,100,30);
}

