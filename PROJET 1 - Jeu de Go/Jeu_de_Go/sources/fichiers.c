/*

    fonctions permettant la gestion des fichiers

*/

#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../include/fichiers.h"
#include "../include/constantes.h"
#include "../include/jeu.h"

settings getSettings()
{
    //declaration des variables
    settings settings = {0};
    FILE* file = NULL;

    //ouverture du fichier en lecture
    file = fopen("ressources/fichiers/go.settings", "r");
    if(file != NULL) //si c'est possible de lire le fichier
    {
        fscanf(file, "fps_limit = %i\nwindow_state = %i\nvolume_music = %i\nvolume_chunk = %i", &settings.fps, &settings.windowState, &settings.volumeMusique, &settings.volumeBruitages);
    }
    else //si c'est impossible il faut en creer un avec les valeurs par defaut
    {
        file = fopen("ressources/fichiers/go.settings", "w");
        fprintf(file, "fps_limit = 0\nwindow_state = 0\nvolume_music = 0\nvolume_chunk = 0");
    }
    fclose(file); //fermeture du fichier

    return settings;
}

SDL_Surface* setSettings(int parametres, SDL_Surface* screen, int val)
{
    //declaration des variables
    FILE* file = NULL;
    settings settings = getSettings();

    //si on modifie les fps
    if(parametres == P_FPS)
    {
        if(getSettings().fps == LOW)
        {
            file = fopen("ressources/fichiers/go.settings", "w+");
            fprintf(file, "fps_limit = %i\nwindow_state = %i\nvolume_music = %i\nvolume_chunk = %i", HIGH, settings.windowState, settings.volumeMusique, settings.volumeBruitages);
        }
        else
        {
            file = fopen("ressources/fichiers/go.settings", "w+");
            fprintf(file, "fps_limit = %i\nwindow_state = %i\nvolume_music = %i\nvolume_chunk = %i", LOW, settings.windowState, settings.volumeMusique, settings.volumeBruitages);
        }
    }
    //si on modifie la fenetre
    else if(parametres == P_FENETRE)
    {
        if(getSettings().windowState == WINDOWED)
        {
            file = fopen("ressources/fichiers/go.settings", "w+");
            fprintf(file, "fps_limit = %i\nwindow_state = %i\nvolume_music = %i\nvolume_chunk = %i", settings.fps, FULLSCREEN, settings.volumeMusique, settings.volumeBruitages);
            screen = SDL_SetVideoMode(SCREEN_w, SCREEN_h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
        }
        else
        {
            file = fopen("ressources/fichiers/go.settings", "w+");
            fprintf(file, "fps_limit = %i\nwindow_state = %i\nvolume_music = %i\nvolume_chunk = %i", settings.fps, WINDOWED, settings.volumeMusique, settings.volumeBruitages);
            screen = SDL_SetVideoMode(SCREEN_w, SCREEN_h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
        }
    }
    //si on modifie le volume de la musique
    else if(parametres == P_VMUSIC)
    {
        file = fopen("ressources/fichiers/go.settings", "w+");
        fprintf(file, "fps_limit = %i\nwindow_state = %i\nvolume_music = %i\nvolume_chunk = %i", settings.fps, settings.windowState, val, settings.volumeBruitages);
        Mix_VolumeMusic((int)(val*1.28));//entier de 0 a 128
    }
    //si on modifie le volume des bruitages
    else if(parametres == P_VCHUNK)
    {
        file = fopen("ressources/fichiers/go.settings", "w+");
        fprintf(file, "fps_limit = %i\nwindow_state = %i\nvolume_music = %i\nvolume_chunk = %i", settings.fps, settings.windowState, settings.volumeMusique, val);
        Mix_Volume(0, (int)(val*1.28)); //entier entre 0 et 128
    }
    fclose(file); //fermeture du fichier

    return screen;
}

void nouveauJeu(SDL_Surface* surface[NB_SURFACE], Mix_Chunk* son[2], Mix_Music* musique, pel pile, bool* debug)
{
    //declaration des variables
    FILE* file = NULL;
    pierreStruct goban[19][19] = {LIBRE};
    int score[2] = {0};

    //suppression de l'ancien fichier
    remove("ressources/fichiers/go.save");

    //ouverture et ecriture dans le fichier go.save
    file = fopen("ressources/fichiers/go.save", "w");
    fprintf(file, "tour : 0\nscore blanc : 0\nscore noir : 0\nbot : 0\n\n");
    fclose(file); //fermeture du fichier

    jeu(surface, 0, goban, score, son, musique, pile, debug, false); //lancement du jeu
}

void reprendreJeu(SDL_Surface* surface[NB_SURFACE], Mix_Chunk* son[2], Mix_Music* musique, pel pile, bool* debug)
{
    //declaration du fichier
    FILE* file = fopen("ressources/fichiers/go.save", "r");
    int score[2] = {0};
    int bot;

    if(file != NULL) //si le fichier a reussi a s'ouvrir = si le fichier existe
    {
        //declaration des variables
        int i, j;
        int tour;
        pierreStruct goban[19][19] = {LIBRE};

        //lecture du fichier go.save et envoi à la fonction jeu
        rewind(file);
        fscanf(file, "tour : %i\nscore blanc : %i\nscore noir : %i\nbot : %i\n\n", &tour, &score[BLANC-1], &score[NOIR-1], &bot);

        for(j = 0; j < 19; j++)
        {
            for(i = 0; i < 19; i++)
            {
                if(i < 18) fscanf(file, "%i ", &goban[i][j].couleur);
                else if(i == 18) fscanf(file, "%i \n", &goban[i][j].couleur);
            }
        }
        fclose(file); //fermeture du fichier

        jeu(surface, tour, goban, score, son, musique, pile, debug, bot); //lancement du jeu
    }
    else nouveauJeu(surface, son, musique, pile, debug); //si le fichier n'a pas reussi a s'ouvrir = si le ficher n'existe pas
}

void save(pierreStruct goban[19][19], int tour, int score[2], bool bot)
{
    //ouverture du fichier go.save et declaration des variables
    FILE* file = fopen("ressources/fichiers/go.save", "r+");
    int i, j;
    int tempBot = bot;

    //ecriture dans le fichier go.save
    rewind(file);

    fprintf(file, "tour : %i\n", tour);
    fprintf(file, "score blanc : %i\n", score[0]);
    fprintf(file, "score noir : %i\n", score[1]);
    fprintf(file, "bot : %i\n\n", tempBot);

    for(j = 0; j < 19; j++)
    {
        for(i = 0; i < 19; i++) fprintf(file, "%i ", goban[i][j].couleur);
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    fclose(file); //fermeture du fichier
}

