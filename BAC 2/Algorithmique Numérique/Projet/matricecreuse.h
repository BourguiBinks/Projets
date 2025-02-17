#ifndef __MATRICECREUSE__
#define __MATRICECREUSE__

typedef struct SparseMatrix_t sparseMatrix;

typedef struct SparseVector_t sparseVector;

typedef struct ElementMatrix_t elementMatrix;

typedef struct SparseVector_t{
    int *startColumn; // variable qui pointe vers l'adresse mémoire d'un tableau d'entiers contenant les indices de début de chaque colonne.
    int *indexRow; // variable qui pointe vers l'adresse mémoire d'un tableau d'entiers contenant les indices de chaque élément non nul.
    double *values; // variable qui pointe vers l'adresse mémoire d'un tableau d'entiers contenant les valeurs de chaque élément non nul.
}sparseVector;

// créer une structure de données en mémoire qui peut stocker efficacement les informations de la matrice creuse.
typedef struct SparseMatrix_t{
    int row;
    int column;
    int size; // // variable correspondant aux nombre d'éléments non nuls.
    sparseVector *vector;
}sparseMatrix;

typedef struct ElementMatrix_t{
    int row;
    int column;
    double value;
}elementMatrix;

// Structure de tableau dynamique pour représenter un ensemble
typedef struct {
    int *elements;
    int size;
}Set;

/**
 * @brief Compare deux éléments pour les besoins du tri.
 *
 * @param a Le premier élément à comparer.
 * @param b Le deuxième élément à comparer.
 * @return Un entier négatif si a < b, 0 si a égale b, un entier positif si a > b.
 */
int compareElements(const void *a, const void *b);

/**
 * @brief Crée une matrice creuse avec la taille spécifiée, le nombre de lignes et de colonnes.
 *
 * @param size La taille de la matrice creuse.
 * @param row Le nombre de lignes de la matrice creuse.
 * @param column Le nombre de colonnes de la matrice creuse.
 * @return Un pointeur vers la matrice creuse nouvellement créée.
 */
sparseMatrix *create_sparse_matrix(int size, int row, int column);

/**
 * @brief Libère la mémoire allouée pour une matrice creuse.
 *
 * @param matrix La matrice creuse à libérer.
 */
void free_sparse_matrix(sparseMatrix *matrix);

/**
 * @brief Sauvegarde une matrice creuse dans un fichier au format .mtx.
 *
 * @param matrix La matrice creuse à sauvegarder.
 * @return Un entier indiquant le succès (0 en cas de succès, -2 en cas d'erreur d'ouverture de fichier).
 */
int filemtx_result(sparseMatrix *matrix, int choice);

/**
 * @brief Charge une matrice creuse et un vecteur à partir d'un fichier spécifié.
 *
 * @param matrix Un pointeur vers une matrice creuse où stocker les données.
 * @param filename Le nom du fichier à partir duquel charger les données.
 * @return Un entier indiquant le succès (0 en cas de succès, -1 en cas d'erreur).
 */
int load_sparse_matrix_and_vector(sparseMatrix **matrix, char *filename);


#endif 