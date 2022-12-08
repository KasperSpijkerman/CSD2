#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "sine.h"
#include "saw.h"
#include "square.h"
#include "audioToFile.h"

/*
 * jackd -d coreaudio -> starting jack client
 */
int main(int argc,char **argv)
{
  auto callback = CustomCallback{};
  auto jackModule = JackModule{callback};

#if WRITE_TO_FILE
  AudioToFile audioToFile;
  audioToFile.write(callback);
#else

  jackModule.init(0, 1);

  bool running = true;
  while (running) {
    switch (std::cin.get()) {
      case 'q':
        running = false;
    }
#endif
  //end the program
  return 0;
} // main()
