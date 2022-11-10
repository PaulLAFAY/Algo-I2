#include <stdio.h>
#include <stdlib.h>

void saisie(int n, float t[n]){

    int i, erreur = 0;

    do{

        printf("Saisir %i reels entre -15 et 45 : \n\n", n);
        for(i = 0; i < n; i++){
            scanf("%f", &t[i]);
            if(t[i] < -15 || t[i] > 45) erreur = 1;
        }
        if(erreur == 1) printf("\nErreur de saisie\n");

    }while(erreur == 1);

}

void affiche(int n, float t[n]){

    int i;
    printf("\nLe tableau :\n\n");
    for(i = 0; i < n; i++) printf("%f\n", t[i]);

}

void recherche(int n, float t[n]){

    int i, test = 0, erreur = 0;
    float val;

    do{
        printf("Saisir une valeur entre -15 et 45 a chercher dans le tableau : ");
        scanf("%f", &val);
        if(val < -15 || val > 45) erreur = 1;
        if(erreur == 1) printf("\nErreur de saisie\n");
    }while(erreur == 1);

    for(i = 0; i < n; i++){
        if(val == t[i]){
            printf("\n%f apparait a la case %i\n", val, i);
            test = 1;
        }
    }
    if(test == 0) printf("\n%f n'apparait pas dans le tableau\n", val);

}

void elemsup(int n, float t[n]){

    int i, compt = 0, test = 0;
    for(i = 0; i < n; i++){
        if(t[i] > 15){
            if(compt == 0){
                printf("Les valeurs superieurs a 15 dans le tableau sont : \n\n");
                compt = 1;
            }
            printf("%f\n", t[i]);
            test = 1;
        }
    }
    if(test == 0) printf("Aucune valeur n'est superieure a 15 dans ce tableau\n\n");

}

void moy(int n, float t[n]){

    int i;
    float somme = 0, moy = 0;
    for(i = 0; i < n; i++) somme += t[i];
    moy = somme / n;
    printf("La moyenne du tableau est de %f\n", moy);

}

int main(){

    int n = 5, select, quit = 0;
    float tab[n];

    saisie(n, tab);

    do{

        printf("\n1 - Afficher le tableau\n");
        printf("2 - Rechercher une valeur\n");
        printf("3 - Afficher les valeurs superieures a 15\n");
        printf("4 - Calculer la moyenne du tableau\n\n");
        printf("5 - Quitter\n\n");

        scanf("%i", &select);

        system("cls");

        switch(select){

        case 1 :
            affiche(n, tab);
        break;

        case 2 :
            recherche(n, tab);
        break;

        case 3 :
            elemsup(n, tab);
        break;

        case 4 :
            moy(n, tab);
        break;

        case 5 :
            quit = 1;
        break;

        }

    }while(quit == 0);

}
