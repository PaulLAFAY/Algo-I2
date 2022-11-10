/*

    fonctions generales du programme

*/

#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "../include/general.h"
#include "../include/constantes.h"
#include "../include/fichiers.h"

SDL_Surface* initSDL(SDL_Surface* screen)
{
    //initialisation de la SDL et configuration de l'ecran, de l'icone et du titre
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Projet informatique I2 : Jeu de Go", NULL);
    SDL_WM_SetIcon(IMG_Load("ressources/images/icones/icon.png"), NULL);
    if(getSettings().windowState == WINDOWED) screen = SDL_SetVideoMode(SCREEN_w, SCREEN_h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    else screen = SDL_SetVideoMode(SCREEN_w, SCREEN_h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

    return screen;
}

void initSurface(SDL_Surface* surface[NB_SURFACE])
{
    //chargement des sprites en memoire
    //global
    surface[FOND_MENU] = IMG_Load("ressources/images/global/menu.png");
    surface[FOND_UNI] = IMG_Load("ressources/images/global/fond.png");
    surface[FOND_BOUTON_60] = IMG_Load("ressources/images/global/fondbouton60.png");
    surface[FOND_BOUTON_110] = IMG_Load("ressources/images/global/fondbouton110.png");
    surface[BOUTON_RETOUR] = IMG_Load("ressources/images/global/retour.png");
    surface[TITRE_GO] = IMG_Load("ressources/images/global/titrego.png");
    surface[FOND_ICONE] = IMG_Load("ressources/images/global/fondicone.png");
    //menu
    surface[BOUTON_NOUVELLE_PARTIE] = IMG_Load("ressources/images/menu/nouvellepartie.png");
    surface[BOUTON_REPRENDRE_LA_PARTIE] = IMG_Load("ressources/images/menu/reprendrelapartie.png");
    surface[BOUTON_PARAMETRES] = IMG_Load("ressources/images/menu/parametres.png");
    //parametres
    surface[BOUTON_FPS_LOW] = IMG_Load("ressources/images/parametres/30fps.png");
    surface[BOUTON_FPS_HIGH] = IMG_Load("ressources/images/parametres/60fps.png");
    surface[BOUTON_MUSIQUE] = IMG_Load("ressources/images/parametres/musique.png");
    surface[BOUTON_BRUITAGES] = IMG_Load("ressources/images/parametres/bruitages.png");
    surface[BOUTON_VOLUMES] = IMG_Load("ressources/images/parametres/volumes.png");
    surface[BOUTON_CREDITS] = IMG_Load("ressources/images/parametres/credits.png");
    surface[BOUTON_FENETRE] = IMG_Load("ressources/images/parametres/fenetre.png");
    surface[BOUTON_MENU_PRINCIPAL] = IMG_Load("ressources/images/parametres/menuprincipal.png");
    surface[BOUTON_PLEIN_ECRAN] = IMG_Load("ressources/images/parametres/pleinecran.png");
    surface[TITRE_PARAMETRES] = IMG_Load("ressources/images/parametres/titreparametres.png");
    surface[BOUTON_BARGRAPHE_MUSIQUE_FOND] = SDL_CreateRGBSurface(SDL_HWSURFACE, BARGRAPHE_w, BARGRAPHE_h, 32, 0, 0, 0, 0);
    surface[BOUTON_BARGRAPHE_BRUITAGES_FOND] = SDL_CreateRGBSurface(SDL_HWSURFACE, BARGRAPHE_w, BARGRAPHE_h, 32, 0, 0, 0, 0);
    surface[BOUTON_BARGRAPHE_MUSIQUE] = NULL;
    surface[BOUTON_BARGRAPHE_BRUITAGES] = NULL;
    //credits
    surface[FOND_CREDITS] = IMG_Load("ressources/images/credits/fondcredits.png");
    //jeu
    surface[ICONE_HOME] = IMG_Load("ressources/images/jeu/boutonmenu.png");
    surface[ICONE_RETOUR] = IMG_Load("ressources/images/jeu/boutonretour.png");
    surface[PLATEAU] = IMG_Load("ressources/images/jeu/plateau.png");
    surface[PIERRE_BLANCHE] = IMG_Load("ressources/images/jeu/pierreblanche.png");
    surface[PIERRE_BLANCHE_ALPLHA] = IMG_Load("ressources/images/jeu/pierreblanchealpha.png");
    surface[PIERRE_NOIR] = IMG_Load("ressources/images/jeu/pierrenoir.png");
    surface[PIERRE_NOIR_ALPHA] = IMG_Load("ressources/images/jeu/pierrenoiralpha.png");
    surface[BOUTON_SCORE] = IMG_Load("ressources/images/jeu/score.png");
    surface[BOUTON_SCORE_BLANC] = IMG_Load("ressources/images/jeu/blanc.png");
    surface[BOUTON_SCORE_NOIR] = IMG_Load("ressources/images/jeu/noir.png");
    surface[BOUTON_PASSER] = IMG_Load("ressources/images/jeu/passerletour.png");
    surface[ICONE_1P] = IMG_Load("ressources/images/jeu/singleplayer.png");
    surface[ICONE_2P] = IMG_Load("ressources/images/jeu/multiplayer.png");
    //debug
    surface[LIBERTE] = IMG_Load("ressources/images/debug/liberte.png");
    surface[ICONE_DEBUG] = IMG_Load("ressources/images/debug/bug.png");
    surface[VOISINE0] = IMG_Load("ressources/images/debug/voisine0.png");
    surface[VOISINE1] = IMG_Load("ressources/images/debug/voisine1.png");
    surface[VOISINE2] = IMG_Load("ressources/images/debug/voisine2.png");
    surface[VOISINE3] = IMG_Load("ressources/images/debug/voisine3.png");
    surface[VOISINE4] = IMG_Load("ressources/images/debug/voisine4.png");
    surface[CHAINE_BLANCHE] = IMG_Load("ressources/images/debug/chaineblanche.png");
    surface[CHAINE_NOIR] = IMG_Load("ressources/images/debug/chainenoir.png");
}

void initMIXER()
{
    //initialisation de SDL_mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
}

Mix_Music* initMusic(Mix_Music* musique)
{
    //initialise la musique
    musique = Mix_LoadMUS("ressources/sons/musiques/musique.mp3");
    Mix_PlayMusic(musique, -1);
    Mix_VolumeMusic(getSettings().volumeMusique); //entier de 0 a 128

    return musique;
}

void initSound(Mix_Chunk* son[2])
{
    //initialise les bruitages
    Mix_AllocateChannels(1);
    Mix_Volume(0, getSettings().volumeBruitages); //entier entre 0 et 128
    son[CLIC] = Mix_LoadWAV("ressources/sons/bruitages/clic.wav");
    son[POSE] = Mix_LoadWAV("ressources/sons/bruitages/pose.wav");
}

void quitApp(SDL_Surface* surface[NB_SURFACE], Mix_Chunk* son[2], Mix_Music* musique)
{
    int i;

    //quitte la sdl et mixer
    Mix_FreeChunk(son[1]);
    Mix_FreeChunk(son[2]);
    Mix_FreeMusic(musique);
    Mix_CloseAudio();
    for(i = 1; i < NB_SURFACE; i++) SDL_FreeSurface(surface[i]);
    SDL_Quit();
}

int limitFPS(int tempsPrecedent)
{
    //limite le fps a 30 ou 60 selon les parametres
    int fps_limit;
    if(getSettings().fps == LOW) fps_limit = FPS_low;
    else fps_limit = FPS_high;

    int tempsActuel = SDL_GetTicks();

    if(tempsActuel - tempsPrecedent < (int)1000/fps_limit) //si ça fait moins de 1000/FPS second alors on attend le temps qu'il faut
    {
        SDL_Delay((int)(1000/fps_limit) - (tempsActuel - tempsPrecedent));
    }

    return tempsActuel;
}

