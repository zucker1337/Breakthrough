/**
 * @file case.c
 * @brief Gestion des coordonnées des cases.
 *
 * Regroupe les fonctions permettant de lire, représenter
 * et vérifier les coordonnées des cases du plateau.
 */

#include "case.h"
#include <stdio.h>
#include <stdlib.h>

bool estDansPlateau(int lig, int col) {
    return lig >= 0 && lig < TAILLE && col >= 0 && col < TAILLE;
}

/**
 * @brief 
 * 
 * @return Case 
 */
Case lireCase() {
    Case caseLue;
    char mot[10] = "";

    if (scanf("%9s", mot) != 1) {
        caseLue.ligne = -1;
        caseLue.colonne = -1;
        return caseLue;
    }

    if (mot[0] >= 'a' && mot[0] <= 'z') {
        mot[0] = (char)(mot[0] - 'a' + 'A');
    }

    caseLue.colonne = mot[0] - 'A';
    caseLue.ligne = TAILLE - atoi(&mot[1]);
    return caseLue;
}
