/**
 * @file gagnant.c
 * @brief Détection de la victoire et de la fin de partie.
 *
 * Vérifie les conditions de victoire, notamment l'arrivée
 * d'un pion sur la dernière rangée adverse et l'absence
 * de pions ou de coups possibles chez l'adversaire.
 */
#include "gagnant.h"

#include <stdio.h>

#include "coup.h"
#include "partie.h"

bool aAtteintDerniereRangee(const struct Partie *ptrPartie, Contenu pion) {
    int rangee = (direction(pion) == 1) ? TAILLE - 1 : 0;

    for (int colonne = 0; colonne < TAILLE; colonne++) {
        if (ptrPartie->plateau[rangee][colonne] == pion) {
            return true;
        }
    }
    return false;
}

int compterPions(const struct Partie *ptrPartie, Contenu pion) {
    int nb = 0;

    for (int ligne = 0; ligne < TAILLE; ligne++) {
        for (int colonne = 0; colonne < TAILLE; colonne++) {
            if (ptrPartie->plateau[ligne][colonne] == pion) {
                nb++;
            }
        }
    }
    return nb;
}

int gagnant(const struct Partie *ptrPartie) {
    int tour = ptrPartie->tour;
    int autre = 1 - tour;

    if (aAtteintDerniereRangee(ptrPartie, ptrPartie->joueur[autre].pion)) {
        return autre;
    }

    if (aAtteintDerniereRangee(ptrPartie, ptrPartie->joueur[tour].pion)) {
        return tour;
    }

    if (compterPions(ptrPartie, ptrPartie->joueur[tour].pion) == 0) {
        return autre;
    }

    if (!peutJouer(ptrPartie)) {
        return autre;
    }

    return PAS_DE_GAGNANT;
}

void afficherGagnant(const struct Partie *ptrPartie, int vainqueur) {
    Joueur joueur = ptrPartie->joueur[vainqueur];
    printf("\n%s gagne la partie en %d coups\n", joueur.nom, ptrPartie->nbCoups);
}

bool demanderRejouer() {
    char reponse[10] = "";

    printf("\nUne autre partie ? (o/n) : ");
    if (scanf("%9s", reponse) != 1) {
        return false;
    }

    return reponse[0] == 'o' || reponse[0] == 'O';
}
