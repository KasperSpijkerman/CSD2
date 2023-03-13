#include "jack_module.h"
#include "delay.h"
#include "flanger.h"
#include <array>

// callback class with prepare and process for sending audio to buffer

class Callback : public AudioCallback {

public:
    // giving the samplerate to every effect and executing init functions
    void prepare (int sampleRate) override 
    {
        for (Flanger& flanger : flangers)
            flanger.prepareToPlay(sampleRate);

        for (Sine& sine : sines) {
            sine.setFrequency(300);
            sine.setSamplerate(sampleRate);

        }
    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

        for (int channel = 0u; channel < numOutputChannels; ++channel) {

            for (int sample = 0u; sample < numFrames; ++sample) 
            {
                sines[channel].tick();
                outputChannels[channel][sample] = flangers[channel].output(inputChannels[0][sample],channel)*0.8;
            }
        }
    }

private:
    std::array<Flanger, 2> flangers;
    //test sines
    std::array<Sine, 2> sines;

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