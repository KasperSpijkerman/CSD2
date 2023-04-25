#include "Synth_Voice.h"

bool Synth_Voice::canPlaySound (SynthesiserSound * sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;

}
void Synth_Voice::startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();

}
void Synth_Voice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();

}
void Synth_Voice::controllerMoved (int controllerNumber, int newControllerValue)
{

}


void Synth_Voice::pitchWheelMoved (int newPitchWheelValue)
{

}

void Synth_Voice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepare (spec);
    gain.prepare (spec);

    gain.setGainLinear (0.05f);
    isPrepared = true;
}

void Synth_Voice::renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> audioBlock { outputBuffer };
    osc.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));

    adsr.applyEnvelopeToBuffer(outputBuffer,startSample,numSamples);
}
