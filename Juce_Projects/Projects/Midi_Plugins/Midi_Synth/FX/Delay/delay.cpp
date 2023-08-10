#include "delay.h"


Delay::Delay() : targetDelaySamples(0), delayTimeChangeRate(0), isDelayTimeChanging(false)
{
    // create delaybuffer with a size
    delayBuffer = new CircBuffer(static_cast<uint>(sampleRate * 60));
    memset(delayBuffer, 0, sizeof delayBuffer);
}

Delay::~Delay()
{
    deleteBuffer();
}

void Delay::prepareToPlay(double samplerate)
{
	sampleRate = samplerate;
    memset(delayBuffer, 0, sizeof delayBuffer);
}



float Delay::output(float input)
{
    // If delay time is changing, adjust the current delay samples
    if (isDelayTimeChanging) {
        delaySamples += delayTimeChangeRate;
        if (abs(targetDelaySamples - delaySamples) < abs(delayTimeChangeRate)) {
            delaySamples = targetDelaySamples;
            isDelayTimeChanging = false; // Stop changing once we're close enough
        }
        delayBuffer->setDistance(delaySamples);
    }

    delayBuffer->input(input + (outputDelay * delayFeedback));
    outputDelay = delayBuffer->output();
    delayBuffer->incrementHeads();
    return (outputDelay * wet) + (input * dry);
}

void Delay::setDelayTime(float delayMs,float bpm, float division, bool sync) {
    delayBpm = bpm / 100;
    delayDivision = 1.0f / division;
    float dtSyncInMs = (2400.0 / delayBpm) * delayDivision;
    delayTimeMs = delayMs;

    if (sync)
        targetDelaySamples = msToSamp(dtSyncInMs, sampleRate);
    else
        targetDelaySamples = msToSamp(delayTimeMs, sampleRate);

    // Assuming you want to change the delay time over a period of 100ms
    delayTimeChangeRate = (targetDelaySamples - delaySamples) / msToSamp(100.0f, sampleRate);
    isDelayTimeChanging = true;
}

float Delay::outputNoIncrement(float input)
{
    // giving the input to writehead with feedback
    delayBuffer->input(input +(outputDelay*delayFeedback));
    // reading output and store in variable
    outputDelay = delayBuffer->output();
    return (outputDelay*wet) + (input*dry);
}


float Delay::msToSamp(float ms, double samplerateFX)
{
	// amount of samples calculated based on miliseconds and samplerate
	float samples = static_cast<float>(ms * samplerateFX / 1000);
	return samples;
}

void Delay::setFeedback(float feedback) 
{
	// make sure feedback goes not out of range
	if(feedback > 0.99) 
	{
		delayFeedback = static_cast<float>(0.99);
	} 
	else if(feedback < 0) 
	{
		delayFeedback = 0;
	}
	else 
	{
		delayFeedback = feedback;
	}
}

void Delay::incrementDelay()
{
    delayBuffer -> incrementHeads();
}

void Delay::deleteBuffer()
{
    delete delayBuffer;
}

