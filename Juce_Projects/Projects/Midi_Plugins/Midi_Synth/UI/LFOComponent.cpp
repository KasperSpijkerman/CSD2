#include "LFOComponent.h"

//constructor
LFOComponent::LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String LFOFreqId, juce::String LFODepthId,juce::String bpmId)
:
        lfofreqknob("knobmovement.png"),
        lfodepthknob("knobmovement.png")
{
    LFOFreqSlider.setLookAndFeel(&lfofreqknob);
    LFODepthSlider.setLookAndFeel(&lfodepthknob);
    bpmSlider.setLookAndFeel(&lfodepthknob);

    LFOFreqlabel.setLookAndFeel(&labelLookAndFeel);
    LFODepthlabel.setLookAndFeel(&labelLookAndFeel);
    bpmLabel.setLookAndFeel(&labelLookAndFeel);
    // making sliders, linking labels, setting text and colour in a function
    setSliderWithLabel(LFOFreqSlider,LFOFreqlabel,apvts,LFOFreqId,LFOFreqAttachment);
    setSliderWithLabel(LFODepthSlider,LFODepthlabel,apvts,LFODepthId,LFODepthAttachment);
    setSliderWithLabel(bpmSlider,bpmLabel,apvts,bpmId,bpmAttachment);
    // background panel

    // Setup BPM Sync Button
    bpmSyncButton.setButtonText("BPM Sync");
    addAndMakeVisible(bpmSyncButton);

    // Attach the BPM Sync button to the AudioProcessorValueTreeState (assuming you've created a parameter for it)
    bpmSyncAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, "sync2", bpmSyncButton);

    background = ImageFileFormat::loadFrom(BinaryData::backgroundpanel_png, BinaryData::backgroundpanel_pngSize);
}
// destructor
LFOComponent::~LFOComponent()
{
    setLookAndFeel (nullptr);
}
void LFOComponent::paint(juce::Graphics& g)
{
    /// Background
    g.fillAll(juce::Colour::fromRGBA(0, 0, 0, 20)); // Adjust the alpha value for opacity

    // Draw pink shadow for the title
    g.setColour(juce::Colour::fromRGBA(255, 105, 180, 80)); // Increased pink shadow opacity
    g.setFont(34.0f);
    g.drawFittedText("Movement", getLocalBounds().translated(4, 4), juce::Justification::centredTop, 1);

    // Draw the title with the adjusted light blue color
    g.setColour(juce::Colours::cyan); // Lighter blue color
    g.setFont(34.0f);
    g.drawFittedText("Movement", getLocalBounds(), juce::Justification::centredTop, 1);

    // Draw more prominent pink glow
    g.setColour(juce::Colour::fromRGBA(255, 105, 180, 60)); // Increased pink glow opacity
    for (int i = 0; i < 3; ++i)
    {
        g.drawFittedText("Movement", getLocalBounds().translated(-i, -i), juce::Justification::centredTop, 1);
    }
}
// layout slider positions
void LFOComponent::resized()
{
    // creating variables to make it easier to read and adjust everything all at once.
    const auto sliderPosY = 55;
    const auto sliderWidth = 130;
    const auto sliderHeigth = 110;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    LFOFreqSlider.setBounds(30,sliderPosY,sliderWidth,sliderHeigth);
    LFOFreqlabel.setBounds(LFOFreqSlider.getX(),LFOFreqSlider.getY()- labelYOffset,LFOFreqSlider.getWidth(),labelHeight);

    LFODepthSlider.setBounds(LFOFreqSlider.getRight()+60,sliderPosY,sliderWidth,sliderHeigth);
    LFODepthlabel.setBounds(LFODepthSlider.getX(),LFODepthSlider.getY()-labelYOffset,LFODepthSlider.getWidth(),labelHeight);

    bpmSlider.setBounds(LFOFreqSlider.getRight()-35,sliderPosY,sliderWidth,sliderHeigth);
    bpmLabel.setBounds(bpmSlider.getX(),bpmSlider.getY()-labelYOffset,bpmSlider.getWidth(),labelHeight);
    bpmSyncButton.setBounds(bpmSlider.getRight() + 10, bpmSlider.getY() + bpmSlider.getHeight() + 10, 80, 20);  // Adjust this to position the button accordingly
}