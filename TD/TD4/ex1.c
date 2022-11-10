#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct el * pel;

typedef struct el{

    char v;
    pel suivant;

}tel;

pel creeElem(char val){

    pel tmp;
    tmp = (pel)malloc(sizeof(tel));
    tmp->v = val;
    tmp->suivant = NULL;
    return tmp;

}

pel empiler(pel p, char val){

    pel tmp;
    tmp = creeElem(val);
    tmp->suivant = p;
    p = tmp;
    return p;

}

pel depiler(pel p, char *pval){

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

int main() {

    int i = 0;
    pel p = NULL;
    char mot[20];
    char motfinal[20];
    fflush(stdin);
    gets(mot);

    do{

        p = empiler(p, mot[i]);
        i++;

    }while(mot[i] != '\0');

    i = 0;

    do{

        p = depiler(p, &motfinal[i]);
        i++;

    }while(p != NULL);

    motfinal[i] = '\0';

    if(strcmp(mot, motfinal) == 0) printf("palindrome");
    else printf("pas palindrome");

}
