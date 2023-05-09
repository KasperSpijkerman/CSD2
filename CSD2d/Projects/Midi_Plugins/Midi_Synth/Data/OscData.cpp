#include "OscData.h"



void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
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

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
    // remembering last midinote when pressed
    lastMidiNote = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    for (int ch =0; ch< block.getNumChannels(); ++ch)
    {
        // processing the fmSynthesis on sample and channel multiplying it with the fmdepth
        for (int samples = 0; samples <block.getNumSamples(); ++samples)
        {
            fmMod = fmOsc.processSample(block.getSample(ch,samples)*fmDepth);
        }
    }

    process (juce::dsp::ProcessContextReplacing<float> (block));
}

void OscData::setFMParams(const float depth, const float frequency)
{
    // setting the fm oscillator
    fmOsc.setFrequency(frequency);
    // setting depth
    fmDepth = depth;
    // making sure the frequency also changes if fm is changed
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod);
}
