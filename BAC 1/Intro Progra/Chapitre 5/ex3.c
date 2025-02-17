#include <stdio.h>

int main(){
    char tab[] = "Je suis homosexuel";
    int i, j = 0;
    char new_tab[20];

    for(i = 0; i < 19; i++){
        if(tab[i] != 'e'){
            new_tab[j] = tab[i];
            j++;
        }
    }
    new_tab[j] = '\0';

    printf("%s", new_tab);

    return 0;
}
