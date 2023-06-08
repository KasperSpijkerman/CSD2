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
     synth.addVoice(new Synth_Voice());
     synth.addVoice(new Synth_Voice());
     synth.addVoice(new Synth_Voice());

     // reference to parameter IDs
     attack = apvts.getRawParameterValue("attack");
     decay = apvts.getRawParameterValue("decay");
     sustain = apvts.getRawParameterValue("sustain");
     release = apvts.getRawParameterValue("release");
     oscWave = apvts.getRawParameterValue("oscwavetype1");
     FMDepth = apvts.getRawParameterValue("fmdepth");
     FMFrequency = apvts.getRawParameterValue("fmfreq");
     filterType = apvts.getRawParameterValue("filtertype");
     filterCutoff = apvts.getRawParameterValue("filtercutoff");
     filterResonance = apvts.getRawParameterValue("filterresonance");
     LFOfreq = apvts.getRawParameterValue("lfofreq");
     LFOdepth = apvts.getRawParameterValue("lfodepth");
     drive = apvts.getRawParameterValue("drive");
     trim = apvts.getRawParameterValue("trim");
     dryWetL = apvts.getRawParameterValue("drywetL");
     dryWetR = apvts.getRawParameterValue("drywetR");
     dryWetC = apvts.getRawParameterValue("drywetC");
     feedbackL = apvts.getRawParameterValue("feedbackL");
     feedbackR = apvts.getRawParameterValue("feedbackR");
     feedbackC = apvts.getRawParameterValue("feedbackC");
     delayTimeL = apvts.getRawParameterValue("delaytimeL");
     delayTimeR = apvts.getRawParameterValue("delaytimeR");
     delayTimeC = apvts.getRawParameterValue("delaytimeC");


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
    juce::ignoreUnused ( samplesPerBlock);
    // prepare to play synth
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i ++)
    {
        // turning the 'synthesizer voice' in our own synth voice
        if (auto voice = dynamic_cast <Synth_Voice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate,samplesPerBlock,getTotalNumOutputChannels());
        }
    }
    // prepare to play effects
    filter.prepareToPlay(sampleRate,samplesPerBlock,getTotalNumOutputChannels());
    for (Tremolo& tremolo : tremolos){
        tremolo.prepareToPlay(sampleRate);
    }
    for (WaveShaper& waveshaper : waveshapers)
    waveshaper.prepareToPlay(sampleRate);

    delay.lcrDelayPrepareToPlay(sampleRate);

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
            auto attackNew = *attack *1.0f;
            auto decayNew = *decay*1.0f;
            auto sustainNew = *sustain*1.0f;
            auto releaseNew = *release*1.0f;

            // OSC wavetype
            auto oscWaveNew = *oscWave*1.0f;
            // FM parameters, depth and frequency
            auto FMDepthNew = *FMDepth*1.0f;
            auto FMFrequencyNew = *FMFrequency*1.0f;

            // updating the parameters
            voice->getOscillator().setWaveType(oscWaveNew);
            voice->getOscillator().setFmParams(FMDepthNew,FMFrequencyNew);
            voice->updateParameters(attackNew,decayNew,sustainNew,releaseNew);
        }
    }
    // outputting the sound by rendering next block
    synth.renderNextBlock(buffer,midiMessages,0,buffer.getNumSamples());

    auto filterTypeNew = *filterType*1.0f;
    auto filterCutoffNew = *filterCutoff*1.0f;
    auto filterResonanceNew = *filterResonance*1.0f;
    filter.updateParameters(filterTypeNew,filterCutoffNew,filterResonanceNew);
    // applying filter to buffer
    filter.process(buffer);

    // LFO updating
    auto LFOfreqNew = *LFOfreq*1.0f;
    auto LFOdepthNew = *LFOdepth*1.0f;

    for (Tremolo& tremolo : tremolos)
    {
        tremolo.updateParameters(LFOfreqNew,LFOdepthNew);
    }
    // Waveshaper Updating
    auto driveNew = *drive*1.0f;
    auto trimNew = *trim*1.0f;

    for (WaveShaper& waveShaper : waveshapers){
        waveShaper.updateParameters(driveNew,trimNew);
    }

    // retrieving delay parameters
    auto dryWetLNew = *dryWetL *1.0f;
    auto dryWetRNew = *dryWetR *1.0f;
    auto dryWetCNew = *dryWetC*1.0f;
    auto feedbackLNew = *feedbackL*1.0f;
    auto feedbackRNew = *feedbackR*1.0f;
    auto feedbackCNew = *feedbackC*1.0f;
    auto delayTimeLNew = *delayTimeL*1.0f;
    auto delayTimeRNew = *delayTimeR*1.0f;
    auto delayTimeCNew = *delayTimeC*1.0f;
    //
    delay.changeDelayLine(0,delayTimeLNew,feedbackLNew,dryWetLNew);
    delay.changeDelayLine(1,delayTimeRNew,feedbackRNew,dryWetRNew);
    delay.changeDelayLine(2,delayTimeCNew,feedbackCNew,dryWetCNew);

    // process the audio with FX
    for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
            auto* channelData = buffer.getWritePointer (channel);
            channelData[sample] = delay.lcrDelayOutput(buffer.getSample(channel, sample), channel);
            channelData[sample] = tremolos[channel].output(waveshapers[channel].output(buffer.getSample(channel, sample)));
        }
        delay.lcrIncrementC();
    }

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
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}


