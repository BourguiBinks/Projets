/**
 * @file main.c
 * @author Alexandre Bourguignon
 * @brief Ce fichier contient la fonction main qui permet de tester la technique de stéganographie sur des images PNM
 * @version 0.1
 * @date 2023-03-23
 * @projet: INFO0030 : Projet 2
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include "pnm.h"
#include "stegano.h"


int main(int argc, char *argv[]) {

    char *optstring = ":hn:p:s::o:";
    char opt;
    char *bitNumberInput = NULL;
    char *input_file = NULL;
    char *message_file = NULL;
    char *output_file = NULL;

    if(argc == 1){
        printf("Correct usage: %s -n <LSB> -p <imput_pgm> -s<input_texte> -o <output>\n", argv[0]);
        return 0;
    }

    while((opt = getopt(argc, argv, optstring)) != -1){ //On parcourt les arguments donnés dans le terminal
        switch(opt){
        case 'h':
            printf("Correct usage: %s -n <LSB> -p <imput_pgm> -s<input_texte> -o <output>\n", argv[0]);
            return 0;
            break;
        case 'n':
            bitNumberInput = optarg;
            break;
        case 'p':
            input_file = optarg;
            break;
        case 's':
            message_file = optarg;
            break;
        case 'o':
            output_file = optarg;
            break;
        case '?':
            printf("Unknown option : %c\n", optopt);
            break;
        case ':':
            printf("Missing argument : %c\n", optopt);
            break;

        default:
            printf("Correct usage: %s -n <LSB> -p <imput_pgm> -s<input_texte> -o <output>\n", argv[0]);
            return 0;
        }
    }

    unsigned int bitNumber = atoi(bitNumberInput);
    if(input_file == NULL || output_file == NULL){ 
        printf("Correct usage: %s -n <LSB> -p <imput_pgm> -s<input_texte> -o <output>\n", argv[0]);
        return 0;
    }
    if(bitNumber != 1 && bitNumber != 2 && bitNumber != 4){
        printf("The number of least significant bits to be considered should be 1, 2 or 4\n");
        return 0;
    }
 
    if(message_file != NULL && verify_extension(output_file) == 2){
        //Traiter le cas où on encode 
        if(verify_extension(output_file) != 2){
        printf("You must put a '.pgm' extension for your output file\n");
        return 0;
    }
        switch(hide_message(bitNumber, input_file, message_file, output_file)){
            case 0:
            printf("Le message a bien été caché\n");
            break;

            case -1:
            printf("Problème d'ouverture du fichier\n");
            return 0;
            break;

            case 1:
            printf("Problème de mémoire\n");
            return 0;
            break;

            case 2:
            //printf("Nom fichier en input incorrect\n");
            return 0;
            break;

            case 3:
            printf("Contenu fichier en input incorrect\n");
            return 0;
            break;

            case 4:
            printf("Aucune idée\n");
            return 0;
            break;

            default:
            printf("?\n");
            return 0;
            break;

        }
        
    }
    else   
        switch(decode_message(bitNumber, input_file, output_file)){
            case 0:
            printf("Le message a bien été décodé ! Voir dans le fichier texte créé\n");
            break;

            case 1:
            printf("Le message est vide\n");
            return 0;
            break;

            case 2:
            printf("Impossible de décoder le message\n");
            return 0;
            break;

            case 3:
            printf("Problème d'allocation mémoire\n");
            return 0;
            break;
            
            case 4:
            printf("Impossible d'ouvrir le fichier en output\n");
            return 0;
            break;

            default:
            printf("Erreur\n");
            return 0;
            break;
        } 
    return 0;
}