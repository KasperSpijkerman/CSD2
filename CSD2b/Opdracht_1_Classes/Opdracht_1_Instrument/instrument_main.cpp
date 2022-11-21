//file for main 
#include <iostream>
#include "instrument.h"

int main()
{
    Instrument myInstrument;
    myInstrument.printName();
    myInstrument.printFrequency();
    myInstrument.askForNotes();
    for(int i = 0; i < myInstrument.notesAmount; i++) 
    {
    myInstrument.playSound();
    }
    return 0;
}