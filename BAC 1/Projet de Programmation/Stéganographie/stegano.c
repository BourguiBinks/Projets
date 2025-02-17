/**
 * @file stegano.c
 * @author Alexandre Bourguignon
 * @brief Ce fichier contient les définitions de types et
 * les fonctions liées à la technique de stéganographie sur des images PNM
 * @version 0.1
 * @date 2023-03-23
 * @projet: INFO0030 : Projet 2
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "stegano.h"
#include "pnm.h"

struct Message_t{
    char *text;
    unsigned int text_size;
};

//PROTOTYPES
static char **create_char_matrix(unsigned int columns, unsigned int lines);
static void destroy_char_matrix(char **matrix, unsigned int columns);
static unsigned int get_size(char *message);
static char *decimal_to_binary(int decimal);
static int binary_to_decimal(char *binary);
static char *string_to_binary(char *string);
static char *binary_to_string(char *binary);
static Message *construct_message();
static void destroy_message(Message *message);
static char *create_text(Message *message);
static char *get_text(char* filename);
static char *set_decimal_on_32bits(unsigned int decimal);
static char **split_in_n_parts(char *binary, unsigned int n);
static char *modify_pixel(char *binaryPixel, unsigned int bitNumber, char *bitsToHide);
static char *get_n_lsb_from_a_pixel(unsigned int bitNumber, char *pixel);
static PNM *hide_size_in_matrix(PNM *image, Message *message, unsigned int bitNumber);
static PNM *hide_text_in_matrix(PNM *image, unsigned int bitNumber, Message *message);
static unsigned int decode_size_in_matrix(PNM *image , unsigned int bitNumber);
static char *decode_text_in_matrix(unsigned int bitNumber, PNM *image, unsigned int size);
/********************************************************************************/
static char **create_char_matrix(unsigned int columns, unsigned int lines){
   char **matrix = malloc(sizeof(char *) * columns);
   if(matrix == NULL){
      return NULL;
   }

   for(unsigned int i = 0; i < columns; i++){
      matrix[i] = malloc(sizeof(char) * (lines + 1)); // On alloue une case de plus pour le caractère de fin de chaîne
      if(matrix[i] == NULL){
         for(unsigned int j = 0; j < i; j++){
            free(matrix[j]);
         }
         free(matrix);
         return NULL;
      }
      matrix[i][lines] = '\0'; // On initialise le caractère de fin de chaîne à '\0'
   }
   return matrix;
}

/********************************************************************************/
static void destroy_char_matrix(char **matrix, unsigned int columns){
   assert(matrix != NULL);

   for(unsigned int i = 0; i < columns; i++){
      if(matrix[i] != NULL)
         free(matrix[i]);
   }
   free(matrix);
   // printf("La matrice a bien été détruite\n");
}

