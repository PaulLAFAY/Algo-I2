#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct jv{
    char titre[50];
    int plateforme; //1 windows    2 macos     3 linux
    int annee;
    int agemin;
    char type[20];
    int nbexemplaire;
}jv;

typedef struct el * pel;

typedef struct el {
    jv v;
    pel suivant;
} tel;

pel creeElem(jv jv){

    pel aux=(pel)malloc(sizeof(tel));
    aux->v=jv;
    aux->suivant=NULL;
    return aux;

}

pel ajouter(pel l, jv jv){

    pel aux;
    if(l==NULL) return creeElem(jv);
    else{
        if(strcmp(jv.titre, l->v.titre) < 0){
            aux=creeElem(jv);
            aux->suivant =l;
            return aux;
        }
        else{
            if(strcmp(jv.titre, l->v.titre) == 0){
                printf("élément déjà présent\n");
                return l;
            }
            else{
                l->suivant = ajouter(l->suivant,jv);
                return l;
            }
        }
    }

}

pel supprimer(pel l, char titre[50]){

    pel aux;
    if(l==NULL){
        printf("liste vide : element absent\n");
        return l;
    }
    else{
        if(strcmp(titre, l->v.titre) < 0){
            printf("element absent\n");
            return l;
        }
        else{
            if(strcmp(titre, l->v.titre) == 0){
                aux=l;
                l=l->suivant;
                printf("element supprime\n");
                free(aux);
                return l;
            }
            else{
                l->suivant=supprimer(l->suivant,titre);
                return l;
            }
        }
    }

}

jv saisiejv(){

    jv jv = {0};

    system("cls");
    printf("AJOUT D'UN JEU :\n\n");

    printf("Titre : ");
    fflush(stdin);
    gets(jv.titre);
    printf("Plate-forme d'utilisation (1 Windows / 2 MacOS / 3 Linux) : ");
    do{
        scanf("%i", &jv.plateforme);
        if(jv.plateforme < 1 || jv.plateforme > 3) printf("ERREUR : Selectionnez une plate-forme existante\n");
    }while(jv.plateforme < 1 || jv.plateforme > 3);
    printf("Annee de sortie : ");
    scanf("%i", &jv.annee);
    printf("Age minimal : ");
    scanf("%i", &jv.agemin);
    printf("Type : ");
    fflush(stdin);
    gets(jv.type);
    printf("Nombre d'exemplaires possedes : ");
    scanf("%i", &jv.nbexemplaire);

    printf("\n");
    system("PAUSE");
    return jv;

}

void afficherliste(pel l){

    system("cls");
    printf("LISTE DES JEUX POSSEDES :\n\n");

    while(l != NULL){

        pel tmp = l;
        printf("Titre : %s\n", tmp->v.titre);
        printf("Plate-forme d'utilisation : ");
        if(tmp->v.plateforme == 1) printf("Windows\n");
        else if(tmp->v.plateforme == 2) printf("MacOS\n");
        else printf("Linux\n");
        printf("Annee de sortie : %i\n", tmp->v.annee);
        printf("Age minimal : %i\n", tmp->v.agemin);
        printf("Type : %s\n", tmp->v.type);
        printf("Nombre d'exemplaires possedes : %i\n\n", tmp->v.nbexemplaire);

        l = l->suivant;

    }

    system("PAUSE");

}

void recherchetype(pel l){

    char type[20];

    system("cls");
    printf("RECHERCHE PAR TYPE :\n\n");

    printf("Saisissez un type de jeu : ");
    fflush(stdin);
    gets(type);

    printf("\nVoici les jeux de type %s disponibles :\n\n", type);

    while(l != NULL){

        pel tmp = l;
        if(strcmp(tmp->v.type, type) == 0){
            printf("Titre : %s\n", tmp->v.titre);
            printf("Plate-forme d'utilisation : ");
            if(tmp->v.plateforme == 1) printf("Windows\n");
            else if(tmp->v.plateforme == 2) printf("MacOS\n");
            else printf("Linux\n");
            printf("Annee de sortie : %i\n", tmp->v.annee);
            printf("Age minimal : %i\n", tmp->v.agemin);
            printf("Type : %s\n", tmp->v.type);
            printf("Nombre d'exemplaires possedes : %i\n\n", tmp->v.nbexemplaire);
        }
        l = l->suivant;

    }

    system("PAUSE");

}

