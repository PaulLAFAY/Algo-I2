/*

    fonctions permettant la gestion du jeu

*/

#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "../include/jeu.h"
#include "../include/constantes.h"
#include "../include/general.h"
#include "../include/fichiers.h"
#include "../include/pile.h"
#include "../include/pierres.h"
#include "../include/chaines.h"

void jeu(SDL_Surface* surface[NB_SURFACE], int tour, pierreStruct goban[19][19], int score[2], Mix_Chunk* son[2], Mix_Music* musique, pel pile, bool* debug, bool bot)
{
    //declaration des variables
    SDL_Rect positionOrigine, positionPlateau, positionTexte[5], positionIcone[4];
    SDL_Event event;
    mouse mouse = {0};
    coordonnee caseSelectionne = {0};
    chaineStruct chaine[MAX_CHAINE] = {0};
    int tempsPrecedent = 0;
    int boutonSelectionne = AUCUNE_SELECTION;
    int passerNoir = 0, passerBlanc = 0, quitter = 0;
    int nbChaine = 0;
    int i;

    //allocation dynamique des chaines
    for(i = 0; i < MAX_CHAINE; i++) chaine[i].pierre = malloc(MAX_PIERRE*sizeof(pierreStruct));

    //initialisation des positions
    initPositionJeu(&positionOrigine, &positionPlateau, positionTexte, positionIcone, surface);

    //iniialisation du generateur de nombre aleatoire
    srand(time(NULL));

    //boucle infinie
    while(!quitter)
    {
        //gestion des evenements
        SDL_PollEvent(&event);

        switch(event.type)
        {
        case SDL_QUIT : //le joueur veut quitter l'appli
            quitApp(surface, son, musique);
            exit(0);
            break;
        case SDL_KEYDOWN : //evenement du clavier
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE : //le joueur veut quitter l'appli
                quitApp(surface, son, musique);
                exit(0);
                break;
            default : break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN : //evenement du clique souris
            if(!mouse.state && event.button.button == SDL_BUTTON_LEFT) //si c'est un clique gauche
            {
                if((mouse.x >= PLATEAU_x && mouse.x <= PLATEAU_x+PLATEAU_w) && (mouse.y >= PLATEAU_y && mouse.y <= PLATEAU_y+PLATEAU_h)) //si la souris est dans le plateau
                {
                    Mix_PlayChannel(0, son[POSE], 0);
                    if(caseSelectionne.x != 20 && caseSelectionne.y != 20 && goban[caseSelectionne.x][caseSelectionne.y].couleur == LIBRE) //si la case clique est vide
                    {
                        placerCoup(goban, score, &tour, &pile, bot, &passerBlanc, &passerNoir, caseSelectionne); //fonction permettant d'ajouter la pierre au tableau, de sauvegarder, etc...
                    }
                }
                else Mix_PlayChannel(0, son[CLIC], 0); //si la souris n'est pas dans le plateau

                if(boutonSelectionne == PASSER) //passer le tour
                {
                    if(tour%2 == NOIR-1)
                    {
                        passerNoir = 1;
                        if(bot) passerBlanc = 1;
                    }
                    else if(tour%2 == BLANC-1) passerBlanc = 1;
                    quitter = testFin(passerBlanc, passerNoir);
                    tour++;
                }
                else if(boutonSelectionne == MENU) return EXIT_SUCCESS; //retour au menu
                else if(boutonSelectionne == RETOUR && pile != NULL) //reviens un tour en arriere
                {
                    retour(&tour, &pile, goban, score, bot);
                    if(bot) retour(&tour, &pile, goban, score, bot); //si le bot est active il faut remonter de deux tours
                }
                else if(boutonSelectionne == PLAYER) //active ou desactive le mode 1 joueur
                {
                    if(bot) bot = false;
                    else bot = true;
                }
                else if(boutonSelectionne == DEBUG) //active ou desactive le mode debug
                {
                    if(*debug) *debug = false;
                    else *debug = true;
                }
            }
            mouse.state = 1; //le clique est desactive
            break;
        case SDL_MOUSEBUTTONUP :
            mouse.state = 0; //le clique est active
            break;
        case SDL_MOUSEMOTION : //evenement deplacement de la souris
            mouse.x = event.motion.x;
            mouse.y = event.motion.y;
        default : break;
        }

        //affichage des sprites et des scores
        afficheSprites(surface, positionOrigine, positionPlateau, positionTexte, positionIcone, tour, mouse, &boutonSelectionne, *debug, bot, score);

        //gestion des coup soit par le joueur soit par le bot
        if(!bot || (bot && tour%2 == NOIR-1)) caseSelectionne = coupJoueur(surface, goban, mouse, tour, caseSelectionne);
        else if(bot && tour%2 == BLANC-1) caseSelectionne = coupBot(goban, score, &tour, &pile, bot, &passerBlanc, &passerNoir);

        //gestion des pierres, chaines et territoires
        paramPierres(goban, surface, *debug);
        nbChaine = resetChaine(chaine, nbChaine);
        nbChaine = paramChaine(goban, chaine, nbChaine, surface, *debug);

        //rafraichissement de l'ecran
        SDL_Flip(surface[SCREEN]);

        //limit des fps
        tempsPrecedent = limitFPS(tempsPrecedent);
    }

    //liberation memoire chaine
    for(i = 0; i < MAX_CHAINE; i++) free(chaine[i].pierre);
}

