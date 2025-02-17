/**
 * @file stegano.h
 * @author Alexandre Bourguignon
 * @brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation de la technique de stéganographie sur des images PNM.
 * @version 0.1
 * @date 2023-03-23
 * @projet: INFO0030 : Projet 2
 * 
 * 
 */
#ifndef __STEGANO__
#define __STEGANO__
#include "pnm.h"

/**
 * @brief Type opaque de la structure message
 * 
 */
typedef struct Message_t Message;
/**
 * @brief Crée une matrice de caractère 
 * @pre /
 * @post Crée une matrice de caractère
 * @param columns 
 * @param lines 
 * @return une matrice de caractère valide
 */
//static char **create_char_matrix(unsigned int columns, unsigned int lines);
/**
 * @brief Libère la mémoire d'une matrice de caractère
 * @pre matrix != NULL 
 * @post La mémoire allouée à la matrice est libérée
 * @param matrix 
 * @param columns 
 */
//static void destroy_char_matrix(char **matrix, unsigned int columns);
/**
 * @brief Permet de transformer un message (chiffre, nombre, chaine de caractère) en sa taille (en octets)
 * 
 * @param message 
 * @return La taille en octet(s) du message
 */
//static unsigned int get_size(char *message);

/**
 * @brief Permet de transformer un nombre décimal en binaire
 * @pre /
 * @post La fonction retourne le chiffre décimal decimal en binaire
 * @param decimal un nombre décimal
 * @return char* 
 */
//static char *decimal_to_binary(int decimal);

/**
 * @brief Permet de transformer un chiffre bianire en décimal (uniquement en octets)
 * @pre binary != NULL
 * @post La fonction retourne le nombre décimal correspondant au nombre binaire binary
 * @param binary 
 * @return int 
 */
//static int binary_to_decimal(char *binary);

/**
 * @brief  Transforme une chaine de caractère en binaire
 * @pre string != NULL
 * @post La fonction retourne le nombre binaire correspondant à string
 * @param string
 * @return char* 
 */
//static char *string_to_binary(char *string);

/**
 * @brief Permet de transformer un nombre binaire en chaine de caractère
 * @pre binary != NULL
 * @post La fonction retourne la chaine de caractère correspondant à binary
 * @param binary 
 * @return char* 
 */
//static char *binary_to_string(char *binary);
/**
 * @brief Constructeur de la structure message
 * @pre !=
 * @post La mémoire pour la structure message est allouée
 * @return Message * 
 */
//static Message *construct_message();

/**
 * @brief Destructeur de la structure message
 * @pre message != NULL
 * @post La mémoire de message est libérée
 * @param message 
 */
//static void destroy_message(Message *message);

/**
 * @brief Alloue de la mémoire pour le champ text
 * @pre message != NULL
 * @post La mémoire est allouée pour le champ text
 * @param message 
 * @return char* 
 */
//static char *create_text(Message *message);

/**
 * @brief Permet de lire une chaine de caractère dans un fichier
 * @pre filename != NULL
 * @post la fonction renvoie la chaine de caractère lue
 * @param filename 
 * @return char* 
 */
//static char *get_text(char* filename);
/**
 * @brief Allonge un nombre donné sur 32 bits
 * @pre n, le nombre decimal à transformer en 32 bits
 * @post la fonction retourne n sur 32 bits
 * @param decimal 
 * @return char* 
 */
//static char *set_decimal_on_32bits(unsigned int decimal);
/**
 * @brief découpe en n blocs une nombre de x bits
 * @pre binary != NULL et n == (1,2 ou 4)
 * @param binary 
 * @param n le nombre de bits à considérer (1,2 ou 4)
 * @return char* 
 */
//static char **split_in_n_parts(char *binary, unsigned int n);
/**
 * @brief modifie un pixel pour y insérer les n bits à cacher
 * @pre binaryPixel != NULL et bitnumber == (1,2 ou 4) et bitstoHide != NULL
 * @param binaryPixel 
 * @param bitNumber le nombre de bits à considérer (1,2 ou 4)
 * @param bitsToHide 
 * @return char* 
 */
//static char *modify_pixel(char *binaryPixel, unsigned int bitNumber, char *bitsToHide);
/**
 * @brief Récupère les n bits de poids faible d'un nombre binaire
 * @pre bitNumber == (1,2 ou 4) et pixel != NULL
 * @param bitNumber 
 * @param pixel 
 * @return char* 
 */
// static char *get_n_lsb_from_a_pixel(unsigned int bitNumber, char *pixel);
/**
 * @brief Cache la taille du message dans les 8, 16 ou 32 premiers pixels de la matrice
 * @pre image != NULL, message != NULL, bitNumber == (1,2 ou 4)
 * @post La taille du message est cachée dans les 8, 16 uo 32 premiers pixels
 * @param image 
 * @param message
 * @param bitNumber le nombre de bits à considérer (1,2 ou 4)
 * @return L'image PNM avec la taille cachée 
 */
//static PNM *hide_size_in_matrix(PNM *image, Message *message, unsigned int bitNumber);
/**
 * @brief Cache le contenu du message dans la matrice après la taille
 * @pre image != NULL, message != NULL, bitNumber == (1,2 ou 4)
 * @param image 
 * @param bitNumber le nombre de bits à considérer (1,2 ou 4)
 * @param message 
 * @return L'image PNM avec le message caché
 */
//static PNM *hide_text_in_matrix(PNM *image, unsigned int bitNumber, Message *message);

/**
 * @brief Permet de cacher un message dans une image PNM
 * @pre bitnumber == (1, 2 ou 4), filename != NULL, messageFile != NULL, outputFilename != NULL
 * @post Le message est caché dans l'image PNM
 * @param bitNumber le nombre de bits à considérer (1,2 ou 4)
 * @param filename le fichier dans lequel cacher le message
 * @param messageFile le fichier contenant le message à cacher
 * @param outputFilename le fichier contenant le message caché
 * @return * 1 si il est impossible d'allouer de la mémoire pour l'image
 *         * 2 si le nom du fichier en input est mal formé
 *         * 3 si le contenu du fichier en input est mal formé
 *         * 4 ou 7 si il y a un erreur non identifiée
 *         * 5 si le nom du fichier en ouput n'est pas valide
 *         * 6 si l'image n'a pas pu etre sauvée
 */
int hide_message(unsigned int bitNumber, char *filename, char *messageFile, char *outputFilename);
/**
 * @brief Permet de décoder la taille d'un message 
 * @pre image != NULL et bitNumber == (1,2 ou 4)
 * @post La fonction renvoie la taille du message caché
 * @param image 
 * @param bitNumber 
 * @return PNM* 
 */
//static unsigned int decode_size_in_matrix(PNM *image , unsigned int bitNumber);
/**
 * @brief Permet de décoder le contenu du message
 * @pre bitNumber == (1,2 ou 4) et image != NULL et size > 0
 * @post La fonction retourne le texte lu
 * @param bitNumber 
 * @param image 
 * @param textSize 
 * @return char* 
 */
//static char *decode_text_in_matrix(unsigned int bitNumber, PNM *image, unsigned int size);
/**
 * @brief Permet de décoder le message caché dans une image PNM 
 * @pre bitNumber != NULL et filename != NULL et outputFilename != NULL
 * @post Le message est décodé et affiché dans un fichier texte
 * @param bitNumber 
 * @param filename 
 * @param outputFilename 
 * @return int 
 */
int decode_message(unsigned int bitNumber, char *filename, char *outputFilename);

#endif