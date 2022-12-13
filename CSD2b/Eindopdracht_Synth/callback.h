#ifndef CALLBACK_H
#define CALLBACK_H

#include "jack_module.h"
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "add_synth.h"
#include "vibe_synth.h"
#include "synth.h"
#include "melody.h"
#include <chrono>
#include <thread>
#include "oscillator.h"

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;
  void updatePitch(Melody* melody, Synth* synth);
  

protected:
  float samplerate = 44100;
  Add_Synth add_synth = Add_Synth(50);
  Vibe_Synth vibe_synth = Vibe_Synth(62);
  Melody melody;
  
};

#endif //CALLBACK_H
