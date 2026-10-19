/**
 * @file affichage.h
 * @brief Tout ce que le jeu écrit à l'écran : règles, plateau, tour, refus.
 */
#pragma once

#include "types.h"

void afficheSep();
void afficherRegles();
void afficherPlateau(const Partie *ptrPartie);
void annoncerTour(const Partie *ptrPartie);
void afficherRefus(Verdict verdict);