juce::AudioProcessorValueTreeState::ParameterLayout AudioPluginAudioProcessor::createParameters()
{

    // vector for all parameters
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    // FM parameters

    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"fmfreq",1}, "FM Freq", juce::NormalisableRange<float>{0.0f, 1000.0f,0.01f,0.3f},5.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"fmdepth",2}, "FM Depth", juce::NormalisableRange<float>{0.0f, 1000.0f,0.01f,0.3f},3.0f));

    // ADSR Parameters

    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"attack",3}, "Attack",juce::NormalisableRange<float>{ 0.1f, 1.0f,0.1f},0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"decay",4}, "Decay", juce::NormalisableRange<float>{0.1f, 1.0f,0.1f},0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"sustain",5}, "Sustain", juce::NormalisableRange<float>{0.0f, 1.0f,0.1f},1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"release",6}, "Release", juce::NormalisableRange<float>{0.1f, 3.0f,0.2f},0.7));

    // parameter choice for choosing different oscillators

    params.push_back (std::make_unique<juce::AudioParameterChoice> (juce::ParameterID {"oscwavetype1",7}, "Oscillator Wave Type", juce::StringArray { "Sine", "Saw", "Square"}, 1));

    // Filter

    params.push_back (std::make_unique<juce::AudioParameterChoice> (juce::ParameterID {"filtertype",8}, "Filtertype", juce::StringArray { "LowPass", "BandPass", "Highpass"}, 0));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"filtercutoff",9}, "Filter Cutoff", juce::NormalisableRange<float>{20.0f, 20000.0f,0.1f,0.6f},20000.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"filterresonance",10}, "Resonance", juce::NormalisableRange<float>{1.0f, 10.0f,0.1f},0.0f));

    // LFO (Tremolo)
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"lfofreq",10}, "LFO Freq", juce::NormalisableRange<float>{0.0f, 60.0f,0.1f,0.6f},0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"lfodepth",11}, "LFO depth", juce::NormalisableRange<float>{0.0f, 1.0f,0.1f},0.0f));

    // Shaper
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"drive",12}, "Drive", juce::NormalisableRange<float>{1.0f, 100.0f,1.0f,0.6f},0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID {"trim",13}, "Trim", juce::NormalisableRange<float>{0.000001, 1.0f,0.001f},1.0f));


    // Delay
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "drywetL", 14 }, "Dry-Wet-L", 0.0f, 1.0f,0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "drywetR", 15 }, "Dry-Wet-R", 0.0f, 1.0f,0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "drywetC", 16 }, "Dry-Wet-C", 0.0f, 1.0f,0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"feedbackL",17}, "Feedback-L", 0.0f, 0.99f,0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"feedbackR",18}, "Feedback-R", 0.0f, 0.99f,0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"feedbackC",19}, "Feedback-C", 0.0f, 0.99f,0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"delaytimeL",20}, "Delaytime-L", 0.0f, 3000.0f,100.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"delaytimeR",21}, "Delaytime-R", 0.0f, 3000.0f,100.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"delaytimeC",22}, "Delaytime-C", 0.0f, 3000.0f,100.0f));


    return {params.begin(), params.end()};
}