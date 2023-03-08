#include "circulair_buffer.h"
#include <iostream>
#include <algorithm>
#include <iterator>

// short 
using namespace std;

CircBuffer::CircBuffer(uint size) : buffer(new float[size]), currentSize(size)
{
    cout << "Inside Circbuffer constructor\n";

}

CircBuffer::~CircBuffer()
{
    cout << "Inside Circbuffer deconstructor\n";
    deleteBuffer();
    cout << "Buffer is now deleted\n";
}

// writing values according to list with values
void CircBuffer::input(float value)
{  
    buffer[writeHead] = value; 
    cout << buffer[writeHead] << " Is written\n";   
}

// reading values and printing them acooring to readhead
float CircBuffer::output() 
{ 
    cout << buffer[readHead] << " Is being read\n"; 
    return buffer[readHead];
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

