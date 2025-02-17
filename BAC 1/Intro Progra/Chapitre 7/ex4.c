#include <stdio.h>
void min_max(int *tab, int *max, int *min){
    tab[5];
    *max = tab[0];
    *min = tab[0];

    for(int i = 0; i < 5 ; i++){
        if(tab[i]>*max)
            *max = tab[i];
        if(tab[i]<*min)
            *min = tab[i];
    }
}
void rempli_tab5val(int *tab, int val1, int val2, int val3, int val4, int val5){
        tab[0] = val1;
        tab[1] = val2;
        tab[2] = val3;
        tab[3] = val4;
        tab[4] = val5;

    }

int main(){
   int minimum, maximum;
   int val1, val2,val3,val4,val5;
   int tableau[5];
   printf("Donne 5 valeurs :\n");
   scanf("%d %d %d %d %d",&val1,&val2,&val3,&val4,&val5);
rempli_tab5val(tableau, val1, val2,val3,val4,val5);
for(int i = 0; i <5; i++){
    printf("%d ",tableau[i]);
}
printf("\n");
  min_max(tableau,&maximum,&minimum);
printf("maximum est %d, le minimum est %d\n", maximum, minimum);

    return 0;
}