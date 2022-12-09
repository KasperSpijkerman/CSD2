#ifndef CALLBACK_H
#define CALLBACK_H

#include "jack_module.h"
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "synth.h"

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

private:
  float samplerate = 44100;
  Synth synth;
};

#endif //CALLBACK_H
