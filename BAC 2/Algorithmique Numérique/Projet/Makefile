CC = gcc
CFLAGS = #-Wall -Wextra -std=c99

all: multiplication vecteur

multiplication: matricecreuse.o produit.o mainproduit.o
	$(CC) $(CFLAGS) -o multiplication matricecreuse.o produit.o mainproduit.o

vecteur: matricecreuse.o valeurpropre.o produit.o mainvecteur.o
	$(CC) $(CFLAGS) -o vecteur matricecreuse.o valeurpropre.o mainvecteur.o produit.o -lm

matricecreuse.o: matricecreuse.c matricecreuse.h
	$(CC) $(CFLAGS) -c matricecreuse.c

produit.o: produit.c produit.h matricecreuse.h
	$(CC) $(CFLAGS) -c produit.c

mainproduit.o: mainproduit.c produit.h matricecreuse.h
	$(CC) $(CFLAGS) -c mainproduit.c

valeurpropre.o: valeurpropre.c valeurpropre.h matricecreuse.h produit.h
	$(CC) $(CFLAGS) -c valeurpropre.c produit.c -lm

mainvecteur.o: mainvecteur.c valeurpropre.h matricecreuse.h produit.h
	$(CC) $(CFLAGS) -c mainvecteur.c produit.c -lm

clean:
	rm -f multiplication vecteur *.o
	rm -f fichier_trie.A.mtx
	rm -f fichier_trie.B.mtx
	rm -f vecteur.mtx
	rm -f produit.mtx
