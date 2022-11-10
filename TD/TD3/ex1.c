#include <stdio.h>
#include <stdlib.h>

typedef struct st{

    char nom[20];
    char prenom[20];
    float noteMath[3];
    float noteInfo[5];

}stdt;

void saisie(stdt etu[], int nbEtu){

    system("cls");

    printf("Saisir %i etudiants : \n\n", nbEtu);

    for(int i = 0; i < nbEtu; i++){
        printf("Etudiant %i :\nNom : ", i+1);
        fflush(stdin);
        scanf("%s", &etu[i].nom);
        printf("Prenom : ");
        fflush(stdin);
        scanf("%s", &etu[i].prenom);
        printf("Notes aux 3 controles de mathematique :\n");
        scanf("%i%i%i", &etu[i])
    }

}

int main()
{

    int nbEtudiants;
    printf("Combien y a-t-il d'etudiants dans cette promotion ?\n\n");
    scanf("%i", &nbEtudiants);
    stdt *etudiants = (stdt*)malloc(nbEtudiants*sizeof(stdt));

    saisie(etudiants, nbEtudiants);

}
