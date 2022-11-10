#include <stdio.h>
#include <stdlib.h>

int fonction1(int n){

    int fact = 1, i;
    for(i = 1; i <= n; i++){
        fact *= i;
    }
    return fact;

}

int fonction2(int n){

    if(n < 2) return 1;
    else return n*fonction2(n-1);

}

int main(){

    int n;
    scanf("%i", &n);
    printf("\nPar la fonction 1 : %i\n\n", fonction1(n));
    printf("Par la fonction 2 : %i\n\n", fonction2(n));

}
