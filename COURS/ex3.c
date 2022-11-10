#include <stdio.h>
#include <stdlib.h>

typedef struct el * pel;

typedef struct el{

    int v;
    pel suivant;

}tel;

pel creeElem(int val){

    pel tmp;
    tmp = (pel)malloc(sizeof(tel));
    tmp->v = val;
    tmp->suivant = NULL;
    return tmp;

}

pel empiler(pel p, int val){

    pel tmp;
    tmp = creeElem(val);
    tmp->suivant = p;
    p = tmp;
    return p;

}

pel depiler(pel p, int *pval){

    pel tmp = p;
    if(p == NULL){
        printf("Pile deja vide\n");
        exit(1);
    }
    else{
        p = p->suivant;
        *pval = tmp->v;
        free(tmp);
    }
    return p;

}

int main(){

    int n = 4;
    char *c = (char *)malloc((n+1)*sizeof(char));
    fflush(stdin);
    scanf("%s", &c);

    pel p = NULL;

    for(int i = 0; i < n; i++){
        p = empiler(p, c[i]);
    }

}
