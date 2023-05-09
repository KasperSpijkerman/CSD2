#include "OscData.h"



void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
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

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    process (juce::dsp::ProcessContextReplacing<float> (block));
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}
