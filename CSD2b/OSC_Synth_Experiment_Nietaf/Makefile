CXX= g++ -g
CXXFLAGS = -I/usr/local/include -Wall -std=c++1z
LDFLAGS= -ljack
SOURCE= synth.o square.o sine.o oscillator.o main.o saw.o add_synth.o vibe_synth.o melody.o ui_file.o writeToFile.o osc.o
TARGET=Synth
$(TARGET) : $(SOURCE)
	$(CXX) -o $@ $(SOURCE) $(LDFLAGS) -llo

.cpp.o:
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o *.csv

