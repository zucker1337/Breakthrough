/**
 * @file regles.c
 * @brief Logique du jeu : validité d'un coup et coups encore possibles.
 * Aucun affichage, aucune saisie : utilisable par l'ordinateur.
 */
#include "regles.h"

#include "plateau.h"


int direction(Contenu pion) {
  if (pion == PION_BLANC) {
    return -1;
  }

  return 1;
}

Verdict verifierCoup(const Partie *ptrPartie, Coup coup) {
  if (!estDansPlateau(coup.depart.ligne, coup.depart.colonne) ||
      !estDansPlateau(coup.arrivee.ligne, coup.arrivee.colonne)) {
    return COUP_HORS_PLATEAU;
  }

  Contenu pion = ptrPartie->joueur[ptrPartie->tour].pion;

  if (ptrPartie->plateau[coup.depart.ligne][coup.depart.colonne] != pion) {
    return COUP_PAS_SON_PION;
  }

  // écart de colonnes en valeur absolue
  int ecart = coup.arrivee.colonne - coup.depart.colonne;
  if (ecart < 0) {
    ecart = -ecart;
  }

  if (coup.arrivee.ligne != coup.depart.ligne + direction(pion) || ecart > 1) {
    return COUP_MAUVAIS_DEPLACEMENT;
  }

  char contenuArrivee = ptrPartie->plateau[coup.arrivee.ligne][coup.arrivee.colonne];

  if (ecart == 0 && contenuArrivee != CASE_VIDE) {
    return COUP_TOUT_DROIT_OCCUPE;
  }

  if (contenuArrivee == pion) {
    return COUP_SUR_SON_PION;
  }

  return COUP_OK;
}

bool peutJouer(const Partie *ptrPartie) {
  Contenu pion = ptrPartie->joueur[ptrPartie->tour].pion;
  Coup coup;

  for (int ligne = 0; ligne < TAILLE; ligne++) {
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      if (ptrPartie->plateau[ligne][colonne] == pion) {
        coup.depart.ligne = ligne;
        coup.depart.colonne = colonne;

        // les 3 cases devant le pion : diagonale gauche, tout droit, diagonale droite
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
