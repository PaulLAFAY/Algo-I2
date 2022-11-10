#include <stdio.h>
#include <stdlib.h>

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

int main(){

    int i = 0;
    char calcul[3];
    pel p = NULL;
    char phrase[50];
    fflush(stdin);
    gets(phrase);

    do{

        if(phrase[i] != '+' && phrase[i] != '-' && phrase[i] != '*' && phrase[i] != '/'){
            p = empiler(p, phrase[i]);
        }
        else{
            p = depiler(p, &calcul[0]);
            calcul[0] -= '0';
            p = depiler(p, &calcul[1]);
            calcul[1] -= '0';
            if(phrase[i] == '+') calcul[2] = calcul[0] + calcul[1];
            else if(phrase[i] == '-') calcul[2] = calcul[0] - calcul[1];
            else if(phrase[i] == '*') calcul[2] = calcul[0] * calcul[1];
            else if(phrase[i] == '/') calcul[2] = calcul[0] / calcul[1];
            p = empiler(p, calcul[2]+'0');
        }

        i++;

    }while(phrase[i] != '\0');

    int resultat = 0;
    p = depiler(p, &resultat);
    printf("%i", resultat-'0');

}
