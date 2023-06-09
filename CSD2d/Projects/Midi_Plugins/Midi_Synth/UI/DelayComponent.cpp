#include "DelayComponent.h"

//constructor
DelayComponent::DelayComponent(juce::AudioProcessorValueTreeState& apvts,
                               juce::String dWLid,
                               juce::String dWRid,
                               juce::String dWCid,
                               juce::String fbLid,
                               juce::String fbRid,
                               juce::String fbCid,
                               juce::String dtLid,
                               juce::String dtRid,
                               juce::String dtCid):
        delayknobs("knobgrey.png"),
        delayknobsDT("knobpurple.png")
{
    // DryWet
    setSliderWithLabel(drywetLSlider,drywetLLabel,apvts,dWLid,drywetLSliderAttachment);
    setSliderWithLabel(drywetRSlider,drywetRLabel,apvts,dWRid,drywetRSliderAttachment);
    setSliderWithLabel(drywetCSlider,drywetCLabel,apvts,dWCid,drywetCSliderAttachment);
    // Feedback LCR
    setSliderWithLabel(feedbackLSlider,feedbackLLabel,apvts,fbLid,feedbackLSliderAttachment);
    setSliderWithLabel(feedbackRSlider,feedbackRLabel,apvts,fbRid,feedbackRSliderAttachment);
    setSliderWithLabel(feedbackCSlider,feedbackCLabel,apvts,fbCid,feedbackCSliderAttachment);
    // Delaytime LRC
    setSliderWithLabel(delayTimeLSlider,delayTimeLLabel,apvts,dtLid,delayTimeLSliderAttachment);
    setSliderWithLabel(delayTimeRSlider,delayTimeRLabel,apvts,dtRid,delayTimeRSliderAttachment);
    setSliderWithLabel(delayTimeCSlider,delayTimeCLabel,apvts,dtCid,delayTimeCSliderAttachment);

    drywetLSlider.setLookAndFeel(&delayknobs);
    drywetRSlider.setLookAndFeel(&delayknobs);
    drywetCSlider.setLookAndFeel(&delayknobs);

    delayTimeLSlider.setLookAndFeel(&delayknobsDT);
    delayTimeRSlider.setLookAndFeel(&delayknobsDT);
    delayTimeCSlider.setLookAndFeel(&delayknobsDT);

    feedbackLSlider.setLookAndFeel(&delayknobs);
    feedbackRSlider.setLookAndFeel(&delayknobs);
    feedbackCSlider.setLookAndFeel(&delayknobs);
}
// destructor
DelayComponent::~DelayComponent()
{

}
void DelayComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::purple);
    g.setColour (juce::Colours::white);
    g.setFont (30.0f);
    g.drawFittedText ("Delay", getLocalBounds(), juce::Justification::centredTop, 1);
}
// layout slider positions
void DelayComponent::resized()
{
    // creating variables to make it easier to read and adjust everything all at once.
    // creating variables to make it easier to read and adjust everything all at once.
    const auto sliderPosY = 55;
    const auto sliderWidth = 90;
    const auto sliderHeigth = 80;
    const auto labelYOffset = 20;
    const auto labelHeight = 15;

    // dry wet setting position
    drywetLSlider.setBounds(0,sliderPosY,sliderWidth,sliderHeigth);
    drywetLLabel.setBounds(drywetLSlider.getX(),drywetLSlider.getY()- labelYOffset,drywetLSlider.getWidth(),labelHeight);
    drywetRSlider.setBounds(200,sliderPosY,sliderWidth,sliderHeigth);
    drywetRLabel.setBounds(drywetRSlider.getX(),drywetRSlider.getY()- labelYOffset,drywetRSlider.getWidth(),labelHeight);
    drywetCSlider.setBounds(100,sliderPosY,sliderWidth,sliderHeigth);
    drywetCLabel.setBounds(drywetCSlider.getX(),drywetCSlider.getY()- labelYOffset,drywetCSlider.getWidth(),labelHeight);

    // feedback setting position
    feedbackLSlider.setBounds(0,sliderPosY + 120,sliderWidth,sliderHeigth);
    feedbackLLabel.setBounds(feedbackLSlider.getX(),feedbackLSlider.getY()- labelYOffset,feedbackLSlider.getWidth(),labelHeight);
    feedbackRSlider.setBounds(200,sliderPosY + 120,sliderWidth,sliderHeigth);
    feedbackRLabel.setBounds(feedbackRSlider.getX(),feedbackRSlider.getY()- labelYOffset,feedbackRSlider.getWidth(),labelHeight);
    feedbackCSlider.setBounds(100,sliderPosY + 120,sliderWidth,sliderHeigth);
    feedbackCLabel.setBounds(feedbackCSlider.getX(),feedbackCSlider.getY()- labelYOffset,feedbackCSlider.getWidth(),labelHeight);
    // delaytime setting position
    delayTimeLSlider.setBounds(0,sliderPosY + 240,sliderWidth,sliderHeigth);
    delayTimeLLabel.setBounds(delayTimeLSlider.getX(),delayTimeLSlider.getY()- labelYOffset,delayTimeLSlider.getWidth(),labelHeight);
    delayTimeRSlider.setBounds(200,sliderPosY + 240,sliderWidth,sliderHeigth);
    delayTimeRLabel.setBounds(delayTimeRSlider.getX(),delayTimeRSlider.getY()- labelYOffset,delayTimeRSlider.getWidth(),labelHeight);
    delayTimeCSlider.setBounds(100,sliderPosY + 240,sliderWidth,sliderHeigth);
    delayTimeCLabel.setBounds(delayTimeCSlider.getX(),delayTimeCSlider.getY()- labelYOffset,delayTimeCSlider.getWidth(),labelHeight);
}