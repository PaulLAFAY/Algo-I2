/*

    Projet informatique I2 : Jeu de Go

    Réalisé par LAFAY Paul et PRUVOT Clara

*/

#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../include/constantes.h"
#include "../include/general.h"
#include "../include/menu.h"
#include "../include/parametres.h"
#include "../include/fichiers.h"

int main(int argc, char *argv[])
{
    //declaration des variables
    SDL_Surface* surface[NB_SURFACE] = {NULL};
    Mix_Music* musique = NULL;
    Mix_Chunk* son[2] = {NULL};
    pel pile = NULL;
    int selection = AUCUNE_SELECTION;
    bool debug = false;

    //redirection du fichier stdout vers la console
    freopen("CON", "w", stdout);
    FILE* ctt = fopen("CON", "w");

    //initialisation de la SDL
    surface[SCREEN] = initSDL(surface[SCREEN]);
    initSurface(surface);

    //initialisation de SDL_mixer
    initMIXER();
    //initialiser la musique
    musique = initMusic(musique);
    //initialiser les sons
    initSound(son);

    while(1)
    {
        selection = playMenu(surface, son, musique); //gestion du menu

        if(selection == NOUVELLE_PARTIE) //le joueur a clique sur nouvelle partie
        {
            nouveauJeu(surface, son, musique, pile, &debug);//nouvelle partie
        }
        else if(selection == REPRENDRE_LA_PARTIE) //le joueur a clique sur reprendre la partie
        {
            reprendreJeu(surface, son, musique, pile, &debug);//reprendre la partie
        }
        else if(selection == PARAMETRES) //le joueur a clique sur parametres
        {
            playParametres(surface, son, musique); //gestion des parametres
        }
    }

    //fermeture du fichier de redirection
    fclose(ctt);

    return EXIT_SUCCESS;
}

