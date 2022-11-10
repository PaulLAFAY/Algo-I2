#include <stdio.h>
#include <stdlib.h>

typedef struct pat{

    char nom_patient[20];
    int demande;     //1 prendre rdv      2 venir pour un rdv
    char nom_medecin;
    int heure;
    int minute;

}patient;

typedef struct el * pel;

typedef struct el{

    patient v;
    pel suivant;

}tel;

pel creeElem(patient val){

    pel tmp;
    tmp=(pel)malloc(sizeof(tel));
    tmp->v=val;
    tmp->suivant=NULL;

    return tmp;

}

pel ajouter(pel f, patient val){

    pel aux =creeElem(val);
    pel tmp = f;
    if(f==NULL) return aux;
    else{
        while(tmp->suivant != NULL) tmp=tmp->suivant;
        tmp->suivant=aux;
        return f;
    }

}

pel supprimer(pel f, patient *pval){

    pel tmp=f;
    if(f==NULL) printf("File vide");
    else{
        f=f->suivant;
        *pval = tmp->v;
        free(tmp);
    }

    return f;

}

pel saisieNouveauPatient(pel fp){

    patient pat = {0};

    system("cls");

    //saisie du patient
    printf("Saisir les informations du nouveau patient :\n\n");
    printf("Nom : ");
    fflush(stdin);
    gets(pat.nom_patient);
    do{
        printf("Demande (1 - prendre rdv / 2 - venir pour un rdv) : ");
        scanf("%i", &pat.demande);
        if(pat.demande < 1 || pat.demande > 2) printf("ERREUR : 1 et 2 sont les seuls valeurs possibles\n");
    }while(pat.demande < 1 || pat.demande > 2);
    do{
        printf("Nom du medecin (X, Y ou Z) : ");
        fflush(stdin);
        scanf("%c", &pat.nom_medecin);
        if(pat.nom_medecin != 'X' && pat.nom_medecin != 'Y' && pat.nom_medecin != 'Z') printf("ERREUR : les seuls noms possibles sont X, Y et Z\n");
    }while(pat.nom_medecin != 'X' && pat.nom_medecin != 'Y' && pat.nom_medecin != 'Z');
    do{
        printf("Heure d'arrivee du patient (heure) :\n");
        scanf("%i", &pat.heure);
        if(pat.heure < 8 || pat.heure > 18) printf("ERREUR : l'heure darrivee du patient doit etre comprise dans les horaires d'ouverture du cabinet\n");
    }while(pat.heure < 8 || pat.heure > 18);
    do{
        printf("Heure d'arrivee du patient (minute) :\n");
        scanf("%i", &pat.minute);
        if(pat.minute < 0 || pat.minute > 59) printf("ERREUR : les minutes doivent etre comprises entre 0min et 59min\n");
    }while(pat.minute < 0 || pat.minute > 59);

    //recap du patient
    system("cls");
    printf("Saisir les informations du nouveau patient :\n\n");
    printf("Nom : %s\n", pat.nom_patient);
    printf("Demande : ");
    if(pat.demande == 1) printf("prendre un rdv\n");
    else printf("venir pour un rdv\n");
    printf("Nom du medecin : %c\n", pat.nom_medecin);
    printf("Heure d'arrivee du patient : %ih %imin\n\n", pat.heure, pat.minute);

    //ajout a la file puis quitter
    fp = ajouter(fp, pat);
    printf("Le patient a ete ajoute a la file principale\n");
    printf("0 - Menu principal\n\n");
    int i;
    scanf("%i", &i);
    return fp;

}

void afficherPat(patient pat){

    //recap patient
    printf("Nom : %s\n", pat.nom_patient);
    printf("Demande : ");
    if(pat.demande == 1) printf("prendre un rdv\n");
    else printf("venir pour un rdv\n");
    printf("Nom du medecin : %c\n", pat.nom_medecin);
    printf("Heure d'arrivee du patient : %ih %imin\n\n", pat.heure, pat.minute);

}

