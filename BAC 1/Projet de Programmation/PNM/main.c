/**
 * main.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Bourguignon Alexandre s211885
 * @date: 06/03/23
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>

#include "pnm.h"


int main(int argc, char *argv[]) {

    char *optstring = "hf:i:o:";
    char opt;
    char *format = NULL;
    char *input_file = NULL;
    char *output_file = NULL;

    if (argc == 1) {
        printf("Correct usage: %s -f <format> -i <input> -o <output>\n", argv[0]);
        return 0;
    }

    while((opt = getopt(argc, argv, optstring)) != -1){ //On parcourt les arguments donnés dans le terminal
        switch(opt){
        case 'f':
            format = optarg;
            break;
        case 'i':
            input_file = optarg;
            break;
        case 'o':
            output_file = optarg;
            break;
        default:
            printf("Correct usage: %s -f <format> -i <image_input> -o <image_output>\n", argv[0]);
            return 0;
        }
    }

    if(format == NULL || input_file == NULL || output_file == NULL){
        printf("Correct usage: %s -f <format> -i <image_input> -o <image_output>\n", argv[0]);
        return 0;
    }
   
    //On vérifie si le format correspond bien à un type PNM
    if(strcmp(format, "PBM") != 0 
      && strcmp(format, "PGM") != 0 
      && strcmp(format, "PPM") != 0){
        printf("Format non pris en charge : %s\n", format);
        return 0;
}
    //On vérifie si le format correspond à l'extension de l'input et de l'ouput
    int verificationPbm = strcmp(format, "PBM");
    int verificationPgm = strcmp(format, "PGM");
    int verificationPpm = strcmp(format, "PPM");
   
    if(verificationPbm == 0){
     if(verify_extension(input_file) != 1 || verify_extension(output_file) != 1){
      printf("L'input ou l'output doit être de type pbm\n");
      return 0;
     }
    }

    if(verificationPgm == 0){
     if(verify_extension(input_file) != 2 || verify_extension(output_file) != 2){
      printf("L'input ou l'output doit être de type pgm\n");
        return 0;
     }
    }
    
    if(verificationPpm == 0){
     if(verify_extension(input_file) != 3 || verify_extension(output_file) != 3){
      printf("L'input ou l'output doit être de type ppm\n");
      return 0;
     }
    }
    
    //Tout à l'air correct, on peut tenter de copier le fichier
    PNM *image = NULL;
    switch(load_pnm(&image, input_file)){
        case 0 :
        printf("Tout s'est bien passé\n");
        break;

        case -1 : 
        printf("Impossible d'allouer de la mémoire pour l'image\n");
        return 0;
        break;

        case -2 :
        printf("Le nom du fichier en imput est mal formé\n");
        return 0;
        break;

        case -3 : 
        printf("Le contenu du fichier en input est mal formé\n");
        return 0;
        break;

        default :
        printf("Erreur non identifiée\n");
        return 0;
        break;
    }

     switch(write_pnm(image, output_file)){
        case 0 :
        printf("L'image est bien sauvée\n");
        break;

        case -1 : 
        printf("Le nom du fichier en output n'est pas valide\n");
        return 0;
        break;

        case -2 : 
        printf("L'image n'a pas pu être sauvée\n");
        return 0;
        break;

        default :
        printf("Erreur non identifiée\n");
        return 0;
        break;
    }

    // Libérer la mémoire allouée pour l'image
    destroy_pnm(image);

    return 0;
}