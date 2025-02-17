/**
 * \file vue_calculatrice.h
 * \author Alexandre Bourguignon
 * \brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la vue de la calculatrice GTK
 * \version 0.1
 * \date 2023-04-12
 * INFO0030 : Projet 3
 * 
 * 
 */
#ifndef __VIEW_CALCULATRICE__
#define __VIEW_CALCULATRICE__

#include "modele_calculatrice.h"
/**
 * \brief type opaque de la vue pour la calculatrice.
 */
typedef struct ViewCalculator_t ViewCalculator;

/**
 * \fn ViewCalculator *create_view_calculator()
 * \brief Crée une vue pour la calculatrice
 *
 * \return ViewCalculator *, un pointeur vers une vue de calculatrice.
 *         NULL en cas d'erreur
 */
ViewCalculator *create_view_calculator();

/**
 * \fn void destroy_view_calculator(ViewCalculator *view)
 * \brief Libère la mémoire allouée pour une structure de type ViewCalculator
 *
 * \param view, un pointeur vers une structure ViewCalculator (!= NULL)
 * 
 */
void destroy_view_calculator(ViewCalculator *view);

/**
 * \fn GtkWidget *get_entry1(ViewCalculator *view)
 * \brief Accesseur pour le champ number1 de la structure view
 *
 * \param view, un pointeur vers une structure ViewCalculator (!= NULL)
 * \return GtkWidget *, un pointeur vers un GtkWidget
 */
GtkWidget *get_entry1(ViewCalculator *view);
/**
 * \fn GtkWidget *get_entry2(ViewCalculator *view)
 * \brief Accesseur pour le champ number2 de la structure view
 *
 * \param view, un pointeur vers une structure ViewCalculator (!= NULL)
 * \return GtkWidget *, un pointeur vers un GtkWidget
 */
GtkWidget *get_entry2(ViewCalculator *view);
/**
 * \fn GtkWidget *get_table(ViewCalculator *view)
 * \brief Accesseur pour le champ number1 de la structure view
 *
 * \param view, un pointeur vers une structure ViewCalculator (!= NULL)
 * \return GtkWidget *, un pointeur vers un GtkWidget
 */
GtkWidget *get_table(ViewCalculator *view);

/**
 * \fn GtkLabel *get_labelResult(ViewCalculator *view)
 * \brief Accesseur pour le champ number1 de la structure view
 *
 * \param view, un pointeur vers une structure ViewCalculator (!= NULL)
 * \return GtkLabel *, un pointeur vers un GtkLabel
 */
GtkLabel *get_labelResult(ViewCalculator *view);

/**
 * \fn ViewCalculator *set_entry1(ViewCalculator *view, GtkWidget *entry1)
 * \brief Accesseur en écriture pour le champ number1 de la structure view
 *
 * \param view, un pointeur vers une structure ViewCalculator (!= NULL)
 * \param entry1, un pointeur vers un GtkWidget (!= NULL)
 * \return ViewCalculator *, un pointeur vers la structure view
 */
ViewCalculator *set_entry1(ViewCalculator *view, GtkWidget *entry1);
/**
 * \fn ViewCalculator *set_entry2(ViewCalculator *view, GtkWidget *entry2)
 * \brief Accesseur en écriture pour le champ number2 de la structure view
 *
 * \param view, un pointeur vers une structure ViewCalculator (!= NULL)
 * \param entry2, un pointeur vers un GtkWidget (!= NULL)
 * \return ViewCalculator *, un pointeur vers la structure view
 */
ViewCalculator *set_entry2(ViewCalculator *view, GtkWidget *entry2);
/**
 * \fn ViewCalculator *set_window(ViewCalculator *view, GtkWidget *window)
 * \brief Accesseur en écriture pour le champ window de la structure view
 *
 * \param view, un pointeur vers une structure ViewCalculator (!= NULL)
 * \param window, un pointeur vers un GtkWidget (!= NULL)
 * \return ViewCalculator *, un pointeur vers la structure view
 */
ViewCalculator *set_window(ViewCalculator *view, GtkWidget *window);
/**
 * \fn ViewCalculator *set_table(ViewCalculator *view, GtkWidget *table)
 * \brief Accesseur en écriture pour le champ table de la structure view
 *
 * \param view, un pointeur vers une structure ViewCalculator (!= NULL)
 * \param table, un pointeur vers un GtkWidget (!= NULL)
 * \return ViewCalculator *, un pointeur vers la structure view
 */
ViewCalculator *set_table(ViewCalculator *view, GtkWidget *table);

/**
 * \fn ViewCalculator *set_labelResult(ViewCalculator *view, GtkLabel *label)
 * \brief Accesseur en écriture pour le champ labelResult de la structure view
 *
 * \param view , un pointeur vers une structure ViewCalculator (!= NULL)
 * \param label , un pointeur vers un GtkLabel (!= NULL)
 * \return ViewCalculator *, un pointeur vers la structure view
 */
ViewCalculator *set_labelResult(ViewCalculator *view, GtkLabel *label);

/**
 * \fn void show_error_popup(char *errorMessage);
 * \brief Permet d'afficher la fenêtre d'erreur si une des entrées est invalide
 *
 * \param errorMessage, une chaine de caractère représentant le message (!= NULL)
 *
 */
void show_error_popup(char *errorMessage);

/**
 * \fn void show_result(ModelCalculator *model, ViewCalculator *view);
 * \brief Permet d'afficher le résultat dans le cas où les entrées sont valides
 *
 * \param model, un pointeur vers une structure de type ModelCalculator (!= NULL)
 * \param view, un pointeur vers une structure de type ViewCalculator (!= NULL)
 *
 */
void show_result(ModelCalculator *model, ViewCalculator *view);


#endif
