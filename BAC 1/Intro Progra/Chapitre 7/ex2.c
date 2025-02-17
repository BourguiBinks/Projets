#include <stdio.h>

void division_entiere(int n, int d, int *quotient, int *reste) {
    *quotient = n / d;
    *reste = n % d;
}

int main() {
    int n = 19;
    int d = 6;
    int quotient, reste;

    division_entiere(n, d, &quotient, &reste);

    printf("Le quotient de %d par %d est : %d\n", n, d, quotient);
    printf("Le reste de la division de %d par %d est : %d\n", n, d, reste);

    return 0;
}
