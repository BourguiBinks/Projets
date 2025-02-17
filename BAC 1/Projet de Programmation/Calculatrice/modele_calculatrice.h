/**
 * \file modele_calculatrice.h
 * \author Alexandre Bourguignon
 * \brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour le modèle de la calculatrice GTK
 * \version 0.1
 * \date 2023-04-12
 * INFO0030 : Projet 3
 * 
 * Contient les constructeurs, destructeurs, accessseurs et l'addition des deux nombres en entrée
 * 
 */
#ifndef __MODEL_CALCULATRICE__
#define __MODEL_CALCULATRICE__

/**
 * \brief Nombre minimum que peut prendre un nombre (arbitraire)
 */
#define MINMUM_NUMBER -1000000000
/**
 * \brief Nombre maximum que peut prendre un nombre (arbitraire)
 */
#define MAXIMUM_NUMBER 1000000000
/**
 * \brief Nombre minimum que peut prendre le résultat (arbitraire)
 */
#define MINIMUM_RESULT -2000000000
/**
 * \brief Nombre maximum que peut prendre le résultat (arbitraire)
 */
#define MAXIMUM_RESULT 2000000000
/**
 * \brief Type opaque du modèle pour la calculatrice.
 */
typedef struct ModelCalculator_t ModelCalculator;

/**
 * \fn ModelCalculator *create_ModelCalculator()
 * \brief Crée un modèle calculatrice
 *
 * \return ModelCalculator *, un pointeur vers un modèle de calculatrice.
 *         NULL en cas d'erreur
 */
ModelCalculator *create_ModelCalculator();
/**
 * \fn void *destroy_ModelCalculator(ModelCalculator *model)
 * \brief Lièbre la mémoire allouée pour un modèle déjà créé
 * \param model, un pointeur vers une structure ModelCalculator (!= NULL)
 */
void *destroy_ModelCalculator(ModelCalculator *model);

/**
 * \fn ModelCalculator *make_addition(ModelCalculator *model, int number1, int number2)
 * \brief Fais l'addition du nombre 1 et du nombre 2 et le stocke dans la structure model
 * \param model, un pointeur vers une structure ModelCalculator (!= NULL)
 * \param number1, le nombre 1 entier
 * \param number2, le nombre 2 entier
 *
 * \return ModelCalculator *, un pointeur vers un modèle de calculatrice.
 *         NULL en cas d'erreur (un des nombres et trop grand ou trop petit)
 */
ModelCalculator *make_addition(ModelCalculator *model, int number1, int number2);

/**
 * \fn int get_number1(ModelCalculator *model)
 * \brief Accesseur pour le champ number1 de la structure model
 *
 * \param model, un pointeur vers une structure ModelCalculator (!= NULL)
 * \return int, le nombre 1 
 * 
 */
int get_number1(ModelCalculator *model);

/**
 * \fn int get_number2(ModelCalculator *model)
 * \brief Accesseur pour le champ number2 de la structure model
 *
 * \param model, un pointeur vers une structure ModelCalculator (!= NULL)
 * \return int, le nombre 12
 */
int get_number2(ModelCalculator *model);
/**
 * \fn int get_result(ModelCalculator *model)
 * \brief Accesseur pour le champ result de la structure ModelCalculator
 *
 * \param model, un pointeur vers une structure ModelCalculator (!= NULL)
 * \return int, le résultat de l'addition
 * 
 */
int get_result(ModelCalculator *model);

#endif
