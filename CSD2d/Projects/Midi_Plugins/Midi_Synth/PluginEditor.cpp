#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    // linkin parameters
    attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "attack",attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "decay",decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "sustain",sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "release",releaseSlider);

    oscSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts,"osc",oscillatorSelect);
    setSize (400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
