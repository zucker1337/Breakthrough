#pragma once

#include "plateau.h"

#define NB_JOUEURS 2
#define TAILLE_NOM 30

typedef struct {
    char nom[TAILLE_NOM];
    Contenu pion;
} Joueur;

struct Partie;
void deuxJoueurs(Joueur joueur[NB_JOUEURS]);
void nommerJoueurs(struct Partie *ptrPartie, int mode);
int choisirMode(void);
