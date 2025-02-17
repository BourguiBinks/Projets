## Makefile for INFO0030: Project 2


CC=gcc
LD=gcc
CFLAGS=
LDFLAGS=
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`
DOXYGEN=doxygen
VUE_CALC=vue_calculatrice.c vue_calculatrice.h
CONTROL_CALC=controleur_calculatrice.c controleur_calculatrice.h
MODEL_CALC=modele_calculatrice.c modele_calculatrice.h
UTILS=utils.c utils.h
FILES= $(VUE_CALC) $(CONTROL_CALC) $(MODEL_CALC) $(UTILS)

all: calculatrice

calculatrice: main_calculatrice.o controleur_calculatrice.o vue_calculatrice.o modele_calculatrice.o utils.o
	$(LD) -o calculatrice $^ $(LDFLAGS) $(GTKFLAGS)

main_calculatrice.o: main_calculatrice.c $(VUE_CALC) $(CONTROL_CALC) $(MODEL_CALC)
	$(CC) -c $< -o $@ $(CFLAGS) $(GTKFLAGS)

controleur_calculatrice.o: $(CONTROL_CALC) $(VUE_CALC) $(MODEL_CALC) $(UTILS)
	$(CC) -c $< -o $@  $(CFLAGS) $(GTKFLAGS)	

vue_calculatrice.o: $(VUE_CALC) $(CONTROL_CALC) $(MODEL_CALC)
	$(CC) -c $< -o $@  $(CFLAGS) $(GTKFLAGS)

modele_calculatrice.o: $(MODEL_CALC)
	$(CC) -c $< -o $@  $(CFLAGS) $(GTKFLAGS)

utils.o: $(UTILS)
	$(CC) -c $< -o $@  $(CFLAGS)


doc:
	mkdir -p doc/
	$(DOXYGEN) Doxyfile

clean:
	rm -f *.o
	rm -f calculatrice
	rm -rf doc
	clear
