/**
 * @file joueur.c
 * @brief Gestion des joueurs de Breakthrough.
 *
 * Gère les informations des joueurs, notamment leur nom
 * et la couleur de leurs pions.
 */
#include "joueur.h"

#include <stdio.h>
#include <string.h>

#include "partie.h"

int choisirMode() {
    int choix = 0;
    puts("Choisir un mode : 1. Pour 2 joueurs, 2. Contre l'ordinateur.");
    if (scanf("%d", &choix) != 1 || choix != 1) {
        choix = 2;
    }
    return choix;
}

void deuxJoueurs(Joueur joueur[NB_JOUEURS]) {
    for (int i = 0; i < NB_JOUEURS; i++) {
        printf("Nom du Joueur %d : ", i + 1);
        scanf("%29s", joueur[i].nom);
    }
}

void nommerJoueurs(struct Partie *ptrPartie, int mode) {
    ptrPartie->joueur[0].pion = PION_BLANC;
    ptrPartie->joueur[1].pion = PION_NOIR;
    strcpy(ptrPartie->joueur[0].nom, "Joueur 1");
    strcpy(ptrPartie->joueur[1].nom, "Ordinateur");

    if (mode == 1) {
        deuxJoueurs(ptrPartie->joueur);
    } else {
        printf("Vous jouez contre l'ordinateur.\n");
        printf("Attention : le mode ordinateur n'est pas implémenté dans ce code.\n");
    }
}
