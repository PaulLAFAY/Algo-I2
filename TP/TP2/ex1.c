#include <stdio.h>
#include <stdlib.h>

typedef struct nbr{

    int num;
    int den;

}nbR;

void saisieTableauRationnel(nbR trat[], int nbrat){



}

void afficherRationnel(){}

void comparerRationnel(){}

void sommeRationnel(){}

void plusGrandRationnel(){}

int main(){

    int select, quitte = 0, nbrat;

    printf("Combien de nombres dans le tableau ?        ");
    scanf("%i", &nbrat);

    nbR *trat = (nbR*)malloc(nbrat*sizeof(nbrat));

    do{

        system("cls");

        printf("1 - Saisir un tableau de rationnel\n");
        printf("2 - Afficher un rationnel du tableau\n");
        printf("3 - Comparer 2 rationnels du tableau\n");
        printf("4 - Afficher la somme de 2 rationnels du tableau\n");
        printf("5 - Affiche le plus grand rationnel du tableau\n\n");
        printf("0 - Quitter\n\n");

        scanf("%i", &select);

        switch(select){

        case 1 : saisieTableauRationnel(trat, nbrat);
        break;

        case 2 : afficherRationnel(trat);
        break;

        case 3 : comparerRationnel(trat);
        break;

        case 4 : sommeRationnel(trat);
        break;

        case 5 : plusGrandRationnel(trat);
        break;

        case 0 : quitte = 1;
        break;

        default : printf("ERREUR");
        break;


        }

    }while(quitte == 0);


}
