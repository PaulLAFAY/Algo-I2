/*

    prototypes des fonctions permettant le parametrage des pierres

*/

#ifndef DEF_PIERRES
#define DEF_PIERRES

#include "../include/constantes.h"

void paramPierres(pierreStruct goban[19][19], SDL_Surface* surface[NB_SURFACE], bool debug);
void setVoisine(pierreStruct goban[19][19], SDL_Surface* surface[NB_SURFACE], bool debug, int i, int j);
void setLiberte(pierreStruct goban[19][19], SDL_Surface* surface[NB_SURFACE], bool debug, int i, int j);


#endif // DEF_PIERRES
