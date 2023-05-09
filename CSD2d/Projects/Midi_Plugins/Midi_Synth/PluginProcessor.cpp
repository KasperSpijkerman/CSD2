#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor() :
    AudioProcessor
    (BusesProperties()
        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
    ),
        apvts(*this, nullptr,"Parameters", createParameters())

{
    // adding a sound and a voice
    synth.addSound(new Synth_Sound());
    synth.addVoice(new Synth_Voice());
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String AudioPluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused ( samplesPerBlock);
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i ++)
    {
        // turning the 'synthesizer voice' in our own synth voice
        if (auto voice = dynamic_cast <Synth_Voice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate,samplesPerBlock,getTotalNumOutputChannels());
        }
    }
}

void AudioPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // making sure the parameters get updated if the user changes them
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast <Synth_Voice*>(synth.getVoice(i)))
        {
            // retreiving values realtime
            // ADSR
            auto& attack = *apvts.getRawParameterValue("attack");
            auto& decay = *apvts.getRawParameterValue("decay");
            auto& sustain = *apvts.getRawParameterValue("sustain");
            auto& release = *apvts.getRawParameterValue("release");

            // OSC wavetype
            auto& oscWave = *apvts.getRawParameterValue("oscwavetype1");
            // FM parameters, depth and frequency
            auto& fmDepth = *apvts.getRawParameterValue("fmdepth");
            auto& fmFrequency = *apvts.getRawParameterValue("fmfreq");



            // updating the parameters
            voice->getOscillator().setWaveType(oscWave);
            voice->getOscillator().setFMParams(fmDepth,fmFrequency);
            voice->updateParameters(attack.load(),decay.load(),sustain.load(),release.load());
        }
    }
    // outputting the sound by rendering next block
    synth.renderNextBlock(buffer,midiMessages,0,buffer.getNumSamples());

}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}


juce::AudioProcessorValueTreeState::ParameterLayout AudioPluginAudioProcessor::createParameters()
{
    // Switchen Oscillators

    // vector for all parameters
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // ADSR Parameters
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"attack",1}, "Attack",juce::NormalisableRange<float>{ 0.1f, 1.0f,0.1},0.3f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"decay",2}, "Decay", juce::NormalisableRange<float>{0.1f, 1.0f,0.1},0.1));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"sustain",3}, "Sustain", juce::NormalisableRange<float>{0.1f, 1.0f,0.1},1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"release",4}, "Release", juce::NormalisableRange<float>{0.1f, 3.0f,0.2},0.7));

    // FM parameters
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"fmfreq",5}, "FM Freq", juce::NormalisableRange<float>{0.0f, 1000.0f},5.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"fmdepth",6}, "FM Depth", juce::NormalisableRange<float>{0.0f, 1000.0f},500.0f));

    // parameter choice for choosing different oscillators
    params.push_back (std::make_unique<juce::AudioParameterChoice> (juce::ParameterID {"oscwavetype1",7}, "Oscillator Wave Type", juce::StringArray { "Sine", "Saw", "Square"}, 0));


    return {params.begin(), params.end()};
}