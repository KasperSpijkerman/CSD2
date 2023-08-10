#include "Synth_Voice.h"

bool Synth_Voice::canPlaySound (SynthesiserSound * sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;

}
void Synth_Voice::startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
{
    ignoreUnused(velocity), ignoreUnused(*sound), ignoreUnused(currentPitchWheelPosition);
    // pass the midinote and activate note on from the ADSR
    osc.setWaveFrequency(midiNoteNumber,1,offset1osc);
    osc2.setWaveFrequency(midiNoteNumber,1,offset2osc);
    osc3.setWaveFrequency(midiNoteNumber,1,offset3osc);
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
void Synth_Voice::setOscillatorGains(float gain1, float gain2,float gain3)
{
    osc1GainValue = gain1/33;
    osc2GainValue = gain2/33;
    osc3GainValue = gain3/33;
    gainOsc1.setGainLinear(osc1GainValue);
    gainOsc2.setGainLinear(osc2GainValue);
    gainOsc3.setGainLinear(osc3GainValue);
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
    osc2.prepareToPlay(spec);
    osc3.prepareToPlay(spec);
    gainOsc1.prepare (spec);
    gainOsc1.setGainLinear (0.05f);

    gainOsc2.prepare (spec);
    gainOsc2.setGainLinear (0.05f);

    gainOsc3.prepare (spec);
    gainOsc3.setGainLinear (0.05f);
    isPrepared = true;
}



void Synth_Voice::renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (! isVoiceActive())
    {
        return;
    }
    // Ensure separate buffers for each oscillator
    juce::AudioBuffer<float> osc1Buffer;
    osc1Buffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    osc1Buffer.clear();

    juce::AudioBuffer<float> osc2Buffer;
    osc2Buffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    osc2Buffer.clear();

    juce::AudioBuffer<float> osc3Buffer;
    osc3Buffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    osc3Buffer.clear();

// Process oscillator 1
    juce::dsp::AudioBlock<float> audioBlock1 { osc1Buffer };
    osc.getNextAudioBlock(audioBlock1);
    gainOsc1.process(juce::dsp::ProcessContextReplacing<float>(audioBlock1));

// Process oscillator 2
    juce::dsp::AudioBlock<float> audioBlock2 { osc2Buffer };
    osc2.getNextAudioBlock(audioBlock2);
    gainOsc2.process(juce::dsp::ProcessContextReplacing<float>(audioBlock2));

    // Process oscillator 3
    juce::dsp::AudioBlock<float> audioBlock3 { osc2Buffer };
    osc3.getNextAudioBlock(audioBlock3);
    gainOsc3.process(juce::dsp::ProcessContextReplacing<float>(audioBlock3));

// Combine both oscillators into synthBuffer
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();


    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
    {
        synthBuffer.addFrom(channel, 0, osc1Buffer, channel, 0, numSamples);
        synthBuffer.addFrom(channel, 0, osc2Buffer, channel, 0, numSamples);
        synthBuffer.addFrom(channel, 0, osc3Buffer, channel, 0, numSamples);
    }

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

void Synth_Voice::setOscillatorOffsets(float offset1, float offset2,float offset3)
{
    offset1osc = offset1;
    offset2osc = offset2;
    offset3osc = offset3;
}