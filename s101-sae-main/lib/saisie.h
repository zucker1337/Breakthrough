/**
 * @file saisie.h
 * @brief Tout ce que le jeu lit au clavier.
 */
#pragma once

#include "partie.h"

/**
 * @brief demande le mode de jeu
 *
 * toute autre réponse que 1 est ramenée au mode 2
 *
 * @return 1 pour deux joueurs et 2 pour une partie contre l'ordinateur
 */
int choisirMode(void);

/**
 * @brief demande quelle stratégie l'ordinateur doit utiliser
 *
 * toute autre réponse que 1 est ramenée à la stratégie 2
 *
 * @return 1 pour jouer au hasard et 2 pour le meilleur coup
 */
int choisirStrategie(void);

/**
 * @brief demande le prénom des 2 joueurs
 *
 * @param ptrPartie la partie dont on remplit les noms
 */
void demanderNoms(Partie *ptrPartie);

/**
 * @brief lit une case tapée au clavier comme B2
 *
 * une saisie qui ne ressemble à rien donne une case en dehors du plateau
 * elle est donc refusée comme n'importe quel autre coup
 *
 * @return la case qui a été tapée
 */
Case lireCase(void);

/**
 * @brief demande un coup au joueur jusqu'à ce qu'il soit valide
 *
 * @param partie la partie en cours
 * @return le coup valide que le joueur a tapé
 */
Coup saisirCoup(Partie partie);

/**
 * @brief demande aux joueurs s'ils veulent une autre partie
 *
 * toute réponse qui ne commence pas par o arrête le jeu
 *
 * @return true pour rejouer et false pour arrêter
 */
bool demanderRejouer(void);
