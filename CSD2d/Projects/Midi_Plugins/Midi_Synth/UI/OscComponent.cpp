#include "OscComponent.h"

//constructor
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String wavetypeID)
{
    juce::StringArray choices {"Sine","Saw", "Square"};
    oscWaveSelector.addItemList(choices,1);
    addAndMakeVisible(oscWaveSelector);
    // linking combobox
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts,wavetypeID,oscWaveSelector);


}
// destructor
OscComponent::~OscComponent()
{

}
void OscComponent::paint(juce::Graphics& g)
{
g.fillAll(juce::Colours::purple);
}
// layout slider positions
void OscComponent::resized()
{
    oscWaveSelector.setBounds(0,0,90,20);
}

