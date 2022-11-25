# Makefile voor Instrument
#
# Marc_G 2012

CC = g++
CFLAGS = -Wall -std=c++14
PROG = Multiple_Instruments
SRC = instruments.cpp instruments_main.cpp bass.cpp guitar.cpp
OBJS = instruments.o instruments_main.o bass.o guitar.o

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	/bin/rm -f $(PROG) $(OBJS)

depend:
	makedepend $(SRC)