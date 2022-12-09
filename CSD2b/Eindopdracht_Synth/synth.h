#ifndef BLOK2B_Synth_H
#define BLOK2B_Synth_H

class Synth
{
public: 
  Synth();
  
  // virtual void setSamplerate() = 0;
  virtual float getSample() = 0;
  // virtual void tick() = 0;
  // void setSamplerate();

protected:
  float frequency;
  // float attackTime;
  // float decayTime;
  // float sustainLevel;
  // float releaseTime;
};

#endif 
