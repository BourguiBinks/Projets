#include <stdio.h>
void initialise1(int *a, int *b, float *c){
    *a = -5;
    *b = -5;
    *c = -5;
    }
int main(){
int enti1 = 0;
int enti2 = 0;
float reel = 0;
    
printf("%d %d %f\n",enti1,enti2,reel);
initialise1(&enti1, &enti2, &reel);
printf("%d %d %f\n",enti1,enti2,reel);

    return 0;
}