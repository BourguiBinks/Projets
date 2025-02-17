#ifndef __PRODUIT__
#define __PRODUIT__

#include "matricecreuse.h"

/**
 * @brief Compare deux éléments pour les besoins du tri des ensembles.
 *
 * @param a Le premier élément à comparer.
 * @param b Le deuxième élément à comparer.
 * @return Un entier négatif si a < b, 0 si a égale b, un entier positif si a > b.
 */
int compareElementsSets(const void *a, const void *b);

/**
 * @brief Crée un ensemble vide.
 *
 * @return Un ensemble vide initialisé.
 */
Set createEmptySet(void);

/**
 * @brief Ajoute un élément à l'ensemble spécifié.
 *
 * @param set L'ensemble auquel ajouter l'élément.
 * @param element L'élément à ajouter à l'ensemble.
 */
void addToSet(Set *set, int element);

/**
 * @brief Affiche les éléments de l'ensemble.
 *
 * Cette fonction affiche les éléments de l'ensemble spécifié sur la sortie standard.
 *
 * @param set L'ensemble dont les éléments doivent être affichés.
 */
void printSet(Set set);

/**
 * @brief Trie les éléments d'un ensemble en utilisant la fonction de comparaison compareElementsSets.
 *
 * @param set L'ensemble à trier.
 */
void sortSet(Set *set);

/**
 * @brief Vérifie et trie les éléments de deux fichiers de matrices creuses.
 *
 * Cette fonction ouvre deux fichiers contenant des matrices creuses, vérifie si les colonnes
 * sont triées dans l'ordre croissant, puis trie et sauvegarde les données dans de nouveaux fichiers
 * si nécessaire. Elle renvoie des codes d'erreur spécifiques selon les cas.
 *
 * @param fileName Le nom du premier fichier contenant la première matrice creuse.
 * @param fileName2 Le nom du deuxième fichier contenant la deuxième matrice creuse.
 * @return Un entier indiquant le résultat de la vérification et du tri :
 *         -2 : Les deux fichiers sont triés.
 *         -3 : Seul le premier fichier est modifié.
 *         -4 : Seul le deuxième fichier est modifié.
 *         -5 : Les deux fichiers sont modifiés.
 *         -1 : Erreur lors de l'ouverture d'un fichier.
 *         0  : Aucune modification nécessaire.
 */
int CheckAndSort(const char *fileName, const char *fileName2);

/**
 * @brief Multiplie deux matrices creuses et renvoie le résultat.
 *
 * Cette fonction prend deux matrices creuses en entrée, les multiplie, et renvoie le résultat
 * sous la forme d'une nouvelle matrice creuse. Elle utilise un ensemble pour gérer les indices
 * des éléments non nuls résultants et les trie avant de les stocker dans la matrice résultante.
 *
 * @param matrix1 La première matrice creuse.
 * @param matrix2 La deuxième matrice creuse.
 * @return Un pointeur vers la matrice creuse résultante, ou NULL en cas d'erreur.
 */
sparseMatrix *multiplication_sparse_matrix(sparseMatrix *matrix1, sparseMatrix *matrix2);


#endif
