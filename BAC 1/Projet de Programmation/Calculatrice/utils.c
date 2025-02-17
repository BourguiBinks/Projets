/**
 * \file utils.c
 * \author Alexandre Bourguignon
 * \brief Ce fichier contient les fonctions utiles pour la calculatrice GTK
 * \version 0.1
 * \date 2023-04-12
 * @projet: INFO0030 : Projet 3
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "utils.h"


int is_valid_number(const char* str) {
  if (str == NULL || strlen(str) == 0) {
    return 1; // Entrée vide
  }
  char* endptr = NULL;
  long val = strtol(str, &endptr, 10);
  if (*endptr != '\0' || val < MINIMUM_NUMBER || val > MAXIMUM_NUMBER) {
    return 2; // Pas un nombre valide
  }
  return 0; // Entrée valide
}

