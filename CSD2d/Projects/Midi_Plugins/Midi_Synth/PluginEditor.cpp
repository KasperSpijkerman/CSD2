#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p) , adsr (audioProcessor.apvts)
{
    setSize (400, 300);
    oscSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts,"osc",oscillatorSelect);
    addAndMakeVisible(adsr);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{

}

void AudioPluginAudioProcessorEditor::resized()
{
    adsr.setBounds(getLocalBounds());
}

