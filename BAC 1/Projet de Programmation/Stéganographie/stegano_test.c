/**
 * @file stegano-test.c
 * @author Alexandre Bourguignon
 * @brief Ce fichier contient toutes les fonctions de test unitaires liées au fichier stegano.c
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

#include "seatest.h"
#include "stegano.h"
#include "pnm.h"

/*static void test_decimal_to_binary(){
   int decimal = 18;
   char *result = decimal_to_binary(decimal);
   //printf("Le nombre est %d et en binaire %s\n", decimal, result);
}*/

/*static void test_set_decimal_on_32bits(){
    unsigned int number = 19;
    char numberIn32bits[33] = set_decimal_on_32bits(number);
    printf("Le nombre est %u et sa représentation sur 32 bits est %s\n", number, numberIn32bits);
}*/

/*static void test_split_in_n_parts(){
    char *binaryNumber = "00111100";
    unsigned int n = 4;
    unsigned int lenght = get_size(binaryNumber)/n;
    char **splittedNumber = split_in_n_parts(binaryNumber, n);
    if(splittedNumber != NULL){
        for(unsigned int i = 0; i < lenght; i++){
            printf("Bloc numéro %d : %s (taille %u)\n", i+1, splittedNumber[i], get_size(splittedNumber[i]));
        }
        destroy_char_matrix(splittedNumber, lenght);
    }
}*/

/*static void test_binary_to_decimal(){
    char *binary = "11100110";
    unsigned int decimal = binary_to_decimal(binary);
    printf("Le nombre binaire est %s et vaut %u en decimal\n", binary, decimal);
}*/

/*static void test_hide_message(){
    char *filename = "images/poivron.pgm";
    unsigned int bitNumber = 4;
    char *messageFile = "message.txt";
    char *output_file = "ok";
    hide_message(bitNumber, filename, messageFile, output_file);
}*/

static void test_hide_message(){
    unsigned int bitNumber1 = 1;
    unsigned int bitNumber2 = 2;
    unsigned int bitNumber4 = 4;

    char *filename = "images/poivron.pgm";
    char *messageFile = "images/message.txt";
    char *outputFilename1 = "images/poivron_encodé1.pgm";
    char *outputFilename2 = "images/poivron_encodé2.pgm";
    char *outputFilename4 = "images/poivron_encodé4.pgm";

    assert_true(hide_message(bitNumber1, filename, messageFile, outputFilename1) == 0);
    assert_true(hide_message(bitNumber2, filename, messageFile, outputFilename2) == 0);
    assert_true(hide_message(bitNumber4, filename, messageFile, outputFilename4) == 0);

}

static void test_decode_message(){
    unsigned int bitNumber1 = 1;
    unsigned int bitNumber2 = 2;
    unsigned int bitNumber4 = 4;

    char *inputFilename1 = "images/poivron_encodé1.pgm";
    char *inputFilename2 = "images/poivron_encodé2.pgm";
    char *inputFilename4 = "images/poivron_encodé4.pgm";

    char *outputFilename1 = "images/message_caché1.txt";
    char *outputFilename2 = "images/message_caché2.txt";
    char *outputFilename4 = "images/message_caché4.txt";

    assert_true(decode_message(bitNumber1, inputFilename1, outputFilename1) == 0);
    assert_true(decode_message(bitNumber2, inputFilename2, outputFilename2) == 0);
    assert_true(decode_message(bitNumber4, inputFilename4, outputFilename4) == 0);

}
static void test_fixture(){
    test_fixture_start();
    run_test(test_hide_message);
    run_test(test_decode_message);
    //run_test(test_decimal_to_binary);
    //run_test(test_set_decimal_on_32bits);
    //run_test(test_split_in_n_parts);
    //run_test(test_binary_to_decimal);
    test_fixture_end();
}


static void all_tests(){
    test_fixture();
}

int main(){

return run_tests(all_tests); 
}