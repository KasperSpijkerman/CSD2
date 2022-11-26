//header file for description of instrument class
#pragma once
#include <iostream>

class Instruments 
    {
    public:
        //constructor and destructor
        // Instruments();
        //constructur with values
        Instruments(std::string name,float freq, float amp);
        ~Instruments();
        
        //set and get
        void setFreq(float freq);
        float getFreq();
        void setAmp(float amp);
        float getAmp();
        //function playing sound
        void playSound(std::string sound);
    protected:  
        float freq;
        float amp;
        std::string name;
    };