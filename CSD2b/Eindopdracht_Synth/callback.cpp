#include "callback.h"


void CustomCallback::prepare(int rate) {
    samplerate = (float) rate;
    sine5th.setSamplerate(samplerate);
    saw7th.setSamplerate(samplerate);
    squareRootNote.setSamplerate(samplerate);
    square3rd.tick();
    std::cout << "\nsamplerate: " << samplerate << "\n";
}

void CustomCallback::process(AudioBuffer buffer) {
  for (int i = 0; i < buffer.numFrames; ++i) {
    // write sample to buffer at channel 0, amp = 0.25
    buffer.outputChannels[0][i] = ;
    buffer.outputChannels[1][i] = ;
  }
}
