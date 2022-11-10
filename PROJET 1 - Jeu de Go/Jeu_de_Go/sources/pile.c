/*

    fonctions permettant la gestion de la pile de RETOUR

*/

#include <stdlib.h>

#include "../include/pile.h"
#include "../include/constantes.h"

pel creeElem(coordonnee val)
{
    pel tmp;
    tmp = (pel)malloc(sizeof(tel));
    tmp->pion = val;
    tmp->suivant = NULL;
    return tmp;
}

pel empiler(pel p, coordonnee val)
{
    pel tmp;
    tmp = creeElem(val);
    tmp->suivant = p;
    p = tmp;
    return p;
}

pel depiler(pel p, coordonnee *pval)
{
    pel tmp = p;
    p = p->suivant;
    *pval = tmp->pion;
    free(tmp);
    return p;
}

