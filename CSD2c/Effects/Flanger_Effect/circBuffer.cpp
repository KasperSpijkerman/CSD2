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

// reading values and printing them according to readhead
float CircBuffer::output() 
{
    int i = (int) trunc (readHead);
    float factor = readHead - (float) i;
    return Util::linearMap(factor, buffer[i], buffer[i + 1]);
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

