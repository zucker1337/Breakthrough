#pragma once

#include "case.h"

typedef enum {
    CASE_VIDE,
    PION_BLANC,
    PION_NOIR
} Contenu;

void initialiserPlateau(char plateau[TAILLE][TAILLE]);
void afficherPlateau(const char plateau[TAILLE][TAILLE]);
int direction(Contenu pion);
