/*
  Example program that plays a simple hard coded melody using a square wave oscillator
*/

#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "melody.h"
#include "synth.h"
#include "add_synth.h"
#include "vibe_synth.h"
#include "ui_file.h"
#include "writeToFile.h"
//modules for scale randomization
#include <algorithm>
#include <chrono>
#include <random>

class Callback : public AudioCallback
{

public:
  //function for writing to file
  void write()
  {
         
   
    WriteToFile fileWriter("output.csv", true);

      for(int i = 0; i < 5000; i++) {
        fileWriter.write(std::to_string(mySynths[0] -> getSample()) + "\n");
          mySynths[0] -> synthTick();
           }

        std::cout << "\nWROTE TO FILE = DONE." << std::endl;
       

  }
  //function for converting midi to frequency
  double mtof(float mPitch, float interval)
  {
    // source of the mtof calculation:
    // https://www.musicdsp.org/en/latest/Other/125-midi-note-frequency-conversion.html
    return 440.0 * pow(2.0, ((mPitch+ interval) - 69.0f)/12.0f);
  } // mtof()
  //function for selecting the synths based on UI.
  void synthSelect(std::string synthOptions[], int chosenSynth, Synth* mySynths[])
  {
    if (synthOptions[chosenSynth] == "add" ) 
    {
      mySynths[0] = new Add_Synth;
      mySynths[1] = new Add_Synth;
      std::cout << mySynths[0] << "\n" << mySynths[1] << "\n";

    }
    if (synthOptions[chosenSynth] == "vibe") 
    {
      mySynths[0] = new Vibe_Synth;
      mySynths[1] = new Vibe_Synth;
      
      freq4 = ui.retrieveDoubleInRange("Enter Wobble Frequency between: ",2,200);
      std::cout << mySynths[0] << "\n" << mySynths[1] << "\n";

    }
    if (synthOptions[chosenSynth] == "both") 
    {
      mySynths[0] = new Add_Synth;
      mySynths[1] = new Vibe_Synth;
      freq4 = ui.retrieveDoubleInRange("Enter Wobble Frequency between: ",2,200);
      std::cout << mySynths[0] << "\n" << mySynths[1] << "\n";

    }
  }
  //function for updating pitch based on melody and selected synth.
  void updatePitch(Melody& melody, Synth* synth) 
  {
    float pitch = melody.getPitch(melody.melody_scale);
    //setting the frequencies for different oscillators
    double freq = mtof(pitch,0);
    double freq2 = mtof(pitch,7);
    double freq3 = mtof(pitch,12);
    std::cout << "next pitch: " << pitch << ", freq is: " << freq << std::endl;
    synth->myOscillators[0]->setFrequency(freq);
    synth->myOscillators[1]->setFrequency(freq2);
    synth->myOscillators[2]->setFrequency(freq3);
    if(synthOptions[chosenSynth]== "vibe") 
    {
      mySynths[0]->setampFrequency(freq4);
      mySynths[1]->setampFrequency(freq4);
    }
    else if(synthOptions[chosenSynth]== "both")
    {
      mySynths[1]->setampFrequency(freq4);
    }

  } // updatePitch()

//function to ask prepare before playback, retrieving UI values.
  void prepare (double sampleRate) override {
    this->sampleRate=sampleRate;
    //asking the user for a rootnote input per synth and bpm
    chosenSynth = ui.retrieveSelection("Hello. This is a synthesizer! Choose a Synthtype: ",synthOptions,synthNumOptions);
    synthSelect(synthOptions,chosenSynth,mySynths);
    melody.key = ui.retrieveSelection("Choose a key for the melody choose from: ",melody.keyOptions,melody.keyNumOptions);
    melody.octaveMultiplier = ui.retrieveFloatInRange("Enter the Octave for the First melody: ",0,6);
    melody2.octaveMultiplier = ui.retrieveFloatInRange("Enter the Octave for the second melody: ",0,6);
    melody.rootNote = melody.calculateRootnote(melody.key,melody.octave,melody.octaveMultiplier);
    melody2.rootNote = melody.calculateRootnote(melody.key,melody.octave,melody2.octaveMultiplier);
    //retrieving scale selection from user
    int scale = ui.retrieveSelection("Choose a scale: ",melody.scaleOptions,melody.scaleNumOptions);
    //setting default scale so scale is never empty
    melody.setScale(melody.major);
    melody2.setScale(melody2.major);
    //choosing scale based on user input
    melody.chooseScale(melody.scaleOptions,scale,melody);
    melody2.chooseScale(melody2.scaleOptions,scale,melody2);
    //using user bpm for playbackspeed
    double userBpm = ui.retrieveDoubleInRange("Enter a bpm between: ",60,400);
    //seperate time divisions for different melodies
    double timeDivision = 30;
    double timeDivision2 = 60;
    //set timedivision to userinput value
    timeDivision = ui.retrieveDoubleInRange("Enter a time division for Melody 1 between: ",30,120);
    timeDivision2 = ui.retrieveDoubleInRange("Enter a time division for Melody 2 between: ",30,120);
    //timedivision devided by bpm determines speed. Higher value for timede
    noteDelayFactor = timeDivision/userBpm;
    noteDelayFactor2 = timeDivision2/userBpm;
    playing = true;
    //setting the scales for both synths
    //creating a random seed to use to randomize
    unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
    //shuffling the array based on length array
    std::shuffle(&melody.melody_scale[0],&melody.melody_scale[7],std::default_random_engine(num));
    //doing it a second time to get a different melody
    unsigned num2 = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(&melody2.melody_scale[0],&melody2.melody_scale[7],std::default_random_engine(num2));
    // updating the pitch seperately
    updatePitch(melody,mySynths[0]);
    updatePitch(melody2,mySynths[1]);
    
  } // prepare()

//sending audio to buffer.
  void process (AudioBuffer buffer) override {
    auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

    if (playing == true) 
    {
      for (int sample = 0; sample < numFrames; ++sample) {
        //splitting both synths on L/R, vibesynth has amp modulation
        outputChannels[0][sample] = mySynths[0]->getSample()* amplitude;
        outputChannels[1][sample] = mySynths[1]->getSample()* amplitude;
        mySynths[0]->synthTick();
        mySynths[1]->synthTick();

        //incrementing frameindexes seperately
        frameIndex++;
        frameIndex2++;
        if (frameIndex > noteDelayFactor * sampleRate) {
          // reset frameIndex
          frameIndex = 0;
          updatePitch(melody,mySynths[0]);
          
        }
        if (frameIndex2 > noteDelayFactor2 * sampleRate) {
          // reset frameIndex
          frameIndex2 = 0;
          updatePitch(melody2,mySynths[1]);
        }
      } // for sample
    } //for playing
  } // process()


  
  

protected:
  double sampleRate;
  //list with synthpointers
  Synth* mySynths[2];
  //let the user choose between 3 different synths
  std::string synthOptions[3] = {"add","vibe","both"};
  int synthNumOptions = 3;
  int chosenSynth = 0;
  //creating ui object
  UI ui;
  float amplitude = 0.25;
  double freq4;
  
  
  //melody 1 and 2 
  Melody melody;
  Melody melody2;
  int frameIndex = 0;
  int frameIndex2 = 0;
  bool playing = false;
  //default bpm 
  double bpm = 120;
  //different time divisions for L/R
  double noteDelayFactor=60/bpm;
  double noteDelayFactor2=30/bpm;
}; // Callback{}


#define WRITE_TO_FILE 1
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
  #if WRITE_TO_FILE 
  callback.write();
  #endif
  } // while
  return 0;

} // main()

