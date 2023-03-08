CXX= g++
CXXFLAGS = -I/usr/local/include -Wall -std=c++1z
LDFLAGS= -ljack
SOURCE= circulair_buffer.o main.o
TARGET= Circular_Buffer
$(TARGET) : $(SOURCE)
	$(CXX) -o $@ $(SOURCE) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o *.csv

