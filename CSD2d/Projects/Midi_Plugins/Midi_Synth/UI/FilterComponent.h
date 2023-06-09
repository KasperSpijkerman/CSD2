#pragma once

#include <JuceHeader.h>
#include "GeneralComponent.h"
#include "myLookAndFeel.h"
class FilterComponent : public GeneralComponent
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts,juce::String filterTypeID, juce::String filterCutoffId, juce::String filterResonanceId);
    ~FilterComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    juce::ComboBox filterTypeSelector {"Filter Type" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;

    // cutoff & resonance
    juce::Slider filterCutoffSlider;
    juce::Slider filterResonanceSlider;
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> filterCutoffAttachment;
    juce::Label filterCutofflabel {"filtercutoff", "Cutoff"};
    juce::Label filterResonancelabel {"filterresonance", "Resonance"};
    std::unique_ptr<Attachment> filterResonanceAttachment;
    // custom knobs
    myLookAndFeelV1 filterknob;
    myLookAndFeelV1 resknob;


protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};




