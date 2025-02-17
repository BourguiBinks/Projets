/**
 * \file modele_calculatrice.c
 * \author Alexandre Bourguignon
 * \brief Ce fichier contient le modèle de la calculatrice GTK
 * \version 0.1
 * \date 2023-04-12
 * INFO0030 : Projet 3
 * 
 */
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <assert.h>

#include "modele_calculatrice.h"

/**
 * \brief Implémentation de la vue pour la calculatrice.
 */
struct ModelCalculator_t{
    int number1;  /*!< un nombre entier 1*/
    int number2; /*!< un nombre entier 2*/
    int result; /*!< Le résultat de l'entier 1 + entier 2*/
};

ModelCalculator *create_ModelCalculator(){
    ModelCalculator *model= malloc(sizeof(ModelCalculator));
    if(model == NULL){
        return NULL;
    }
    return model;
}

ModelCalculator *make_addition(ModelCalculator *model, int number1, int number2){
    assert(model != NULL);

    if(number1 > MAXIMUM_NUMBER || number1 < MINIMUM_RESULT 
    || number2 > MAXIMUM_NUMBER || number2 < MINIMUM_RESULT){
        return NULL;
    }
    model->number1 = number1;
    model->number2 = number2;
    
    if(number1 + number2 > MAXIMUM_RESULT || number1 + number2 < MINIMUM_RESULT){
        return NULL;
    }
    model->result = number1 + number2;
    
    return model;
}

void *destroy_ModelCalculator(ModelCalculator *model){
    assert(model != NULL);

    free(model);
}

int get_number1(ModelCalculator *model){
    assert(model != NULL);

    return model->number1;
}

int get_number2(ModelCalculator *model){
    assert(model != NULL);

    return model->number2;
}

int get_result(ModelCalculator *model){
    assert(model != NULL);

    return model->result;
}