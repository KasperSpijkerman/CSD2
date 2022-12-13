#include "callback.h"
#include "synth.h"







void CustomCallback::prepare(int rate) {
    samplerate = (float) rate;
    // synth.setSamplerate(samplerate);
    std::cout << "\nsamplerate: " << samplerate << "\n";
};

void CustomCallback::process(AudioBuffer buffer) {
  for (int i = 0; i < buffer.numFrames; ++i) {
    // write sample to buffer at channel 0, amp = 0.25
    buffer.outputChannels[0][i] = (add_synth.getSample());
    // buffer.outputChannels[1][i] = (vibe_synth.getSample());
    
    add_synth.synthTick();
    updatePitch(&melody,&add_synth);
    //vibe_synth.synthTick();
    
  }
};

//sleep function inpsired on code openai
void CustomCallback::updatePitch(Melody* melody, Synth* synth) {
  int bpm = 120;
  int timeMS = 60000/bpm;
  for (int i = 0; i < NUM_NOTES; i++)
    {
        // Print a message indicating the start of the beat
        
        float pitch = melody->getPitch();
        int freq = synth->mtof(pitch,0);
        synth->myOscillators[0]->setFrequency(freq);
        std::cout << "Note: " <<  pitch  << "  Freq: " << freq << "\n" ;

        // Sleep for the specified number of milliseconds per beat
        std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
    }
}