#include <stdio.h>
#include <string.h>
#include <assert.h>
void *nombre_binaire(unsigned int nombre, unsigned int N){
  assert((nombre && N) > 0);
  int j = N-1;
  unsigned int i =0;
  unsigned int repres_binaire[N];
  for(j=N-1;j>=0;j--){

    if((nombre%2)==0){
    repres_binaire[j]=0;
    nombre = nombre>>1;
  }

    else if((nombre%2)==1&&nombre!=0){
      repres_binaire[j]=1;
      nombre = nombre>>1;
    }}
    printf("La représentation binaire de %u est : ", nombre);
    while(i<=N-1){
     printf("%d",repres_binaire[i]);
     i++;
   }
   printf("\nC'est pas fou ? Si clairement, beh c'est moi qui l'ai fait tout seul frérot\n");

    return 0;
  }



int main(){
unsigned int test;
unsigned int nb_bits;
char reponse[256];
printf("Mon frérot... Si tu le souhaites, je suis capable de transformer un nombre positif en sa représentation binaire. Si cela t'intéresse, dis moi le nombre que tu veux transformer ainsi que le nombre de bits représentés.\n");
scanf( "%u", &test);
scanf("%u" , &nb_bits);
nombre_binaire(test, nb_bits);
printf("t'es jaloux?\n");
scanf("%s", reponse);
if (         strcmp(reponse, "oui")== 0    || strcmp(reponse, "Oui") == 0     )
  printf("Bah t'as raison\n");

else if (  strcmp(reponse, "Non") == 0    || strcmp(reponse, "non") == 0  )
  printf("Zehma toi tu sais faire mieux ? Bien ce qu'il me semblait \n");

else
  printf("Je m'en bat les couilles\n");


return 0;

}
