#include <stdio.h>

int main(){
int n;

printf("donne un entier gros chien\n");
scanf("%d",&n);
int factorielle = 1;
for(int i = n;i>1;i--){
  factorielle *= i;
}
printf("la factorielle de %d est %d\n", n,factorielle);
  return 0;
}
