//header file for description of instrument class
#pragma once
#include <iostream>

class Instrument 
    {
    public:
        //constructor and destructor
        Instrument();
        //constructur with values
        Instrument(float freq, float amp, std::string name);
        ~Instrument();
        
        //set and get
        void setFreq(float freq);
        float getFreq();
        void setAmp(float amp);
        float getAmp();
        void setName(std::string name);
        std::string getName();
        // void getNotes();
        // void setNotes(float amp);
        // void playSound();
    protected:  
        float freq;
        float amp;
        std::string name;
        // int notesAmount;
    };