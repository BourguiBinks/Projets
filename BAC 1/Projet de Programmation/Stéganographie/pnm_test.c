/**
 * @file pnm-test.c
 * @author Alexandre Bourguignon
 * @brief Ce fichier contient toutes les fonctions de test unitaires liées au fichier pnm.c 
 * @version 0.1
 * @date 2023-03-23
 * NOTE : J'ai compris trop tard qu'il ne fallait pas tester les fonctions static, les tests sont donc inutiles
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
#include "seatest.h"

//PROTOTYPES 
PNM *construct_pnm(void);
/*static unsigned int **create_matrix(unsigned int columns, unsigned int lines);
static void destroy_matrix(unsigned int **matrix, unsigned int columns);
static int transform_into_format(char *magicNumber);
static int verify_pnm_type(FILE *fp);
static void skip_comments(FILE *fp);
static unsigned int get_columns(FILE *fp);
static unsigned int get_lines(FILE *fp);
static unsigned int get_maxValue(FILE *fp, PNMFORMAT magicNumber);
static int read_matrix(FILE *fp, PNM *image);
//FIN PROTOYPES

***************************************************************
NOTE : J'avais commencé à testes toutes mes fonctions jusqu'à ce que 
je sache qu'il fallait ne tester que les fonctions non statiques, c'est
pour cette raison qu'il y a tant de fonctions de tests

***************************************************************
static void test_create_matrix(){
    // Vérifie que la matrice est créée avec les bonnes dimensions
    unsigned int columns = 3;
    unsigned int lines = 4;
    unsigned int **matrix = create_matrix(columns, lines);
    assert_true(matrix != NULL);
    
    for(unsigned int i = 0; i < columns; i++)
        assert_true(matrix[i] != NULL);
   

    destroy_matrix(matrix, columns);
}


static void test_transform_into_format(){
   char *magicNumberPBM = "P1";
   int expectedPBM = 1;
   assert_true(transform_into_format(magicNumberPBM) == expectedPBM);

   char *magicNumberPGM = "P2";
   int expectedPGM = 2;
   assert_true(transform_into_format(magicNumberPGM) == expectedPGM);

   char *magicNumberPPM = "P3";
   int expectedPPM = 3;
   assert_true(transform_into_format(magicNumberPPM) == expectedPPM);

   char *magicNumberError = "P7";
   int expectedError = -1;
   assert_true(transform_into_format(magicNumberError) == expectedError);
}

static void test_verify_pnm_type(){
    char *scs = "images/scs.pbm";
    FILE *fp1 = fopen(scs, "r");
    assert_true(fp1 != NULL);
    assert_true(verify_pnm_type(fp1) == 1);
    fclose(fp1);

    char *Lena_file = "image_Lena/Lena.pgm";
    FILE *fp2 = fopen(Lena_file, "r");
    assert_true(fp2 != NULL);
    assert_true(verify_pnm_type(fp2) == 2);
    fclose(fp2);

    char *antilope = "images/antilope.ppm";
    FILE *fp3 = fopen(antilope, "r");
    assert_true(fp3 != NULL);
    assert_true(verify_pnm_type(fp3) == 3);
    fclose(fp3);


    char *notPnmFile = "images/notPnmfile.plm";
    FILE *fp4 = fopen(notPnmFile, "r");
    assert_true(fp4 != NULL);
    assert_true(verify_pnm_type(fp4) == -1);
    fclose(fp4);
}

static void test_skip_comments(){ //Ouvre 2 fichiers, les 2 contiennent une valeur mais un fichier a une ligne de commentaires
    FILE *fp1 = fopen("images/filewithcomment","r");
    assert_true(fp1 != NULL);
    skip_comments(fp1);//Il y a un commentaire donc le curseur est déplacé au début de la prochaine ligne
    int value = 0; //Crée une variable qui va contenir la valeur contenue dans le fichier
    fscanf(fp1, "%d", &value);
    assert_int_equal(18, value); //value doit valoir 18 
    fclose(fp1);

    FILE *fp2 = fopen("images/filewithoutcomment","r");
    assert_true(fp1 != NULL);
    skip_comments(fp2); //Il n'y a pas de commentaires donc le curseur revient au début de la ligne
    int value2 = 0;
    fscanf(fp2, "%d", &value2);
    assert_int_equal(18, value2); //value doit valoir 18 également
    fclose(fp2);

}

static void test_get_columns(){
    FILE *fp1 = fopen("images/noExtension","r"); //Ouvre un fichier ne contenant rien
    assert_true(fp1 != NULL);
    assert_true(get_columns(fp1) == 0);  //get_columns renvoie 0 si il ne lit rien
    fclose(fp1);

    FILE *fp2 = fopen("images/filewithoutcomment","r"); //Ouvre un fichier contenant une valeur arbitraire
    assert_true(fp2 != NULL);
    assert_true(get_columns(fp2) == 18);
    fclose(fp2);
}

static void test_get_lines(){ //Cette fonction est quasi identique à get_columns
    FILE *fp1 = fopen("images/noExtension","r"); //Ouvre un fichier ne contenant rien
    assert_true(fp1 != NULL);
    assert_true(get_lines(fp1) == 0);
    fclose(fp1);

    FILE *fp2 = fopen("images/filewithoutcomment","r"); //Ouvre un fichier contenant une valeur arbitraire
    assert_true(fp2 != NULL);
    assert_true(get_lines(fp2) == 18);//get_lines renvoie 0 si il ne lit rien
    fclose(fp2);
}

static void test_get_maxValue(){
    FILE *fp1 = fopen("images/noExtension","r"); //cas où maxValue est 0 par défaut car le fichier est pbm
    assert_true(fp1 != NULL);
    assert_true(get_maxValue(fp1, PBM_ID) == 0);
    fclose(fp1);

    FILE *fp2 = fopen("images/filewithoutcomment","r");//cas où maxValue est scanné car le fichier est pgm
    assert_true(fp2 != NULL);
    assert_true(get_maxValue(fp2, PGM_ID) == 18);
    fclose(fp2);

    FILE *fp3 = fopen("images/filewithoutcomment","r");//cas où maxValue est scanné car le fichier est ppm
    assert_true(fp3 != NULL);
    assert_true(get_maxValue(fp3, PPM_ID) == 18);
    fclose(fp3);

    FILE *fp4 = fopen("images/noExtension","r");//cas où maxValue est scanné car le fichier est pgm
    assert_true(fp4 != NULL);                   //mais le fichier ne contient rien
    assert_true(get_maxValue(fp4, PGM_ID) == 2);
    fclose(fp4);

    FILE *fp5 = fopen("images/filewithoutcomment","r");//cas où le fichier n'est d'aucun type PNM
    assert_true(fp5 != NULL);
    assert_true(get_maxValue(fp5, 6) == 3);
    fclose(fp5);
}

*/


