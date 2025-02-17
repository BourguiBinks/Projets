/**
 * \file controleur_calculatrice.h
 * \author Alexandre Bourguignon
 * \brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour le controleur de la calculatrice GTK
 * \version 0.1
 * \date 2023-04-12
 * @projet: INFO0030 : Projet 3
 * 
 * 
 */
#ifndef __CONTROLER_CALCULATRICE__
#define __CONTROLER_CALCULATRICE__
/**
 * \fn void click_diminuer(GtkWidget *pF, gpointer data)
 * \brief Signal pour la diminution de température
 *
 * \param button, le widget bouton
 * \param user_data pointeur générique
 */
void on_button_addition_clicked(GtkWidget *button, gpointer user_data);

#endif
