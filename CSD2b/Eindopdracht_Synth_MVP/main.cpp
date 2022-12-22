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
  // function for converting midi to frequency
  double mtof(float mPitch, float interval,float detune)
  {
    return (440.0 * pow(2.0, ((mPitch+ interval) - 69.0f)/12.0f))+detune;
  } // mtof()
  //function for selecting the synths based on UI.
  void synthSelect(std::string synthOptions[], int chosenSynth, Synth* mySynths[])
  {
    if (synthOptions[chosenSynth] == "add" ) 
    {
      mySynths[0] = new Add_Synth;
      mySynths[1] = new Add_Synth;
      detuneOsc4 = ui.retrieveFloatInRange("The add synth has 3 extra oscillators which can be detuned for width\nEnter a the frequency of detuning for the 1st Oscillator between: ", 0,100);
      detuneOsc5 = ui.retrieveFloatInRange("Enter a frequency of detuning for the 2nd Oscillator: ", 0,100);
      detuneOsc5 = ui.retrieveFloatInRange("Enter a frequency of detuning for the 3rd Oscillator: ", 0,100);
      #if DEBUG
      std::cout << mySynths[0] << "\n" << mySynths[1] << "\n";
      #endif

    }
    if (synthOptions[chosenSynth] == "vibe") 
    {
      mySynths[0] = new Vibe_Synth;
      mySynths[1] = new Vibe_Synth;
      
      freq4 = ui.retrieveDoubleInRange("The vibe synth has a wobble\nEnter a Frequency for the wobble between: ",2,200);
      #if DEBUG
      std::cout << mySynths[0] << "\n" << mySynths[1] << "\n";
      #endif

    }
    if (synthOptions[chosenSynth] == "both") 
    {
      mySynths[0] = new Add_Synth;
      mySynths[1] = new Vibe_Synth;
      freq4 = ui.retrieveDoubleInRange("The vibe synth has a wobble\nEnter a Frequency for the wobble between: ",2,200);
      detuneOsc4 = ui.retrieveFloatInRange("The add synth has 3 extra oscillators which can be detuned for width\nEnter the frequency of detuning between: ", 0,100);
      detuneOsc5 = ui.retrieveFloatInRange("Enter the frequency of detuning for the 2nd Oscillator between: ", 0,100);
      detuneOsc5 = ui.retrieveFloatInRange("Enter the frequency of detuning for the 3rd Oscillator between: ", 0,100);
      #if DEBUG
      std::cout << mySynths[0] << "\n" << mySynths[1] << "\n";
      #endif

    }
  }
  //function for updating pitch based on melody and selected synth.
  void updatePitch(Melody& melody, Synth* synth) 
  {
    float pitch = melody.getPitch(melody.melody_scale);
    //setting the frequencies for different oscillators
    double freq = mtof(pitch,0,0);
    double freq2 = mtof(pitch,7,0);
    double freq3 = mtof(pitch,12,0);
    //freq4 is a modulator frequency and will be created in another function.
    double freq5 = mtof(pitch,0,detuneOsc4);
    double freq6 = mtof(pitch,7,detuneOsc5);
    double freq7 = mtof(pitch,12,detuneOsc6);
    std::cout << "next pitch: " << pitch << std::endl;
    synth->myOscillators[0]->setFrequency(freq);
    synth->myOscillators[1]->setFrequency(freq2);
    synth->myOscillators[2]->setFrequency(freq3);
    synth->myOscillators[3]->setFrequency(freq5);
    synth->myOscillators[4]->setFrequency(freq6);
    synth->myOscillators[5]->setFrequency(freq7);
    if(synthOptions[chosenSynth]== "vibe") 
    {
      //setting the wobble frequency
      mySynths[0]->setampFrequency(freq4);
      mySynths[1]->setampFrequency(freq4);
    }
    else if(synthOptions[chosenSynth]== "both")
    {
      //setting the wobble frequency only for 2nd synth.
      mySynths[1]->setampFrequency(freq4);
    }

  } // updatePitch()

