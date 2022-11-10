/*

    fonctions permettant le parametrage des pierres

*/

#include <SDL.h>

#include "../include/pierres.h"
#include "../include/constantes.h"

void paramPierres(pierreStruct goban[19][19], SDL_Surface* surface[NB_SURFACE], bool debug)
{
    //declaration des variables
    int i, j;

    //detection des pierres voisines et des libertes
    for(j = 0; j < 19; j++)
    {
        for(i = 0; i < 19; i++)
        {
            setVoisine(goban, surface, debug, i, j);
            setLiberte(goban, surface, debug, i, j);
        }
    }
}

void setVoisine(pierreStruct goban[19][19], SDL_Surface* surface[NB_SURFACE], bool debug, int i, int j)
{
    //declaration des variables
    SDL_Rect positionSurface;

    //detection des pierres voisines
    if(goban[i][j].couleur != LIBRE && goban[i][j].couleur == goban[i+1][j].couleur && i < 18) goban[i][j].voisine[DOWN] = true;
    else goban[i][j].voisine[DOWN] = false;
    if(goban[i][j].couleur != LIBRE && goban[i][j].couleur == goban[i-1][j].couleur && i > 0) goban[i][j].voisine[UP] = true;
    else goban[i][j].voisine[UP] = false;
    if(goban[i][j].couleur != LIBRE && goban[i][j].couleur == goban[i][j+1].couleur && j < 18) goban[i][j].voisine[RIGHT] = true;
    else goban[i][j].voisine[RIGHT] = false;
    if(goban[i][j].couleur != LIBRE && goban[i][j].couleur == goban[i][j-1].couleur && j > 0) goban[i][j].voisine[LEFT] = true;
    else goban[i][j].voisine[LEFT] = false;

    //calcul du nombre de pierres voisines
    goban[i][j].nbVoisine = 0;
    if(goban[i][j].voisine[DOWN]) goban[i][j].nbVoisine++;
    if(goban[i][j].voisine[UP]) goban[i][j].nbVoisine++;
    if(goban[i][j].voisine[RIGHT]) goban[i][j].nbVoisine++;
    if(goban[i][j].voisine[LEFT]) goban[i][j].nbVoisine++;

    //affichage des pierres voisines
    if(debug && goban[i][j].couleur != LIBRE)
    {
        positionSurface.x = (PIERRE_ORIGINE_x-surface[VOISINE0]->w/2)+i*CASE;
        positionSurface.y = (PIERRE_ORIGINE_y-surface[VOISINE0]->h/2)+j*CASE;
        if(goban[i][j].nbVoisine == 0) SDL_BlitSurface(surface[VOISINE0], NULL, surface[SCREEN], &positionSurface);
        else if(goban[i][j].nbVoisine == 1) SDL_BlitSurface(surface[VOISINE1], NULL, surface[SCREEN], &positionSurface);
        else if(goban[i][j].nbVoisine == 2) SDL_BlitSurface(surface[VOISINE2], NULL, surface[SCREEN], &positionSurface);
        else if(goban[i][j].nbVoisine == 3) SDL_BlitSurface(surface[VOISINE3], NULL, surface[SCREEN], &positionSurface);
        else if(goban[i][j].nbVoisine == 4) SDL_BlitSurface(surface[VOISINE4], NULL, surface[SCREEN], &positionSurface);
    }
}

void setLiberte(pierreStruct goban[19][19], SDL_Surface* surface[NB_SURFACE], bool debug, int i, int j)
{
    //declaration des variables
    SDL_Rect positionSurface;

    //detection et affichage des libertes
    if(goban[i][j].couleur != LIBRE && goban[i+1][j].couleur == LIBRE && i < 18)
    {
        goban[i][j].liberte[DOWN] = true;
        goban[i][j].nbLiberte++;
        if(debug)
        {
            positionSurface.x = (PIERRE_ORIGINE_x-surface[LIBERTE]->w/2)+(i+1)*CASE;
            positionSurface.y = (PIERRE_ORIGINE_y-surface[LIBERTE]->h/2)+j*CASE;
            SDL_BlitSurface(surface[LIBERTE], NULL, surface[SCREEN], &positionSurface);
        }
    }
    else
    {
        goban[i][j].liberte[DOWN] = false;
        goban[i][j].nbLiberte--;
    }
    if(goban[i][j].couleur != LIBRE && goban[i-1][j].couleur == LIBRE && i > 0)
    {
        goban[i][j].liberte[UP] = true;
        if(debug)
        {
            positionSurface.x = (PIERRE_ORIGINE_x-surface[LIBERTE]->w/2)+(i-1)*CASE;
            positionSurface.y = (PIERRE_ORIGINE_y-surface[LIBERTE]->h/2)+j*CASE;
            SDL_BlitSurface(surface[LIBERTE], NULL, surface[SCREEN], &positionSurface);
        }
    }
    else
    {
        goban[i][j].liberte[UP] = false;
        goban[i][j].nbLiberte--;
    }
    if(goban[i][j].couleur != LIBRE && goban[i][j+1].couleur == LIBRE && j < 18)
    {
        goban[i][j].liberte[RIGHT] = true;
        if(debug)
        {
            positionSurface.x = (PIERRE_ORIGINE_x-surface[LIBERTE]->w/2)+i*CASE;
            positionSurface.y = (PIERRE_ORIGINE_y-surface[LIBERTE]->h/2)+(j+1)*CASE;
            SDL_BlitSurface(surface[LIBERTE], NULL, surface[SCREEN], &positionSurface);
        }
    }
    else
    {
        goban[i][j].liberte[RIGHT] = false;
        goban[i][j].nbLiberte--;
    }
    if(goban[i][j].couleur != LIBRE && goban[i][j-1].couleur == LIBRE && j > 0)
    {
        goban[i][j].liberte[LEFT] = true;
        if(debug)
        {
            positionSurface.x = (PIERRE_ORIGINE_x-surface[LIBERTE]->w/2)+i*CASE;
            positionSurface.y = (PIERRE_ORIGINE_y-surface[LIBERTE]->h/2)+(j-1)*CASE;
            SDL_BlitSurface(surface[LIBERTE], NULL, surface[SCREEN], &positionSurface);
        }
    }
    else
    {
        goban[i][j].liberte[LEFT] = false;
        goban[i][j].nbLiberte--;
    }
}

