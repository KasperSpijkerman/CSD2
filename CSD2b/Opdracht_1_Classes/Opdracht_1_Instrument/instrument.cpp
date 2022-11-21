//putting the information in the class
#include <iostream>
#include "instrument.h"

Instrument::Instrument()
{
    name = "Guitar";
    frequency = 440;
}
void Instrument::printFrequency()
    {
    std::cout << "Tuning Frequency is: " << frequency << " Hz" << std::endl;
    }
void Instrument::printName()
{
    std::cout << "Instrument name is: " << name << std::endl;
}
int Instrument::askForNotes()
{
    std::cout << "Enter the amount of Notes " << std::endl;
    std::cin >> notesAmount;
    return notesAmount;
}
void Instrument::playSound()
{
    std::cout << "Pling" << std::endl;
}

