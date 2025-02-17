/**
 * \file vue_calculatrice.c
 * \author Alexandre Bourguignon
 * \brief Ce fichier contient la vue de la calculatrice GTK
 * \version 0.1
 * \date 2023-04-12
 * INFO0030 : Projet 3
 * 
 */
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <assert.h>

#include "vue_calculatrice.h"
#include "modele_calculatrice.h"
#include "controleur_calculatrice.h"

//PROTOTYPES

/**
 * \fn void close_error_popup(GtkWidget *widget, gpointer data)
 * \brief Permet de détruire la fenêtre pop-up d'erreur
 *
 * \param widget, un pointeur vers un GgkWidget (!= NULL)
 * \param data, un pointeur générique (!= NULL)
 *
 */
static void close_error_popup(GtkWidget *widget, gpointer data) ;


/**
 * \brief Implémentation de la vue pour la calculatrice.
 */
struct ViewCalculator_t {
    GtkWidget *entry1; /*!< l'entrée 1*/
    GtkWidget *entry2; /*!< l'entrée 2*/
    GtkWidget *window; /*!< la fenêtre*/
    GtkWidget *table; /*!< la table*/
    GtkLabel *labelResult; /*!< le label pour afficher le résultat*/   
};

GtkWidget *get_entry1(ViewCalculator *view){
    assert(view != NULL);

    return view->entry1;
}
GtkWidget *get_entry2(ViewCalculator *view){
    assert(view != NULL);

    return view->entry2;
}

GtkWidget *get_table(ViewCalculator *view){
    assert(view != NULL);

    return view->table;
}

GtkLabel *get_labelResult(ViewCalculator *view){
    assert(view != NULL);

    return view->labelResult;
}


ViewCalculator *set_window(ViewCalculator *view, GtkWidget *window){
    assert(view != NULL && window != NULL);
    view->window = window;
    return view;
}

ViewCalculator *set_entry1(ViewCalculator *view, GtkWidget *entry1){
    assert(view != NULL && entry1 != NULL);
    view->entry1 = entry1;

    return view;
}

ViewCalculator *set_entry2(ViewCalculator *view, GtkWidget *entry2){
    assert(view != NULL && entry2 != NULL);
    view->entry2 = entry2;

    return view;
}

ViewCalculator *set_table(ViewCalculator *view, GtkWidget *table){
    assert(view != NULL && table != NULL);
    view->table = table;

    return view;
}

ViewCalculator *set_labelResult(ViewCalculator *view, GtkLabel*label){
    assert(view != NULL && label != NULL);
    view->labelResult = label;

    return view;
}

ViewCalculator *create_view_calculator(){
    ViewCalculator *viewCalculator = malloc(sizeof(ViewCalculator));
    if(viewCalculator == NULL){
        return NULL;
    }
    
    return viewCalculator;
}

void destroy_view_calculator(ViewCalculator *view){
    assert(view != NULL);

    free(view);
}


void show_result(ModelCalculator *model, ViewCalculator *view){
    assert(model != NULL && view != NULL);

    if(get_labelResult(view) != NULL){
        gtk_container_remove(GTK_CONTAINER(get_table(view)), GTK_WIDGET(get_labelResult(view)));
    }

    char outputText[20];
    sprintf(outputText, "La somme est %d", get_result(model));

    GtkWidget *pLabel = gtk_label_new(outputText);
    set_labelResult(view, GTK_LABEL(pLabel));
    gtk_table_attach(GTK_TABLE(get_table(view)), pLabel, 1, 2, 2 , 3, GTK_EXPAND, GTK_EXPAND, 0, 0);
    gtk_widget_show(pLabel);
}

static void close_error_popup(GtkWidget *widget, gpointer data) {
  if (GTK_IS_WIDGET(data)) {
    gtk_widget_destroy(GTK_WIDGET(data));
  }
}

void show_error_popup(char *errorMessage){
  assert(errorMessage != NULL);
  // Création de la fenêtre pop-up
  GtkWidget *popupWindow = gtk_window_new(GTK_WINDOW_POPUP);
  gtk_window_set_default_size(GTK_WINDOW(popupWindow), 25, 100);
  gtk_window_set_position(GTK_WINDOW(popupWindow), GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(popupWindow), "destroy", G_CALLBACK(close_error_popup), NULL);
  
  // Création de la table
  GtkWidget *table = gtk_table_new(3,3,TRUE);
  gtk_container_add(GTK_CONTAINER(popupWindow), table);

  // Création du label pour afficher le message d'erreur
  GtkWidget *popupLabel = gtk_label_new(errorMessage);
  gtk_table_attach(GTK_TABLE(table), popupLabel, 1, 3, 0, 1, GTK_EXPAND,GTK_EXPAND, 0, 0);

  // Création du bouton "ok"
  GtkWidget *popupButton = gtk_button_new_from_stock(GTK_STOCK_OK);
  gtk_button_set_label(GTK_BUTTON(popupButton), "OK");
  gtk_button_set_image(GTK_BUTTON(popupButton), gtk_button_get_image(GTK_BUTTON(popupButton)));
  g_signal_connect(G_OBJECT(popupButton), "clicked", G_CALLBACK(close_error_popup), G_OBJECT(popupWindow));
  gtk_table_attach(GTK_TABLE(table), popupButton, 1, 2, 2, 3, GTK_EXPAND,GTK_EXPAND, 0, 0);


  //Insersion de l'image
  GtkWidget *popupImage = gtk_image_new_from_icon_name("gtk-dialog-info", GTK_ICON_SIZE_DIALOG);
  gtk_image_set_pixel_size(GTK_IMAGE(popupImage), 50);
  gtk_table_attach(GTK_TABLE(table), popupImage, 0, 1, 0, 1, GTK_SHRINK, GTK_SHRINK, 0, 0);

  // Affichage de la fenêtre pop-up
  gtk_widget_show_all(popupWindow);
}