#pragma once

#include "case.h"
#include "plateau.h"

typedef struct {
    Case depart;
    Case arrivee;
} Coup;

typedef enum {
    COUP_OK,
    COUP_HORS_PLATEAU,
    COUP_PAS_SON_PION,
    COUP_MAUVAIS_DEPLACEMENT,
    COUP_TOUT_DROIT_OCCUPE,
    COUP_SUR_SON_PION
} Verdict;

struct Partie;
Verdict verifierCoup(const struct Partie *ptrPartie, Coup coup);
void afficherRefus(Verdict verdict);
Coup saisirCoup(const struct Partie *ptrPartie);
void jouerCoup(struct Partie *ptrPartie, Coup coup);
bool peutJouer(const struct Partie *ptrPartie);