//function to prepare before playback, retrieving UI values.
  void prepare (double sampleRate) override {
    //setting samplerate
    this->sampleRate=sampleRate;
    //letting the user choose a synthtype
    chosenSynth = ui.retrieveSelection("Hello. This is a synthesizer! Choose a Synthtype: ",synthOptions,synthNumOptions);
    //selecting the chosensynth
    synthSelect(synthOptions,chosenSynth,mySynths);
    //asking user for a key of the to be generated melody
    melody.key = ui.retrieveSelection("Choose a key for the melody choose from: ",melody.keyOptions,melody.keyNumOptions);
    //asking user for the scale for the key
    int scale = ui.retrieveSelection("Choose a scale: ",melody.scaleOptions,melody.scaleNumOptions);
    //let the user decide if the synth plays one or 2 melodies and executing the functions after choice is made.
    melodyAmount = ui.retrieveSelection("Would you like one or two melodies? type: ",melodyOptions,melodyNumOptions);
    if (melodyAmount == 0) 
    {
    melody.octaveMultiplier = ui.retrieveFloatInRange("Enter the octave for the melody between: ",0,6);
    melody.rootNote = melody.calculateRootnote(melody.key,melody.octave,melody.octaveMultiplier);
    melody.setScale(melody.major);
    melody.chooseScale(melody.scaleOptions,scale,melody);
    timeDivision = ui.retrieveDoubleInRange("Enter a time division for the melody between: ",30,120);
    //if there is one melody the time division is equal for both.
    timeDivision2 = timeDivision;
    //generating a random seed based on a clock
    unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
    //shuffling the array based on length array and a random seed
    std::shuffle(&melody.melody_scale[0],&melody.melody_scale[7],std::default_random_engine(num));
    //retrieving user bpm
    
    userBpm = ui.retrieveDoubleInRange("Enter a bpm between: ",60,400);
    }
    //if the user selected 2 melodies, more functions will be executed and more questions will be asked
    else if (melodyAmount == 1) 
    {
    melody.octaveMultiplier = ui.retrieveFloatInRange("Enter the octave for the first melody between: ",0,6);
    melody2.octaveMultiplier = ui.retrieveFloatInRange("Enter the octave for the second melody between: ",0,6);
    melody.rootNote = melody.calculateRootnote(melody.key,melody.octave,melody.octaveMultiplier);
    melody2.rootNote = melody.calculateRootnote(melody.key,melody.octave,melody2.octaveMultiplier);
    //setting default scale so scale is never empty
    melody.setScale(melody.major);
    melody2.setScale(melody2.major);
    melody.chooseScale(melody.scaleOptions,scale,melody);
    melody2.chooseScale(melody2.scaleOptions,scale,melody2);
    timeDivision = ui.retrieveDoubleInRange("Enter a time division for Melody 1 between: ",30,120);
    timeDivision2 = ui.retrieveDoubleInRange("Enter a time division for Melody 2 between: ",30,120);
    unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
    //shuffling the array based on length array and a random seed
    std::shuffle(&melody.melody_scale[0],&melody.melody_scale[7],std::default_random_engine(num));
    //doing it a second time to get a different melody
    unsigned num2 = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(&melody2.melody_scale[0],&melody2.melody_scale[7],std::default_random_engine(num2));
    userBpm = ui.retrieveDoubleInRange("Enter a bpm between: ",60,400);
    }    
    //set timedivision to userinput value
    //timedivision devided by bpm determines speed. Higher value for more space between notes
    amplitudeL = ui.retrieveFloatInRange("Enter amplitude for Left channel between: ",0.1,1);
    amplitudeR = ui.retrieveFloatInRange("Enter amplitude for Right channel between: ",0.1,1);
    noteDelayFactor = timeDivision/userBpm;
    noteDelayFactor2 = timeDivision2/userBpm;
    //starting playback
    playing = true;
  } // prepare()

//sending audio to buffer.
  void process (AudioBuffer buffer) override {
    auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

    if (playing == true) 
    {
      for (int sample = 0; sample < numFrames; ++sample) {
        //splitting both synths on L/R 0.5 so if user enter max amplitude it's still not clipping.
        outputChannels[0][sample] = mySynths[0]->getSample()* amplitudeL*0.5;
        outputChannels[1][sample] = mySynths[1]->getSample()* amplitudeR*0.5;
        mySynths[0]->synthTick();
        mySynths[1]->synthTick();

        //incrementing frameindexes seperately
        frameIndex++;
        frameIndex2++;

          if (frameIndex > noteDelayFactor * sampleRate) 
          {
            // reset frameIndex
            frameIndex = 0;
            updatePitch(melody,mySynths[0]);
            if (melodyAmount == 0) 
            {
            updatePitch(melody,mySynths[1]);
            }
          }
        
        else if (melodyAmount == 1 ) 
        {
          if (frameIndex2 > noteDelayFactor2 * sampleRate) 
          {
            // reset frameIndex
            frameIndex2 = 0;
            updatePitch(melody2,mySynths[1]);
          }
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
  std::string melodyOptions[2] = {"1","2"};
  int melodyNumOptions = 2;
  int synthNumOptions = 3;
  int chosenSynth = 0;
  //frequency for modulation
  double freq4;
  //amount of melodies
  int melodyAmount;
  //seperate time divisions for different melodies
  
  
  //melody 1 and 2 
  Melody melody;
  Melody melody2;
  //creating ui object
  UI ui;
  int frameIndex = 0;
  int frameIndex2 = 0;
  bool playing = false;
  //default bpm 
  double bpm = 120;
  double userBpm;
  //amplitudes for L&R
  float amplitudeL = 0.125;
  float amplitudeR = 0.125;
  //different time divisions for L/R
  double timeDivision = 60;
  double timeDivision2 = 60;
  double noteDelayFactor=60/bpm;
  double noteDelayFactor2=30/bpm;
  float detuneOsc4; 
  float detuneOsc5; 
  float detuneOsc6; 
}; // Callback{}

//enabling/disabling write to file
#define WRITE_TO_FILE 1
//main
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

