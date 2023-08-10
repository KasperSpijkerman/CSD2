#pragma once
#include "circBuffer.h"

class Delay : public Effect 
{
public:
	Delay();
	~Delay();

    float output(float input) override ;
	void prepareToPlay(double samplerate) override;
	// function for converting miliseconds to samples 
	float msToSamp(float ms, double samplerate);
    void deleteBuffer();
    float outputNoIncrement(float input);
    void incrementDelay();

	// setters
	void setDelayTime(float delayTime, float bpm, float division, bool sync);
	void setFeedback(float feedback);

private:
	// creating a circbuffer pointer
    CircBuffer* delayBuffer;
    // delay time in miliseconds
	float delayTimeMs { 0 };
    // delay in samples
	float delaySamples { 0 };
    // output
	float outputDelay { 0 };
    // feedback amount
	float delayFeedback { 0 };
    //
    float delayBpm {120};
    float delayDivision {1};
    // smooth delay change
    float targetDelaySamples;   // Target delay samples after user changes slider
    float delayTimeChangeRate;  // Rate of change of delay time per sample
    bool isDelayTimeChanging;   // Flag to check if delay time is currently changing
};