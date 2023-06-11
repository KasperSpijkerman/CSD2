#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p),
    audioProcessor (p) ,
    adsr (audioProcessor.apvts),
    osc(audioProcessor.apvts,"oscwavetype1","fmfreq","fmdepth"),
    filter(audioProcessor.apvts, "filtertype", "filtercutoff", "filterresonance"),
    LFO(audioProcessor.apvts,"lfofreq","lfodepth"),
    shaper(audioProcessor.apvts,"drive","trim"),
    control(audioProcessor.apvts,"Lighter","Darker","Closer","Spacier","Earthlier","Weirder","Faster","Slower","Rougher","Smoother","Shorter", "Longer"),
    visualiser(&audioProcessor),
    delay(audioProcessor.apvts,"drywetL","drywetR","drywetC","feedbackL","feedbackR","feedbackC","delaytimeL","delaytimeR","delaytimeC")


{
    setSize (1000, 800);
    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
    addAndMakeVisible(LFO);
    addAndMakeVisible(shaper);
    addAndMakeVisible(control);
    addAndMakeVisible(visualiser);
    addAndMakeVisible(delay);
    startTimer(1);
    File customDirectory("/Volumes/SSD Kasper 1/HKU/Jaar_2/CSD2/Juce_Projects/Projects/Midi_Synth/UI/backgrounds");
    File backgroundimage = customDirectory.getChildFile("Backgroundmain.png");
    background = ImageCache::getFromFile(backgroundimage);

}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{

    g.drawImageAt(background,0,0);
    //g.fillAll(juce::Colours::purple);
    g.setColour(juce::Colours::green);
    g.setFont (30.0f);
}

void AudioPluginAudioProcessorEditor::resized()
{
    const auto paddingX = 0;
    const auto paddingY = 0;
    const auto paddingY2 = 400;
    const auto paddingY3 = 600;
    // standard formats
    const auto objectWidth = 400;
    const auto objectHeight = 235;
    // bigger format
    const auto objectWidthBig = 300;
    const auto objectWidthControl = 300;
    const auto objectHeightBig = 650;
    const auto moveRight = 233;
    // placing objects on screen
    osc.setBounds(paddingX,paddingY,objectWidth,objectHeight);
    adsr.setBounds(osc.getRight()+moveRight,paddingY,objectWidth, objectHeight);
    filter.setBounds(paddingX,paddingY2,objectWidth,objectHeight-20);
    LFO.setBounds(osc.getRight()+moveRight,paddingY2,objectWidth,objectHeight);
    shaper.setBounds(osc.getRight()+moveRight,paddingY3,objectWidth,objectHeight+250);
    control.setBounds(static_cast<int>(getWidth() / 3), getHeight() / 700, objectWidthControl, objectHeightBig);
    delay.setBounds(getWidth()/3,getHeight()/2,objectWidthBig,objectHeightBig);
    visualiser.setBounds(paddingX,paddingY3,objectWidthBig+33,objectHeight);
}
// updating the data based on buttons
void AudioPluginAudioProcessorEditor::updateControlData()
{
    // passing audio parameters and the right sliders to adjust
    // changing cutoff frequency
    control.changeFilter(audioProcessor.apvts,
                         filter.filterCutoffSlider,
                         filter.filterTypeSelector,
                         osc.oscWaveSelector);
    // changing Delay dry wet and delay times
    control.changeSpace(audioProcessor.apvts,
                        delay.drywetLSlider,
                        delay.drywetRSlider,
                        delay.drywetCSlider);
    // changing FM params and Resonance
    control.changePredict(audioProcessor.apvts,
                          osc.fmDepthSlider,
                          osc.fmFreqSlider,
                          filter.filterResonanceSlider,
                          LFO.LFODepthSlider);
    // changing AM and Attack time
    control.changeSpeed(audioProcessor.apvts,
                        LFO.LFOFreqSlider,
                        adsr.attackSlider,
                        LFO.LFODepthSlider);
    // changing Drive and trim
    control.changeTexture(audioProcessor.apvts,
                          shaper.ShaperDriveSlider,
                          shaper.ShaperTrimSlider);
    control.changeLength(audioProcessor.apvts,
                         adsr.releaseSlider,
                         delay.feedbackLSlider,
                         delay.feedbackRSlider,
                         delay.feedbackCSlider,
                         delay.delayTimeLSlider,
                         delay.delayTimeRSlider,
                         delay.delayTimeCSlider);
}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    updateControlData();
}