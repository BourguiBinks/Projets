#include <stdio.h>
#include <stdlib.h>

float *charge_tableau(int *nb_element) {
    FILE *fp = fopen("fichier", "r");
    char nb_element_str[10];
    fgets(nb_element_str, 10, fp);
    *nb_element = atoi(nb_element_str);
    float *tab = malloc(*nb_element * sizeof(float));
    for (int i = 0; i < *nb_element; i++) {
        fscanf(fp, "%f", &tab[i]);
    }
    fclose(fp);
    return tab;
}

void affiche_tab(float *tab, int N) {
    printf("Les réels contenus dans le fichier texte sont [");
    for (int i = 0; i < N; i++) {
        printf("%.2f ", tab[i]);
    }
    printf("]\n");
}

int main() {
    int nb_element;
    float *tableau = charge_tableau(&nb_element);
    affiche_tab(tableau, nb_element);
    free(tableau);
    return 0;
}
