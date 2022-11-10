/*

    fonctions permettant la detection des chaines et leur parametrage

*/

#include <stdlib.h>
#include <SDL.h>

#include "../include/chaines.h"
#include "../include/constantes.h"
#include "../include/pile.h"

int resetChaine(chaineStruct chaine[MAX_CHAINE], int nbChaine)
{
    //declaration des variables
    int c, p, d;

    //reset des champs de chaine[i]
    for(c = 0; c < nbChaine; c++)
    {
        chaine[c].complete = false;
        chaine[c].nbLiberte = 0;
        for(p = 0; p < chaine[c].nbPierre; p++)
        {
            chaine[c].pierre[p].couleur = LIBRE;
            chaine[c].pierre[p].isChained = false;
            for(d = 0; d < 4; d++)
            {
                chaine[c].pierre[p].liberte[d] = 0;
                chaine[c].pierre[p].voisine[d] = 0;
            }
            chaine[c].pierre[p].nbLiberte = 0;
            chaine[c].pierre[p].nbVoisine = 0;
            chaine[c].pierre[p].position.x = 0;
            chaine[c].pierre[p].position.y = 0;
        }
        chaine[c].nbPierre = 0;
    }

    return 0;
}

int paramChaine(pierreStruct goban[19][19], chaineStruct chaine[MAX_CHAINE], int nbChaine, SDL_Surface* surface[NB_SURFACE], bool debug)
{
    //declaration des variables
    pierreStruct gobanAlt[19][19] = {LIBRE};
    pel pileIntersection = NULL;
    coordonnee curseur = {0};
    int i, j;

    //copie du plateau dans un plateau alternatif
    copieGoban(goban, gobanAlt);

    //detection des chaines
    for(j = 0; j < 19; j++)
    {
        for(i = 0; i < 19; i++)
        {
            if(gobanAlt[i][j].couleur != LIBRE && !gobanAlt[i][j].isChained) //si c'est une case avec une pierre et qu'elle ne fait pas deja partie d'une chaine
            {
                curseur.x = i;
                curseur.y = j;
                while(!chaine[nbChaine].complete) //boucle jusqu'a ce que la chaine soit complete
                {
                    //ajouter les pierres a la chaine
                    if(!gobanAlt[curseur.x][curseur.y].isChained) addPierreToChaine(chaine, nbChaine, gobanAlt, curseur.x, curseur.y);

                    if(gobanAlt[curseur.x][curseur.y].nbVoisine == 0) //si la pierre n'a aucune pierres voisines
                    {
                        curseur = aucuneVoisine(chaine, nbChaine, gobanAlt, curseur, &pileIntersection);
                    }
                    else if(gobanAlt[curseur.x][curseur.y].nbVoisine == 1) //si la pierre n'a qu'une seule pierre voisine
                    {
                        curseur = uneVoisine(gobanAlt, curseur);
                    }
                    else if(gobanAlt[curseur.x][curseur.y].nbVoisine > 1) //si la pierre a plusieurs pierres voisines
                    {
                        curseur = plusieursVoisines(gobanAlt, curseur, &pileIntersection);
                    }
                }
                chaine[nbChaine].numChaine = nbChaine;
                nbChaine++;
                pileIntersection = NULL;
            }
        }
    }

    //si mode debug alors affiche les chaines
    if(debug) afficheChaine(gobanAlt, chaine, nbChaine, surface);

    return nbChaine;
}

void copieGoban(pierreStruct goban[19][19], pierreStruct gobanAlt[19][19])
{
    //declaration des variables
    int i, j;

    //copie du plateau dans un plateau alternatif
    for(j = 0; j < 19; j++)
    {
        for(i = 0; i < 19; i++) gobanAlt[i][j] = goban[i][j];
    }
}

coordonnee aucuneVoisine(chaineStruct chaine[MAX_CHAINE], int nbChaine, pierreStruct gobanAlt[19][19], coordonnee curseur, pel* pileIntersection)
{
    if(*pileIntersection == NULL) chaine[nbChaine].complete = true;
    else
    {
        *pileIntersection = depiler(*pileIntersection, &curseur);
        if(gobanAlt[curseur.x][curseur.y].nbVoisine > 1) *pileIntersection = empiler(*pileIntersection, curseur);
        curseur = moveCurseur(gobanAlt, curseur);
    }

    return curseur;
}

