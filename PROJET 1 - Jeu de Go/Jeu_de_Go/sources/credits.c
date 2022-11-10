/*

    fonctions permettant l'affichage des credit

*/

#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../include/credits.h"
#include "../include/constantes.h"
#include "../include/general.h"

void playCredits(SDL_Surface* surface[NB_SURFACE], Mix_Chunk* son[2], Mix_Music* musique)
{
    //declaration des variables
    SDL_Rect positionFond, positionRetour;
    SDL_Event event;
    mouse mouse = {0};
    int tempsPrecedent = 0;
    int boutonSelectionne = 0;

    //initialisation des coordonnees des sprites
    positionFond.x = 0;
    positionFond.y = 0;

    positionRetour.x = (surface[SCREEN]->w/2)-(surface[BOUTON_RETOUR]->w/2);
    positionRetour.y = RETOUR_CREDITS_y;

    //boucle infinie
    while(1)
    {
        //affichage des sprites fixes
        SDL_BlitSurface(surface[FOND_CREDITS], NULL, surface[SCREEN], &positionFond);

        SDL_PollEvent(&event);
        switch(event.type) //evenement divers
        {
        case SDL_QUIT : //si le joueur veut quitter
            quitApp(surface, son, musique);
            exit(0);
            break;
        case SDL_KEYDOWN :
            switch(event.key.keysym.sym) //evenements du clavier
            {
            case SDLK_ESCAPE : //si le joueur veut quitter
                quitApp(surface, son, musique);
                exit(0);
                break;
            default : break;
            }
            break;
        case SDL_MOUSEBUTTONUP :
            mouse.state = 0; //le clique n'est plus actif
            break;
        case SDL_MOUSEBUTTONDOWN : //evenement de la souris
            if(!mouse.state)
            {
                Mix_PlayChannel(0, son[CLIC], 0);
                if(boutonSelectionne) return EXIT_SUCCESS; //si on clique sur le bouton retour
            }
            mouse.state = 1; //le clique est actif
            break;
        case SDL_MOUSEMOTION :
            mouse.x = event.motion.x;
            mouse.y = event.motion.y;
            break;
        default : break;
        }

        //si la souris est sur le bouton retour et affichage des elements mobiles
        if(mouse.x > positionRetour.x && mouse.x <= positionRetour.x+BOUTON_w && mouse.y > RETOUR_CREDITS_y && mouse.y <= RETOUR_CREDITS_y+BOUTON_h_CREDITS)
        {
            SDL_BlitSurface(surface[FOND_BOUTON_110], NULL, surface[SCREEN], &positionRetour);
            boutonSelectionne = 1;
        }
        else boutonSelectionne = 0;
        SDL_BlitSurface(surface[BOUTON_RETOUR], NULL, surface[SCREEN], &positionRetour);

        SDL_Flip(surface[SCREEN]); //rafraichit l'ecran

        tempsPrecedent = limitFPS(tempsPrecedent); //limite les fps
    }
}