coordonnee coupJoueur(SDL_Surface* surface[NB_SURFACE], pierreStruct goban[19][19], mouse mouse, int tour, coordonnee caseSelectionne)
{
    //declaration des variables
    SDL_Rect positionPierre;
    int i, j;

    //parcours le tableau et affiche les pierres
    for(j = 0; j < 19; j++)
    {
        for(i = 0; i < 19; i++)
        {
            //affichage pierres
            if(goban[i][j].couleur == BLANC)
            {
                positionPierre.x = (PIERRE_ORIGINE_x-surface[PIERRE_BLANCHE]->w/2)+i*CASE;
                positionPierre.y = (PIERRE_ORIGINE_y-surface[PIERRE_BLANCHE]->h/2)+j*CASE;
                SDL_BlitSurface(surface[PIERRE_BLANCHE], NULL, surface[SCREEN], &positionPierre);
            }
            else if(goban[i][j].couleur == NOIR)
            {
                positionPierre.x = (PIERRE_ORIGINE_x-surface[PIERRE_NOIR]->w/2)+i*CASE;
                positionPierre.y = (PIERRE_ORIGINE_y-surface[PIERRE_NOIR]->h/2)+j*CASE;
                SDL_BlitSurface(surface[PIERRE_NOIR], NULL, surface[SCREEN], &positionPierre);
            }

            //pre-affichage des pierres
            if((mouse.x >= PIERRE_ORIGINE_x-surface[PIERRE_NOIR]->w/2 && mouse.x <= PIERRE_ORIGINE_x+surface[PIERRE_NOIR]->w/2+18*CASE) && (mouse.y >= PIERRE_ORIGINE_y-surface[PIERRE_NOIR]->h/2 && mouse.y <= PIERRE_ORIGINE_y+surface[PIERRE_NOIR]->h/2+18*CASE))
            {
                if(tour%2 == BLANC-1 && (mouse.x >= PIERRE_ORIGINE_x-surface[PIERRE_BLANCHE_ALPLHA]->w/2+i*26 && mouse.x <= PIERRE_ORIGINE_x+surface[PIERRE_BLANCHE_ALPLHA]->w/2+i*26) && (mouse.y >= PIERRE_ORIGINE_y-surface[PIERRE_BLANCHE_ALPLHA]->h/2+j*26 && mouse.y <= PIERRE_ORIGINE_y+surface[PIERRE_BLANCHE_ALPLHA]->h/2+j*26))
                {
                    positionPierre.x = (PIERRE_ORIGINE_x-surface[PIERRE_BLANCHE_ALPLHA]->w/2)+i*CASE;
                    positionPierre.y = (PIERRE_ORIGINE_y-surface[PIERRE_BLANCHE_ALPLHA]->h/2)+j*CASE;
                    SDL_BlitSurface(surface[PIERRE_BLANCHE_ALPLHA], NULL, surface[SCREEN], &positionPierre);
                    caseSelectionne.x = i;
                    caseSelectionne.y = j;
                }
                else if(tour%2 == NOIR-1 && (mouse.x >= PIERRE_ORIGINE_x-surface[PIERRE_NOIR_ALPHA]->w/2+i*26 && mouse.x <= PIERRE_ORIGINE_x+surface[PIERRE_NOIR_ALPHA]->w/2+i*26) && (mouse.y >= PIERRE_ORIGINE_y-surface[PIERRE_NOIR_ALPHA]->h/2+j*26 && mouse.y <= PIERRE_ORIGINE_y+surface[PIERRE_NOIR_ALPHA]->h/2+j*26))
                {
                    positionPierre.x = (PIERRE_ORIGINE_x-surface[PIERRE_NOIR_ALPHA]->w/2)+i*CASE;
                    positionPierre.y = (PIERRE_ORIGINE_y-surface[PIERRE_NOIR_ALPHA]->h/2)+j*CASE;
                    SDL_BlitSurface(surface[PIERRE_NOIR_ALPHA], NULL, surface[SCREEN], &positionPierre);
                    caseSelectionne.x = i;
                    caseSelectionne.y = j;
                }
            }
            else
            {
                caseSelectionne.x = 20;
                caseSelectionne.y = 20;
            }
        }
    }

    return caseSelectionne;
}

