#include <stdio.h>

void affiche(int a, int b){
    printf("%d, %d\n",a,b);
}
void incr1(int x){x = x +1;}
void incr2(int* x){*x = *x +1;}
void decr1(int* x){ x = x - 1; }
void decr2(int* x){ *x = *x - 1; }

int main(){
int i = 1;
int j = 1;
affiche(i, j);
incr2(&i);
affiche(i, j);
decr1(&j);
affiche(i, j);
decr2(&j);
affiche(i, j);
while(i != j){
incr1(j);
decr2(&i);
}
affiche(i, j);
return 0;
}