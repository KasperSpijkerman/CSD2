/*
  Example program that plays a simple hard coded melody using a square wave oscillator
*/

#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "square.h"
#include "melody.h"
#include "synth.h"
#include "add_synth.h"
#include "vibe_synth.h"

/*
 * NOTE: the development library with headers for jack2 needs to be installed to build this program.
 * 
 * When built, before running the program start jackd, the JACK audio server daemon.
 *
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 *
 * start jackd : jackd -d <backend>
 * where backend is e.g. coreaudio (MacOS) or alsa (Linux)
 *
 * Alternatively there are graphical clients that start jackd.
 */



class Callback : public AudioCallback
{

public:

  double mtof(float mPitch, float interval)
  {
    // source of the mtof calculation:
    // https://www.musicdsp.org/en/latest/Other/125-midi-note-frequency-conversion.html
    return 440.0 * pow(2.0, ((mPitch+ interval) - 69.0f)/12.0f);
  } // mtof()


  void updatePitch(Melody& melody, Synth& synth) {
    float pitch = melody.getPitch(melody.melody_scale);
    double freq = mtof(pitch,0);
    double freq2 = mtof(pitch,7);
    double freq3 = mtof(pitch,12);
    std::cout << "next pitch: " << pitch << ", freq is: " << freq << std::endl;
    synth.myOscillators[0]->setFrequency(freq);
    synth.myOscillators[1]->setFrequency(freq2);
    synth.myOscillators[2]->setFrequency(freq3);
  } // updatePitch()


  void prepare (double sampleRate) override {
    this->sampleRate=sampleRate;
    melody.setScale(melody_scale);
    melody2.setScale(melody2_scale);
    updatePitch(melody,addsynth);
    updatePitch(melody2,vibesynth);
  } // prepare()


  /*
    * process() gets called by the JACK engine.
    *
    * If you are interested in incoming audio, use inputChannels[channel][sample]
    * For sending audio to the output(s), use outputChannels[channel][sample]
    */
  void process (AudioBuffer buffer) override {
    auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

    for (int sample = 0; sample < numFrames; ++sample) {
      outputChannels[0][sample] = addsynth.getSample() * amplitude;
      outputChannels[1][sample] = vibesynth.getSample() * amplitude;
      addsynth.synthTick();
      vibesynth.synthTick();
      // rather mixed up functionality

      /* After every sample, check if we need to advance to the next note
      * This is a bit awkward in this scheme of buffers per channel
      *  In a multichannel setting we should update pitches independently per channel!
      */
      frameIndex++;
      frameIndex2++;
      if (frameIndex > noteDelayFactor * sampleRate) {
        // reset frameIndex
        frameIndex = 0;
        updatePitch(melody, addsynth);
      }
      if (frameIndex2 > noteDelayFactor2 * sampleRate) {
        // reset frameIndex
        frameIndex2 = 0;
        updatePitch(melody2, vibesynth);
      }
    } // for sample
  } // process()


  
  

private:
  double sampleRate;
  Add_Synth addsynth;
  Vibe_Synth vibesynth;
  
  float amplitude = 0.025;
  float melody_scale[9] = {0, 2, 3, 5, 6, 10, 11, 12, 10};
  float melody2_scale[9] = {12, 10, 11, 12, 10, 12, 10, 11, 12};
  Melody melody;
  Melody melody2;
  int frameIndex = 0;
  int frameIndex2 = 0;

  /* instead of using bpm and specifying note lenghts we'll make every note
   * equal length and specify the delay between notes in term of the
   * samplerate
   *
   * A note of say 500 msec or 0.5 sec, takes 0.5*samplerate samples to be
   * played
   */
  double noteDelayFactor=2;
  double noteDelayFactor2=1;
}; // Callback{}



int main(int argc,char **argv)
{
  auto callback = Callback {};
  auto jack_module = JackModule(callback);

  jack_module.init(0,2);

  std::cout << "\n\nType 'quit' to exit\n";
  bool running = true;
  while (running) {
    switch (std::cin.get())
    {
      case 'q':
        running = false;
        break;
    }
  } // while

  return 0;

} // main()

