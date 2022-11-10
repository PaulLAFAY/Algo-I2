#include <stdio.h>
#include <stdlib.h>

typedef struct article{

    char nom[20];
    char ref[20];
    int quant[10];
    int prix[10];

}article;

void saisie(int* pnbart, int nbmag, article art[100]){

    int quit = 0, i, nbart = *pnbart;

    do{

        system("cls");

        nbart++;

        printf("ARTICLE %i :\n\n", nbart);

        printf("Nom : ");
        fflush(stdin);
        scanf("%s", &art[nbart-1].nom);

        printf("Reference : ");
        fflush(stdin);
        scanf("%s", &art[nbart-1].ref);

        printf("Quantite en stock et prix dans les differents magasins :\n");
        for(i = 0; i < nbmag;i++){
            printf("Quantite en magasin %i : ", i+1);
            scanf("%i", &art[nbart-1].quant[i]);
            printf("Prix en magasin %i : ", i+1);
            scanf("%i", &art[nbart-1].prix[i]);
        }

        printf("\nQuitter (1 - oui | 0 - non)\n\n");
        scanf("%i", &quit);

    }while(quit == 0);

    *pnbart = nbart;

}

void affichestock(int nbart, int nbmag, article art[100]){

    system("cls");

    int i, j;

    for(i = 0; i < nbart; i++){

        printf("ARTICLE %i :\n\n", i+1);
        printf("Nom : %s\n", art[i].nom);
        printf("Reference : %s\n", art[i].ref);
        printf("Quantite en stock et prix dans les differents magasins :\n");
        for(j = 0; j < nbmag; j++){
            printf("Quantite en magasin %i : %i\n", j+1, art[i].quant[j]);
            printf("Prix en magasin %i : %i\n", j+1, art[i].prix[j]);
        }
        printf("\n");

    }

    printf("0 - Quitter\n\n");
    scanf("%i", &nbart);

}

void afficheart(int nbart, int nbmag, article art[100]){

    system("cls");

    int select, i;

    printf("Selectionner un article (par son numero) a afficher : ");
    scanf("%i", &select);

    system("cls");

    printf("ARTICLE %i :\n\n", select);
    printf("Nom : %s\n", art[select-1].nom);
    printf("Reference : %s\n", art[select-1].ref);
    printf("Quantite en stock et prix dans les differents magasins :\n");
    for(i = 0; i < nbmag; i++){
        printf("Quantite en magasin %i : %i\n", i+1, art[select-1].quant[i]);
        printf("Prix en magasin %i : %i\n", i+1, art[select-1].prix[i]);
    }

    printf("\n0 - Quitter\n\n");
    scanf("%i", &select);

}

void prixmoyart(int nbart, int nbmag, article art[100]){

    system("cls");

    int select, somme = 0, i;
    float moy = 0;

    printf("Selectionner un article (par son numero) : ");
    scanf("%i", &select);

    for(i = 0; i < nbmag; i++) somme += art[select-1].prix[i];
    moy = somme / nbmag;

    printf("\nLe prix moyen de cette article est : %f", moy);

    printf("\n\n0 - Quitter\n\n");
    scanf("%i", &select);

}

void prixmaxmag(int nbart, int nbmag, article art[100]){

    system("cls");

    int select, magmax = 0, i, compteur = 0;

    printf("Selectionner un article : ");
    scanf("%i", &select);

    for(i = 0; i < nbmag; i++) {
        if(art[select-1].prix[i] > art[select-1].prix[magmax]) magmax = i;
    }

    for(i = 0; i < nbmag; i++) {
        if(art[select-1].prix[i] == art[select-1].prix[magmax]) compteur++;
    }

    int tmag[compteur];
    int compteurtab = 0;

    for(i = 0; i < nbmag; i++) {
        if(art[select-1].prix[i] == art[select-1].prix[magmax]){
            tmag[compteurtab] = i;
            compteurtab++;
        }
    }

    if(compteur == 1) printf("L'article %i est plus cher dans le magasin %i", select, magmax);
    else {
        printf("L'article %i est plus cher dans les magasins ", select);
        for(i = 0; i < compteur; i++){
            if(i == compteur-1) printf("%i", tmag[i]+1);
            else printf("%i et ", tmag[i]+1);
        }
    }

    printf("\n\n0 - Quitter\n\n");
    scanf("%i", &select);

}

