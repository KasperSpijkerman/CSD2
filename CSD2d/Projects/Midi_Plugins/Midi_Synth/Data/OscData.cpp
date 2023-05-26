#include "OscData.h"



void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    // preparing oscillators
    fmOsc.prepare(spec);
    prepare(spec);
}

void OscData::setWaveType(const int choice)
{
   // making choices for the oscillators
    switch(choice)
    {
        case 0:
            // sin
            initialise([](float x) {return  std::sin(x);});
            break;

        case 1:
            // saw
            initialise([](float x) {return  x / MathConstants<float>::pi;});
            break;

        case 2:
            // square
            initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
            break;

        default:
            jassertfalse;

    }
}

void OscData::setWaveFrequency(const int midiNoteNumber,const float detune)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod *detune);
    // remembering last midinote when pressed
    lastMidiNote = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    for (int ch =0; ch< block.getNumChannels(); ++ch)
    {
        // processing the fmSynthesis on sample and channel multiplying it with the fmdepth
        for (int s = 0; s <block.getNumSamples(); ++s)
        {
            fmMod = fmOsc.processSample(block.getSample(ch,s))*fmDepth;
        }
    }

    process (juce::dsp::ProcessContextReplacing<float> (block));
}

void OscData::setFmParams(const float depth, const float frequency)
{
    // setting the fm oscillator
    fmOsc.setFrequency(frequency);
    // setting depth
    fmDepth = depth;
    // making sure the frequency also changes if fm is changed
    auto currentFrequency = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod;
    setFrequency( currentFrequency >= 0 ? currentFrequency : currentFrequency *-1.0f );
}
