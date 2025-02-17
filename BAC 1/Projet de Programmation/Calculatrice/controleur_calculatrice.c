/**
 * @file controleur_calculatrice.c
 * @author Alexandre Bourguignon
 * @brief Ce fichier contient le controleur de la calculatrice GTK
 * @version 0.1
 * @date 2023-04-12
 * @projet: INFO0030 : Projet 3
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "vue_calculatrice.h"
#include "modele_calculatrice.h"
#include "utils.h"


void on_button_addition_clicked(GtkWidget *button, gpointer user_data){
    ViewCalculator *view = (ViewCalculator *)user_data;
   
    const char *inputText1 = gtk_entry_get_text(GTK_ENTRY(get_entry1(view)));
    const char *inputText2 = gtk_entry_get_text(GTK_ENTRY(get_entry2(view)));

    /*printf("Input 1: %s\n", inputText1);
     *printf("Input 2: %s\n", inputText2);
     */
    int valid1 = is_valid_number(inputText1);

    switch(valid1) {
      case 0:
         break; // Entrée valide
      case 1:
         show_error_popup("L'une des deux entrées est vide !");
         return;
      case 2:
         show_error_popup("Le nombre 1 est invalide !");
         return;
    }
    int valid2 = is_valid_number(inputText2);

    switch(valid2) {
     case 0:
         break; // Entrée valide
    case 1:
        show_error_popup("L'une des deux entrées est vide !");
        return;
    case 2:
        show_error_popup("Le nombre 2 est invalide !");
        return;
  }

    int number1 = atoi(inputText1);
    int number2 = atoi(inputText2);

    ModelCalculator *model = create_ModelCalculator();
    if(model == NULL){
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    model = make_addition(model, number1, number2);
    if(model == NULL){
        destroy_ModelCalculator(model);
        destroy_view_calculator(view);
        return;
    }
    show_result(model, view);
    destroy_ModelCalculator(model);
}
