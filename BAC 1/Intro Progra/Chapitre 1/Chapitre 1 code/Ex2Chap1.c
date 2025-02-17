#include <stdio.h>
int calcul_image(int x){
int image=(((2*x)+3))*((3*(x*x)+2));
return image;
}
int calcul_derive(int x, int h){
  int derive = ((calcul_image(x+h)-calcul_image(x))/h);
return derive;
}
int main(){
int x;
int h;

printf("Donne moi un nombre et je te donne la dérivé de f en ce point:\n");
scanf("%d",&x);
printf("Donne moi un h assez petit\n");
scanf("%d",&h);
printf("La derivé est : %d\n", calcul_derive(x,h));

  return 0;
}
