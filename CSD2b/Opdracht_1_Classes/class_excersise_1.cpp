#include <iostream>
#include <random>
#include <ctime>

class Woofer
{
public:
  float magnet;
  float coil;

  void printCoilPosition() 
  {
    std::cout << "Coil position: " << coil << std::endl;
  }
  
  void move(float position)
  {
    coil = position;
  }

};


int main()
{
    Woofer myWoofer;
    srand(time(NULL));
    //for loop 10 times speaker position and printing
    for(int i = 0; i < 10; i++)
    {
    if (i == 0) 
    {
        myWoofer.move(0);
    }
    //generating random float value
    float r = rand() / static_cast<float>(RAND_MAX);
    if (i > 0 && i < 9) 
    {
        myWoofer.move(r);
    }
    if (i == 9) 
    {
        myWoofer.move(0);
    }
    myWoofer.printCoilPosition();
    };

    return 0;
}