#ifndef __VALEURPROPRE__
#define __VALEURPROPRE__
#include <math.h>
#include "matricecreuse.h"
#include "produit.h"


/**
 * @brief Vérifie et trie les éléments d'un fichier de matrice creuse.
 *
 * Cette fonction ouvre un fichier contenant une matrice creuse, vérifie si les colonnes
 * sont triées dans l'ordre croissant, puis trie et sauvegarde les données dans un nouveau fichier
 * si nécessaire. Elle renvoie des codes d'erreur spécifiques selon les cas.
 *
 * @param fileName Le nom du fichier contenant la matrice creuse.
 * @return Un entier indiquant le résultat de la vérification et du tri :
 *         -2 : Le fichier est trié.
 *         -3 : Le fichier a été modifié.
 *         -1 : Erreur lors de l'ouverture du fichier.
 *         0  : Aucune modification nécessaire.
 */
int CheckAndSort2(const char *fileName);

/**
 * @brief Applique la méthode de puissance pour calculer la valeur propre dominante et le vecteur propre associé d'une matrice creuse.
 *
 * La méthode de puissance itère la multiplication de la matrice creuse par un vecteur propre initial
 * pour converger vers la valeur propre dominante et le vecteur propre associé. La fonction renvoie le
 * vecteur propre normalisé correspondant à la valeur propre dominante et met à jour le résultat de la
 * valeur propre dans la variable pointée par eigenResult.
 *
 * @param matrix La matrice creuse sur laquelle appliquer la méthode de puissance.
 * @param maxIterations Le nombre maximal d'itérations à effectuer.
 * @param eigenResult Un pointeur vers une variable pour stocker la valeur propre dominante.
 * @return Un pointeur vers la matrice creuse représentant le vecteur propre associé, ou NULL en cas d'erreur.
 */
sparseMatrix *powerMethod(sparseMatrix *matrix, int maxIterations, double *eigenResult);


#endif