unsigned int get_size(char *message){
    assert(message != NULL);
    unsigned int size = (strlen(message) * sizeof(char));

    return size;
}
/********************************************************************************/
static char *decimal_to_binary(int decimal){
    char *result = malloc(9 * sizeof(char));
    for(int i = 0; i < 8; i++){
        result[7-i] = (decimal & (1 << i)) ? '1' : '0';
    }
    result[8] = '\0';
    return result;
}
/********************************************************************************/
static int binary_to_decimal(char *binary){
    assert(binary != NULL);
    int result = 0;
    for (int i = 0; i < 8; i++) {
        if (binary[i] == '1') {
            result += 1 << (7 - i);
        }
    }
    return result;
}
/********************************************************************************/
static char *string_to_binary(char *string){
    assert(string != NULL);
    int lenght = get_size(string);
    if(lenght == 0){
        printf("Il n'y a pas de message\n");
        return NULL;
    }
    char *binaryString = malloc((lenght * 8 + 1) * sizeof(char));  // +1 pour le caractère nul
    if(binaryString == NULL){
        printf("Impossible d'allouer de la mémoire pour tranformer en binaire\n");
        return NULL;
    }
    int j = 0;
    for(int i = 0; i < lenght; i++) {
        char c = string[i];
        int decimal = (int) c;  // conversion du caractère en entier
        char *binary = decimal_to_binary(decimal);  // conversion de l'entier en binaire
        for(int k = 0; k < 8; k++) {
            binaryString[j++] = binary[k];  // concaténation des chaînes de caractères binaires
        }
        free(binary);
    }
    binaryString[j] = '\0';  // ajout du caractère nul pour terminer la chaîne de caractères
    return binaryString;
}
/********************************************************************************/
static char *binary_to_string(char* binary){
    assert(binary != NULL);
    int lenght = get_size(binary);
    if(lenght == 0){
        printf("Il n'y a pas de code binaire !\n");
        return NULL;
    }
    int val = 0;
    char* string = malloc((lenght/8)+1);
    if(string == NULL){
        printf("Impossible d'allouer de la mémoire pour transformer en chaine\n ");
        free(string);
        return NULL;
    }
    for(int i = 0, k = 0; i < lenght; i += 8, k++){
        val = 0;
        for(int j = 0; j < 8; j++) {
            if(binary[i+j] == '1'){
                val += 1 << (7-j);
            }
        }
        string[k] = val;
    }
    string[(lenght/8)] = '\0';
    return string;
}
/********************************************************************************/
static Message *construct_message(){
   Message *message = malloc(sizeof(Message)); // Allocation pour une structure PNM
   if(message == NULL){
      printf("Impossible d'allouer de la mémoire pour le message\n");
      return NULL;
   }
   return message;
}
/********************************************************************************/
static void destroy_message(Message *message){
    assert(message != NULL);
    if(message->text != NULL)
        free(message->text);
    free(message);
}
/********************************************************************************/
static char *create_text(Message *message){
    assert(message != NULL);

    message->text = malloc(sizeof(char *));
    if(message->text == NULL){
        printf("Impossible d'allouer le message dans le texte\n");
        return NULL;
    }
    return message->text;
}
/********************************************************************************/
static char *get_text(char* filename){
    FILE* fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Erreur: impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    // Calculer la taille du fichier.
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    rewind(fp);

    // Allouer suffisamment de mémoire pour contenir le message.
    char* message = malloc(sizeof(char) * (file_size + 1));
    if(message == NULL) {
        fprintf(stderr, "Erreur: impossible d'allouer suffisamment de mémoire.\n");
        return NULL;
    }

    // Lire le contenu du fichier dans la variable message.
    int read_size = fread(message, sizeof(char), file_size, fp);
    if (read_size != file_size) {
        fprintf(stderr, "Erreur de lecture du fichier %s.\n", filename);
        return NULL;
    }

    // Ajouter le caractère de fin de chaîne.
    message[file_size] = '\0';

    fclose(fp);
    return message;
}
/********************************************************************************/
static char *set_decimal_on_32bits(unsigned int n){
    char *binary = calloc(33, sizeof(char));
    if(binary == NULL) {
        return NULL; // gestion d'erreur si l'allocation échoue
    }
    for(int i = 31; i >= 0; i--){
        binary[i] = (n & 1) + '0'; // ajout du dernier bit de n à binary
        n >>= 1; // décalage de n vers la droite pour obtenir le bit suivant
    }
    binary[32] = '\0'; // ajout du caractère de fin de chaîne
    return binary;
}
/********************************************************************************/
static char **split_in_n_parts(char *binary, unsigned int n){
    assert(binary != NULL && (n == 1 || n == 2 || n == 4));

    unsigned int lenght = get_size(binary)/n;
    char **splitted = create_char_matrix(lenght,n);
    if(splitted == NULL){
        return NULL;
    }
    if(n == 1){
        for(unsigned int i = 0; i < lenght; i++){
        sscanf(binary + i, "%1c", &splitted[i][0]);
        if(splitted[i] == NULL){
            free(splitted);
            return NULL;
        }
     }
     return splitted; 
    }
    if(n == 2){
        for(unsigned int i = 0; i < lenght; i++){
        sscanf(binary + 2*i, "%2c", splitted[i]); 
        if(splitted[i] == NULL){
            destroy_char_matrix(splitted, lenght);
            return NULL;
        }
     }
     return splitted;
    }
    if(n == 4){
    for(unsigned int i = 0; i < lenght; i++){
        sscanf(binary + 4*i, "%4c", splitted[i]); 
        if(splitted[i] == NULL){
            destroy_char_matrix(splitted, lenght);
            return NULL;
        }
     }
     return splitted;
    }
    else{
        printf("Problème lors de la séparation en n parties");
        destroy_char_matrix(splitted, lenght);
        return NULL;
    }
}
/********************************************************************************/
static char *modify_pixel(char *binaryPixel, unsigned int bitNumber, char *bitsToHide){
    assert(binaryPixel != NULL && bitsToHide != NULL && (bitNumber == 1 || bitNumber == 2 || bitNumber == 4)
     && get_size(bitsToHide) == bitNumber); //bitNumber doit être égal au nb de bits dans bitsToHide
   
    
        if(bitNumber == 1){
            binaryPixel[7] = bitsToHide[0];
            return binaryPixel;
        }
        if(bitNumber == 2){
            binaryPixel[6] = bitsToHide[0];
            binaryPixel[7] = bitsToHide[1];
            return binaryPixel;
        }
        if(bitNumber == 4){
            binaryPixel[4] = bitsToHide[0];
            binaryPixel[5] = bitsToHide[1];
            binaryPixel[6] = bitsToHide[2];
            binaryPixel[7] = bitsToHide[3];
            return binaryPixel;
        }
        else{
            printf("Problème de changement dans un pixel\n");
            return NULL;
        }
}
/********************************************************************************/
static char *get_n_lsb_from_a_pixel(unsigned int bitNumber, char *pixel){
    assert(pixel != NULL && (bitNumber == 1 || bitNumber == 2 || bitNumber == 4));
    //Créer une fonction qui retourne les n bits de poids faible d'un pixel
    char *lsb = malloc(sizeof(char) * bitNumber + 1);
    if(lsb == NULL){
        return NULL;
    }
    if(bitNumber == 1){
        lsb[0] = pixel[7];
        lsb[1] = '\0';
        return lsb; 
    }
    if(bitNumber == 2){
        lsb[0] = pixel[6];
        lsb[1] = pixel[7];
        lsb[2] = '\0';
        return lsb; 
    }
    if(bitNumber == 4){
        lsb[0] = pixel[4];
        lsb[1] = pixel[5];
        lsb[2] = pixel[6];
        lsb[3] = pixel[7];
        lsb[4] = '\0';
        return lsb;
    }
    else 
        return NULL;
}
/********************************************************************************/
static PNM *hide_size_in_matrix(PNM *image, Message *message, unsigned int bitNumber){
    assert(image != NULL && message != NULL 
    && (bitNumber == 1 || bitNumber == 2 || bitNumber == 4));

    PNMFORMAT format = getter_magicNumber(image);
    if(format != PGM_ID){
        printf("Il est impossible de cacher un message dans autre chose que une image PGM\n");
        return NULL;
    }
    unsigned int **matrix = getter_matrix(image);
    if(matrix == NULL){
        printf("La matrice n'a pas pu être enregistrée\n");
        return NULL;
    }
    const unsigned int numberOfPixelsNeeded = 32/bitNumber;
    unsigned int pixels[numberOfPixelsNeeded];
    unsigned int columns = getter_columns(image);
    unsigned int lines = getter_lines(image);
    //S'assure que on puisse lire assez de pixels
    if(columns * lines < numberOfPixelsNeeded){
        printf("Il n'y pas assez de pixels dans l'image pour cacher le message\n");
        return NULL;
    }

    char *binaryPixels[numberOfPixelsNeeded];
    for(unsigned int i = 0; i < numberOfPixelsNeeded; i++){ // le tableau pixels contient les 8, 16 ou 32 premiers pixels (suivant bitNumber)
       pixels[i] = matrix[0][i];
       unsigned int pixel = pixels[i]; 
       binaryPixels[i] = decimal_to_binary(pixel); //Rempli le tableau par chaque représentation binaire d'un pixel
       //printf("Pixel numéro %d : %s\n", i + 1, binaryPixels[i]);
    }

    char *binarySize = set_decimal_on_32bits(message->text_size);//La taille T a cacher est allongé sur 32 bits
    //printf("La taille du texte en binaire est %s\n", binarySize);
    if(binarySize == NULL){
        destroy_char_matrix(binaryPixels,numberOfPixelsNeeded);
        return NULL;
    }

    unsigned int lenght = get_size(binarySize)/bitNumber;
    char **splittedBinarySize = split_in_n_parts(binarySize, bitNumber); // Contient la taille splité en n parties
    if(splittedBinarySize == NULL){
        destroy_char_matrix(binaryPixels,numberOfPixelsNeeded);
        free(binarySize);
        return NULL;
    }
    /*if(splittedBinarySize != NULL){   //Imprime les blocs de n bits correspondant à la taille
     *  for(unsigned int i = 0; i < lenght; i++){
     *       printf("Bloc numéro %d : %s (taille : %u)\n", i+1, splittedBinarySize[i],get_size(splittedBinarySize[i]));
     *   }
     *   destroy_char_matrix(splittedBinarySize, lenght);
    }*/
 
    char *bitsToHide = malloc(sizeof(char) * bitNumber);
    if(bitsToHide == NULL){
        printf("Impossible d'allouer de la mémoire pour bitsToHide\n");
        destroy_char_matrix(binaryPixels,numberOfPixelsNeeded);
        free(binarySize);
        destroy_char_matrix(splittedBinarySize, lenght);
        return NULL;
    }

    for(unsigned int i = 0; i < numberOfPixelsNeeded; i++){ //chaque pixel de binaryPixels est modifié pour y cacher la taille
        bitsToHide = splittedBinarySize[i];
         if(bitsToHide == NULL){
            //printf("NULL\n");
            destroy_char_matrix(binaryPixels,numberOfPixelsNeeded);
            free(binarySize);
            destroy_char_matrix(splittedBinarySize, lenght);
            free(bitsToHide);
            return NULL;
        }
        binaryPixels[i] = modify_pixel(binaryPixels[i], bitNumber, bitsToHide);
        pixels[i] = binary_to_decimal(binaryPixels[i]);
        matrix[0][i] = pixels[i]; //Chaque nouveau pixel est mit dans pixels puis changé dans la matrice
    }
    
    /*for(unsigned int i = 0; i < numberOfPixelsNeeded; i++){ //Test pour imprimer les pixels après changement
     *printf("Pixel numéro %d après : %s\n",i+1,binaryPixels[i]);
    }*/

    set_matrix(image, matrix); //Change la matrice dans l'image PNM

    //destroy_char_matrix(binaryPixels,numberOfPixelsNeeded);
    free(binarySize);
    free(bitsToHide);

    return image;
}
/********************************************************************************/
static PNM *hide_text_in_matrix(PNM *image, unsigned int bitNumber, Message *message){
    assert(image != NULL && message != NULL 
    && (bitNumber == 1 || bitNumber == 2 || bitNumber == 4));

    const unsigned int numberOfPixelNeeded = message->text_size * (8/bitNumber); //Le nombre de pixels à altérer pour le texte
    const unsigned int numberOfPixelAlreadyChanged = 32/bitNumber;//Le nombre de pixels avec la taille cachée
    unsigned int pixelsToModify[numberOfPixelNeeded];
    unsigned int columns = getter_columns(image);
    unsigned int lines = getter_lines(image);
    //S'assure que on puisse lire assez de pixels
    if(columns * lines < numberOfPixelNeeded){
        printf("Il n'y pas assez de pixels dans l'image pour cacher le texte\n");
        return NULL;
    }
    unsigned int **matrix = getter_matrix(image);//Contient la matrice avec la taille déjà cachée
    char *binaryPixels[numberOfPixelNeeded];

    for(unsigned int i = 0; i < numberOfPixelNeeded; i++){ 
        pixelsToModify[i] = matrix[0][i + numberOfPixelAlreadyChanged]; //pixelsTOModify contient les prochains pixels à modifier
        unsigned int pixel = pixelsToModify[i];
        binaryPixels[i] = decimal_to_binary(pixel); //binaryPixels contient les prochains pixels en binaire
        if(binaryPixels[i] == NULL){
            for(unsigned int j = 0; j < i; j++){
                free(binaryPixels[j]);
            }
            return NULL;
        }
        //printf("Pixel numero %u : %u\n", i + 1 + numberOfPixelAlreadyChanged, pixelsToModify[i]);
        //printf("Pixel numéro %u en binaire : %s\n", i + 1 + numberOfPixelAlreadyChanged, binaryPixels[i]);
    }
    char *text = message->text;
    if(text == NULL){
        printf("Il n'y a pas de message à cacher\n");
        destroy_char_matrix(binaryPixels, numberOfPixelNeeded);
        return NULL;
    }

    char *textInBinary = NULL;
    textInBinary = string_to_binary(text); // Contient le message en binaire 
    if(textInBinary == NULL){
        destroy_char_matrix(binaryPixels, numberOfPixelNeeded);
        return NULL;
    }
    //printf("Le message est %s et en binaire : %s (taille %u)\n", text, textInBinary, get_size(textInBinary));

    char **splittedBinaryText = split_in_n_parts(textInBinary, bitNumber); // Contient le text en binaire splité en bitNumber parties
    if(splittedBinaryText == NULL){
        destroy_char_matrix(binaryPixels, numberOfPixelNeeded);
        free(textInBinary);
        return NULL;
    }
    unsigned int lenght = get_size(textInBinary)/bitNumber;
     /*if(splittedBinaryText != NULL){   
     *  for(unsigned int i = 0; i < lenght; i++){                //Imprime les blocs de bitNumber bits correspondant à la taille
     *       printf("Bloc numéro %d : %s (taille : %u)\n", i+1, splittedBinaryText[i],get_size(splittedBinaryText[i]));
     *   }
    }*/

    char *bitsToHide = malloc(sizeof(char) * bitNumber);
    if(bitsToHide == NULL){
        destroy_char_matrix(binaryPixels, numberOfPixelNeeded);
        free(textInBinary);
        destroy_char_matrix(splittedBinaryText, lenght);
        return NULL;
    }

    for(unsigned int i = 0; i < numberOfPixelNeeded; i++){
        bitsToHide = splittedBinaryText[i];
        if(bitsToHide == NULL){
            destroy_char_matrix(binaryPixels, numberOfPixelNeeded);
            free(textInBinary);
            destroy_char_matrix(splittedBinaryText, lenght);
            free(bitsToHide);
            return NULL;
        }
        binaryPixels[i] = modify_pixel(binaryPixels[i], bitNumber, bitsToHide); //Chaque pixel est modifié
        pixelsToModify[i] = binary_to_decimal(binaryPixels[i]);//Chaque pixel est retransformé en decimal
        matrix[0][i+numberOfPixelAlreadyChanged] = pixelsToModify[i];// Puis réinséré dans la matrice
    }

    /*for(unsigned int i = 0; i < numberOfPixelNeeded; i++){ //Test pour imprimer les pixels après changement
     *  printf("Pixel numéro %d après : %s\n",i+1+numberOfPixelAlreadyChanged , binaryPixels[i]);
    }*/
    set_matrix(image, matrix);
    free(textInBinary);
    free(bitsToHide);
    //destroy_char_matrix(splittedBinaryText, lenght);
    for(unsigned int i = 0; i < numberOfPixelNeeded; i++){
        free(binaryPixels[i]);
    }
    return image;
}

