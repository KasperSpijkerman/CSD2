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
            delay.setDistance(44100 * 2);
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
                outputChannels[channel][sample] = tremolos[channel].output(waveshapers[channel].output (inputChannels[0][sample]))/3 + (delays[channel].output(waveshapers[channel].output (inputChannels[0][sample]))/3);
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