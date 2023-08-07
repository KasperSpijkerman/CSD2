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
                               juce::String dtCid,
                               juce::String divLid,
                               juce::String divRid,
                               juce::String divCid,
                               juce::String syncid):
                               //changed
        delayknobsDW("knobbrightpurple.png"),
        delayknobsFB("knoblightpurple.png"),
        delayknobsDT("knobpurple.png")
{
    // Setting custom knobs
    // DryWet
    drywetLSlider.setLookAndFeel(&delayknobsDW);
    drywetRSlider.setLookAndFeel(&delayknobsDW);
    drywetCSlider.setLookAndFeel(&delayknobsDW);
    // Feedback LCR
    delayTimeLSlider.setLookAndFeel(&delayknobsDT);
    delayTimeRSlider.setLookAndFeel(&delayknobsDT);
    delayTimeCSlider.setLookAndFeel(&delayknobsDT);
    // Delaytime LRC
    feedbackLSlider.setLookAndFeel(&delayknobsFB);
    feedbackRSlider.setLookAndFeel(&delayknobsFB);
    feedbackCSlider.setLookAndFeel(&delayknobsFB);
    //
    // division LRC
    divisionLSlider.setLookAndFeel(&delayknobsFB);
    divisionRSlider.setLookAndFeel(&delayknobsFB);
    divisionCSlider.setLookAndFeel(&delayknobsFB);

    // DryWet
    drywetLLabel.setLookAndFeel(&labelLookAndFeel);
    drywetRLabel.setLookAndFeel(&labelLookAndFeel);
    drywetCLabel.setLookAndFeel(&labelLookAndFeel);
    // Feedback LCR
    delayTimeLLabel.setLookAndFeel(&labelLookAndFeel);
    delayTimeRLabel.setLookAndFeel(&labelLookAndFeel);
    delayTimeCLabel.setLookAndFeel(&labelLookAndFeel);
    // Delaytime LRC
    feedbackLLabel.setLookAndFeel(&labelLookAndFeel);
    feedbackRLabel.setLookAndFeel(&labelLookAndFeel);
    feedbackCLabel.setLookAndFeel(&labelLookAndFeel);
    //
    // division LRC
    divisionLLabel.setLookAndFeel(&labelLookAndFeel);
    divisionRLabel.setLookAndFeel(&labelLookAndFeel);
    divisionCLabel.setLookAndFeel(&labelLookAndFeel);
    // DryWet
    setSliderWithLabel(drywetLSlider,drywetLLabel,apvts,dWLid,drywetLSliderAttachment);
    setSliderWithLabel(drywetRSlider,drywetRLabel,apvts,dWRid,drywetRSliderAttachment);
    setSliderWithLabel(drywetCSlider,drywetCLabel,apvts,dWCid,drywetCSliderAttachment);
    // Feedback LCR
    setSliderWithLabel(feedbackLSlider,feedbackLLabel,apvts,fbLid,feedbackLSliderAttachment);
    setSliderWithLabel(feedbackRSlider,feedbackRLabel,apvts,fbRid,feedbackRSliderAttachment);
    setSliderWithLabel(feedbackCSlider,feedbackCLabel,apvts,fbCid,feedbackCSliderAttachment);
    // Delaytime LRC // Division
    setSliderWithLabel(delayTimeLSlider,delayTimeLLabel,apvts,dtLid,delayTimeLSliderAttachment);
    setSliderWithLabel(delayTimeRSlider,delayTimeRLabel,apvts,dtRid,delayTimeRSliderAttachment);
    setSliderWithLabel(delayTimeCSlider,delayTimeCLabel,apvts,dtCid,delayTimeCSliderAttachment);
    // Delaytime LRC // Division
    setSliderWithLabel(divisionLSlider,divisionLLabel,apvts,divLid,divisionLSliderAttachment);
    setSliderWithLabel(divisionRSlider,divisionRLabel,apvts,divRid,divisionRSliderAttachment);
    setSliderWithLabel(divisionCSlider,divisionCLabel,apvts,divCid,divisionCSliderAttachment);

    //
    setButton(syncTogglebutton,apvts,syncid,syncToggleAttachment);
    // background panel
    background = ImageFileFormat::loadFrom(BinaryData::backgroundpanelbig_png, BinaryData::backgroundpanelbig_pngSize);;
}
// destructor
DelayComponent::~DelayComponent()
{
    setLookAndFeel (nullptr);
}
void DelayComponent::paint(juce::Graphics& g)
{
        // Background
        g.fillAll(juce::Colour::fromRGBA(0, 0, 0, 20)); // Adjust the alpha value for opacity

        // Draw pink shadow for the title
        g.setColour(juce::Colour::fromRGBA(255, 105, 180, 80)); // Increased pink shadow opacity
        g.setFont(34.0f);
        g.drawFittedText("Space", getLocalBounds().translated(4, 4), juce::Justification::centredTop, 1);

        // Draw the title with the adjusted light blue color
        g.setColour(juce::Colour::fromRGBA(173, 216, 255, 255)); // Lighter blue color
        g.setFont(34.0f);
        g.drawFittedText("Space", getLocalBounds(), juce::Justification::centredTop, 1);

        // Draw more prominent pink glow
        g.setColour(juce::Colour::fromRGBA(255, 105, 180, 60)); // Increased pink glow opacity
        for (int i = 0; i < 3; ++i)
        {
            g.drawFittedText("Space", getLocalBounds().translated(-i, -i), juce::Justification::centredTop, 1);
        }
}
// layout slider positions
void DelayComponent::resized()
{
    // creating variables to make it easier to read and adjust everything all at once.
    const auto sliderPosY = 55;
    const auto sliderWidth = 90;
    const auto sliderHeigth = 80;
    const auto sliderWidthsmall = 70;
    const auto sliderHeigthsmall = 60;
    const auto labelYOffset = 20;
    const auto labelHeight = 15;
    const auto labelHeightsmall = 12;
    // dry wet setting position
    drywetLSlider.setBounds(0+20,sliderPosY,sliderWidth,sliderHeigth);
    drywetLLabel.setBounds(drywetLSlider.getX()+20,drywetLSlider.getY()- labelYOffset,drywetLSlider.getWidth(),labelHeight);
    drywetRSlider.setBounds(200+20,sliderPosY,sliderWidth,sliderHeigth);
    drywetRLabel.setBounds(drywetRSlider.getX()+20,drywetRSlider.getY()- labelYOffset,drywetRSlider.getWidth(),labelHeight);
    drywetCSlider.setBounds(100+20,sliderPosY,sliderWidth,sliderHeigth);
    drywetCLabel.setBounds(drywetCSlider.getX(),drywetCSlider.getY()- labelYOffset,drywetCSlider.getWidth(),labelHeight);
    // feedback setting position
    feedbackLSlider.setBounds(0+20,sliderPosY + 100,sliderWidth,sliderHeigth);
    feedbackLLabel.setBounds(feedbackLSlider.getX()+20,feedbackLSlider.getY()- labelYOffset,feedbackLSlider.getWidth(),labelHeight);
    feedbackRSlider.setBounds(200+20,sliderPosY + 100,sliderWidth,sliderHeigth);
    feedbackRLabel.setBounds(feedbackRSlider.getX(),feedbackRSlider.getY()- labelYOffset,feedbackRSlider.getWidth(),labelHeight);
    feedbackCSlider.setBounds(100+20,sliderPosY + 100,sliderWidth,sliderHeigth);
    feedbackCLabel.setBounds(feedbackCSlider.getX()+20,feedbackCSlider.getY()- labelYOffset,feedbackCSlider.getWidth(),labelHeight);
    //delaytime setting position
    syncTogglebutton.setBounds(200,0,sliderWidth,sliderHeigth);
    delayTimeLSlider.setBounds(8+20, sliderPosY + 200, sliderWidthsmall, sliderHeigthsmall);
    delayTimeLLabel.setBounds(delayTimeLSlider.getX()+20, delayTimeLSlider.getY() - labelYOffset, delayTimeLSlider.getWidth(), labelHeightsmall);
    delayTimeRSlider.setBounds(208+20, sliderPosY + 200, sliderWidthsmall, sliderHeigthsmall);
    delayTimeRLabel.setBounds(delayTimeRSlider.getX()+20, delayTimeRSlider.getY() - labelYOffset, delayTimeRSlider.getWidth(), labelHeightsmall);
    delayTimeCSlider.setBounds(108+20, sliderPosY + 200, sliderWidthsmall, sliderHeigthsmall);
    delayTimeCLabel.setBounds(delayTimeCSlider.getX()+20, delayTimeCSlider.getY() - labelYOffset, delayTimeCSlider.getWidth(), labelHeightsmall);

    divisionLSlider.setBounds(8+20, sliderPosY + 280, sliderWidthsmall, sliderHeigthsmall);
    divisionLLabel.setBounds(divisionLSlider.getX()+20, divisionLSlider.getY() - labelYOffset, divisionLSlider.getWidth(), labelHeightsmall);
    divisionRSlider.setBounds(208+20, sliderPosY + 280, sliderWidthsmall, sliderHeigthsmall);
    divisionRLabel.setBounds(divisionRSlider.getX()+20, divisionRSlider.getY() - labelYOffset, divisionRSlider.getWidth(), labelHeightsmall);
    divisionCSlider.setBounds(108+20, sliderPosY + 280, sliderWidthsmall, sliderHeigthsmall);
    divisionCLabel.setBounds(divisionCSlider.getX()+20, divisionCSlider.getY() - labelYOffset, divisionCSlider.getWidth(), labelHeightsmall);

}

void DelayComponent::setButton (juce::Button& button, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<buttonAttachment>& attachment)
{
    // Slider style, textbox and making visible
    button.setButtonText("Sync");
    addAndMakeVisible(button);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts,paramID,button);
}




