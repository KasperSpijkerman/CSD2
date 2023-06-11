
#pragma once
#include <JuceHeader.h>
using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
// General Component class because all the component classes use setSliderwithlabel function.
class GeneralComponent : public juce::Component
    {
    public:
        void setSliderWithLabel (juce::Slider& slider,
                                 juce::Label& label,
                                 juce::AudioProcessorValueTreeState& apvts,
                                 juce::String paramID,
                                 std::unique_ptr<Attachment>& attachment);
    };



