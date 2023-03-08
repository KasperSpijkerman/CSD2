#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SuperTramAudioProcessor::SuperTramAudioProcessor()
:
    AudioProcessor (BusesProperties()
                   .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                   .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                   ), apvts(*this, nullptr,"Parameters", createParameters())
{
}

SuperTramAudioProcessor::~SuperTramAudioProcessor()
{
}

//==============================================================================
const juce::String SuperTramAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SuperTramAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SuperTramAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SuperTramAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SuperTramAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SuperTramAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SuperTramAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SuperTramAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SuperTramAudioProcessor::getProgramName (int index)
{
    return {};
}

void SuperTramAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SuperTramAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (Tremolo& tremolo : tremolos)
        tremolo.prepareToPlay(sampleRate);
}

void SuperTramAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SuperTramAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SuperTramAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // getting
    auto s = apvts.getRawParameterValue("rate");
    // setting rate according to value from
    rate = s->load();




    auto a = apvts.getRawParameterValue("depth");

    depth = a->load();


    for (Tremolo& tremolo : tremolos)
    {
        tremolo.setAmplitude(depth);
        tremolo.setSpeed(rate);
    }


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // process the audio
        for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = tremolos[channel].output(buffer.getSample(channel,sample)) ;
        }
    }
}

//==============================================================================
bool SuperTramAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SuperTramAudioProcessor::createEditor()
{
    return new SuperTramAudioProcessorEditor (*this);
}

//==============================================================================
void SuperTramAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SuperTramAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SuperTramAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout SuperTramAudioProcessor::createParameters()
{
    // all parameters
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back (std::make_unique<juce::AudioParameterFloat>("rate", "Rate", 0.0f, 10.0f,3));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("depth", "Depth", 0.0f, 1.0f,3));
    return {params.begin(), params.end()};
}