void stockvidemag(int nbart, article art[100]){

    system("cls");

    int select, i, compteur = 0;

    printf("Selectionner un magasin : ");
    scanf("%i", &select);

    system("cls");

    for(i = 0; i < nbart; i++){
        if(art[i].quant[select-1] == 0){
            printf("ARTICLE %i :\n", i+1);
            printf("Nom : %s\n", art[i].nom);
            printf("Reference : %s\n\n", art[i].ref);
            compteur++;
        }
    }
    if(compteur == 0) printf("Le magasin %i possede au moins un exemplaire de chaque articles\n\n", select);

    printf("0 - Quitter\n\n");
    scanf("%i", &select);

}

void commande(int nbart, article art[100]){

    system("cls");

    int cart, cmag, cquant;

    printf("Selectionner un article (par son numero) a commander : ");
    scanf("%i", &cart);
    printf("Selectionner un magasin dans lequel commander : ");
    scanf("%i", &cmag);

    printf("\nARTICLE %i :\n\n", cart);
    printf("Nom : %s\n", art[cart-1].nom);
    printf("Reference : %s\n", art[cart-1].ref);
    printf("Quantite en magasin %i : %i\n", cmag, art[cart-1].quant[cmag-1]);
    printf("Prix en magasin %i : %i\n\n", cmag, art[cart-1].prix[cmag-1]);

    do{
        printf("Quantite a commander : ");
        scanf("%i", &cquant);
        if(cquant > art[cart-1].quant[cmag-1]) printf("\nCommande impossible pour cette quantite\n\n");
    }while(cquant > art[cart-1].quant[cmag-1]);

    art[cart-1].quant[cmag-1] -= cquant;

    printf("\n0 - Quitter\n\n");
    scanf("%i", &cmag);

}

void reappro(int nbart, article art[100]){

    system("cls");

    int cart, cmag, cquant;

    printf("Selectionner un article (par son numero) a commander : ");
    scanf("%i", &cart);
    printf("Selectionner un magasin dans lequel reapprovisionner : ");
    scanf("%i", &cmag);

    printf("\nARTICLE %i :\n\n", cart);
    printf("Nom : %s\n", art[cart-1].nom);
    printf("Reference : %s\n", art[cart-1].ref);
    printf("Quantite en magasin %i : %i\n", cmag, art[cart-1].quant[cmag-1]);
    printf("Prix en magasin %i : %i\n\n", cmag, art[cart-1].prix[cmag-1]);


    printf("Quantite a reapprovisionner : ");
    scanf("%i", &cquant);

    art[cart-1].quant[cmag-1] += cquant;

    printf("\n0 - Quitter\n\n");
    scanf("%i", &cmag);

}

int main(){

    int nbart = 0, nbmag = 3, quit = 0, select;
    article art[100] = {0};

    do{

        system("cls");

        printf("1 - Saisir un article\n2 - Afficher tout le stock\n3 - Afficher un article precis\n4 - Calculer le prix moyen d'un article\n5 - Magasin dans lequel un article est le plus cher\n6 - Stock d'un article vide dans un magasin precis\n7 - Commande dans un magasin\n8 - Ajout en stock dans un magasin\n\n0 - Quitter\n\n");

        scanf("%i", &select);

        switch(select){

            case 1 : saisie(&nbart, nbmag, art);
            break;

            case 2 : affichestock(nbart, nbmag, art);
            break;

            case 3 : afficheart(nbart, nbmag, art);
            break;

            case 4 : prixmoyart(nbart, nbmag, art);
            break;

            case 5 : prixmaxmag(nbart, nbmag, art);
            break;

            case 6 : stockvidemag(nbart, art);
            break;

            case 7 : commande(nbart, art);
            break;

            case 8 : reappro(nbart, art);
            break;

            case 0 : quit = 1;
            break;

            default :
                system("cls");
                printf("ERREUR\n\n0 - Menu principal\n\n");
                scanf("%i", &select);
            break;

        }

    }while(quit == 0);

    return 0;

}
