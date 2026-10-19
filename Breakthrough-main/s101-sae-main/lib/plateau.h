/**
 * @file plateau.h
 * @brief État de la partie : mise en place du plateau et modifications après
 * un coup. Aucun affichage, aucune saisie.
 */
#pragma once

#include "types.h"

void initialiserPartie(Partie *ptrPartie);
bool estDansPlateau(int lig, int col);
void jouerCoup(Partie *ptrPartie, Coup coup);
void changerJoueur(Partie *ptrPartie);
