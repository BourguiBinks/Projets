#include <stdio.h>
#define entier1 a
#define entier2 b

int main(){
  int entier1;
  int entier2;

  printf("Donne moi deux entiers :\n");
  scanf("%d %d",&entier1, &entier2);
  //printf("tes entiers sont : %d et %d\n",entier1, entier2 );


/*if(entier1<entier2)
  printf("%d < %d\n", entier1, entier2 );
  else
    printf("%d > %d\n", entier1, entier2 );

if ((((entier1*entier2)  %2)    ==0))
  printf("a+b est pair! zemel va\n");

  else
  printf("a+b est impair! couillon \n");
*/
if((a*b)<0)
  printf("a + b est négatif\n");
  else
  printf("a + b est positif\n");

  return 0;
}
