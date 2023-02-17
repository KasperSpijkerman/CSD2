#include "Utilities.h"
#include <cmath>

using uint = unsigned int;

class WaveShaper {
public:
    WaveShaper (int size);
    ~WaveShaper();

    float output (float input);
    void setDrive (float k);

private:
    uint bufferSize { 0 };
    float* buffer;
};