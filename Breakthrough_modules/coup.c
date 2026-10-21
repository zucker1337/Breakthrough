/**
 * @file coup.c
 * @brief Saisie et vérification des coups.
 *
 * Contrôle les coordonnées des déplacements et vérifie
 * que les coups respectent les règles de Breakthrough.
 */
#include "coup.h"

#include <stdio.h>

#include "partie.h"

/**
 * @brief 
 * 
 * @param ptrPartie 
 * @param coup 
 * @return Verdict 
 */
Verdict verifierCoup(const struct Partie *ptrPartie, Coup coup) {
    Case depart = coup.depart;
    Case arrivee = coup.arrivee;
    Contenu pion = ptrPartie->joueur[ptrPartie->tour].pion;

    if (!estDansPlateau(depart.ligne, depart.colonne) ||
        !estDansPlateau(arrivee.ligne, arrivee.colonne)) {
        return COUP_HORS_PLATEAU;
    }

    if (ptrPartie->plateau[depart.ligne][depart.colonne] != pion) {
        return COUP_PAS_SON_PION;
    }

    int ecart = arrivee.colonne - depart.colonne;
    if (ecart < 0) {
        ecart = -ecart;
    }

    if (arrivee.ligne != depart.ligne + direction(pion) || ecart > 1) {
        return COUP_MAUVAIS_DEPLACEMENT;
    }

  
    char contenuArrivee = ptrPartie->plateau[arrivee.ligne][arrivee.colonne];

    if (ecart == 0 && contenuArrivee != CASE_VIDE) {
        return COUP_TOUT_DROIT_OCCUPE;
    }

    if (contenuArrivee == pion) {
        return COUP_SUR_SON_PION;
    }

    return COUP_OK;
}

/**
 * @brief 
 * 
 * @param verdict 
 */
void afficherRefus(Verdict verdict) {
    switch (verdict) {
        case COUP_HORS_PLATEAU:
            puts("Coup refusé : une des deux cases est en dehors du plateau");
            break;
        case COUP_PAS_SON_PION:
            puts("Coup refusé : la case de départ ne contient pas un de vos pions");
            break;
        case COUP_MAUVAIS_DEPLACEMENT:
            puts("Coup refusé : un pion avance d'une seule case vers l'avant, tout droit ou en diagonale");
            break;
        case COUP_TOUT_DROIT_OCCUPE:
            puts("Coup refusé : on n'avance tout droit que sur une case vide");
            break;
        case COUP_SUR_SON_PION:
            puts("Coup refusé : la case d'arrivée contient déjà un de vos pions");
            break;
        default:
            break;
    }
}

bool peutJouer(const struct Partie *ptrPartie) {
    Contenu pion = ptrPartie->joueur[ptrPartie->tour].pion;
    Coup coup;

    for (int ligne = 0; ligne < TAILLE; ligne++) {
        for (int colonne = 0; colonne < TAILLE; colonne++) {
            if (ptrPartie->plateau[ligne][colonne] == pion) {
                coup.depart.ligne = ligne;
                coup.depart.colonne = colonne;

                for (int ecart = -1; ecart <= 1; ecart++) {
                    coup.arrivee.ligne = ligne + direction(pion);
                    coup.arrivee.colonne = colonne + ecart;

                    if (verifierCoup(ptrPartie, coup) == COUP_OK) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

Coup saisirCoup(const struct Partie *ptrPartie) {
    Joueur joueur = ptrPartie->joueur[ptrPartie->tour];
    Coup coup;
    Verdict verdict = COUP_HORS_PLATEAU;

    while (verdict != COUP_OK) {
        printf("%s, votre coup (ex : B2 B3) : ", joueur.nom);
        coup.depart = lireCase();
        coup.arrivee = lireCase();
        verdict = verifierCoup(ptrPartie, coup);
        if (verdict != COUP_OK) {
            afficherRefus(verdict);
        }
    }

    return coup;
}

void jouerCoup(struct Partie *ptrPartie, Coup coup) {
    Case depart = coup.depart;
    Case arrivee = coup.arrivee;

    ptrPartie->plateau[arrivee.ligne][arrivee.colonne] =
        ptrPartie->plateau[depart.ligne][depart.colonne];
    ptrPartie->plateau[depart.ligne][depart.colonne] = CASE_VIDE;
    ptrPartie->nbCoups++;
}
