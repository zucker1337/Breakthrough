/**
 * @file partie.c
 * @brief Gestion du déroulement d'une partie.
 *
 * Initialise la partie, organise les tours des joueurs
 * et gère l'enchaînement des coups.
 */
#include "partie.h"

#include <stdio.h>

#include "coup.h"
#include "gagnant.h"
#include "plateau.h"

void initialiserPartie(Partie *ptrPartie) {
    initialiserPlateau(ptrPartie->plateau);
    ptrPartie->tour = 0;
    ptrPartie->nbCoups = 0;
}

void annoncerTour(const Partie *ptrPartie) {
    Joueur joueur = ptrPartie->joueur[ptrPartie->tour];
    printf("\nC'est à %s de jouer (coup numéro %d)\n",
           joueur.nom, ptrPartie->nbCoups + 1);
}

void changerJoueur(Partie *ptrPartie) {
    ptrPartie->tour = 1 - ptrPartie->tour;
}

int jouerPartie(Partie *ptrPartie) {
    int vainqueur = PAS_DE_GAGNANT;

    afficherPlateau(ptrPartie->plateau);

    while (vainqueur == PAS_DE_GAGNANT) {
        annoncerTour(ptrPartie);
        Coup coup = saisirCoup(ptrPartie);
        jouerCoup(ptrPartie, coup);
        afficherPlateau(ptrPartie->plateau);
        changerJoueur(ptrPartie);
        vainqueur = gagnant(ptrPartie);
    }

    return vainqueur;
}
