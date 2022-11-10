#include <stdio.h>
#include <stdlib.h>

typedef struct el * pel;

typedef struct el{

    int v;
    pel suivant;

}tel;

pel creeElem(int val){

    pel tmp;
    tmp=(pel)malloc(sizeof(tel));
    tmp->v=val;
    tmp->suivant=NULL;

    return tmp;

}

pel ajouter(pel f, int val){

    pel aux =creeElem(val);
    pel tmp = f;
    if(f==NULL) return aux;
    else{
        while(tmp->suivant != NULL) tmp=tmp->suivant;
        tmp->suivant=aux;
        return f;
    }

}

pel supprimer(pel f, int *pval){

    pel tmp=f;
    if(f==NULL) printf("File vide\n\n");
    else{
        f=f->suivant;
        *pval = tmp->v;
        free(tmp);
    }

    return f;

}

void afficher(pel f){

    int i = 0;
    while(f != NULL){

        pel tmp = f;
        printf("Position %i : %i\n", i+1, tmp->v);
        f = f->suivant;
        i++;

        printf("ok\n");

    }

    printf("\n");

}

int main()
{

    int select, element;
    pel f = NULL;

    do{

        system("cls");

        printf("1 - Ajouter un element\n2 - Supprimer un element\n3 - Afficher les elements\n\n0 - Quitter\n\n");
        scanf("%i", &select);

        switch(select){

            default : exit(1);
            break;

            case 1 :

                system("cls");
                printf("Saisir un entier : ");
                int entier;
                scanf("%i", &entier);
                f = ajouter(f, entier);

            break;

            case 2 :

                system("cls");
                f = supprimer(f, &element);
                if (f != NULL) printf("On a supprime la valeur %i\n\n", element);
                system("PAUSE");

            break;

            case 3 :

                system("cls");
                afficher(f);
                system("PAUSE");

            break;

        }

    }while(1);

}
