#include <stdio.h>

int main(){
int n;
int s = 0;
printf("donne un nombre zbi\n");
scanf("%d",&n);

for(int i = 1;i<=n;i++){
  s = s + (i*i*i);
}
printf("la somme des cubes de %d est %d\n", n, s);
  return 0;
}
