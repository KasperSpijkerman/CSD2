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
#include "ui_file.h"

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
    //asking the user for a rootnote input per synth and bpm
    melody.rootNote = ui.retrieveValueInRange(20,80);
    melody2.rootNote = ui.retrieveValueInRange(20,80);
    double userBpm = ui.retrieveBPMInRange(60,200);
    //using user bpm for playbackspeed
    noteDelayFactor = 30/userBpm;
    noteDelayFactor2 = 60/userBpm;
    playing = true;
    //setting the scales for both melodies
    melody.setScale(melody_scale);
    melody2.setScale(melody2_scale);
    //updating the pitch seperately
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

    if (playing == true) 
    {
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
    }
  } // process()


  
  

protected:
  double sampleRate;
  //creating 2 synth objects
  Add_Synth addsynth;
  Vibe_Synth vibesynth;
  UI ui;
  float amplitude = 0.025;
  //scales for different melodies
  float melody_scale[9] = {0, 7,10, 7, 12, 0, 12, 10, 10};
  float melody2_scale[9] = {12, 7, 12, 0, 7, 12, 7, 0, 12};
  //melody 1 and 2 
  Melody melody;
  Melody melody2;
  int frameIndex = 0;
  int frameIndex2 = 0;
  bool playing = false;
  double bpm = 120;
  double noteDelayFactor=60/bpm;
  double noteDelayFactor2=30/bpm;
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

