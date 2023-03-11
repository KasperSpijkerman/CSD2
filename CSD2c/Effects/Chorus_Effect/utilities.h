#pragma once

namespace Util
{
    inline double mapInRange(double factor, double inputMin, double inputMax, double outputMin, double outputMax)
    {
        double inputDelta = inputMax - inputMin;
        double outputDelta = outputMax - outputMin;
        double valueScaled = (factor-inputMin)/inputDelta;
        double output = valueScaled * outputDelta + outputMin;
        return output;
    }

    inline double linearMap(double factor, double min, double max)
    {
        double output = mapInRange(factor, 0.0, 1.0, min, max);
        return output;
    }

}