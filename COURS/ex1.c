#include <stdio.h>
#include <stdlib.h>

void echange(int* a, int* b){

    int c;
    c = *a;
    *a = *b;
    *b = c;

}

int main()
{

    int a, b;
    scanf("%i%i", &a, &b);
    printf("a : %i          b : %i\n", a, b);
    echange(&a, &b);
    printf("a : %i          b : %i", a, b);

}
