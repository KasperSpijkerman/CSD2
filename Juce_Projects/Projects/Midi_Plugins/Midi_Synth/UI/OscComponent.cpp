#include "OscComponent.h"

//constructor
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts,
                                         juce::String wavetypeID, juce::String wavetypeID2, juce::String wavetypeID3,
                                         juce::String fmFreqId, juce::String fmDepthId,
                                         juce::String volumeID1,
                                         juce::String volumeID2,
                                         juce::String volumeID3)
:
        fmknobs("knobstate.png")
{
    juce::StringArray choices {"Sine","Square", "Saw"};
    oscWaveSelector.addItemList(choices,2);
    addAndMakeVisible(oscWaveSelector);
    // For 2nd oscillator
    oscWaveSelector2.addItemList(choices, 2);
    addAndMakeVisible(oscWaveSelector2);
    oscWaveSelectorAttachment2 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, wavetypeID2, oscWaveSelector2);
    // For 3rd oscillator
    oscWaveSelector3.addItemList(choices, 2);
    addAndMakeVisible(oscWaveSelector3);
    oscWaveSelectorAttachment3 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, wavetypeID3, oscWaveSelector3);
    // linking combobox
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts,wavetypeID,oscWaveSelector);
    // custom knobs
    fmFreqSlider.setLookAndFeel(&fmknobs);
    fmDepthSlider.setLookAndFeel(&fmknobs);

    fmFreqlabel.setLookAndFeel(&labelLookAndFeel);
    fmDepthlabel.setLookAndFeel(&labelLookAndFeel);

    oscVolumeSlider1.setLookAndFeel(&fmknobs);
    oscVolumeSlider2.setLookAndFeel(&fmknobs);
    oscVolumeSlider3.setLookAndFeel(&fmknobs);

    oscNoteOffsetSlider1.setLookAndFeel(&fmknobs);
    oscNoteOffsetSlider2.setLookAndFeel(&fmknobs);
    oscNoteOffsetSlider3.setLookAndFeel(&fmknobs);

    oscVolumeLabel1.setLookAndFeel(&labelLookAndFeel);
    oscVolumeLabel2.setLookAndFeel(&labelLookAndFeel);
    oscVolumeLabel3.setLookAndFeel(&labelLookAndFeel);

    oscWaveSelector.setLookAndFeel(&boxLookAndFeel);
    oscWaveSelector2.setLookAndFeel(&boxLookAndFeel);
    oscWaveSelector3.setLookAndFeel(&boxLookAndFeel);


    // making sliders, linking labels, setting text and colour in a function
    setSliderWithLabel(fmFreqSlider,fmFreqlabel,apvts,fmFreqId,fmFreqAttachment);
    setSliderWithLabel(fmDepthSlider,fmDepthlabel,apvts,fmDepthId,fmdepthAttachment);

    // For 1st oscillator volume
    setSliderWithLabel(oscVolumeSlider1, oscVolumeLabel1, apvts, volumeID1, oscVolumeAttachment1);

    // For 2nd oscillator volume
    setSliderWithLabel(oscVolumeSlider2, oscVolumeLabel2, apvts, volumeID2, oscVolumeAttachment2);

    // For 3rd oscillator volume
    setSliderWithLabel(oscVolumeSlider3, oscVolumeLabel3, apvts, volumeID3, oscVolumeAttachment3);

    // Oscillator 1 Note Offset
    setSliderWithLabel(oscNoteOffsetSlider1, oscNoteOffsetLabel1, apvts, "osc1offset", oscNoteOffsetAttachment1);

// Oscillator 2 Note Offset
    setSliderWithLabel(oscNoteOffsetSlider2, oscNoteOffsetLabel2, apvts, "osc2offset", oscNoteOffsetAttachment2);

