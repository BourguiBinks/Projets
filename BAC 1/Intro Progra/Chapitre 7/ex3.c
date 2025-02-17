#include <stdio.h>
void echange( int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main(){
int zboub;
int zgueg;
printf("Donne moi 2 entiers et je les échange par magie : \n");
scanf("%d %d",&zboub,&zgueg);
printf("Tes entiets sont %d et %d\n", zboub, zgueg);
echange(&zboub, &zgueg);
printf("Maintenant tes enties sont %d et %d\n", zboub, zgueg);


    return 0;
}