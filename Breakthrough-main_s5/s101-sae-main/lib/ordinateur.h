/**
 * @file ordinateur.h
 * @brief Les 2 stratégies de l'adversaire automatique.
 *
 * C'est le sous-problème qu'on compare : deux façons de choisir le coup de
 * l'ordinateur. On passe de l'une à l'autre en répondant à la question posée
 * au lancement, sans toucher au programme.
 */
#pragma once

#include "partie.h"

/// nombre de coups possibles au maximum : 2 lignes de pions et 3 cases devant
#define MAX_COUPS (2 * TAILLE * 3)

/// approche 1 : l'ordinateur prend un coup valide au hasard
#define STRATEGIE_HASARD 1

/// approche 2 : l'ordinateur cherche à gagner puis à manger puis joue au hasard
#define STRATEGIE_MEILLEUR 2

/// graine du hasard, fixée pour qu'une partie rejouée donne le même résultat
#define GRAINE 42

/**
 * @brief met dans une liste tous les coups valides du joueur du tour
 *
 * @param partie la partie en cours
 * @param liste le tableau qui reçoit les coups
 * @return le nombre de coups trouvés
 */
int listerCoups(Partie partie, Coup liste[MAX_COUPS]);

/**
 * @brief approche 1 : prend un coup valide au hasard
 *
 * @param partie la partie en cours
 * @return le coup choisi
 */
Coup coupAuHasard(Partie partie);

/**
 * @brief approche 2 : joue le coup gagnant sinon mange sinon au hasard
 *
 * @param partie la partie en cours
 * @return le coup choisi
 */
Coup meilleurCoup(Partie partie);

/**
 * @brief donne le coup de l'ordinateur avec la stratégie demandée
 *
 * @param partie la partie en cours
 * @param strategie STRATEGIE_HASARD ou STRATEGIE_MEILLEUR
 * @return le coup choisi
 */
Coup coupOrdinateur(Partie partie, int strategie);
