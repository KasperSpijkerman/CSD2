#include "melody.h"
#include "timer.h"
#include <chrono>
#include <thread>


Melody::Melody()
{

}

Melody::~Melody()
{}

float Melody::getPitch()
{
  // wrap index
  if(index >= NUM_NOTES) {
    index = 0;
  }
  // index++ --> first use current value to read from array, after this
  // increment with 1
  return melody[index++];
}

//sleep function inpsired on code openai
void Melody::updatePitch(*Melody melody, *) {
  int bpm = 700;
  //float was not working for the chrono milliseconds input. 
  int timeMS = 60000/bpm;
  for (int i = 0; i < NUM_NOTES; i++)
    {
        // Print a message indicating the start of the beat

        float pitch = getPitch();

        std::cout << "Note: " <<  pitch  << "  Freq: \n" ;


        // Sleep for the specified number of milliseconds per beat
        std::this_thread::sleep_for(std::chrono::milliseconds(timeMS));
    }
}
  


