/**
 * \file utils.h
 * \author Alexandre Bourguignon
 * \brief Ce fichier contient les fonctions utiles pour la calculatrice GTK
 * \version 0.1
 * \date 2023-04-12
 * @projet: INFO0030 : Projet 3
 * 
 */

#ifndef __UTILS_CALCULATRICE__
#define __UTILS_CALCULATRICE__
/**
 * \brief Nombre minimum que peut prendre un nombre (arbitraire)
 */
#define MINIMUM_NUMBER -1000000000
/**
 * \brief Nombre maximum que peut prendre un nombre (arbitraire)
 */
#define MAXIMUM_NUMBER 1000000000

/**
 * \fn int is_valid_number(const char* str)
 * \brief Vérifie si une chaine de caractère transformée en nombre est valide
 *
 * \param str, une chaine de caractère
 * \return 1 si l'entrée est vide
 *         2 si l'entrée n'est pas un nombre 
 *         0 si l'entrée est valide
 */
int is_valid_number(const char* str);


#endif