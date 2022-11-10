/*

    prototype des fonctions permettant la gestion des fichiers

*/

#ifndef DEF_FICHIERS
#define DEF_FICHIERS

#include "../include/constantes.h"

settings getSettings();
SDL_Surface* setSettings(int parametres, SDL_Surface* screen, int val);

void reprendreJeu(SDL_Surface* surface[NB_SURFACE], Mix_Chunk* tableauSon[2], Mix_Music* musique, pel pile, bool* booleenDebug);
void nouveauJeu(SDL_Surface* surface[NB_SURFACE], Mix_Chunk* tableauSon[2], Mix_Music* musique, pel pile, bool* booleenDebug);
void save(pierreStruct tableauPlateau[19][19], int nbTour, int tableauScore[2], bool booleenBot);

#endif // DEF_FICHIERS