coordonnee coupBot(pierreStruct goban[19][19], int score[2], int* tour, pel* pile, bool bot, int* passerBlanc, int* passerNoir)
{
    //declaration des variables
    coordonnee coup = {0};

    //rentre des valeurs aleatoires dans les champs x et y
    do
    {
        coup.x = rand()%19;
        coup.y = rand()%19;
    }while(goban[coup.x][coup.y].couleur != LIBRE);

    placerCoup(goban, score, tour, pile, bot, passerBlanc, passerNoir, coup);

    return coup;
}

void placerCoup(pierreStruct goban[19][19], int score[2], int* tour, pel* pile, bool bot, int* passerBlanc, int* passerNoir, coordonnee caseSelectionne)
{
    if(*tour%2 == BLANC-1) //placement pierre blanche
    {
        goban[caseSelectionne.x][caseSelectionne.y].couleur = BLANC;
        (*tour)++;
    }
    else if(*tour%2 == NOIR-1) //placement pierre noir
    {
        goban[caseSelectionne.x][caseSelectionne.y].couleur = NOIR;
        (*tour)++;
    }
    goban[caseSelectionne.x][caseSelectionne.y].position = caseSelectionne;
    save(goban, *tour, score, bot);
    *pile = empiler(*pile, caseSelectionne); //on empile le coup joue pour la gestion des retours
    *passerBlanc = 0;
    *passerNoir = 0;
}

void retour(int* tour, pel* pile, pierreStruct goban[19][19], int score[2], bool bot)
{
    //declaration des variables
    int i;
    coordonnee caseRetour = {0};

    (*tour)--;
    *pile = depiler(*pile, &caseRetour); //on depile le dernier coup empiler et on le remet en jeu
    goban[caseRetour.x][caseRetour.y].couleur = LIBRE;
    for(i = 0; i < 4; i++)
    {
        goban[caseRetour.x][caseRetour.y].liberte[i] = false;
        goban[caseRetour.x][caseRetour.y].voisine[i] = false;
    }
    goban[caseRetour.x][caseRetour.y].position.x = 0;
    goban[caseRetour.x][caseRetour.y].position.y = 0;
    save(goban, *tour, score, bot);
}

