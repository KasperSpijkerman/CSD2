#pragma once

#include <JuceHeader.h>

class FilterComponent : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts,juce::String filterTypeID, juce::String filterCutoffId, juce::String filterResonanceId);
    ~FilterComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
private:
    juce::ComboBox filterTypeSelector {"Filter Type" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;

    // cutoff & resonance
    juce::Slider filterCutoffSlider;
    juce::Slider filterResonanceSlider;
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> filterCutoffAttachment;
    juce::Label filterCutofflabel {"filtercutoff", "Cutoff"};
    std::unique_ptr<Attachment> filterResonanceAttachment;
    juce::Label filterResonancelabel {"filterresonance", "Resonance"};


    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};




