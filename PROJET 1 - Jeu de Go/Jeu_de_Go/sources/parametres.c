/*

    fonctions permettant l'affiche et la gestion des parametres

*/

#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../include/parametres.h"
#include "../include/constantes.h"
#include "../include/general.h"
#include "../include/fichiers.h"
#include "../include/credits.h"

SDL_Surface* playParametres(SDL_Surface* surface[NB_SURFACE], Mix_Chunk* son[2], Mix_Music* musique)
{
    //declaration des variables
    SDL_Rect positionOrigine, positionTitre, positionBouton[10], positionVolumes[2];
    SDL_Event event;
    mouse mouse = {0};
    int tempsPrecedent = 0;
    int boutonSelectionne = AUCUNE_SELECTION;

    //chargement de la couleur des bargraphes
    SDL_FillRect(surface[BOUTON_BARGRAPHE_MUSIQUE_FOND], NULL, SDL_MapRGB(surface[SCREEN]->format, 50, 0, 0));
    SDL_FillRect(surface[BOUTON_BARGRAPHE_BRUITAGES_FOND], NULL, SDL_MapRGB(surface[SCREEN]->format, 50, 0, 0));

    //initialisation des coordonnees des sprites
    initPositionParam(&positionOrigine, &positionTitre, positionBouton, positionVolumes, surface);

    //boucle infinie
    while(1)
    {
        //chargement des bargraphe en mémoire
        surface[BOUTON_BARGRAPHE_MUSIQUE] = SDL_CreateRGBSurface(SDL_HWSURFACE, getSettings().volumeMusique*2, BARGRAPHE_h, 32, 0, 0, 0, 0);
        surface[BOUTON_BARGRAPHE_BRUITAGES] = SDL_CreateRGBSurface(SDL_HWSURFACE, getSettings().volumeBruitages*2, BARGRAPHE_h, 32, 0, 0, 0, 0);

        //chargement de la couleur des bargraphes
        SDL_FillRect(surface[BOUTON_BARGRAPHE_MUSIQUE], NULL, SDL_MapRGB(surface[SCREEN]->format, 146, 84, 30));
        SDL_FillRect(surface[BOUTON_BARGRAPHE_BRUITAGES], NULL, SDL_MapRGB(surface[SCREEN]->format, 146, 84, 30));

        //affichage des elements sauf les boutons
        SDL_BlitSurface(surface[FOND_UNI], NULL, surface[SCREEN], &positionOrigine);
        SDL_BlitSurface(surface[FOND_MENU], NULL, surface[SCREEN], &positionOrigine);
        SDL_BlitSurface(surface[TITRE_PARAMETRES], NULL, surface[SCREEN], &positionTitre);

        //detection des evenements
        SDL_PollEvent(&event);
        switch(event.type) //evenements divers
        {
        case SDL_QUIT : //le joueur veut quitter le jeu
            quitApp(surface, son, musique);
            exit(0);
            break;
        case SDL_KEYDOWN :
            switch(event.key.keysym.sym) //evenements du clavier
            {
            case SDLK_ESCAPE : //le joueur veut quitter le jeu
                quitApp(surface, son, musique);
                exit(0);
                break;
            default : break;
            }
            break;
        case SDL_MOUSEBUTTONUP : //evenements des cliques haut de la souris
            mouse.state = 0; //le clique n'est plus actif
            break;
        case SDL_MOUSEBUTTONDOWN : //evenements des cliques bas de la souris
            if(!mouse.state)
            {
                Mix_PlayChannel(0, son[CLIC], 0);
                switch(boutonSelectionne)
                {
                case FPS_LIMIT : //limite des fps
                    if(!mouse.state) surface[SCREEN] = setSettings(P_FPS, surface[SCREEN], 0);
                    break;
                case FENETRE : //plein ecran ou fenetre
                    if(!mouse.state) surface[SCREEN] = setSettings(P_FENETRE, surface[SCREEN], 0);
                    break;
                case CREDITS : //credits
                    playCredits(surface, son, musique);
                    break;
                case MENU_PRINCIPAL : //menu principal
                    return surface[SCREEN]; //quitte playparametres
                    break;
                }
            }
            mouse.state = 1; //le clique est actif
            break;
        case SDL_MOUSEMOTION : //evenements du mouvement de la souris
            mouse.x = event.motion.x;
            mouse.y = event.motion.y;
            break;
        default : break;
        }

        //le pointeur de la souris se trouve dans la zone des boutons
        if((mouse.x > (surface[SCREEN]->w/2)-(BOUTON_w/2) && mouse.x <= (surface[SCREEN]->w/2)+(BOUTON_w/2)) && (mouse.y > FPS_LIMIT_y))
        {
            if(mouse.y > MUSIQUE_y && mouse.y <= MUSIQUE_y+BOUTON_h_PARAMETRES) //le pointeur de la souris est sur musique
            {
                SDL_BlitSurface(surface[FOND_BOUTON_60], NULL, surface[SCREEN], &positionBouton[MUSIQUE]);
            }
            else if(mouse.y > BRUITAGES_y && mouse.y <= BRUITAGES_y+BOUTON_h_PARAMETRES) //le pointeur de la souris est sur bruitages
            {
                SDL_BlitSurface(surface[FOND_BOUTON_60], NULL, surface[SCREEN], &positionBouton[BRUITAGES]);
            }
            else if(mouse.y > FPS_LIMIT_y && mouse.y <= FPS_LIMIT_y+BOUTON_h_PARAMETRES) //le pointeur de la souris est sur fpslimit
            {
                SDL_BlitSurface(surface[FOND_BOUTON_60], NULL, surface[SCREEN], &positionBouton[FPS_LIMIT]);
                boutonSelectionne = FPS_LIMIT;
            }
            else if(mouse.y > FENETRE_y && mouse.y <= FENETRE_y+BOUTON_h_PARAMETRES) //le pointeur de la souris est sur fenetre
            {
                SDL_BlitSurface(surface[FOND_BOUTON_60], NULL, surface[SCREEN], &positionBouton[FENETRE]);
                boutonSelectionne = FENETRE;
            }
            else if(mouse.y > CREDITS_y && mouse.y <= CREDITS_y+BOUTON_h_PARAMETRES) //le pointeur de la souris est sur credits
            {
                SDL_BlitSurface(surface[FOND_BOUTON_60], NULL, surface[SCREEN], &positionBouton[CREDITS]);
                boutonSelectionne = CREDITS;
            }
            else if(mouse.y > MENU_PRINCIPAL_y && mouse.y <= MENU_PRINCIPAL_y+BOUTON_h_PARAMETRES) //le pointeur de la souris est sur menuprincipal
            {
                SDL_BlitSurface(surface[FOND_BOUTON_60], NULL, surface[SCREEN], &positionBouton[MENU_PRINCIPAL]);
                boutonSelectionne = MENU_PRINCIPAL;
            }
            else boutonSelectionne = AUCUNE_SELECTION;
        }
        else boutonSelectionne = AUCUNE_SELECTION;

        //si la souris se trouve dans les volumes + clique
        if((mouse.x > positionVolumes[BARGRAPHE_MUSIQUE].x && mouse.x <= positionVolumes[BARGRAPHE_MUSIQUE].x+BARGRAPHE_w) && (mouse.y > positionVolumes[BARGRAPHE_MUSIQUE].y && mouse.y <= positionVolumes[BARGRAPHE_MUSIQUE].y+BARGRAPHE_h))
        {
            if(event.type == SDL_MOUSEBUTTONDOWN) surface[SCREEN] = setSettings(P_VMUSIC, surface[SCREEN], (int)((mouse.x-positionVolumes[BARGRAPHE_MUSIQUE].x)/2));
        }
        else if((mouse.x > positionVolumes[BARGRAPHE_BRUITAGES].x && mouse.x <= positionVolumes[BARGRAPHE_BRUITAGES].x+BARGRAPHE_w) && (mouse.y > positionVolumes[BARGRAPHE_BRUITAGES].y && mouse.y <= positionVolumes[BARGRAPHE_BRUITAGES].y+BARGRAPHE_h))
        {
            if(event.type == SDL_MOUSEBUTTONDOWN) surface[SCREEN] = setSettings(P_VCHUNK, surface[SCREEN], (int)((mouse.x-positionVolumes[BARGRAPHE_BRUITAGES].x)/2));
        }

        //affichage des boutons
        SDL_BlitSurface(surface[BOUTON_VOLUMES], NULL, surface[SCREEN], &positionBouton[VOLUMES]);
        SDL_BlitSurface(surface[BOUTON_MUSIQUE], NULL, surface[SCREEN], &positionBouton[MUSIQUE]);
        SDL_BlitSurface(surface[BOUTON_BRUITAGES], NULL, surface[SCREEN], &positionBouton[BRUITAGES]);
        SDL_BlitSurface(surface[BOUTON_BARGRAPHE_MUSIQUE_FOND], NULL, surface[SCREEN], &positionVolumes[BARGRAPHE_MUSIQUE]);
        SDL_BlitSurface(surface[BOUTON_BARGRAPHE_BRUITAGES_FOND], NULL, surface[SCREEN], &positionVolumes[BARGRAPHE_BRUITAGES]);
        SDL_BlitSurface(surface[BOUTON_BARGRAPHE_MUSIQUE], NULL, surface[SCREEN], &positionVolumes[BARGRAPHE_MUSIQUE]);
        SDL_BlitSurface(surface[BOUTON_BARGRAPHE_BRUITAGES], NULL, surface[SCREEN], &positionVolumes[BARGRAPHE_BRUITAGES]);
        if(getSettings().fps == LOW) SDL_BlitSurface(surface[BOUTON_FPS_LOW], NULL, surface[SCREEN], &positionBouton[FPS_LIMIT]);
        else SDL_BlitSurface(surface[BOUTON_FPS_HIGH], NULL, surface[SCREEN], &positionBouton[FPS_LIMIT]);
        if(getSettings().windowState == WINDOWED) SDL_BlitSurface(surface[BOUTON_FENETRE], NULL, surface[SCREEN], &positionBouton[FENETRE]);
        else SDL_BlitSurface(surface[BOUTON_PLEIN_ECRAN], NULL, surface[SCREEN], &positionBouton[FENETRE]);
        SDL_BlitSurface(surface[BOUTON_CREDITS], NULL, surface[SCREEN], &positionBouton[CREDITS]);
        SDL_BlitSurface(surface[BOUTON_MENU_PRINCIPAL], NULL, surface[SCREEN], &positionBouton[MENU_PRINCIPAL]);

        //rafraichissement de l'ecran
        SDL_Flip(surface[SCREEN]);

        //suppression des bargraphes de la mémoire
        SDL_FreeSurface(surface[BOUTON_BARGRAPHE_MUSIQUE]);
        SDL_FreeSurface(surface[BOUTON_BARGRAPHE_BRUITAGES]);

        //limitation des fps
        tempsPrecedent = limitFPS(tempsPrecedent);
    }
}

