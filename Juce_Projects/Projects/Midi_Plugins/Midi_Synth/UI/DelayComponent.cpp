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
        delayknobsDW("knobspace.png"),
        delayknobsFB("knobduration.png"),
        delayknobsDT("knobduration.png")
{
    syncTogglebutton.addListener(this);
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
    syncTogglebutton.removeListener(this);
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
        g.setColour(juce::Colours::cyan); // Lighter blue color
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
void DelayComponent::resized() {

    const int panelWidth = 336;
    const int panelHeight = 397;
    const int titleSpace = 20; // space reserved for title
    const int sliderWidth = 85;
    const int sliderHeight = 75;
    const int labelYOffset = 22;

// Define our nine center points
    int centersX[3] = {panelWidth / 6, panelWidth / 2, 5 * panelWidth / 6};
    int centersY[3] = {titleSpace + panelHeight / 4, titleSpace + panelHeight / 2, titleSpace + 3 * panelHeight / 4}; // Updated Y values

// Position Sliders and Labels

// Row 1
    positionSliderAndLabel(drywetLSlider, drywetLLabel, centersX[0] - sliderWidth/2, centersY[0] - sliderHeight/2, sliderWidth, sliderHeight, labelYOffset);
    positionSliderAndLabel(drywetCSlider, drywetCLabel, centersX[1] - sliderWidth/2, centersY[0] - sliderHeight/2, sliderWidth, sliderHeight, labelYOffset);
    positionSliderAndLabel(drywetRSlider, drywetRLabel, centersX[2] - sliderWidth/2, centersY[0] - sliderHeight/2, sliderWidth, sliderHeight, labelYOffset);

// Row 2
    positionSliderAndLabel(feedbackLSlider, feedbackLLabel, centersX[0] - sliderWidth/2, centersY[1] - sliderHeight/2, sliderWidth, sliderHeight, labelYOffset);
    positionSliderAndLabel(feedbackCSlider, feedbackCLabel, centersX[1] - sliderWidth/2, centersY[1] - sliderHeight/2, sliderWidth, sliderHeight, labelYOffset);
    positionSliderAndLabel(feedbackRSlider, feedbackRLabel, centersX[2] - sliderWidth/2, centersY[1] - sliderHeight/2, sliderWidth, sliderHeight, labelYOffset);

// Row 3 (Delay Sliders)
    positionSliderAndLabel(delayTimeLSlider, delayTimeLLabel, centersX[0] - sliderWidth/2, centersY[2] - sliderHeight/2, sliderWidth, sliderHeight, labelYOffset);
    positionSliderAndLabel(delayTimeCSlider, delayTimeCLabel, centersX[1] - sliderWidth/2, centersY[2] - sliderHeight/2, sliderWidth, sliderHeight, labelYOffset);
    positionSliderAndLabel(delayTimeRSlider, delayTimeRLabel, centersX[2] - sliderWidth/2, centersY[2] - sliderHeight/2, sliderWidth, sliderHeight, labelYOffset);

// Row 3 (Division Sliders)
    positionSliderAndLabel(divisionLSlider, divisionLLabel, centersX[0] - sliderWidth/2, centersY[2] - sliderHeight/2, sliderWidth, sliderHeight, labelYOffset);
    positionSliderAndLabel(divisionCSlider, divisionCLabel, centersX[1] - sliderWidth/2, centersY[2] - sliderHeight/2, sliderWidth, sliderHeight, labelYOffset);
    positionSliderAndLabel(divisionRSlider, divisionRLabel, centersX[2] - sliderWidth/2, centersY[2] - sliderHeight/2, sliderWidth, sliderHeight, labelYOffset);

// Toggle button at the bottom
    syncTogglebutton.setBounds(20, 333, sliderWidth, sliderHeight);
}

void DelayComponent::setButton (juce::Button& button, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<buttonAttachment>& attachment)
{
    // Slider style, textbox and making visible
    button.setButtonText("Sync");
    addAndMakeVisible(button);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts,paramID,button);
}



void DelayComponent::buttonClicked(juce::Button* button) {
    if (button == &syncTogglebutton) {
        // If the sync is enabled
        if (syncTogglebutton.getToggleState()) {
            // Show the division sliders and labels
            divisionLSlider.setVisible(true);
            divisionRSlider.setVisible(true);
            divisionCSlider.setVisible(true);
            divisionLLabel.setVisible(true);
            divisionRLabel.setVisible(true);
            divisionCLabel.setVisible(true);

            // Hide the other sliders and labels
            delayTimeLSlider.setVisible(false);
            delayTimeRSlider.setVisible(false);
            delayTimeCSlider.setVisible(false);
            delayTimeLLabel.setVisible(false);
            delayTimeRLabel.setVisible(false);
            delayTimeCLabel.setVisible(false);
        } else {
            // Show the other sliders and labels
            delayTimeLSlider.setVisible(true);
            delayTimeRSlider.setVisible(true);
            delayTimeCSlider.setVisible(true);
            delayTimeLLabel.setVisible(true);
            delayTimeRLabel.setVisible(true);
            delayTimeCLabel.setVisible(true);

            // Hide the division sliders and labels
            divisionLSlider.setVisible(false);
            divisionRSlider.setVisible(false);
            divisionCSlider.setVisible(false);
            divisionLLabel.setVisible(false);
            divisionRLabel.setVisible(false);
            divisionCLabel.setVisible(false);
        }
        repaint();
        resized();
    }
}