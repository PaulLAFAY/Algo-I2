#include <stdio.h>
#include <stdlib.h>

void saisie(char p[150]){

    printf("Saisir une phrase d'au plus 150 caracteres :\n\n");
    fflush(stdin);
    gets(p);

}

void affiche(char p[150]){

    printf("La phrase saisie est :\n\n");
    printf("%s\n\n", p);
    printf("0 - Menu principale\n\n");
    int i;
    scanf("%i", &i);

}

void afficheligne(char p[150]){

    printf("La phrase saisie est : (version 1 mot par ligne)\n\n");
    int i;
    for(i = 0; i < 150; i++){
        printf("%c", p[i]);
        if(p[i] == ' ') printf("\n");
    }
    printf("\n\n0 - Menu principale\n\n");
    scanf("%i", &i);

}

void nbcaract(char p[150]){

    int i, nb = 0;
    for(i = 0; i < 150; i++){
        if(p[i] != 0) nb++;
    }
    printf("Il y a %i caractere dans la phrase\n\n", nb);
    printf("0 - Menu principale\n\n");
    scanf("%i", &i);

}

void nbmots(char p[150]){

    int i, nb = 1;
    for(i = 0; i < 150; i++){
        if(p[i] == ' ') nb++;
    }
    printf("Il y a %i mots dans la phrase\n\n", nb);
    printf("0 - Menu principale\n\n");
    scanf("%i", &i);

}

void occlettre(char p[150]){

    int i, nb = 0;
    char caract = 0;
    printf("Saisir un caractere a compter : ");
    fflush(stdin);
    scanf("%c", &caract);
    for(i = 0; i < 150; i++){
        if(p[i] == caract) nb++;
    }
    printf("\nIl y a %i caracteres %c dans la phrase\n\n", nb, caract);
    printf("0 - Menu principale\n\n");
    scanf("%i", &i);

}

void recherchemot(char p[150]){

    int i, j, tmot = 0,nbmot = 0;
    char mot[30] = {0};

    printf("Saisir un mot a rechercher : ");
    fflush(stdin);
    scanf("%s", &mot);

    for(i = 0; i < 30; i++){
        if(mot[i] != 0) tmot++;
    }

    for(i = 0; i < 150; i++){
        if(p[i] == mot[0]){
            int compteur = 0;
            for(j = 0; j < tmot; j++){
                if(p[i+j] == mot[j]) compteur++;
            }
            if(compteur == tmot) nbmot++;
        }
    }

    printf("\nLe mot '%s' apparait %i fois dans la phrase\n\n", mot, nbmot);
    printf("0 - Menu principale\n\n");
    scanf("%i", &i);

}

int main(){

    char p[150] = {0};
    int select, quit = 0;

    saisie(p);

    do{

        system("cls");

        printf("1 - Afficher la phrase\n2 - Afficher la phrase un mot par ligne\n3 - Compter le nombre de caractere\n4 - Compter le nombre de mots\n5 - Occurence d'une lettre donnee\n6 - Recherche d'un mot\n\n0 - Quitter\n\n");
        scanf("%i", &select);

        system("cls");

        switch(select){

            case 0 : quit = 1;
            break;

            case 1 : affiche(p);
            break;

            case 2 : afficheligne(p);
            break;

            case 3 : nbcaract(p);
            break;

            case 4 : nbmots(p);
            break;

            case 5 : occlettre(p);
            break;

            case 6 : recherchemot(p);
            break;

        }

    }while(quit == 0);

    return 0;

}
