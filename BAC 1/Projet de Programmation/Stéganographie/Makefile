## Makefile for INFO0030: Project 2
##
## Targets:
##  - pnm_tests: build the PNM library unit tests binary
##  - stegano_tests: build the LSB steganography library unit tests binary
##  - stegano: build the LSB steganography program
##  - doc: generate documentation in HTML format
##  - clean: remove object files, binaries and documentation

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -Wswitch-default -Wswitch-enum -Winit-self
LD=gcc
LDFLAGS=
DOXYGEN=doxygen

# Files

#EXEC=pnm_tests stegano_tests stegano doc

## Rules

# pnm_tests
pnm_tests: pnm.o seatest.o pnm_test.o
	$(CC) -o pnm_tests $^ $(LDFLAGS)
pnm.o: pnm.c pnm.h
	$(CC) -c $< -o $@ $(CFLAGS)
seatest.o: seatest.c seatest.h
	$(CC) -c $< -o $@ $(CFLAGS)
pnm_tests.o: pnm_test.c pnm.c pnm.h seatest.c seatest.h
	$(CC) -c $< -o $@ $(CFLAGS)

# stegano_tests
stegano_tests: stegano.o seatest.o stegano_test.o pnm.o 
	$(CC) -o stegano_tests $^ $(LDFLAGS)
stegano.o: stegano.c pnm.c stegano.h pnm.h
	$(CC) -c $< -o $@ $(CFLAGS)
stegano_test.o: stegano_test.c stegano.c stegano.h pnm.c pnm.h seatest.c seatest.h
	$(CC) -c $< -o $@ $(CFLAGS)

# stegano
stegano: stegano.o pnm.o main.o
	$(CC) -o stegano $^ $(LDFLAGS)
main.o: main.c stegano.c pnm.c stegano.h pnm.h
	$(CC) -c $< -o $@ $(CFLAGS)
# doc
doc:
	$(DOXYGEN) .doc_conf

# clean
clean:
	rm -f *.o $(EXEC) *~
