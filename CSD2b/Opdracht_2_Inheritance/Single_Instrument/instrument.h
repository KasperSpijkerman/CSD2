//header file for description of instrument class
#pragma once
#include <iostream>

class Instrument 
    {
    public:
        //constructor and destructor
        Instrument();
        //constructur with values
        Instrument(float freq, float amp);
        ~Instrument();
        
        //set and get
        void setFreq(float freq);
        float getFreq();
        void setAmp(float amp);
        float getAmp();
        // void getNotes();
        // void setNotes(float amp);
        // void setName(std::string name);
        // std::string getName();
        // void playSound();
    protected:  
        float freq;
        float amp;
        // int notesAmount;
        // std::string name;
    };