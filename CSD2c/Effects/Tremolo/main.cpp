#include "jack_module.h"
#include "tremolo.h"
#include <array>
#include <iostream>


class Callback : public AudioCallback {

public:

    void prepare (int sampleRate) override {
        for (Tremolo& tremolo : tremolos)
            tremolo.prepareToPlay (static_cast<double> (sampleRate));
    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            for (int sample = 0u; sample < numFrames; ++sample) {
                outputChannels[channel][sample] = tremolos[channel].output (inputChannels[0][sample]);
            }
        }
    }

private:
    std::array<Tremolo,2> tremolos;
};


int main() {

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
