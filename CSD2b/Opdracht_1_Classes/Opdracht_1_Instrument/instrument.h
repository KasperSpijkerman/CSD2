//header file for description of instrument class
#pragma once
#include <iostream>

class Instrument 
    {
    public:
        Instrument();
        std::string name;
        void printName();
        int frequency;
        int notesAmount;
        void printFrequency();
        int askForNotes();
        void playSound();

    };