/********************************************************************************/
int hide_message(unsigned int bitNumber, char *filename, char *messageFile, char *outputFilename){
    assert((bitNumber == 1 || bitNumber == 2 || bitNumber == 4)
    && filename != NULL && messageFile != NULL && outputFilename != NULL);
    Message *message = construct_message();
    if(message == NULL){
        printf("Impossible d'allouer de la mémoire pour la structure message\n");
        return -1;
    }

    message->text = create_text(message);
    if(message->text == NULL){
        printf("Impossible d'allouer de la mémoire pour le texte\n");
        return -1;
    }

    message->text = get_text(messageFile); //Enregistre le contenu du fichier (= le message)
    if(message->text == NULL){
        printf("Le texte n'a pas pu être recopié\n");
        destroy_message(message);
        return -1;
    }
    message->text_size = get_size(message->text);
    if(message->text_size == 0){
        printf("Il n'y a pas de message\n");
        destroy_message(message);
        return -1;
    }
    //printf("Le texte est %s et de taille %u\n", message->text, message->text_size);
    
    char *output_file = outputFilename;
    //printf("Le fichier en output est %s\n", output_file);
    PNM *image = NULL;
    switch(load_pnm(&image, filename)){ //Enregistre le fichier PNM dans image
        case 0 :
        printf("Chargement de l'image...\n");
        break;

        case -1 : 
        printf("Impossible d'allouer de la mémoire pour l'image\n");
        destroy_message(message);
        return 1;
        break;

        case -2 :
        printf("Le nom du fichier en imput est mal formé\n");
        destroy_message(message);
        return 2;
        break;

        case -3 : 
        printf("Le contenu du fichier en input est mal formé\n");
        destroy_message(message);
        return 3;
        break;

        default :
        printf("Erreur non identifiée\n");
        destroy_message(message);
        return 4;
        break;
    }
    if(hide_size_in_matrix(image, message, bitNumber) == NULL){
        destroy_message(message);
        destroy_pnm(image);
        return 2;
    }

    if(hide_text_in_matrix(image, bitNumber, message) == NULL){
        destroy_message(message);
        destroy_pnm(image);
        return 1;
    }
    switch(write_pnm(image, output_file)){
        case 0 :
        printf("L'image est bien sauvée\n");
        break;

        case -1 : 
        printf("Le nom du fichier en output n'est pas valide\n");
        return 5;
        break;

        case -2 : 
        printf("L'image n'a pas pu être sauvée\n");
        return 6;
        break;

        default :
        printf("Erreur non identifiée\n");
        return 7;
        break;
    }
    destroy_message(message);
    destroy_pnm(image);
    return 0;
}
/********************************************************************/
static unsigned int decode_size_in_matrix(PNM *image , unsigned int bitNumber){
    assert((bitNumber == 1 || bitNumber == 2 || bitNumber == 4) && image != NULL);
    unsigned int **matrix = getter_matrix(image);
    const unsigned int numberOfSizePixels = 32/bitNumber;
    unsigned int pixels[numberOfSizePixels];
    unsigned int columns = getter_columns(image);
    unsigned int lines = getter_lines(image);
    //S'assure que on puisse lire assez de pixels
    if(columns * lines < numberOfSizePixels){
        //printf("Il n'y pas assez de pixels dans l'image pour décoder la taille\n");
        return 2;
    }
    char *binaryPixels[numberOfSizePixels];
    for(unsigned int i = 0; i < numberOfSizePixels; i++){
        pixels[i] = matrix[0][i];
        unsigned int pixel = pixels[i];
        binaryPixels[i] = decimal_to_binary(pixel);
        if(binaryPixels[i] == NULL){
            for(unsigned int j = 0; j < i; j++){
                free(binaryPixels[j]);
                return 3;
            }
        }
        //printf("Pixel numéro %d : %s\n", i + 1, binaryPixels[i]);
    }
    char *binarySize[numberOfSizePixels]; //binarySize va contenir les 32 bits correspondant à la taille
    //Faire une boucle qui va mettre dans binarySize chaque bit de poids faible de chaque pixel contenu dans binaryPixel
    for(unsigned int i = 0; i < numberOfSizePixels; i++){
        binarySize[i] =  get_n_lsb_from_a_pixel(bitNumber, binaryPixels[i]);
        if(binarySize[i] == NULL){
            for(unsigned int j = 0; j < i; j++){
                free(binarySize[j]);
            }
            return 3;
        }
        //printf("Bloc numéro %d : %s (taille %u)\n", i + 1,binarySize[i], get_size(binarySize[i]));
    }
    char concatenatedSize[33] = "";
    for(unsigned int i = 0; i < numberOfSizePixels; i++) {
    //Copie chaque caractère de la chaîne de bits actuelle dans le tableau de sortie
       for(unsigned int j = 0; j < get_size(binarySize[i]); j++) {
        concatenatedSize[i*get_size(binarySize[i]) + j] = binarySize[i][j];
       }
    }
    concatenatedSize[32] = '\0'; //Termine la chaine avec '\0'
    //printf("La chaine concaténée est %s (taille %u)\n", concatenatedSize, get_size(concatenatedSize));
   
    //Free
    for(unsigned int i = 0; i < numberOfSizePixels; i++){
        free(binarySize[i]);
    }

    for(unsigned int i = 0; i < numberOfSizePixels; i++){
        free(binaryPixels[i]);
    
    }
    //Fin free
    unsigned int size = 0;
    for(unsigned int i = 0; i < 4; i++){
       char subString[9];  // 8 bits + '\0'
       strncpy(subString, concatenatedSize + (i * 8), 8);
       subString[8] = '\0';
       size = (size<< 8) | binary_to_decimal(subString);
    }
    //printf("Taille : %u\n", size);
    if(size == 0){
        return 1;
    }
    //printf("La taille en décimal est %u\n", size);


    return size;
}
/********************************************************************/

