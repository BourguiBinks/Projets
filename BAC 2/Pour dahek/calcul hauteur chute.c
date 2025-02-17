#include <stdio.h>
#include <math.h>
int main(){
	float h;
	double t; 
	printf("Entrée une durée : ");
	scanf("%lf", &t);
	
	h=(9.81 * t * t) / 2.0 ;
	
	printf("A t = %lf, la hauteur est de %f m", t, h);
}