static void test_verify_extension(){ //Vérifie chaque cas (pbm,pgm,ppm,
    char *scs = "images/scs.pbm";    // pas d'extension et mauvaise extension)
    char *Lena_file = "image_Lena/Lena.pgm";
    char *antilope = "images/antilope.ppm";
    char *noExtension = "images/noExtension";
    char *notPnmFile = "images/notPnmfile.plm";
    assert_true(verify_extension(scs) == 1);
    assert_true(verify_extension(Lena_file) == 2);
    assert_true(verify_extension(antilope) == 3);
    assert_true(verify_extension(noExtension) == -2);
    assert_true(verify_extension(notPnmFile) == -1);

}

static void test_construct_pnm(){
    PNM *image = construct_pnm();
    assert_true(image != NULL);
    free(image);
}

static void test_load_pnm(){
    PNM *image1 = NULL;
    PNM *image2 = NULL;
    PNM *image3 = NULL;
    char *pbmFile = "images/scs.pbm";
    char *pgmFile = "images/totem.pgm";
    char *ppmFile = "images/antilope.ppm";
    assert_true(load_pnm(&image1, pbmFile) == 0);
    destroy_pnm(image1);
    assert_true(load_pnm(&image2, pgmFile) == 0);
    destroy_pnm(image2);
    assert_true(load_pnm(&image3, ppmFile) == 0);
    destroy_pnm(image3);
}

static void test_write_pnm(){
    PNM *image1 = NULL;
    PNM *image2 = NULL;
    PNM *image3 = NULL;
    char *pbmFile = "images/scs.pbm";
    char *pbmFileCopy = "images/scs_copie.pbm";
    char *pgmFile = "images/totem.pgm";
    char *pgmFileCopy = "images/totem_copie.pgm";
    char *ppmFile = "images/antilope.ppm";
    char *ppmFileCopy = "images/antilope_copie.ppm";
    assert_true(load_pnm(&image1, pbmFile) == 0);
    assert_true(write_pnm(image1, pbmFileCopy) == 0);
    destroy_pnm(image1);
    assert_true(load_pnm(&image2, pgmFile) == 0);
    assert_true(write_pnm(image2, pgmFileCopy) == 0);
    destroy_pnm(image2);
    assert_true(load_pnm(&image3, ppmFile) == 0);
    assert_true(write_pnm(image3, ppmFileCopy) == 0);
    destroy_pnm(image3);


}

static void test_fixture(){
    test_fixture_start();
    run_test(test_verify_extension);
    run_test(test_construct_pnm);
    run_test(test_load_pnm);
    run_test(test_write_pnm);
   /*run_test(test_create_matrix);
    *run_test(test_transform_into_format);
    *run_test(test_verify_pnm_type);
    *run_test(test_skip_comments);
    *run_test(test_get_columns);
    *run_test(test_get_lines);
    *run_test(test_get_maxValue);
    */
    test_fixture_end();
}

static void all_tests(){
    test_fixture();
}

int main(){
      
return run_tests(all_tests);
}