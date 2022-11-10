/*

    prototypes des fonctions permettant la detection des chaines et leur parametrage

*/

#ifndef DEF_CHAINES
#define DEF_CHAINES

#include "../include/constantes.h"

int resetChaine(chaineStruct chaine[MAX_CHAINE], int nbChaine);
int paramChaine(pierreStruct goban[19][19], chaineStruct chaine[MAX_CHAINE], int nbChaine, SDL_Surface* surface[NB_SURFACE], bool debug);
void copieGoban(pierreStruct tableauPlateau[19][19], pierreStruct tableauPlateauAlt[19][19]);
coordonnee aucuneVoisine(chaineStruct chaine[MAX_CHAINE], int nbChaine, pierreStruct tableauPlateauAlt[19][19], coordonnee curseur, pel* pileIntersection);
coordonnee uneVoisine(pierreStruct tableauPlateauAlt[19][19], coordonnee curseur);
coordonnee plusieursVoisines(pierreStruct tableauPlateauAlt[19][19], coordonnee curseur, pel* pileIntersection);
coordonnee moveCurseur(pierreStruct tableauPlateauAlt[19][19], coordonnee curseur);
void addPierreToChaine(chaineStruct chaine[MAX_CHAINE], int nbChaine, pierreStruct tableauPlateauAlt[19][19], int iAlt, int jAlt);
void afficheChaine(pierreStruct tableauPlateau[19][19], chaineStruct chaine[MAX_CHAINE], int nbChaine, SDL_Surface* surface[NB_SURFACE]);

#endif // DEF_CHAINES
