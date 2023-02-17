#include "delay.h"
#include "jack_module.h"
#include <array>

// callback class with prepare and process for sending audio to buffer

class Callback : public AudioCallback {

public:

    void prepare (int sampleRate) override 
    {
        for (Delay& delay : delays)
        {
			delay.setDistance(44100 * 0.5);
        }
    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            for (int sample = 0u; sample < numFrames; ++sample) {
                outputChannels[channel][sample] = (delays[channel].output (inputChannels[0][sample]) + inputChannels[0][sample])/2;
            }
        }
    }

private:
    std::array<Delay, 2> delays;
};







int main()
{
    auto callback = Callback {};
    auto jack = JackModule (callback);

    // start jack client with 2 inputs and 2 outputs
    jack.init (1, 2);

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