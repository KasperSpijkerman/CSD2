#include "circBuffer.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>

// short 
using namespace std;

CircBuffer::CircBuffer(uint size) : buffer(new float[size]), currentSize(size)
{

}

CircBuffer::~CircBuffer()
{
    deleteBuffer();
}

// writing values according to list with values
void CircBuffer::input(float value)
{  
    buffer[writeHead] = value;   
}

// reading values and printing them acooring to readhead
float CircBuffer::output() 
{
    // truncate index (remove everything after the decimal point)
    int i = (int) trunc (readHead);
    // subtract from the original value to find the remainder
    float indexDecimal = readHead - (float) i;
    // std::cout << linearMap(indexDecimal, buffer[i], buffer[i + 1]) << " IS THE OUTPUT" << std::endl;
    return Util::linearMap(indexDecimal, buffer[i], buffer[i + 1]);


    //return buffer[readHead];
}

// setting a distance between readheader and writeheader
void CircBuffer::setDistance (uint distance) 
{
    
    this->distance = distance;
    readHead = (writeHead - distance + currentSize) % currentSize;
    
}
// incrementing the writehead 
inline void CircBuffer::incrementWrite()
{
    writeHead++;
    wrapHeader(writeHead);
}
// incrementing the readhead
inline void CircBuffer::incrementRead()
{
    readHead++;
    wrapHeader(readHead);
}
void CircBuffer::incrementHeads() 
{
    incrementRead();
    incrementWrite();
}
// deleting buffer 
void CircBuffer::deleteBuffer()
{
    delete[] buffer;
}
inline void CircBuffer::wrapHeader(uint& head) 
{
     if (head >= currentSize)
        {
            head = 0 ;
        }
}