int testFin(int passerBlanc, int passerNoir)
{
    if(passerBlanc == 1 && passerNoir == 1) return 1;
    else return 0;
}

void initPositionJeu(SDL_Rect* positionOrigine, SDL_Rect* positionPlateau, SDL_Rect positionTexte[5], SDL_Rect positionIcone[3], SDL_Surface* surface[NB_SURFACE])
{
    positionOrigine->x = 0;
    positionOrigine->y = 0;

    positionPlateau->x = PLATEAU_x;
    positionPlateau->y = PLATEAU_y;

    positionTexte[TITRE].x = TITRE_x;
    positionTexte[TITRE].y = 0;

    positionTexte[SCORE].x = SCORE_x;
    positionTexte[SCORE].y = SCORE_y;

    positionTexte[SCORE_NOIR].x = SCORE_NOIR_x;
    positionTexte[SCORE_NOIR].y = SCORE_NOIR_y;

    positionTexte[SCORE_BLANC].x = SCORE_BLANC_x;
    positionTexte[SCORE_BLANC].y = SCORE_BLANC_y;

    positionTexte[PASSER].x = PASSER_x;
    positionTexte[PASSER].y = PASSER_y;

    positionIcone[MENU].x = MENU_x;
    positionIcone[MENU].y = MENU_y;

    positionIcone[RETOUR].x = RETOUR_x;
    positionIcone[RETOUR].y = RETOUR_y;

    positionIcone[PLAYER].x = BOT_x;
    positionIcone[PLAYER].y = BOT_y;

    positionIcone[DEBUG].x = DEBUG_x;
    positionIcone[DEBUG].y = DEBUG_y;
}

void afficheSprites(SDL_Surface* surface[NB_SURFACE], SDL_Rect positionOrigine, SDL_Rect positionPlateau, SDL_Rect positionTexte[5], SDL_Rect positionIcone[4], int tour, mouse mouse, int* boutonSelectionne, bool debug, bool bot, int score[2])
{
    SDL_BlitSurface(surface[FOND_UNI], NULL, surface[SCREEN], &positionOrigine);
    SDL_BlitSurface(surface[PLATEAU], NULL, surface[SCREEN], &positionPlateau);
    SDL_BlitSurface(surface[TITRE_GO], NULL, surface[SCREEN], &positionTexte[TITRE]);
    SDL_BlitSurface(surface[BOUTON_SCORE], NULL, surface[SCREEN], &positionTexte[SCORE]);
    if(tour%2 == BLANC-1) SDL_BlitSurface(surface[FOND_BOUTON_110], NULL, surface[SCREEN], &positionTexte[SCORE_BLANC]);
    else SDL_BlitSurface(surface[FOND_BOUTON_110], NULL, surface[SCREEN], &positionTexte[SCORE_NOIR]);
    SDL_BlitSurface(surface[BOUTON_SCORE_NOIR], NULL, surface[SCREEN], &positionTexte[SCORE_NOIR]);
    SDL_BlitSurface(surface[BOUTON_SCORE_BLANC], NULL, surface[SCREEN], &positionTexte[SCORE_BLANC]);
    //si la souris est sur le bouton passer
    if((mouse.x > PASSER_x && mouse.x <= PASSER_x+BOUTON_w) && (mouse.y > PASSER_y && mouse.y <= PASSER_y+BOUTON_h_JEU))
    {
        SDL_BlitSurface(surface[FOND_BOUTON_110], NULL, surface[SCREEN], &positionTexte[PASSER]);
        *boutonSelectionne = PASSER;
    }
    //si la souris est sur un des trois icones
    else if((mouse.y > positionIcone[MENU].y && mouse.y <= positionIcone[MENU].y+ICONE_h) && mouse.x <= positionIcone[RETOUR].x+surface[ICONE_RETOUR]->w)
    {
        if(mouse.x > positionIcone[MENU].x && mouse.x <= positionIcone[MENU].x+ICONE_w)
        {
            SDL_BlitSurface(surface[FOND_ICONE], NULL, surface[SCREEN], &positionIcone[MENU]);
            *boutonSelectionne = MENU;
        }
        else if(mouse.x > positionIcone[RETOUR].x && mouse.x <= positionIcone[RETOUR].x+ICONE_w)
        {
            SDL_BlitSurface(surface[FOND_ICONE], NULL, surface[SCREEN], &positionIcone[RETOUR]);
            *boutonSelectionne = RETOUR;
        }
    }
    else if((mouse.x > positionIcone[PLAYER].x && mouse.x <= positionIcone[PLAYER].x+surface[ICONE_1P]->w) && (mouse.y > positionIcone[PLAYER].y && mouse.y <= positionIcone[PLAYER].y+surface[ICONE_1P]->h))
    {
        *boutonSelectionne = PLAYER;
    }
    //si la souris est sur le bouton debug
    else if((mouse.x > positionIcone[DEBUG].x && mouse.x <= positionIcone[DEBUG].x+surface[ICONE_DEBUG]->w) && (mouse.y > positionIcone[DEBUG].y && mouse.y <= positionIcone[DEBUG].y+surface[ICONE_DEBUG]->h))
    {
        *boutonSelectionne = DEBUG;
    }
    else *boutonSelectionne = AUCUNE_SELECTION;
    SDL_BlitSurface(surface[BOUTON_PASSER], NULL, surface[SCREEN], &positionTexte[PASSER]);
    SDL_BlitSurface(surface[ICONE_HOME], NULL, surface[SCREEN], &positionIcone[MENU]);
    SDL_BlitSurface(surface[ICONE_RETOUR], NULL, surface[SCREEN], &positionIcone[RETOUR]);
    if(debug) SDL_BlitSurface(surface[FOND_ICONE], NULL, surface[SCREEN], &positionIcone[DEBUG]);
    SDL_BlitSurface(surface[ICONE_DEBUG], NULL, surface[SCREEN], &positionIcone[DEBUG]);
    if(bot) SDL_BlitSurface(surface[ICONE_1P], NULL, surface[SCREEN], &positionIcone[PLAYER]);
    else SDL_BlitSurface(surface[ICONE_2P], NULL, surface[SCREEN], &positionIcone[PLAYER]);
    afficheScore(score, surface);
}

