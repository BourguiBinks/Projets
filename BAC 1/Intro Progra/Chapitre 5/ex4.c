#include <stdio.h>

typedef struct panneau {
    char type;
    float largeur;
    float longueur;
    float epaisseur;
} Panneau;

int main() {
    Panneau p1;
    Panneau p2;
    Panneau p3;

    printf("Pour encoder un panneau, indique le type de bois (p = pin, c=chene, hetre=h), la largeur, la longueur et l'épaisseur\n");
    scanf("%c %f %f %f", &p1.type, &p1.largeur, &p1.longueur, &p1.epaisseur);
    printf("fais de même pour le 2 panneau (p = pin, c=chene, hetre=h), la largeur, la longueur et l'épaisseur\n");
    scanf(" %c %f %f %f", &p2.type, &p2.largeur, &p2.longueur, &p2.epaisseur);
    printf("encore un 3e panneau... (p = pin, c=chene, hetre=h), la largeur, la longueur et l'épaisseur\n");
    scanf(" %c %f %f %f", &p3.type, &p3.largeur, &p3.longueur, &p3.epaisseur);

    int nb_pin = 0;
    int nb_chene = 0;
    int nb_hetre = 0;

    if (p1.type == 'p') {
        nb_pin += 1;
    }
    if (p2.type == 'p') {
        nb_pin += 1;
    }
    if (p3.type == 'p') {
        nb_pin += 1;
    }
    if (p1.type == 'c') {
        nb_chene += 1;
    }
    if (p2.type == 'c') {
        nb_chene += 1;
    }
    if (p3.type == 'c') {
        nb_chene += 1;
    }
    if (p1.type == 'h') {
        nb_hetre += 1;
    }
    if (p2.type == 'h') {
        nb_hetre += 1;
    }
    if (p3.type == 'h') {
        nb_hetre += 1;
    }

    printf("Il y a actuellement %d pins, %d chene, %d hetre\n", nb_pin, nb_chene, nb_hetre);
}