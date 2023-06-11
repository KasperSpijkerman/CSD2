#pragma once
#include "GeneralComponent.h"
#include <JuceHeader.h>
#include "../PluginProcessor.h"
// This code is inspired on this video: https://www.youtube.com/watch?v=Y_MHh0z1to8 with a few variations made with open AI conversation :)
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


