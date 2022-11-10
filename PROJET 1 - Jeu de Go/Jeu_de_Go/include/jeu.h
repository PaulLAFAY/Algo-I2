/*

    prototype des fonctions permettant la gestion du jeu

*/

#ifndef DEF_JEU
#define DEF_JEU

#include "../include/constantes.h"

void jeu(SDL_Surface* surface[NB_SURFACE], int nbTour, pierreStruct tableauPlateau[19][19], int tableauScore[2], Mix_Chunk* tableauSon[2], Mix_Music* musique, pel pile, bool* booleenDebug, bool booleenBot);
coordonnee coupJoueur(SDL_Surface* surface[NB_SURFACE], pierreStruct tableauPlateau[19][19], mouse souris, int nbTour, coordonnee caseSelect);
coordonnee coupBot(pierreStruct goban[19][19], int score[2], int* tour, pel* pile, bool bot, int* passerBlanc, int* passerNoir);
void placerCoup(pierreStruct tableauPlateau[19][19], int tableauScore[2], int* nbTour, pel* pile, bool booleenBot, int* passerBlanc, int* passerNoir, coordonnee caseSelect);
void retour(int* tour, pel* pile, pierreStruct goban[19][19], int score[2], bool bot);
int testFin(int passerBlanc, int passerNoir);
void initPositionJeu(SDL_Rect* positionOrigine, SDL_Rect* positionPlateau, SDL_Rect positionTexte[5], SDL_Rect positionIcone[3], SDL_Surface* surface[NB_SURFACE]);
void afficheSprites(SDL_Surface* surface[NB_SURFACE], SDL_Rect positionOrigine, SDL_Rect positionPlateau, SDL_Rect positionTexte[5], SDL_Rect positionIcone[4], int nbTour, mouse souris, int* boutonSelectionne, bool booleenDebug, bool booleenBot, int tableauScore[2]);
void afficheScore(int tableauScore[2], SDL_Surface* surface[NB_SURFACE]);

#endif // DEF_JEU
