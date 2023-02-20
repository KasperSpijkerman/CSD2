#include "tremolo.h"

void Tremolo::prepareToPlay (double sampleRate)
{
   // initializing samplerate
   tremSine.setSamplerate(sampleRate);
   // setting the modulation frequency
   setSpeed(50);
   // setting dry wet;
   setDryWet(0.8);
}


float Tremolo::output (float input) 
{
   auto tremSignal = tremSine.getSample();
   tremSine.tick();
   //std::cout << tremSignal << "\n";
   tremSignal *= amp;
   tremSignal += 1.0f - amp;
   // returning modulated or dry signal based on dry wet
   return (input * tremSignal* wet) + (input * dry);
}

void Tremolo::setAmplitude(float amplitude)
{
   amp = amplitude;
}
    
void Tremolo::setSpeed(float speed)
{
   tremSine.setFrequency(speed);
}

// TODO create bypass
void Tremolo::bypass (bool bypass) 
{

}
