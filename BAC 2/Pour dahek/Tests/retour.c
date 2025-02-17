#include <stdio.h>
#include <string.h>

int puissance(int x){
  int resultat = x*x*x*x*x;
  return resultat;
}
int main(){
int zeub;
char reponse[255];
  printf("Choisis un nombre gros fils de pute \n");
  scanf("%d", &zeub);
  printf("%d puissance 5 c'est %d\n",zeub,puissance(zeub));

  scanf("%s", reponse);

  if (strcmp(reponse,"cimer mon reuf") == 0)
    printf("De rien mon reuf on est là\n");

  else
    printf("bah ntm alors si t'es pas content\n");


  return 0;
}
