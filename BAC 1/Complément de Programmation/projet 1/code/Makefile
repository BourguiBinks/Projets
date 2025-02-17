### 
## Makefile skeleton
## INFO0947: Projet 1
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=

# Files
EXEC=somme
MODULES=main-somme.c somme.c
OBJECTS=main-somme.o somme.o

## Rules

all: $(EXEC)

somme: $(OBJECTS)
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

main-somme.o: main-somme.c
	$(CC) -c main-somme.c -o main-somme.o $(CFLAGS)

somme.o: somme.c
	$(CC) -c somme.c -o somme.o $(CFLAGS)

clean:
	rm -f *.o $(EXEC)~