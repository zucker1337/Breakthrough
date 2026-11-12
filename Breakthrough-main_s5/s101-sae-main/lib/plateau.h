/**
 * @file plateau.h
 * @brief Le plateau : mise en place et lecture des cases.
 */
#pragma once

#include "partie.h"
#include <stdbool.h>

/**
 * @brief place les pions de départ sur le plateau
 *
 * les noirs vont sur les 2 premières lignes et les blancs sur les 2 dernières
 *
 * @param ptrPartie la partie dont on remplit le plateau
 */
void initialiserPlateau(Partie *ptrPartie);

/**
 * @brief dit si une case se trouve dans le plateau
 *
 * @param ligne le numéro de ligne à tester
 * @param colonne le numéro de colonne à tester
 * @return true si la case est dans le plateau et false sinon
 */
bool estDansPlateau(int ligne, int colonne);

/**
 * @brief donne le sens dans lequel un pion avance
 *
 * @param pion PION_BLANC ou PION_NOIR
 * @return -1 pour les blancs qui montent vers la ligne 0 et 1 pour les noirs
 */
int direction(Contenu pion);

/**
 * @brief compte les pions d'un camp encore sur le plateau
 *
 * @param partie la partie en cours
 * @param pion PION_BLANC ou PION_NOIR
 * @return le nombre de pions de ce camp
 */
int compterPions(Partie partie, Contenu pion);

/**
 * @brief dit si un pion a atteint la dernière rangée adverse
 *
 * les blancs visent la ligne 0 et les noirs la ligne TAILLE - 1
 *
 * @param partie la partie en cours
 * @param pion PION_BLANC ou PION_NOIR
 * @return true si un pion de ce camp est arrivé au bout et false sinon
 */
bool aAtteintDerniereRangee(Partie partie, Contenu pion);
