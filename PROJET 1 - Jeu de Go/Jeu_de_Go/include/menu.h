/*

    prototype des fonctions permettant l'affichage et la gestion du menu

*/

#ifndef DEF_MENU
#define DEF_MENU

#include "../include/constantes.h"

int playMenu(SDL_Surface* surface[NB_SURFACE], Mix_Chunk* tableauSon[2], Mix_Music* musique);
void initPositionMenu(SDL_Rect* positionOrigine, SDL_Rect* positionTitre, SDL_Rect positionBouton[3], SDL_Surface* surface[NB_SURFACE]);

#endif // DEF_MENU
