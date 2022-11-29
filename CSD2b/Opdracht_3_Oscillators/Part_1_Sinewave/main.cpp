#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "sine.h"

/*
 * jackd -d coreaudio -> starting jack client
 */

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override {
    samplerate = (float) rate;
    sine.setFrequency(1000);
    sine.getFrequency();
    sine.setSamplerate(samplerate);
    // sine2.setSamplerate(samplerate);
    std::cout << "\nsamplerate: " << samplerate << "\n";
  }

  void process(AudioBuffer buffer) override {
    for (int i = 0; i < buffer.numFrames; ++i) {
      // write sample to buffer at channel 0, amp = 0.25
      buffer.outputChannels[0][i] = sine.getSample();
      sine.tick();
      // buffer.outputChannels[0][i] = sine2.getSample();
      // sine2.tick();
    }
  }
  private:
  float samplerate = 44100;
  Sine sine = Sine(500, samplerate);

  
  
};

int main(int argc,char **argv)
{
  auto callback = CustomCallback {};
  auto jackModule = JackModule { callback };

  jackModule.init (0, 1);

  bool running = true;
  while (running) {
      switch (std::cin.get()) {
          case 'q':
              running = false;
      }
  }

  //end the program
  return 0;
} // main()