void affichenbjeux(pel l){

    int nbjeuxglobal = 0, nbjeuxdifferents = 0;

    system("cls");
    printf("NOMBRE DE JEUX DISPONIBLES :\n\n");

    while(l != NULL){

        pel tmp = l;
        printf("Titre : %s\n", tmp->v.titre);
        printf("Nombre d'exemplaires possedes : %i\n\n", tmp->v.nbexemplaire);
        nbjeuxdifferents++;
        nbjeuxglobal += tmp->v.nbexemplaire;
        l = l->suivant;

    }

    printf("Il y a %i jeux differents et un total de %i exemplaires disponibles\n\n", nbjeuxdifferents, nbjeuxglobal);
    system("PAUSE");

}

void affichenbjeuxage(pel l){

    int nbjeuxglobal = 0, nbjeuxdifferents = 0, age;

    system("cls");
    printf("NOMBRE DE JEUX DISPONIBLES POUR UN AGE DONNE :\n\n");

    printf("Saisir un age minimum : ");
    scanf("%i", &age);

    printf("\n");

    while(l != NULL){

        pel tmp = l;
        if(tmp->v.agemin == age){
            printf("Titre : %s\n", tmp->v.titre);
            printf("Nombre d'exemplaires possedes : %i\n\n", tmp->v.nbexemplaire);
            nbjeuxdifferents++;
            nbjeuxglobal += tmp->v.nbexemplaire;
        }
        l = l->suivant;

    }

    printf("Il y a %i jeux differents convenant aux personnes de %i ans et un total de %i exemplaires disponibles\n\n", nbjeuxdifferents, age, nbjeuxglobal);
    system("PAUSE");

}

void classement(pel l){

    //je n'ai pas eu le temps de finir cette partie

}

//il y a une erreur dans cette fonction mais le temps m'a manqué pour trouver où elle etait

/*char supprimerjv(){

    char titre[50] = {0};

    system("cls");
    printf("SUPPRESSION D'UN JEU :\n\n");

    printf("Saisir le titre du jeu a supprimer : ");
    fflush(stdin);
    gets(titre);

    printf("\n");
    system("PAUSE");

    return titre;

}*/

int main()
{

    int select;
    pel l = NULL;

    while(1){

        system("cls");
        printf("MENU PRINCIPAL :\n\n");
        printf("1 - Ajouter un jeu\n");
        printf("2 - Afficher la liste des jeux possedes\n");
        printf("3 - Recherche par type de jeux\n");
        printf("4 - Afficher le nombre de jeux possedes\n");
        printf("5 - Supprimer un jeux de la bibliotheque\n");
        printf("6 - Afficher le nombre de jeux possedes pour un age minimal donne\n");
        printf("7 - Classer les jeux du plus recent au plus ancien\n\n");
        printf("0 - Quitter\n\n");

        scanf("%i", &select);

        switch(select){

        case 0 : exit(1);
        break;

        case 1 : l = ajouter(l, saisiejv());
        break;

        case 2 : afficherliste(l);
        break;

        case 3 : recherchetype(l);
        break;

        case 4 : affichenbjeux(l);
        break;

        case 5 : //l = supprimer(l, supprimerjv()); voir ligne 234
        break;

        case 6 : affichenbjeuxage(l);
        break;

        case 7 : classement(l);
        break;

        default :
            printf("\nErreur : rentrez une valeur entre 0 et 7\n");
            system("PAUSE");
        break;

        }

    }

}
