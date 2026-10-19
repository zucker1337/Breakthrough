/**
 * @file regles.h
 * @brief Logique du jeu : validité d'un coup et coups encore possibles.
 * Aucun affichage, aucune saisie : utilisable par l'ordinateur.
 */
#pragma once

#include "types.h"

int direction(Contenu pion);
Verdict verifierCoup(const Partie *ptrPartie, Coup coup);
bool peutJouer(const Partie *ptrPartie);