coordonnee uneVoisine(pierreStruct gobanAlt[19][19], coordonnee curseur)
{
    curseur = moveCurseur(gobanAlt, curseur);

    return curseur;
}

coordonnee plusieursVoisines(pierreStruct gobanAlt[19][19], coordonnee curseur, pel* pileIntersection)
{
    *pileIntersection = empiler(*pileIntersection, gobanAlt[curseur.x][curseur.y].position);

    curseur = moveCurseur(gobanAlt, curseur);

    return curseur;
}

coordonnee moveCurseur(pierreStruct gobanAlt[19][19], coordonnee curseur)
{
    if(gobanAlt[curseur.x][curseur.y].voisine[DOWN] == true)
    {
        gobanAlt[curseur.x][curseur.y].nbVoisine--;
        gobanAlt[curseur.x][curseur.y].voisine[DOWN] = false;
        curseur.x++;
        gobanAlt[curseur.x][curseur.y].nbVoisine--;
        gobanAlt[curseur.x][curseur.y].voisine[UP] = false;
    }
    else if(gobanAlt[curseur.x][curseur.y].voisine[UP] == true)
    {
        gobanAlt[curseur.x][curseur.y].nbVoisine--;
        gobanAlt[curseur.x][curseur.y].voisine[UP] = false;
        curseur.x--;
        gobanAlt[curseur.x][curseur.y].nbVoisine--;
        gobanAlt[curseur.x][curseur.y].voisine[DOWN] = false;
    }
    else if(gobanAlt[curseur.x][curseur.y].voisine[RIGHT] == true)
    {
        gobanAlt[curseur.x][curseur.y].nbVoisine--;
        gobanAlt[curseur.x][curseur.y].voisine[RIGHT] = false;
        curseur.y++;
        gobanAlt[curseur.x][curseur.y].nbVoisine--;
        gobanAlt[curseur.x][curseur.y].voisine[LEFT] = false;
    }
    else if(gobanAlt[curseur.x][curseur.y].voisine[LEFT] == true)
    {
        gobanAlt[curseur.x][curseur.y].nbVoisine--;
        gobanAlt[curseur.x][curseur.y].voisine[LEFT] = false;
        curseur.y--;
        gobanAlt[curseur.x][curseur.y].nbVoisine--;
        gobanAlt[curseur.x][curseur.y].voisine[RIGHT] = false;
    }

    return curseur;
}

void addPierreToChaine(chaineStruct chaine[MAX_CHAINE], int nbChaine, pierreStruct gobanAlt[19][19], int iAlt, int jAlt)
{
    chaine[nbChaine].pierre[chaine[nbChaine].nbPierre] = gobanAlt[iAlt][jAlt];
    chaine[nbChaine].pierre[chaine[nbChaine].nbPierre].position.x = iAlt;
    chaine[nbChaine].pierre[chaine[nbChaine].nbPierre].position.y = jAlt;

    chaine[nbChaine].nbPierre++;
    chaine[nbChaine].nbLiberte += gobanAlt[iAlt][jAlt].nbLiberte;

    gobanAlt[iAlt][jAlt].isChained = true;
}

void afficheChaine(pierreStruct gobanAlt[19][19], chaineStruct chaine[MAX_CHAINE], int nbChaine, SDL_Surface* surface[NB_SURFACE])
{
    //declaration des variables
    SDL_Rect positionSurface;
    int n = 0, p;

    for(n = 0; n < nbChaine; n++)
    {
        for(p = 0; p < chaine[n].nbPierre; p++)
        {
            positionSurface.x = (PIERRE_ORIGINE_x-surface[VOISINE1]->w/2)+chaine[n].pierre[p].position.x*CASE;
            positionSurface.y = (PIERRE_ORIGINE_y-surface[VOISINE1]->h/2)+chaine[n].pierre[p].position.y*CASE;
            if(chaine[n].pierre[p].couleur == BLANC) SDL_BlitSurface(surface[CHAINE_BLANCHE], NULL, surface[SCREEN], &positionSurface);
            else if(chaine[n].pierre[p].couleur == NOIR) SDL_BlitSurface(surface[CHAINE_NOIR], NULL, surface[SCREEN], &positionSurface);
        }
    }
}