static char *decode_text_in_matrix(unsigned int bitNumber, PNM *image, unsigned int size){
    assert((bitNumber == 1 || bitNumber == 2 || bitNumber == 4) && image != NULL && size > 0);
    
    const unsigned int numberOfPixelsNeeded = (size * 8)/bitNumber;
    const unsigned int numberOfSizePixels = 32/bitNumber;
    unsigned int pixelsToDecode[numberOfPixelsNeeded];
    unsigned int **matrix = getter_matrix(image);
    unsigned int columns = getter_columns(image);
    unsigned int lines = getter_lines(image);
    //printf("Colonnes %u , lignes %u, lignes * colonnes = %u < nbrOfPixelsNeeded + numberOfSizePixels = %u\n", columns, lines, columns * lines, numberOfPixelsNeeded +numberOfSizePixels);
    //S'assure que on puisse lire assez de pixels
    if(columns * lines < numberOfPixelsNeeded + numberOfSizePixels){
        printf("Il n'y pas assez de pixels dans l'image pour décoder le message\n");
        return NULL;
    }
    char *binaryPixels[numberOfPixelsNeeded];

    for(unsigned int i = 0; i < numberOfPixelsNeeded; i++){
        pixelsToDecode[i] = matrix[0][i + numberOfSizePixels];
        unsigned int pixel = pixelsToDecode[i];
        char *binaryPixel = decimal_to_binary(pixel);
        if(binaryPixel == NULL){
           return NULL; 
        }
        binaryPixels[i] = get_n_lsb_from_a_pixel(bitNumber, binaryPixel);
        if(binaryPixels[i] == NULL){
            for(unsigned int j = 0; j < i; j++){
                free(binaryPixels[j]);
                free(binaryPixel);
            }  
            return NULL;
        }
        free(binaryPixel);
        //printf("Pixel numero %u : %u\n", i + 1 + numberOfSizePixels, pixelsToDecode[i]);
        //printf("LSB du pixel numéro %u : %s\n", i + 1 + numberOfSizePixels, binaryPixels[i]);
    }
    
    char *binaryMessage = malloc(sizeof(char)*(bitNumber) * numberOfPixelsNeeded + 1);
    binaryMessage[0] = '\0';
    for(unsigned int i = 0; i < numberOfPixelsNeeded; i++){
       for(unsigned int j = 0; j < bitNumber; j++){
          strncat(binaryMessage, &binaryPixels[i][j], 1);
        }
    }  
    binaryMessage[bitNumber * numberOfPixelsNeeded] = '\0';
    //printf("La message binaire au complet est %s (taille %u)\n", binaryMessage, get_size(binaryMessage));
    char *message = binary_to_string(binaryMessage);
    //printf("Le message est donc %s\n", message);
    for(unsigned int i = 0; i < numberOfPixelsNeeded; i++){
        free(binaryPixels[i]);
    }
    free(binaryMessage);
    return message;

}
/********************************************************************/
int decode_message(unsigned int bitNumber, char *filename, char *outputFilename){
    assert((bitNumber == 1 || bitNumber == 2 || bitNumber == 4)
    && filename != NULL && outputFilename != NULL);

    PNM *image = NULL;
    switch(load_pnm(&image, filename)){ //Enregistre le fichier PNM dans image
        case 0 :
        printf("Chargement de l'image...\n");
        break;

        case -1 : 
        printf("Impossible d'allouer de la mémoire pour l'image\n");
        return 1;
        break;

        case -2 :
        printf("Le nom du fichier en imput est mal formé\n");
        return 2;
        break;

        case -3 : 
        printf("Le contenu du fichier en input est mal formé\n");
        return 3;
        break;

        default :
        printf("Erreur non identifiée\n");
        return 4;
        break;
    }
    unsigned int size = decode_size_in_matrix(image, bitNumber);
    switch(size){
        case 1:
        printf("La taille du message est nulle\n");
        destroy_pnm(image);
        return 1;
        break;

        case 2 : 
        printf("Il n'y a pas assez de pixels pour décoder le message !\n");
        destroy_pnm(image);
        return 2;

        case 3:
        //printf("Problème d'allocation mémoire\n");
        destroy_pnm(image);
        return 3;
        break;

        default:
        printf("La taille a bien été lue\n");
        break;
    }
    char *message = decode_text_in_matrix(bitNumber, image, size);
    if(message == NULL){
        return 2;
    }
    else{
        FILE *fp = fopen(outputFilename,"w");
        if(fp == NULL){
            //printf("Impossible d'ouvrir le fichier en output\n");
            return 4;
        }
        fputs(message,fp);
        fclose(fp);
    }
    free(message);
    destroy_pnm(image);
    return 0;
}