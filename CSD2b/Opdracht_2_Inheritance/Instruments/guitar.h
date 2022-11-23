//header file for description of instrument class
#pragma once
#include <iostream>
#include "instruments.h"

class Guitar : public Instruments 
    {
    Guitar(std::string name);
    ~Guitar();

    //methods
    void screech();
    
    };