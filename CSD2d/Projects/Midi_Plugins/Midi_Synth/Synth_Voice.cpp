#include "Synth_Voice.h"

bool Synth_Voice::canPlaySound (SynthesiserSound * sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;

}
void Synth_Voice::startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
{
    ignoreUnused(velocity), ignoreUnused(*sound), ignoreUnused(currentPitchWheelPosition);
    // pass the midinote and activate note on from the ADSR
    osc.setWaveFrequency(midiNoteNumber,1);
    adsr.noteOn();
}
void Synth_Voice::stopNote (float velocity, bool allowTailOff)
{
    // note off message
    ignoreUnused(velocity);
    adsr.noteOff();
    if (! allowTailOff || ! adsr.isActive())
    {
        clearCurrentNote();
    }

}
void Synth_Voice::controllerMoved (int controllerNumber, int newControllerValue)
{
    ignoreUnused(controllerNumber), ignoreUnused(newControllerValue);
}



void Synth_Voice::pitchWheelMoved (int newPitchWheelValue)
{
    ignoreUnused(newPitchWheelValue);
}

void Synth_Voice::updateParameters(const float attack, const float decay, const float sustain, const float release)
{
    // updating params
    adsr.updateADSR(attack,decay, sustain, release);
}

void Synth_Voice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    // Prepare to Play giving everything samplerate
    adsr.setSampleRate(sampleRate);
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = static_cast<uint32>(samplesPerBlock);
    spec.sampleRate = sampleRate;
    spec.numChannels = static_cast<uint32>(outputChannels);
    osc.prepareToPlay(spec);
    gain.prepare (spec);
    gain.setGainLinear (0.05f);
    isPrepared = true;
}



void Synth_Voice::renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (! isVoiceActive())
    {
        return;
    }
    // setting size of the buffer
    synthBuffer.setSize(outputBuffer.getNumChannels(),numSamples,false,false,true);
    synthBuffer.clear();
    // generating sound for audioblock
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    osc.getNextAudioBlock(audioBlock);
    // applying volume
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    // applying ADSR
    adsr.applyEnvelopeToBuffer(synthBuffer,0,synthBuffer.getNumSamples());

    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel ++)
    {
        outputBuffer.addFrom(channel,startSample,synthBuffer,channel, 0, numSamples);
    //trigering new ADSR
        if (! adsr.isActive())
        {
            clearCurrentNote();
        }
    }
}
