/**
 * pnm.c
 *
 * Ce fichier contient les définitions de types et
 * les fonctions de manipulation d'images PNM.
 *
 * @author: Bourguignon Alexandre s211885
 * @date: 06/03/23
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pnm.h"

PNM *construct_pnm(void);
static unsigned int **create_matrix(unsigned int columns, unsigned int lines);
static void destroy_matrix(unsigned int **matrix, unsigned int columns);
static int transform_into_format(char *magicNumber);
static int verify_pnm_type(FILE *fp);
static void skip_comments(FILE *fp);
static unsigned int get_columns(FILE *fp);
static unsigned int get_lines(FILE *fp);
static unsigned int get_maxValue(FILE *fp, PNMFORMAT magicNumber);
static int read_matrix(FILE *fp, PNM *image);

struct PNM_t
{
   PNMFORMAT magicNumber;
   unsigned int columns;
   unsigned int lines;
   unsigned int maxValue;
   unsigned int **matrix;
};


static unsigned int **create_matrix(unsigned int columns, unsigned int lines){

   unsigned int **matrix = malloc(sizeof(unsigned int *) * columns);
   if(matrix == NULL){
      return NULL;
   }

   for(unsigned int i = 0; i < columns; i++){
      matrix[i] = malloc(sizeof(unsigned int) * lines);
      if(matrix[i] == NULL){
         for(unsigned int j = 0; j < i; j++){
            free(matrix[j]);
         }
         free(matrix);
         return NULL;
      }
   }
   return matrix;
}

static void destroy_matrix(unsigned int **matrix, unsigned int columns){
   assert(matrix != NULL);

   for(unsigned int i = 0; i < columns; i++){
      if(matrix[i] != NULL)
         free(matrix[i]);
   }
   free(matrix);
   // printf("La matrice a bien été détruite\n");
}

PNM *construct_pnm(){
   PNM *image = malloc(sizeof(PNM)); // Allocation pour une structure PNM
   if(image == NULL){
      printf("Impossible d'allouer de la mémoire pour l'image\n");
      return NULL;
   }
   return image;
}

void destroy_pnm(PNM *image){
   assert(image != NULL);
   destroy_matrix(image->matrix, image->columns);
   free(image);
   //printf("L'image a bien été détruite\n");
}

static int transform_into_format(char *magicNumber){
   if(strcmp(magicNumber, MAGIC_NUMBER_PBM) == 0)
      return PBM_FORMAT;
   else if(strcmp(magicNumber, MAGIC_NUMBER_PGM) == 0)
      return PGM_FORMAT;
   else if(strcmp(magicNumber, MAGIC_NUMBER_PPM) == 0)
      return PPM_FORMAT;
   else{
      // printf("Ce n'est pas un format PNM\n");
      return -1;
   }
}

int verify_extension(char *filename)
{
   assert(filename != NULL);

   char *extension = strrchr(filename, '.');
   if (extension == NULL){
      printf("Il n'y a pas d'extension\n");
      return -1; // pas d'extension
   }
   else if(strcmp(extension, ".pbm") == 0)
      return 1;
   else if(strcmp(extension, ".pgm") == 0)
      return 2;
   else if(strcmp(extension, ".ppm") == 0)
      return 3;
   else
      return -1; // extension invalide
}

static int verify_pnm_type(FILE *fp)
{
   assert(fp != NULL);

   char array[ARRAY_SIZE];
   fscanf(fp, "%2s", array);
   switch (transform_into_format(array)){
   case PBM_ID:
      return PBM_FORMAT;
      break;
   case PGM_ID:
      return PGM_FORMAT;
      break;
   case PPM_ID:
      return PPM_FORMAT;
      break;
   default:
      return -1;
      break;
   }
}

static void skip_comments(FILE *fp)
{
   assert(fp != NULL);
   char c;
   while(fscanf(fp, " %c", &c) == 1){
      if(c == '#'){
         while(getc(fp) != '\n'){
            if(feof(fp)){
               return;
            }
         }
      }
      else{
         fseek(fp, -1L, SEEK_CUR);
         return;
      }
   }
}

static unsigned int get_columns(FILE *fp){
   assert(fp != NULL);

   unsigned int columns;
   if(fscanf(fp, "%u", &columns) != 1)
      return 0;

   return columns;
}

static unsigned int get_lines(FILE *fp){
   assert(fp != NULL);

   unsigned int lines;
   if(fscanf(fp, "%u", &lines) != 1)
      return 0;

   return lines;
}

static unsigned int get_maxValue(FILE *fp, PNMFORMAT magicNumber){
   assert(fp != NULL);

   unsigned int maxValue;

   if(magicNumber == 1)
      return 0;

   else if(magicNumber == 2 || magicNumber == 3){
      if(fscanf(fp, "%u", &maxValue) != 1)
         return 2;

      else
         return maxValue;
   }
   else 
      return 2;
}

static int read_matrix(FILE *fp, PNM *image){
   assert(fp != NULL && image != NULL);
   if(image->magicNumber == 3){
      for(unsigned int i = 0; i < image->columns; i++){
         for(unsigned int j = 0; j < image->lines * 3; j++){
            if(fscanf(fp, "%u ", &image->matrix[i][j]) != 1 
            || (image->magicNumber != 1 && image->matrix[i][j] > image->maxValue)){
               return -1;
            }
         }
      }
   }
   
   else{
      for(unsigned int i = 0; i < image->columns; i++){
         for(unsigned int j = 0; j < image->lines; j++){
            if(fscanf(fp, "%u ", &image->matrix[i][j]) != 1)
               return -1;
         }
      }
   }
       return 0;
   }
int load_pnm(PNM **image, char *filename){
   
   assert(image != NULL && filename != NULL);
   FILE *fp = fopen(filename, "r"); // Ouverture du fichier
   if (fp == NULL){
      printf("Impossible d'ouvrir le fichier\n");
      return -2;
   }

   *image = construct_pnm();
   if(*image == NULL){
      fclose(fp);
      return -1;
   }

   PNM *newImage = *image;
   newImage->magicNumber = verify_pnm_type(fp); // Affectation du nombre magique
   if((int)newImage->magicNumber == -1){
      printf("Ce n'est pas un format PNM\n");
      fclose(fp);
      destroy_pnm(newImage);
      return -2;
   }

   skip_comments(fp); // On passe les commentaires

   newImage->columns = get_columns(fp); // Affectation des colonnes
   if(newImage->columns == 0){
      destroy_pnm(newImage);
      fclose(fp);
      return -3;
   }
   newImage->lines = get_lines(fp); // Affectation des lignes
   if(newImage->lines == 0){
      destroy_pnm(newImage);
      fclose(fp);
      return -3;
   } 

   PNMFORMAT magicNumberTemporary = newImage->magicNumber;
   newImage->maxValue = get_maxValue(fp, magicNumberTemporary); // Affectation de maxVlue
   if(newImage->maxValue == 2){
      destroy_pnm(newImage);
      fclose(fp);
      return -3;
   }

   if(magicNumberTemporary == 3){
      newImage->matrix = create_matrix(newImage->columns, newImage->lines * 3);
      if(newImage->matrix == NULL){
         destroy_pnm(newImage);
         fclose(fp);
         return -1;
      }
   }
   else{
      newImage->matrix = create_matrix(newImage->columns, newImage->lines);
      if(newImage->matrix == NULL){
         destroy_pnm(newImage);
         fclose(fp);
         return -1;
      }
   }
   if(read_matrix(fp, newImage) == -1){
      destroy_pnm(newImage);
      fclose(fp);
      return -3;
   }

   fclose(fp);
   return 0;
}

int write_pnm(PNM *image, char *filename){
   assert(image != NULL && filename != NULL);

   FILE *fp = fopen(filename, "w"); // Ouverture du fichier en mode écriture
   if(fp == NULL){
      return -1;
   }

   fprintf(fp, "P%d\n", image->magicNumber); // Ecriture de nombre magique

   fprintf(fp, "%u %u\n", image->columns, image->lines); // Ecriture des colonnes puis des lignes

   if(image->magicNumber == 2 || image->magicNumber == 3){ // Ecriture de maxValue seulement pour les fichiers PGM ou PPM
      fprintf(fp, "%u\n", image->maxValue);
   }

    if(image->magicNumber == 3){
      for(unsigned int i = 0; i < image->columns; i++){
         for(unsigned int j = 0; j < image->lines * 3; j++){
            fprintf(fp, "%u ", image->matrix[i][j]);
         }
      }
   }else{
      for(unsigned int i = 0; i < image->columns; i++){
         for(unsigned int j = 0; j < image->lines; j++){
            fprintf(fp, "%u ", image->matrix[i][j]);
         }
      }
   }

   fclose(fp);
   return 0;
}