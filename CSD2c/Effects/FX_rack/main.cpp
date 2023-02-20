#include "jack_module.h"
#include "waveshaper.h"
#include "delay.h"
#include "tremolo.h"
#include <array>

// callback class with prepare and process for sending audio to buffer

class Callback : public AudioCallback {

public:

    void prepare (int sampleRate) override 
    {
        for (Delay& delay : delays)
        {
            delay.prepareToPlay(sampleRate);
            // set delay time
            delay.setDelayTime(200);
            // set dry wet (input wet amount)
            delay.setDryWet(0.5);
        }
        for (Tremolo& tremolo : tremolos)
            tremolo.prepareToPlay(sampleRate);
        for (WaveShaper& waveshaper : waveshapers)
            waveshaper.prepareToPlay(sampleRate);
    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            for (int sample = 0u; sample < numFrames; ++sample) {
                outputChannels[channel][sample] = delays[channel].output (inputChannels[0][sample])/2;
            }
        }
    }

private:
    std::array<Delay, 2> delays;
    std::array<Tremolo, 2> tremolos;
    std::array<WaveShaper, 2>waveshapers;
};







int main()
{
    auto callback = Callback {};
    auto jack = JackModule (callback);

    // start jack client with 1 input and 2 outputs
    jack.init (1, 2);
    //std::cout << " Press d to enter Dry/wet for the different Effects:\n ";
    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
                break;
        }
    }





    return 0;
    


    
}