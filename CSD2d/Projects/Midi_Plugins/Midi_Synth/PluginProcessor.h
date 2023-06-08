#pragma once

#include <JuceHeader.h>
#include "Synth_Sound.h"
#include "Synth_Voice.h"
#include "Data/FilterData.h"
#include "FX/Tremolo/tremolo.h"
#include "FX/Waveshaper/waveshaper.h"
#include "FX/Delay/lcrDelay.h"
//==============================================================================
class AudioPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


    // audio value treestate for parameters
    juce::AudioProcessorValueTreeState apvts;
    // creating the parameters in seperate function
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();


private:
    // synth object
    juce::Synthesiser synth;
    // filter object
    FilterData filter;
    // FX objects
    std::array<Tremolo, 2> tremolos;
    std::array<WaveShaper, 2> waveshapers;
    // lcr delay
    LcrDelay delay;

    // Creating atomic float pointers for all the parameters.
    std::atomic<float>* attack = nullptr;
    std::atomic<float>* decay = nullptr;
    std::atomic<float>* sustain = nullptr;
    std::atomic<float>* release = nullptr;
    // OSC wavetype
    std::atomic<float>* oscWave = nullptr;
    // FM parameters, depth and frequency
    std::atomic<float>* FMDepth = nullptr;
    std::atomic<float>* FMFrequency = nullptr;
    std::atomic<float>* filterType = nullptr;
    std::atomic<float>* filterCutoff = nullptr;
    std::atomic<float>* filterResonance = nullptr;
    // AM
    std::atomic<float>* LFOfreq = nullptr;
    std::atomic<float>* LFOdepth = nullptr;
    // Shaper
    std::atomic<float>* drive = nullptr;
    std::atomic<float>* trim = nullptr;
    // Delay
    std::atomic<float>* dryWetL = nullptr;
    std::atomic<float>* dryWetR = nullptr;
    std::atomic<float>* dryWetC = nullptr;
    std::atomic<float>* feedbackL = nullptr;
    std::atomic<float>* feedbackR = nullptr;
    std::atomic<float>* feedbackC = nullptr;
    std::atomic<float>* delayTimeL = nullptr;
    std::atomic<float>* delayTimeR = nullptr;
    std::atomic<float>* delayTimeC = nullptr;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};
