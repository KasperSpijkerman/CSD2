# Makefile voor Instrument
#
# Marc_G 2012

CC = g++
CFLAGS = -Wall
PROG = Instrument
SRC = Instrument.cpp Instrument_main.cpp
OBJS = Instrument.o Instrument_main.o 

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	/bin/rm -f $(PROG) $(OBJS)

depend:
	makedepend $(SRC)