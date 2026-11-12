/**
 * @file coups.h
 * @brief Les coups : vérification et déplacement des pions.
 */
#pragma once

#include "partie.h"
#include <stdbool.h>

/**
 * @brief vérifie un coup pour le joueur dont c'est le tour
 *
 * @param partie la partie en cours
 * @param coup le coup à vérifier
 * @return COUP_OK si le coup est jouable sinon la raison du refus
 */
Verdict verifierCoup(Partie partie, Coup coup);

/**
 * @brief place un coup valide sur le plateau
 *
 * le pion quitte sa case de départ et un pion adverse présent sur la case
 * d'arrivée est retiré du plateau
 *
 * @param ptrPartie la partie en cours
 * @param coup le coup à jouer
 */
void jouerCoup(Partie *ptrPartie, Coup coup);

/**
 * @brief dit si le joueur dont c'est le tour a encore un coup jouable
 *
 * @param partie la partie en cours
 * @return true s'il reste au moins un coup valide et false sinon
 */
bool peutJouer(Partie partie);
