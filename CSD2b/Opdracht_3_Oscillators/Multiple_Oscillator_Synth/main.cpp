#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "sine.h"
#include "saw.h"
#include "square.h"
#include "writeToFile.h"

/*
 * jackd -d coreaudio -> starting jack client
 */

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override {
    samplerate = (float) rate;
    sine5th.setSamplerate(samplerate);
    saw7th.setSamplerate(samplerate);
    squareRootNote.setSamplerate(samplerate);
    square3rd.tick();
    std::cout << "\nsamplerate: " << samplerate << "\n";
  }

  void process(AudioBuffer buffer) override {
    for (int i = 0; i < buffer.numFrames; ++i) {
      // write sample to buffer at channel 0, amp = 0.25
      buffer.outputChannels[0][i] = squareRootNote.getSample() + square3rd.getSample() + saw7th.getSample();
      buffer.outputChannels[1][i] = squareRootNote.getSample() + square3rd.getSample() +sine5th.getSample();
      saw7th.tick();
      sine5th.tick();
      square3rd.tick();
      squareRootNote.tick();
  }
  // WriteToFile fileWriter("output.csv", true);
  // for(int i = 0; i < samplerate; i++) {
  //   fileWriter.write(std::to_string(square.getSample()) + "\n");
  //   square.tick();
  //   }
  }
  private:
  float samplerate = 44100;
  Sine sine5th = Sine(220,samplerate);
  Saw saw7th = Saw(277,samplerate);
  Square squareRootNote = Square(146.83f,samplerate);
  Square square3rd = Square(185,samplerate);
};

int main(int argc,char **argv)
{
  auto callback = CustomCallback {};
  auto jackModule = JackModule { callback };

  jackModule.init (0, 2);

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
