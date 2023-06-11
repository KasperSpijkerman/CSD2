#pragma once
#include "GeneralComponent.h"
#include <JuceHeader.h>
#include "../PluginProcessor.h"
class visualiserComponent : public GeneralComponent, public Timer
{
    Image historyImage;
    Image background;
    AudioPluginAudioProcessor* pAmp;
    std::unique_ptr<Graphics> historyGraphic;
public:
    visualiserComponent(AudioPluginAudioProcessor* processor);
    void paint(juce::Graphics& g) override;
    void resized() override;
    void timerCallback() override;
private:

};


