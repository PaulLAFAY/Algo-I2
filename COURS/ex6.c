#include<stdio.h>
#include<stdlib.h>

typedef struct el * pel;

typedef struct el {

    int v;
    pel suivant;

} tel;

pel creeElem(int val){

    pel aux=(pel)malloc(sizeof(tel));
    aux->v=val;
    aux->suivant=NULL;
    return aux;

}

pel ajouter(pel l, int val){

    pel aux;
    if(l==NULL)
    {
        return creeElem(val);
    }
    else
    {
        if(val < l->v)
        {
            aux=creeElem(val);
            aux->suivant =l;
            return aux;
        }
        else
        {
            if(val == l->v)
            {
                printf("élément déjà présent\n");
                return l;
            }
            else
            {
                l->suivant = ajouter(l->suivant,val);
                return l;
            }
        }
    }

}

pel supprimer(pel l, int val){

    pel aux;
    if(l==NULL)
    {
        printf("liste vide : element absent\n");
        return l;
    }
    else
    {
        if(val < l->v)
        {
            printf("element absent\n");
            return l;
        }
        else
        {
            if(l->v == val)
            {
                aux=l;
                l=l->suivant;
                printf("element supprime\n");
                free(aux);
                return l;
            }
            else
            {
                l->suivant=supprimer(l->suivant,val);
                return l;
            }
        }
    }

}

void afficheiter(pel l){

    system("cls");
    printf("Liste des elements presents :\n\n");

    while(l != NULL){

        pel tmp = l;
        printf("%i\n", tmp->v);
        l = l->suivant;

    }

    int menu;
    printf("\n\n\n0 - Menu principal\n\n");
    scanf("%i", &menu);

}

void afficherecur(pel l){

    if(l == NULL){

        int menu;
        printf("\n\n\n0 - Menu principal\n\n");
        scanf("%i", &menu);

    }
    else{

        pel tmp = l;
        printf("%i\n", tmp->v);
        afficherecur(l->suivant);

    }

}

void cbiter(pel l){

    system("cls");

    int i = 0;

    while(l != NULL){

        i++;
        l = l->suivant;

    }

    printf("Il y a %i elements dans la liste", i);
    int menu;
    printf("\n\n\n0 - Menu principal\n\n");
    scanf("%i", &menu);

}

void cbrecur(pel l, int i){

    if(l == NULL){

        printf("Il y a %i elements dans la liste", i);
        int menu;
        printf("\n\n\n0 - Menu principal\n\n");
        scanf("%i", &menu);

    }
    else{

        i++;
        cbrecur(l->suivant, i);

    }

}

void sommeiter(pel l){

    system("cls");

    int somme = 0;

    while(l != NULL){

        somme += l->v;
        l = l->suivant;

    }

    printf("La somme des elements de la liste est egal a %i", somme);
    int menu;
    printf("\n\n\n0 - Menu principal\n\n");
    scanf("%i", &menu);

}

void sommerecur(pel l, int somme){

    if(l == NULL){

        printf("La somme des elements de la liste est egal a %i", somme);
        int menu;
        printf("\n\n\n0 - Menu principal\n\n");
        scanf("%i", &menu);

    }
    else{

        somme += l->v;
        sommerecur(l->suivant, somme);

    }

}

int main(){

    int select, val, i = 0;
    pel l = NULL;

    do{

        system("cls");

        printf("1 - Ajouter un element\n");
        printf("2 - Supprimer un element\n");
        printf("3 - Afficher la liste des elements (iteratif)\n");
        printf("4 - Afficher la liste des elements (recurcif)\n");
        printf("5 - Determiner le nombre d'element (iteratif)\n");
        printf("6 - Determiner le nombre d'element (recurcif)\n");
        printf("7 - Calculer la somme des elements (iteratif)\n");
        printf("8 - Calculer la somme des elements (recurcif)\n\n");
        printf("0 - Quitter\n\n");

        scanf("%i", &select);

        switch(select){

        default : exit(1);
        break;

        case 1 :

            system("cls");
            printf("Saisir un entier a ajouter dans la liste : ");
            scanf("%i", &val);
            l = ajouter(l, val);

        break;

        case 2 :

            system("cls");
            printf("Saisir un entier a supprimer de la liste : ");
            scanf("%i", &val);
            l = supprimer(l, val);
            system("PAUSE");

        break;

        case 3 :

            afficheiter(l);

        break;

        case 4 :

            system("cls");
            printf("Liste des elements presents :\n\n");
            afficherecur(l);

        break;

        case 5 :

            cbiter(l);

        break;

        case 6 :

            system("cls");
            i = 0;
            cbrecur(l, i);

        break;

        case 7 :

            sommeiter(l);

        break;

        case 8 :

            system("cls");
            i = 0;
            sommerecur(l, i);

        break;

        }

    }while(1);

}
