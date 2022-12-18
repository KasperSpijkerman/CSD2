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
//modules for scale randomization
#include <algorithm>
#include <chrono>
#include <random>

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
    melody.rootNote = ui.retrieveRootnoteInRange(20,80);
    melody2.rootNote = ui.retrieveRootnoteInRange(20,80);
    double userBpm = ui.retrieveBPMInRange(60,200);
    vibesynth.fmIndex = ui.retrieveModulationInRange(1,10);
    //retrieving scale selection from user
    int scale = ui.retrieveUserSelection(scaleOptions,numOptions);
    std::cout << scaleOptions[scale] << "\n";
    //using user bpm for playbackspeed
    noteDelayFactor = 30/userBpm;
    noteDelayFactor2 = 30/userBpm;
    playing = true;
    //setting the scales for both synths
    
    melody.setScale(major);
    melody2.setScale(major);

    if (scaleOptions[scale] == "harmonicminor" )
    {
      melody.setScale(harmonicminor);
      melody2.setScale(harmonicminor);
    }
    if (scaleOptions[scale] == "major" )
    {
      melody.setScale(major);
      melody2.setScale(major);
    }
    if (scaleOptions[scale] == "minor" )
    {
      melody.setScale(minor);
      melody2.setScale(minor);
    }
    if (scaleOptions[scale] == "dorian" )
    {
      melody.setScale(dorian);
      melody2.setScale(dorian);
    }
    if (scaleOptions[scale] == "phrygian" )
    {
      melody.setScale(phrygian);
      melody2.setScale(phrygian);
    }
    if (scaleOptions[scale] == "lydian" )
    {
      melody.setScale(lydian);
      melody2.setScale(lydian);
    }
    if (scaleOptions[scale] == "mixolydian" )
    {
      melody.setScale(mixolydian);
      melody2.setScale(mixolydian);
    }
    if (scaleOptions[scale] == "locrian" )
    {
      melody.setScale(locrian);
      melody2.setScale(locrian);
    }

    //creating a random number to use to randomize
    unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
    //shuffling the array based on length array
    std::shuffle(&melody.melody_scale[0],&melody.melody_scale[7],std::default_random_engine(num));
    //doing it a second time to get a different melody
    unsigned num2 = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(&melody2.melody_scale[0],&melody2.melody_scale[7],std::default_random_engine(num2));
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
        //splitting both synths on L/R, vibesynth has amp modulation
        outputChannels[0][sample] = addsynth.getSample() * amplitude;
        outputChannels[1][sample] = vibesynth.getSample() * amplitude *vibesynth.ampMod;
        
        addsynth.synthTick();
        vibesynth.ampsine.tick();
        // std::cout << vibesynth.ampMod <<"\n";
        vibesynth.ampMod = vibesynth.ampsine.getSample();
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
  //creating ui object
  UI ui;
  float amplitude = 0.025;
  //scales for different melodies
  float harmonicminor[8] = {0,2,3,5,7,8,11,12};
  float minor[8] = {0,2,3,5,7,8,10,12};
  float major[8] = {0,2,4,5,7,9,11,12};
  float dorian[8] = {0,2,3,5,7,9,10,12};
  float phrygian[8] = {0,1,3,5,7,8,10,12};
  float lydian[8] = {0,2,4,6,7,9,11,12};
  float mixolydian[8] = {0,2,4,5,7,9,10,12};
  float locrian[8] = {0,1,3,5,6,8,10,12};
  //list of options of scales
  std::string scaleOptions[8] = {"harmonicminor","minor","major","dorian","phrygian","lydian","mixolydian","locrian"};
  int numOptions = 8;
  
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

