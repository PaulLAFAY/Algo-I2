/*

    definitions des constantes utiles au programme

*/

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

    #include <stdbool.h>

    //taille de la fenetre
    #define SCREEN_w 1280
    #define SCREEN_h 720

    //struture souris
    typedef struct
    {
        int x;
        int y;
        int state;
    }mouse;

    //parametres
    #define FPS_low 30
    #define FPS_high 60

    //structure des parametres
    typedef struct
    {                         //DANS LE FICHIER go.settings :
        int fps;                //FPS_LOW ou FPS_HIGH
        int windowState;        //0 ou 1
        int volumeMusique;      //de 0% a 100%
        int volumeBruitages;    //de 0% a 100%
    }settings;

    enum fps{LOW, HIGH};
    enum windowState{WINDOWED, FULLSCREEN};
    enum parametres{P_FPS, P_FENETRE, P_VMUSIC, P_VCHUNK};

    //differents sons
    enum typeSon{CLIC, POSE};

    //surfaces
    #define NB_SURFACE 49
    enum surface_enum
    {
        //ecran
        SCREEN,
        //global
        FOND_MENU, FOND_UNI, FOND_BOUTON_60, FOND_BOUTON_110, BOUTON_RETOUR, TITRE_GO, FOND_ICONE,
        //menu
        BOUTON_NOUVELLE_PARTIE, BOUTON_REPRENDRE_LA_PARTIE, BOUTON_PARAMETRES,
        //parametres
        BOUTON_FPS_LOW, BOUTON_FPS_HIGH, BOUTON_MUSIQUE, BOUTON_BRUITAGES, BOUTON_VOLUMES, BOUTON_CREDITS, BOUTON_FENETRE, BOUTON_MENU_PRINCIPAL, BOUTON_PLEIN_ECRAN,
        TITRE_PARAMETRES, BOUTON_BARGRAPHE_MUSIQUE, BOUTON_BARGRAPHE_BRUITAGES, BOUTON_BARGRAPHE_MUSIQUE_FOND, BOUTON_BARGRAPHE_BRUITAGES_FOND,
        //credits
        FOND_CREDITS,
        //jeu
        ICONE_HOME, ICONE_RETOUR, PLATEAU, PIERRE_BLANCHE, PIERRE_BLANCHE_ALPLHA, PIERRE_NOIR, PIERRE_NOIR_ALPHA, BOUTON_SCORE, BOUTON_SCORE_BLANC, BOUTON_SCORE_NOIR, BOUTON_PASSER, ICONE_1P, ICONE_2P,
        //debug
        LIBERTE, ICONE_DEBUG, VOISINE0, VOISINE1, VOISINE2, VOISINE3, VOISINE4, CHAINE_BLANCHE, CHAINE_NOIR
    };

    //boutons
    #define BOUTON_w 550
    #define BOUTON_h_MENU 110
    #define BOUTON_h_CREDITS 110
    #define BOUTON_h_PARAMETRES 60
    #define BOUTON_h_JEU 110
    #define ICONE_w surface[ICONE_HOME]->w
    #define ICONE_h surface[ICONE_HOME]->h

    //boutons menu
    #define NOUVELLE_PARTIE_y 300
    #define REPRENDRE_LA_PARTIE_y 410
    #define PARAMETRES_y 520

    //boutons parametres
    #define VOLUMES_y 190
    #define MUSIQUE_y 270
    #define BRUITAGES_y 330
    #define BARGRAPHE_MUSIQUE_y (MUSIQUE_y+(BOUTON_h_PARAMETRES/2)-(BARGRAPHE_h/2))
    #define BARGRAPHE_BRUITAGES_y (BRUITAGES_y+(BOUTON_h_PARAMETRES/2)-(BARGRAPHE_h/2))
    #define FPS_LIMIT_y 430
    #define FENETRE_y 490
    #define CREDITS_y 550
    #define MENU_PRINCIPAL_y 630

    #define BARGRAPHE_w 200
    #define BARGRAPHE_h 30

    //boutons credits
    #define RETOUR_CREDITS_y 575

    enum boutons{NOUVELLE_PARTIE, REPRENDRE_LA_PARTIE, PARAMETRES, VOLUMES, MUSIQUE, BRUITAGES, FPS_LIMIT, FENETRE, CREDITS, MENU_PRINCIPAL, AUCUNE_SELECTION};
    enum bargraphe{BARGRAPHE_MUSIQUE, BARGRAPHE_BRUITAGES};

    //jeu
    typedef struct
    {
        int x;
        int y;
    }coordonnee;

    #define PLATEAU_x SCREEN_h-surface[PLATEAU]->h-surface[TITRE_GO]->h
    #define PLATEAU_y surface[TITRE_GO]->h
    #define PLATEAU_w surface[PLATEAU]->w
    #define PLATEAU_h surface[PLATEAU]->h

    #define TITRE_x (SCREEN_w/2)-(surface[TITRE_GO]->w/2)

    #define SCORE_x ((SCREEN_w-(PLATEAU_x+PLATEAU_w))+(PLATEAU_x+PLATEAU_w))/2
    #define SCORE_y surface[TITRE_GO]->h

    #define SCORE_NOIR_x ((SCREEN_w-(PLATEAU_x+PLATEAU_w))+(PLATEAU_x+PLATEAU_w))/2
    #define SCORE_NOIR_y SCORE_y+150

    #define SCORE_BLANC_x ((SCREEN_w-(PLATEAU_x+PLATEAU_w))+(PLATEAU_x+PLATEAU_w))/2
    #define SCORE_BLANC_y SCORE_NOIR_y+110

    #define PASSER_x ((SCREEN_w-(PLATEAU_x+PLATEAU_w))+(PLATEAU_x+PLATEAU_w))/2
    #define PASSER_y surface[TITRE_GO]->h+PLATEAU_h-surface[BOUTON_PASSER]->h

    #define MENU_x PLATEAU_x
    #define MENU_y (surface[TITRE_GO]->h/2)-(ICONE_h/2)

    #define RETOUR_x MENU_x+ICONE_w+10
    #define RETOUR_y (surface[TITRE_GO]->h/2)-(ICONE_h/2)

    #define DEBUG_x SCREEN_w-(PLATEAU_x)-surface[ICONE_DEBUG]->w
    #define DEBUG_y (surface[TITRE_GO]->h/2)-(ICONE_h/2)

    #define BOT_x DEBUG_x-surface[ICONE_1P]->w-10
    #define BOT_y (surface[TITRE_GO]->h/2)-(ICONE_h/2)

    #define PIERRE_ORIGINE_x PLATEAU_x+15
    #define PIERRE_ORIGINE_y PLATEAU_y+15

    #define CASE 26

    enum textes{TITRE, SCORE, SCORE_NOIR, SCORE_BLANC, PASSER};
    enum icones{MENU, RETOUR, PLAYER, DEBUG};
    enum typePierre{LIBRE, NOIR, BLANC};

    //pile
    typedef struct el * pel;

    typedef struct el
    {
        coordonnee pion;
        pel suivant;
    }tel;

    //gestion des territoires
    #define MAX_CHAINE 361
    #define MAX_PIERRE 361

    enum direction{UP, RIGHT, DOWN, LEFT};

    typedef struct
    {
        coordonnee position;
        int couleur;
        int nbVoisine;
        int nbLiberte;
        bool voisine[4]; //0 UP, 1 RIGHT, 2 DOWN, 3 LEFT
        bool liberte[4]; //0 UP, 1 RIGHT, 2 DOWN, 3 LEFT
        bool isChained;
    }pierreStruct;

    typedef struct
    {
        int numChaine;
        int nbPierre;
        pierreStruct* pierre;
        int nbLiberte;
        bool complete;
    }chaineStruct;

#endif // DEF_CONSTANTES
