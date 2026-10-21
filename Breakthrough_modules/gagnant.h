#pragma once

#include <stdbool.h>
#include "plateau.h"

struct Partie;

bool aAtteintDerniereRangee(const struct Partie *ptrPartie, Contenu pion);
int compterPions(const struct Partie *ptrPartie, Contenu pion);
int gagnant(const struct Partie *ptrPartie);
void afficherGagnant(const struct Partie *ptrPartie, int vainqueur);
bool demanderRejouer();
