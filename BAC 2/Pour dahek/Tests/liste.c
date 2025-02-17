#include <stdio.h>
#include <stdlib.h>

/* Définition de la structure de cellule */
typedef struct Cell_t{
    char *data;
    struct Cell_t *next;
} Cell;

/* Fonction pour ajouter une cellule à la fin de la liste */
Cell *create_list() {
    Cell *head = NULL;
    for(int i = 0; i < 10; i++) {
        Cell *new_cell = malloc(sizeof(Cell));
        if(new_cell == NULL){
            return NULL;
        }
        new_cell->data = NULL;
        new_cell->next = NULL;

        if(head == NULL) {
            head = new_cell;
        } else{
            Cell *current = head;
            while(current->next != NULL) {
                current = current->next;
            }
            current->next = new_cell;
        }
    }
    return head;
}


/* Fonction pour calculer le nombre de cellules dans la liste */
int count_cells(Cell *head) {
    int count = 0;
    Cell *current = head;

    while(current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

void set_at(Cell *head, int i, char *c) {
    Cell *current = head;
    int j = 0;

    // Parcourir la liste jusqu'à la ième cellule
    while (j < i && current != NULL) {
        current = current->next;
        j++;
    }

    // Vérifier si la ième cellule existe
    if (j == i && current != NULL) {
        current->data = c;
    } else {
        printf("La i-eme cellule n'existe pas\n");
    }
}

void print_list(Cell* head) {
    Cell* current = head;
    while (current != NULL) {
        if (current->data == NULL) {
            printf("NULL ");
        } else {
            printf("%s ", current->data);
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    Cell *head = create_list();

    

    /* Afficher le nombre de cellules */
    printf("Nombre de cellules dans la liste : %d\n", count_cells(head));

    set_at(head, 7, "@");
    set_at(head, 4, "%");

    print_list(head);
    return 0;
}