void afficherCabinet(pel fp, pel fx, pel fy, pel fz){

    system("cls");
    int i = 1;

    printf("FILE D'ATTENTE PRINCIPALE\n\n\n\n");
    if(fp == NULL) printf("La file d'attente principale est vide\n");
    while(fp != NULL){

        pel tmp = fp;
        printf("PATIENT %i :\n", i);
        afficherPat(tmp->v);
        i++;
        fp = fp->suivant;

    }

    i = 1;

    printf("\n\n\nFILE D'ATTENTE DU MEDECIN X\n\n\n\n");
    if(fx == NULL) printf("La file d'attente du medecin X est vide\n");
    while(fx != NULL){

        pel tmp = fx;
        printf("PATIENT %i :\n", i);
        afficherPat(tmp->v);
        i++;
        fx = fx->suivant;

    }

    i = 1;

    printf("\n\n\nFILE D'ATTENTE DU MEDECIN Y\n\n\n\n");
    if(fy == NULL) printf("La file d'attente du medecin Y est vide\n");
    while(fy != NULL){

        pel tmp = fy;
        printf("PATIENT %i :\n", i);
        afficherPat(tmp->v);
        i++;
        fy = fy->suivant;

    }

    i = 1;

    printf("\n\n\nFILE D'ATTENTE DU MEDECIN Z\n\n\n\n");
    if(fz == NULL) printf("La file d'attente du medecin Z est vide\n");
    while(fz != NULL){

        pel tmp = fz;
        printf("PATIENT %i :\n", i);
        afficherPat(tmp->v);
        i++;
        fz = fz->suivant;

    }

    printf("\n\n\n0 - Menu principal\n\n");
    scanf("%i", &i);

}

int main(){

    int select, i;
    pel fp = NULL;
    pel fx = NULL;
    pel fy = NULL;
    pel fz = NULL;
    patient pat = {0};

    while(1){

        system("cls");

        printf("1 - Ajouter un patient a la file d'attente principale\n");
        printf("2 - Supprimer un patient de la file d'attente principale\n");
        printf("3 - Supprimer un patient d'une des files d'attente secondaires\n");
        printf("4 - Afficher les patients presents dans les quatre files d'attente\n\n");
        printf("0 - Quitter\n\n");

        scanf("%i", &select);

        switch(select){

        //ajout d'un patient dans la file principale
        case 1 : fp = saisieNouveauPatient(fp);
        break;

        //supprimer un patient dans la file principale et l'orienter en fonction de sa demande
        case 2 :

            system("cls");

            if(fp != NULL){
                fp = supprimer(fp, &pat);
                if(pat.demande == 1){
                    printf("Informations du patient :\n\n");
                    afficherPat(pat);
                    printf("Le patient a ete supprime de la file principale et est parti du caninet\n");
                }
                else if(pat.nom_medecin == 'X'){
                    fx = ajouter(fx, pat);
                    printf("Informations du patient :\n\n");
                    afficherPat(pat);
                    printf("Le patient a ete ajoute a la file du medecin X\n");
                }
                else if(pat.nom_medecin == 'Y'){
                    fy = ajouter(fy, pat);
                    printf("Informations du patient :\n\n");
                    afficherPat(pat);
                    printf("Le patient a ete ajoute a la file du medecin Y\n");
                }
                else if(pat.nom_medecin == 'Z'){
                    fz = ajouter(fz, pat);
                    printf("Informations du patient :\n\n");
                    afficherPat(pat);
                    printf("Le patient a ete ajoute a la file du medecin Z\n");
                }
            }
            else printf("La file principale est vide\n");

            printf("0 - Menu principal\n\n");
            scanf("%i", &i);

        break;

        //supprimer un patient d'une des files secondaires
        case 3 :

            system("cls");

            //selection de la file
            char medecin = 0;
            do{
                printf("Selectionner la file d'attente d'un medecin (X, Y ou Z) : ");
                fflush(stdin);
                scanf("%c", &medecin);
                if(medecin != 'X' && medecin != 'Y' && medecin != 'Z') printf("ERREUR : les seuls noms possibles sont X, Y et Z\n");
            }while(medecin != 'X' && medecin != 'Y' && medecin != 'Z');

            printf("\n");

            //suppression du patient si la file n'est pas vide
            if(medecin == 'X' && fx != NULL){
                fx = supprimer(fx, &pat);
                printf("Informations du patient :\n\n");
                afficherPat(pat);
                printf("Le patient a termine son rdv et est sorti du cabinet\n");
            }
            else if(medecin == 'Y' && fy != NULL){
                fy = supprimer(fy, &pat);
                printf("Informations du patient :\n\n");
                afficherPat(pat);
                printf("Le patient a termine son rdv et est sorti du cabinet\n");
            }
            else if(medecin == 'Z' && fz != NULL){
                fz = supprimer(fz, &pat);
                printf("Informations du patient :\n\n");
                afficherPat(pat);
                printf("Le patient a termine son rdv et est sorti du cabinet\n");
            }
            else printf("La file selectionnee est vide\n");

            printf("0 - Menu principal\n\n");
            scanf("%i", &i);

        break;

        //affiche les patients presents dans les 4 files
        case 4 : afficherCabinet(fp, fx, fy, fz);
        break;

        default : exit(1);
        break;

        }

    }

}
