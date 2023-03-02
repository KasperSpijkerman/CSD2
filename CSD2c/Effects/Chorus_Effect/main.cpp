#include "jack_module.h"
#include "delay.h"
#include "chorus.h"
#include <array>

// callback class with prepare and process for sending audio to buffer

class Callback : public AudioCallback {

public:
    // giving the samplerate to every effect and executing init functions
    void prepare (int sampleRate) override 
    {
        for (Chorus& chorus : choruses)
            delay.prepareToPlay(sampleRate);
    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            for (int sample = 0u; sample < numFrames; ++sample) 
            {
                outputChannels[channel][sample] = choruses[channel].output(inputChannels[0][sample]);
            }
        }
    }

private:
    std::array<Chorus, 2> choruses;
};







int main()
{
    auto callback = Callback {};
    auto jack = JackModule (callback);

    // start jack client with 1 input and 2 outputs
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