void afficheScore(int score[2], SDL_Surface* surface[NB_SURFACE])
{
    //initialisation de sdl_ttf, de la police et des variables
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("ressources/police/bauhs.ttf", 80);
    SDL_Color couleurScore = {146, 84, 30};
    SDL_Surface *texteA = NULL, *texteB = NULL;
    SDL_Rect positionA, positionB;
    char scoreN[3] = "", scoreB[3] = "";

    //ecriture des valeurs du score dans les chaines respectives
    sprintf(scoreN, "%i", score[NOIR-1]);
    sprintf(scoreB, "%i", score[BLANC-1]);

    //ecriture du texte dans les surface texteA et texteB
    texteA = TTF_RenderText_Blended(font, scoreN, couleurScore);
    texteB = TTF_RenderText_Blended(font, scoreB, couleurScore);

    //initialisation des positions des textes
    positionA.x = SCORE_NOIR_x+400;
    positionA.y = SCORE_NOIR_y+(surface[BOUTON_SCORE_NOIR]->h/2-texteA->h/2);

    positionB.x = SCORE_BLANC_x+400;
    positionB.y = SCORE_BLANC_y+(surface[BOUTON_SCORE_BLANC]->h/2-texteB->h/2);

    //blitage sur l'ecran
    SDL_BlitSurface(texteA, NULL, surface[SCREEN], &positionA);
    SDL_BlitSurface(texteB, NULL, surface[SCREEN], &positionB);

    //fermeture des surface, de sdl_ttf et de la police
    SDL_FreeSurface(texteA);
    SDL_FreeSurface(texteB);
    TTF_CloseFont(font);
    TTF_Quit();
}