void initPositionParam(SDL_Rect* positionOrigine, SDL_Rect* positionTitre, SDL_Rect positionBouton[10], SDL_Rect positionVolumes[2], SDL_Surface* surface[NB_SURFACE])
{
    positionOrigine->x = 0;
    positionOrigine->y = 0;

    positionTitre->x = (surface[SCREEN]->w/2)-(surface[TITRE_PARAMETRES]->w/2);
    positionTitre->y = 0;

    positionBouton[VOLUMES].x = (surface[SCREEN]->w/2)-(surface[BOUTON_VOLUMES]->w/2);
    positionBouton[VOLUMES].y = VOLUMES_y;

    positionBouton[MUSIQUE].x = (surface[SCREEN]->w/2)-(surface[BOUTON_MUSIQUE]->w/2);
    positionBouton[MUSIQUE].y = MUSIQUE_y;

    positionBouton[BRUITAGES].x = (surface[SCREEN]->w/2)-(surface[BOUTON_BRUITAGES]->w/2);
    positionBouton[BRUITAGES].y = BRUITAGES_y;

    positionBouton[FPS_LIMIT].x = (surface[SCREEN]->w/2)-(surface[BOUTON_FPS_LOW]->w/2);
    positionBouton[FPS_LIMIT].y = FPS_LIMIT_y;

    positionBouton[FENETRE].x = (surface[SCREEN]->w/2)-(surface[BOUTON_FENETRE]->w/2);
    positionBouton[FENETRE].y = FENETRE_y;

    positionBouton[CREDITS].x = (surface[SCREEN]->w/2)-(surface[BOUTON_CREDITS]->w/2);
    positionBouton[CREDITS].y = CREDITS_y;

    positionBouton[MENU_PRINCIPAL].x = (surface[SCREEN]->w/2)-(surface[BOUTON_MENU_PRINCIPAL]->w/2);
    positionBouton[MENU_PRINCIPAL].y = MENU_PRINCIPAL_y;

    positionVolumes[BARGRAPHE_MUSIQUE].x = positionBouton[MUSIQUE].x+(BOUTON_w-BARGRAPHE_w-(BARGRAPHE_h/4));
    positionVolumes[BARGRAPHE_MUSIQUE].y = BARGRAPHE_MUSIQUE_y;

    positionVolumes[BARGRAPHE_BRUITAGES].x = positionBouton[BRUITAGES].x+(BOUTON_w-BARGRAPHE_w-(BARGRAPHE_h/4));
    positionVolumes[BARGRAPHE_BRUITAGES].y = BARGRAPHE_BRUITAGES_y;
}
