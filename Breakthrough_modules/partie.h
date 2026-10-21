#pragma once

#include "joueur.h"

#define PAS_DE_GAGNANT (-1)

typedef struct Partie {
    char plateau[TAILLE][TAILLE];
    Joueur joueur[NB_JOUEURS];
    int tour;
    int nbCoups;
} Partie;

void initialiserPartie(Partie *ptrPartie);
void annoncerTour(const Partie *ptrPartie);
void changerJoueur(Partie *ptrPartie);
int jouerPartie(Partie *ptrPartie);