// Oscillator 3 Note Offset
    setSliderWithLabel(oscNoteOffsetSlider3, oscNoteOffsetLabel3, apvts, "osc3offset", oscNoteOffsetAttachment3);
    // background panel
    background = ImageFileFormat::loadFrom(BinaryData::backgroundpanel_png, BinaryData::backgroundpanel_pngSize);;
}
// destructor
OscComponent::~OscComponent()
{
    // protection
    setLookAndFeel (nullptr);
}
void OscComponent::paint(juce::Graphics& g)
{
    /// Background
    g.fillAll(juce::Colour::fromRGBA(0, 0, 0, 20)); // Adjust the alpha value for opacity

    // Draw pink shadow for the title
    g.setColour(juce::Colour::fromRGBA(255, 105, 180, 50)); // Increased pink shadow opacity
    g.setFont(34.0f);
    g.drawFittedText("State", getLocalBounds().translated(4, 4), juce::Justification::centredTop, 1);

    // Draw the title with the adjusted light blue color
    g.setColour(juce::Colours::cyan); // Lighter blue color
    g.setFont(34.0f);
    g.drawFittedText("State", getLocalBounds(), juce::Justification::centredTop, 1);

    // Draw more prominent pink glow
    g.setColour(juce::Colour::fromRGBA(255, 105, 180, 60)); // Increased pink glow opacity
    for (int i = 0; i < 3; ++i)
    {
        g.drawFittedText("State", getLocalBounds().translated(-i, -i), juce::Justification::centredTop, 1);
    }
}
// layout slider positions
void OscComponent::resized()
{
    const auto sliderPosY = 20;  // Further moved everything a bit up
    const auto sliderWidth = 130;
    const auto sliderHeight = 90;
    const auto sliderWidth2 = 90;
    const auto sliderHeight2 = 60;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto comboBoxSpacing = 80;

// FM Sliders
    positionSliderAndLabel(fmFreqSlider, fmFreqlabel, 10, sliderPosY, sliderWidth, sliderHeight, labelYOffset);
    positionSliderAndLabel(fmDepthSlider, fmDepthlabel, fmFreqSlider.getRight() + 30, sliderPosY, sliderWidth, sliderHeight, labelYOffset);

// Osc Wave Selectors
    const auto comboBoxWidth = 20;
    const auto comboBoxHeight = 3;
    oscWaveSelector.setBounds(getWidth() / 2.7, 5, comboBoxWidth, comboBoxHeight);  // Adjusted the vertical position based on slider adjustments
    oscWaveSelector2.setBounds(getWidth() / 2.7, oscWaveSelector.getBottom() + 5, comboBoxWidth, comboBoxHeight);
    oscWaveSelector3.setBounds(getWidth() / 2.7, oscWaveSelector2.getBottom() + 5, comboBoxWidth, comboBoxHeight);

// Volume Sliders
    positionSliderComboBoxAndLabel(oscVolumeSlider1, oscVolumeLabel1, oscWaveSelector, 20, fmDepthSlider.getBottom() + 5, sliderWidth2, sliderHeight2, labelYOffset, comboBoxSpacing);
    positionSliderComboBoxAndLabel(oscVolumeSlider2, oscVolumeLabel2, oscWaveSelector2, 20, oscVolumeSlider1.getBottom() + 5, sliderWidth2, sliderHeight2, labelYOffset, comboBoxSpacing);
    positionSliderComboBoxAndLabel(oscVolumeSlider3, oscVolumeLabel3, oscWaveSelector3, 20, oscVolumeSlider2.getBottom() + 5, sliderWidth2, sliderHeight2, labelYOffset, comboBoxSpacing);

    const auto noteOffsetSliderSpacing = -30;

// Note Offset Sliders
    positionSliderAndLabel(oscNoteOffsetSlider1, oscNoteOffsetLabel1, oscVolumeSlider1.getRight() + noteOffsetSliderSpacing, oscVolumeSlider1.getY(), sliderWidth2, sliderHeight2, labelYOffset);
    positionSliderAndLabel(oscNoteOffsetSlider2, oscNoteOffsetLabel2, oscVolumeSlider2.getRight() + noteOffsetSliderSpacing, oscVolumeSlider2.getY(), sliderWidth2, sliderHeight2, labelYOffset);
    positionSliderAndLabel(oscNoteOffsetSlider3, oscNoteOffsetLabel3, oscVolumeSlider3.getRight() + noteOffsetSliderSpacing, oscVolumeSlider3.getY(), sliderWidth2, sliderHeight2, labelYOffset);
}