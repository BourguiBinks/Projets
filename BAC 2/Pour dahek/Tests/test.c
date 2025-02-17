#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

     void filtrer(int *T, int N, int valeur){
     int i = 0;
     static int longueur_utile = 0;
     int j = N-1;
     int tmp = 0;

    assert((N>0) && (T != NULL));
    while(i <= j){
      if(T[i] % valeur ==0){
       longueur_utile ++;
       i++;
      }
      else{
        tmp = T[i];
        T[i] = T[j];
        T[j] = 0;
        j--;
    }
    }
    printf("le tableau après est: [");
    for(i=0; i<N; i++)
      printf("%d|", T[i]);

    printf("]\n");


    printf("la longueur utile est de :%d\n", longueur_utile);
    }

    int main() {
      int N;
      int valeur;
      int i=0;
      printf("Salut mon pote, je te propose de choisir le nombre de case pour ton tableau\n");
      scanf("%u", &N);
      assert(N>(int)0);
      int *T = (int*)malloc(sizeof(int)*N);




      while (i<N){
        T[i]= i + 1;
        i++;
      }

      printf("le tableau avant est: [");
      for(i=0; i<N; i++)
        printf("%d|", T[i]);

      printf("]\n");

      printf("Toutes les valeurs de ton tableau ont la possibilité d'être changées par 0 si elles ne sont pas divisible par un certain nombre. Choisis ce nombre!\n");
      scanf("%d", &valeur);

      filtrer(T,N, valeur);
      free(T);
      return 0;
    }
