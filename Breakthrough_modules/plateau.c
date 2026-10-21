/**
 * @file plateau.c
 * @brief Initialisation et affichage du plateau de jeu.
 *
 * Gère la représentation du plateau et l'affichage
 * des cases, des lignes et des colonnes.
 */
#include "plateau.h"
#include <stdio.h>

void initialiserPlateau(char plateau[TAILLE][TAILLE]) {
    for (int ligne = 0; ligne < TAILLE; ligne++) {
        for (int colonne = 0; colonne < TAILLE; colonne++) {
            if (ligne < 2) {
                plateau[ligne][colonne] = PION_NOIR;
            } else if (ligne >= TAILLE - 2) {
                plateau[ligne][colonne] = PION_BLANC;
            } else {
                plateau[ligne][colonne] = CASE_VIDE;
            }
        }
    }
}

void afficherPlateau(const char plateau[TAILLE][TAILLE]) {
    printf("   ");
    for (int colonne = 0; colonne < TAILLE; colonne++) {
        printf("  %c", 'A' + colonne);
    }
    printf("\n\n");

    for (int ligne = 0; ligne < TAILLE; ligne++) {
        printf("%d    ", TAILLE - ligne);

        for (int colonne = 0; colonne < TAILLE; colonne++) {
            if (plateau[ligne][colonne] == PION_NOIR) {
                printf("N  ");
            } else if (plateau[ligne][colonne] == PION_BLANC) {
                printf("B  ");
            } else {
                printf("0  ");
            }
        }

        printf("  %d\n", TAILLE - ligne);
    }

    printf("\n   ");
    for (int colonne = 0; colonne < TAILLE; colonne++) {
        printf("  %c", 'A' + colonne);
    }
    printf("\n");
}

int direction(Contenu pion) {
    return pion == PION_BLANC ? -1 : 1;
}
