/**
 * pnm.h
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 * 
 * @author: Bourguignon Alexandre s211885
 * @date: 06/03/23
 * @projet: INFO0030 Projet 1
 */

#ifndef __PNM__
#define __PNM__
#define MAGIC_NUMBER_PBM "P1"
#define MAGIC_NUMBER_PGM "P2"
#define MAGIC_NUMBER_PPM "P3"
#define ARRAY_SIZE 255
#define PBM_ID 1
#define PGM_ID 2
#define PPM_ID 3
#define BUFFER 1000


/**
 * 
 * @brief Définition du type opaque PNM
 *  -magicNumber contient le nombre magique (1 , 2 ou 3)
 *  -maxValue n'est utile que dans les fichiers PGM et PPM et vaut 0 par défaut dans le cas PBM
 *  -columns, lignes et matrix correspondent aux colonnes et lignes de la matrice représentant le dessin dans un fichier
 */
typedef struct PNM_t PNM;

/** 
 *
 *  Définition de l'énumération nombreMagique
 */

typedef enum{PBM_FORMAT = 1, PGM_FORMAT = 2, PPM_FORMAT = 3}PNMFORMAT;

/** 
 * @brief Crée une matrice
 * @pre columns>=0 et lines>=0
 * @post La fonction retourne une matrice avec de la mémoire allouée
 * @param columns 
 * @param lines 
 *  
 */
//static unsigned int **create_matrix(unsigned int columns, unsigned int lines);
/**
 * @brief Détruit une matrice
 * @pre matrix != NULL
 * @post La mémoire de la matrice "matrix" prise en paramètre est libérée
 * @param matrix 
 * @param columns 
 */
void destroy_matrix(unsigned int **matrix, unsigned int columns);

/**
 * @brief Constructeur d'une structure PNM
 * @pre /
 * @post Crée un pointeur sur une structure PNM valide
 */

PNM *construct_pnm();

/**
 * @brief Détruit une structure PNM
 * @pre image != NULL
 * @post La mémoire de la structure PNM prise en entrée est libérée
 * @param image 
 */


void destroy_pnm(PNM *image);

/** 
 * @brief Permet de transformer un nombre magique en identifiant
 * @pre magicNumber != NULL
 * @post le nombre magique est associé à son identifiant correspondant
 * @param magicNumber 
 */
//static int transform_into_format(char *magicNumber);
/**
 * @brief Permet de vérifier l'extension d'un fichier
 * @pre filename != NULL
 * @post La fonction retourne 1 2 ou 3 suivant l'extension .pbm, .pgm ou .ppm 
 * (retourne également -2 si le fichier n'a pas d'extension et -1
 * si l'extension n'est pas valide)
 * @param filename 
 * 
 */
int verify_extension(char *filename);
/** 
 * @brief Permet de vérifier le type d'image PNM d'un fichier
 * @pre fp != NULL
 * @post Le type de fichier est vérifié
 * @return
 *       * 1 si le fichier est de type PBM
 *       * 2 si le fichier est de type PGM
 *       * 3 si le fichier est de type PPM
 *       *-1 si le fichier n'est pas de type PNM
 */
//static int verify_pnm_type(FILE *fp);

/**
 * @brief Ignore une ligne de commentaire si il y en a
 * @pre fp != NULL
 * @post Les commentaires sont ignorés si il y en a
 * @param fp 
 */
//static void skip_comments(FILE *fp);

/**
 * @brief Permet d'avoir le nombre de colonnes d'un fichier
 * @pre fp != NULL
 * @post La fonction retourne le nombre de colonnes
 * @param fp 
 */
//static unsigned int get_columns(FILE *fp);

/**
 * @brief Permet d'avoir le nombre de lignes d'un fichier
 * @pre fp != NULL
 * @post La fonction retourne le nombre de lignes
 * @param fp 
 */
//static unsigned int get_lines(FILE *fp);

/**
 * @brief Permet d'avoir la valeur maximale d'un pixel d'un fichier
 * @pre fp != NULL et magicNumber != NULL
 * @post La fonction retourne la valeur maximal d'un pixel
 * @param fp 
 * @param magicNumber
 */
//static unsigned int get_maxValue(FILE *fp, PNMFORMAT magicNumber);
/**
 * @brief Permet de lire une matrice et l'affecter dans la structure image
 * @pre fp != NULL et image != NULL
 * @post La matrice lue est affectée dans la structure image
 * @param fp 
 * @param image 
 */
//static int read_matrix(FILE *fp, PNM *image);
//********************** DEBUT GETTERS ****************************
/**
 * @brief Get the magicNumber object
 * 
 * @param image 
 * @return PNMFORMAT 
 */
PNMFORMAT getter_magicNumber(PNM *image);

/**
 * @brief Get the columns object
 * 
 * @param image 
 * @return unsigned int 
 */
unsigned int getter_columns(PNM *image);

/**
 * @brief Get the line object
 * 
 * @param image 
 * @return unsigned int 
 */
unsigned int getter_lines(PNM *image);

/**
 * @brief Get the maxValue object
 * 
 * @param image 
 * @return unsigned int 
 */
unsigned int getter_maxValue(PNM *image);

/**
 * @brief Get the ter matrix object
 * 
 * @param image 
 * @return unsigned int** 
 */
unsigned int **getter_matrix(PNM *image);
/**
 * @brief 
 * 
 * @param image 
 * @return PNM* 
 */
//PNM *get_PNM(PNM *image);
// ******************************* FIN GETTERS **********************************


//*********************************DEBUT SETTERS*********************************
/**
 * @brief Set the magicNumber object
 * 
 * @param image 
 * @param magicNumber 
 * @return PNM* 
 */
PNM *set_magicNumber(PNM *image, PNMFORMAT magicNumber);

/**
 * @brief Set the columns object
 * 
 * @param image 
 * @param columns 
 * @return PNM* 
 */
PNM *set_columns(PNM *image, unsigned int columns);

/**
 * @brief Set the lines object
 * 
 * @param image 
 * @param lines 
 * @return PNM* 
 */
PNM *set_lines(PNM *image, unsigned int lines);

/**
 * @brief Set the maxValue object
 * 
 * @param image 
 * @param maxValue 
 * @return PNM* 
 */

/**
 * @brief Set the maxValue object
 * 
 * @param image 
 * @param maxValue 
 * @return PNM* 
 */
PNM *set_maxValue(PNM *image, unsigned int maxValue);

/**
 * @brief Set the matrix object
 * 
 * @param image 
 * @param matrix 
 * @return PNM* 
 */
PNM *set_matrix(PNM *image, unsigned int **matrix);
//********************************FIN SETTERS************************************
/**
 * load_pnm
 *
 * Charge une image PNM depuis un fichier.
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param filename le chemin vers le fichier contenant l'image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image pointe vers l'image chargée depuis le fichier.
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char *filename);

/**
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *.
 * @return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */
//
int write_pnm(PNM *image, char* filename);

#endif //__PNM__

