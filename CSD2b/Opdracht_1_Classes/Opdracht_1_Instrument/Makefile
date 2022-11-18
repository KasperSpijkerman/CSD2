# Makefile voor Instrument
#
# Marc_G 2012

CC = g++
CFLAGS = -Wall
PROG = Instrument
SRC = instrument.cpp instrument_main.cpp
OBJS = instrument.o instrument_main.o 

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	/bin/rm -f $(PROG) $(OBJS)

depend:
	makedepend $(SRC)