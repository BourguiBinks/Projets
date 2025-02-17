/**
 * @file main_calculatrice.c
 * @author Alexandre Bourguignon
 * @brief Ce fichier contient la fonction main qui permet de tester la calculatrice GTK
 * @version 0.1
 * @date 2023-04-12
 * @projet: INFO0030 : Projet 3
 * 
 */
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include "assert.h"

#include "modele_calculatrice.h"
#include "controleur_calculatrice.h"
#include "vue_calculatrice.h"

static void destroy_window(GtkWidget *pF, gpointer data){
  gtk_main_quit();
}//fin detruire_fenetre()

static GtkWidget *create_window(){
    GtkWidget *pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pFenetre), "Addition");
    gtk_window_set_default_size(GTK_WINDOW(pFenetre), 240, 150);
    gtk_window_set_position(GTK_WINDOW(pFenetre), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(destroy_window), NULL);
    
    return pFenetre;
}

int main(int argc, char **argv){
  
  ViewCalculator *view = create_view_calculator();
  if(view == NULL){
    printf("Impossible d'allouer de la mémoire\n");
    return EXIT_FAILURE;
  }

  gtk_init(&argc, &argv);

  GtkWidget *window = create_window();
  set_window(view, window);

  GtkWidget *table = gtk_table_new(3, 2, TRUE);
  gtk_container_add(GTK_CONTAINER(window), table);
  set_table(view, table);
  
  GtkWidget *label1 = gtk_label_new("Nombre 1 :");
  gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 0, 1, GTK_EXPAND, GTK_EXPAND, 0, 0);
  GtkWidget *label2 = gtk_label_new("Nombre 2 :");
  gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 1, 2, GTK_EXPAND, GTK_EXPAND, 0, 0 );


  GtkWidget *entry1 = gtk_entry_new();
  gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 0, 1, GTK_EXPAND, GTK_EXPAND, 0, 0 );
  set_entry1(view, entry1);

  GtkWidget *entry2 = gtk_entry_new();
  gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 1, 2, GTK_EXPAND, GTK_EXPAND, 0, 0);
  set_entry2(view, entry2);

  GtkWidget *button = gtk_button_new_with_label("Addition");
  gtk_table_attach(GTK_TABLE(table), button, 0, 1, 2, 3, GTK_EXPAND, GTK_EXPAND, 0, 0);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_addition_clicked), view);   

  gtk_widget_show_all(window);

  gtk_main();

  destroy_view_calculator(view);
    return EXIT_SUCCESS;
}