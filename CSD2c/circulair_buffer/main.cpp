#include "circulair_buffer.h"

int main()
{
int circBufferSize = 8;
CircBuffer myBuffer(circBufferSize);
// setting distance/delay between write and read
myBuffer.setDistance(3);
// an array with buffervalues for write
float bufferValues[8] = {0.1,0.2,0.4,0.5,0.6,0.7,0.8,0.9};


// giving bufferValues to input and ouput
for(int i=0; i<8; i++)
{ 
    myBuffer.incrementHeads(); 
    myBuffer.input(bufferValues[i]); 
    myBuffer.output(); 
    
}

return 0; 

}