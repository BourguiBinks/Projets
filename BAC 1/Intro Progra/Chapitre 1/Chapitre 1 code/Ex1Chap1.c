#include <stdio.h>

int main(){
float temp_degre;
float temp_faren;

printf("Donne moi une température en farenheit et je te la convertit en degré\n");
scanf("%f",&temp_faren);

temp_degre = 0.55556 * (temp_faren - 32);

printf("Cette température en degré celcius est : %f\n", temp_degre);
 

  return 0;
}
