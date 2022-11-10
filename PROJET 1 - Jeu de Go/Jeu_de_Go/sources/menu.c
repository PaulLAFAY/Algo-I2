/*

    fonctions permettant l'affichage et la gestion du menu

*/

#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../include/menu.h"
#include "../include/constantes.h"
#include "../include/general.h"

int playMenu(SDL_Surface* surface[NB_SURFACE], Mix_Chunk* son[2], Mix_Music* musique)
{
    //declaration des variables
    SDL_Rect positionOrigine, positionTitre, positionBouton[3];
    SDL_Event event;
    mouse mouse = {0};
    int tempsPrecedent = 0;
    int boutonSelectionne = AUCUNE_SELECTION;

    //initialisation des coordonnees des sprites
    initPositionMenu(&positionOrigine, &positionTitre, positionBouton, surface);

    //boucle infinie
    while(1)
    {
        //affichage des elements sauf boutons
        SDL_BlitSurface(surface[FOND_UNI], NULL, surface[SCREEN], &positionOrigine);
        SDL_BlitSurface(surface[FOND_MENU], NULL, surface[SCREEN], &positionOrigine);
        SDL_BlitSurface(surface[TITRE_GO], NULL, surface[SCREEN], &positionTitre);

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
            if(!mouse.state) Mix_PlayChannel(0, son[CLIC], 0);
            switch(boutonSelectionne)
            {
            case NOUVELLE_PARTIE : //nouvelle partie
                return NOUVELLE_PARTIE;
                break;
            case REPRENDRE_LA_PARTIE : //reprendre la partie
                return REPRENDRE_LA_PARTIE;
                break;
            case PARAMETRES : //parametres
                return PARAMETRES;
                break;
            }
            mouse.state = 1; //le clique est actif
            break;
        case SDL_MOUSEMOTION : //evenements du mouvement de la souris
            mouse.x = event.motion.x;
            mouse.y = event.motion.y;
            break;
        default : break;
        }

        //le pointeur de la souris se trouve dans la zone des boutons en x
        if(mouse.x > (surface[SCREEN]->w/2)-(BOUTON_w/2) && mouse.x <= (surface[SCREEN]->w/2)+(BOUTON_w/2))
        {
            if(mouse.y > NOUVELLE_PARTIE_y && mouse.y <= NOUVELLE_PARTIE_y+BOUTON_h_MENU) //le pointeur de la souris est sur nouvelle partie
            {
                SDL_BlitSurface(surface[FOND_BOUTON_110], NULL, surface[SCREEN], &positionBouton[NOUVELLE_PARTIE]);
                boutonSelectionne = NOUVELLE_PARTIE;
            }
            else if(mouse.y > REPRENDRE_LA_PARTIE_y && mouse.y <= REPRENDRE_LA_PARTIE_y+BOUTON_h_MENU) //le pointeur de la souris est sur reprendre la partie
            {
                SDL_BlitSurface(surface[FOND_BOUTON_110], NULL, surface[SCREEN], &positionBouton[REPRENDRE_LA_PARTIE]);
                boutonSelectionne = REPRENDRE_LA_PARTIE;
            }
            else if(mouse.y > PARAMETRES_y && mouse.y <= PARAMETRES_y+BOUTON_h_MENU) //le pointeur de la souris est sur parametres
            {
                SDL_BlitSurface(surface[FOND_BOUTON_110], NULL, surface[SCREEN], &positionBouton[PARAMETRES]);
                boutonSelectionne = PARAMETRES;
            }
            else boutonSelectionne = AUCUNE_SELECTION;
        }
        else boutonSelectionne = AUCUNE_SELECTION;

        //affichage des boutons
        SDL_BlitSurface(surface[BOUTON_NOUVELLE_PARTIE], NULL, surface[SCREEN], &positionBouton[NOUVELLE_PARTIE]);
        SDL_BlitSurface(surface[BOUTON_REPRENDRE_LA_PARTIE], NULL, surface[SCREEN], &positionBouton[REPRENDRE_LA_PARTIE]);
        SDL_BlitSurface(surface[BOUTON_PARAMETRES], NULL, surface[SCREEN], &positionBouton[PARAMETRES]);

        //rafraichissement de l'ecran
        SDL_Flip(surface[SCREEN]);

        //limitation des fps
        tempsPrecedent = limitFPS(tempsPrecedent);
    }
}

void initPositionMenu(SDL_Rect* positionOrigine, SDL_Rect* positionTitre, SDL_Rect positionBouton[3], SDL_Surface* surface[NB_SURFACE])
{
    positionOrigine->x = 0;
    positionOrigine->y = 0;

    positionTitre->x = (surface[SCREEN]->w/2)-(surface[TITRE_GO]->w/2);
    positionTitre->y = 0;

    positionBouton[NOUVELLE_PARTIE].x = (surface[SCREEN]->w/2)-(surface[BOUTON_NOUVELLE_PARTIE]->w/2);
    positionBouton[NOUVELLE_PARTIE].y = NOUVELLE_PARTIE_y;

    positionBouton[REPRENDRE_LA_PARTIE].x = (surface[SCREEN]->w/2)-(surface[BOUTON_REPRENDRE_LA_PARTIE]->w/2);
    positionBouton[REPRENDRE_LA_PARTIE].y = REPRENDRE_LA_PARTIE_y;

    positionBouton[PARAMETRES].x = (surface[SCREEN]->w/2)-(surface[BOUTON_PARAMETRES]->w/2);
    positionBouton[PARAMETRES].y = PARAMETRES_y;
}

