/**
 * @file affichage.h
 * @brief Tout ce que le jeu écrit sur la sortie standard.
 */
#pragma once

#include "partie.h"

/**
 * @brief affiche une ligne de séparation
 */
void afficherSeparation(void);

/**
 * @brief affiche les règles du jeu
 */
void afficherRegles(void);

/**
 * @brief affiche le plateau de la partie
 *
 * les lettres des colonnes sont affichées en haut et en bas du plateau
 * les numéros de lignes sont affichés à gauche et à droite
 * une case vide s'affiche 0 un pion blanc s'affiche B et un pion noir N
 *
 * @param partie la partie dont on affiche le plateau
 */
void afficherPlateau(Partie partie);

/**
 * @brief annonce le joueur dont c'est le tour
 *
 * @param partie la partie en cours
 */
void annoncerTour(Partie partie);

/**
 * @brief affiche le coup que l'ordinateur vient de choisir
 *
 * @param partie la partie en cours
 * @param coup le coup choisi par l'ordinateur
 */
void afficherCoupOrdinateur(Partie partie, Coup coup);

/**
 * @brief explique au joueur pourquoi son coup est refusé
 *
 * @param verdict la réponse rendue par verifierCoup
 */
void afficherRefus(Verdict verdict);

/**
 * @brief annonce le résultat de la partie en nommant le gagnant
 *
 * @param partie la partie finie
 * @param vainqueur l'indice du joueur qui a gagné
 */
void afficherGagnant(Partie partie, int vainqueur);
