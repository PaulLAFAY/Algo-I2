#include <stdio.h>
#include <stdlib.h>

void saisie(int n, int stock[n]){

    printf("Saisir le stock des %i articles :\n\n",n);
    for(int i = 0; i < n; i++){
        printf("Nb article %i : ", i+1);
        scanf("%i", &stock[i]);
    }

}

void afficheinv(int n, int stock[n]){

    int i;

    printf("Inventaire :\n\n");
    for(i = 0; i < n; i++) printf("Article %i : %i\n", i+1, stock[i]);

    printf("\n\n0 - Menu principal\n\n");
    scanf("%i", &i);

}

void afficheart(int n, int stock[n]){

    printf("Selectionner un article : ");
    int select;
    scanf("%i", &select);
    printf("\nStock de l'article %i : %i", select, stock[select-1]);

    printf("\n\n0 - Menu principal\n\n");
    scanf("%i", &select);

}

void commande(int n, int stock[n]){

    int select, nb;
    printf("Selectionner un article : ");
    scanf("%i", &select);
    printf("Quantite a prelever de cet article : ");
    scanf("%i", &nb);

    if(stock[select-1] >= nb){
        stock[select-1] -= nb;
        if(stock[select-1] < 5) printf("\n/!\ ATTENTION /!\ Il reste moins de 5 exemplaires de l'article %i", select);
        printf("\n\nNouveau stock de l'article %i : %i", select, stock[select-1]);
    }
    else printf("\nCommande impossible");

    printf("\n\n0 - Menu principal\n\n");
    scanf("%i", &select);

}

void reappro(int n, int stock[n]){

    int select, nb;
    printf("Selectionner un article : ");
    scanf("%i", &select);
    printf("Quantite a reapprovisionner de cet article : ");
    scanf("%i", &nb);
    stock[select-1] += nb;
    printf("\nNouveau stock de l'article %i : %i", select, stock[select-1]);

    printf("\n\n0 - Menu principal\n\n");
    scanf("%i", &select);

}

int main(){

    int n = 5, quit = 0, select;
    int stock[n];

    saisie(n, stock);

    do{

        system("cls");

        printf("1 - Afficher l'inventaire\n2 - Afficher la quantite d'un article precis\n3 - Effectuer une commande\n4 - Reaprovisionner un article\n\n0 - Quitter\n\n");
        scanf("%i", &select);

        system("cls");

        switch(select){

            case 0 : quit = 1;
            break;

            case 1 : afficheinv(n, stock);
            break;

            case 2 : afficheart(n, stock);
            break;

            case 3 : commande(n, stock);
            break;

            case 4 : reappro(n, stock);
            break;

            default : printf("ERREUR");

        }

    }while(quit == 0);

    return 0;

}
