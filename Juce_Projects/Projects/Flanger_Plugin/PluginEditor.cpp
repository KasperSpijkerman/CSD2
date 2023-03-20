/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>

//==============================================================================
FlangerAudioProcessorEditor::FlangerAudioProcessorEditor (FlangerAudioProcessor& p,juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState (vts), audioProcessor (p)
{

    // dry wet slider and label
    drywetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    drywetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    drywetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "drywet",drywetSlider);
    drywetSlider.setTextValueSuffix (" Dry-wet");
    // labels for text attached to slider
    drywetLabel.setText ("Dry-Wet", juce::dontSendNotification);
    drywetLabel.attachToComponent (&drywetSlider, true);
    drywetLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(drywetSlider);

    // feedback slider and label
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    feedbackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "feedback",feedbackSlider);
    feedbackSlider.setTextValueSuffix (" Feedback");
    // labels for text attached to slider
    feedbackLabel.setText ("Feedback", juce::dontSendNotification);
    feedbackLabel.attachToComponent (&feedbackSlider, true);
    feedbackLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(feedbackSlider);


    // rate L slider and label
    rateLSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateLSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    rateLSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ratel",rateLSlider);
    rateLSlider.setTextValueSuffix (" Rate L");
    // labels for text attached to slider
    rateLLabel.setText ("Rate L", juce::dontSendNotification);
    rateLLabel.attachToComponent (&rateLSlider, true);
    rateLLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(rateLSlider);

    // rate R slider and label
    rateRSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateRSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    rateRSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "rater",rateRSlider);
    rateRSlider.setTextValueSuffix (" Rate R");
    // labels for text attached to slider
    rateRLabel.setText ("Rate R", juce::dontSendNotification);
    rateRLabel.attachToComponent (&rateRSlider, true);
    rateRLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(rateRSlider);

    // rate R slider and label
    depthLSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthLSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    depthLSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "depthl",depthLSlider);
    depthLSlider.setTextValueSuffix (" Depth L");
    // labels for text attached to slider
    depthLLabel.setText ("Depth L", juce::dontSendNotification);
    depthLLabel.attachToComponent (&depthLSlider, true);
    depthLLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(depthLSlider);

    // rate R slider and label
    depthRSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthRSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    depthRSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "depthr",depthRSlider);
    depthRSlider.setTextValueSuffix (" Depth R");
    // labels for text attached to slider
    depthRLabel.setText ("Depth R", juce::dontSendNotification);
    depthRLabel.attachToComponent (&depthRSlider, true);
    depthRLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(depthRSlider);

    // rate R slider and label
    intensitySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    intensitySlider.setTextBoxStyle(juce::Slider::TextBoxBelow,true,200,25);
    intensitySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "intensity",intensitySlider);
    intensitySlider.setTextValueSuffix (" Intensity");
    // labels for text attached to slider
    intensityLabel.setText ("Intensity", juce::dontSendNotification);
    intensityLabel.attachToComponent (&intensitySlider, true);
    intensityLabel.setJustificationType(juce::Justification::topLeft);
    // adding the actual slider
    addAndMakeVisible(intensitySlider);

    // specify here on which UDP port number to receive incoming OSC messages
    if (! connect (9001))    {
        showConnectionErrorMessage ("Error: could not connect to UDP port 9001.");
    }                   // [3]

    juce::OSCReceiver::addListener(this, "/juce/drywet");
    juce::OSCReceiver::addListener(this, "/juce/feedback");
    setSize (800, 800);

}

FlangerAudioProcessorEditor::~FlangerAudioProcessorEditor()
{}

//==============================================================================
void FlangerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::darkviolet);
    g.setFont (juce::Font ("New Times Roman", 83.0f, juce::Font::bold));
    g.setColour(juce::Colours::orange);
    g.drawText("SpinFlange",160,50,500,100,juce::Justification::centred);
    g.setFont (juce::Font ("New Times Roman", 80.0f, juce::Font::bold));
    g.setColour(juce::Colours::deepskyblue);
    g.drawText("SpinFlange",160,50,500,100,juce::Justification::centred);



}


void FlangerAudioProcessorEditor::resized()
{
    // layout sliders
    drywetSlider.setBounds(getWidth() / 8.2, getHeight() / 2.0, 200, 100);
    feedbackSlider.setBounds(getWidth() / 1.4, getHeight() / 2.0, 200, 100);
    rateLSlider.setBounds(getWidth() / 8.2, getHeight() / 4.0, 200, 100);
    rateRSlider.setBounds(getWidth() / 1.4, getHeight() / 4.0, 200, 100);
    depthLSlider.setBounds(getWidth() / 8.2, getHeight() / 1.2, 200, 100);
    depthRSlider.setBounds(getWidth() / 1.4, getHeight() / 1.2, 200, 100);
    intensitySlider.setBounds(getWidth() / 2.5, getHeight() / 1.2, 200, 100);

    // set the color to red
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::deeppink);
}

// Function for receiving OSC and getting the messages.
void FlangerAudioProcessorEditor::oscMessageReceived (const juce::OSCMessage& message)
{
    if (message.size() == 1 && message[0].isFloat32())   {}
    OSCAddressPattern drywetPattern("/juce/drywet");
    OSCAddressPattern feedbackPattern("/juce/feedback");

    OSCAddress messageAddress(message.getAddressPattern().toString());

    if (drywetPattern.matches(messageAddress))
    {
        drywetSlider.setValue (juce::jlimit (0.5f, 1.0f, message[0].getFloat32()));
    }

    else if (feedbackPattern.matches(messageAddress))
    {
        feedbackSlider.setValue (juce::jlimit (0.0f, 0.90f, message[0].getFloat32()));
    }
}

// debug OSC connection
void FlangerAudioProcessorEditor::showConnectionErrorMessage (const juce::String& messageText)
{
    juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                                            "Connection error",
                                            messageText,
                                            "OK");
}