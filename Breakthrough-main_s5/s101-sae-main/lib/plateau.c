/**
 * @file plateau.c
 * @brief Le plateau : mise en place et lecture des cases.
 *
 * Ce module ne fait aucun affichage et aucune saisie.
 */
#include "plateau.h"
#include <stdbool.h>

void initialiserPlateau(Partie *ptrPartie) {
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      // 2 premières lignes : noirs, 2 dernières : blancs, sinon vide
      if (ligne < 2) {
        ptrPartie->plateau[ligne][colonne] = PION_NOIR;
      } else if (ligne >= TAILLE - 2) {
        ptrPartie->plateau[ligne][colonne] = PION_BLANC;
      } else {
        ptrPartie->plateau[ligne][colonne] = CASE_VIDE;
      }
    }
  }
}

bool estDansPlateau(int ligne, int colonne) {
  if (ligne >= 0 && ligne < TAILLE && colonne >= 0 && colonne < TAILLE) {
    return true;
  }

  return false;
}

int direction(Contenu pion) {
  if (pion == PION_BLANC) {
    return -1;
  }

  return 1;
}

int compterPions(Partie partie, Contenu pion) {
  int nb = 0;

  for (int ligne = 0; ligne < TAILLE; ligne++) {
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      if (partie.plateau[ligne][colonne] == pion) {
        nb++;
      }
    }
  }

  return nb;
}

bool aAtteintDerniereRangee(Partie partie, Contenu pion) {
  int rangee = 0;

  // les noirs descendent donc leur rangée d'arrivée est en bas du tableau
  if (direction(pion) == 1) {
    rangee = TAILLE - 1;
  }

  for (int colonne = 0; colonne < TAILLE; colonne++) {
    if (partie.plateau[rangee][colonne] == pion) {
      return true;
    }
  }

  return false;
}
