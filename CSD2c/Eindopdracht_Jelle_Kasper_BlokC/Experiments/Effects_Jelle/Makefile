CXX= g++
CXXFLAGS = -I/usr/local/include -Wall -g -std=c++17
LDFLAGS= -ljack
SOURCE= tremolo.o circ_buff.o main.o effect.o delay.o waveshaper.o sine.o saw.o oscillator.o square.o monoChorus.o stereoChorus.o lcrDelay.o onepole.o
TARGET= test_effects 

$(TARGET) : $(SOURCE)
	$(CXX) -o $@ $(SOURCE) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o