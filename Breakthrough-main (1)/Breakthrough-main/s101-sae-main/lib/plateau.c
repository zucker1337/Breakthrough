/**
 * @file plateau.c
 * @brief État de la partie : mise en place du plateau et modifications après
 * un coup. Aucun affichage, aucune saisie.
 */
#include "plateau.h"


void initialiserPartie(Partie *ptrPartie) {
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

  // les blancs commencent donc ils sont le joueur d'indice 0
  ptrPartie->joueur[0].pion = PION_BLANC;
  ptrPartie->joueur[1].pion = PION_NOIR;

  ptrPartie->tour = 0;
  ptrPartie->nbCoups = 0;
}


bool estDansPlateau(int lig, int col) {
  if (lig >= 0 && lig < TAILLE && col >= 0 && col < TAILLE) {
    return true;
  }

  return false;
}


void jouerCoup(Partie *ptrPartie, Coup coup) {
  ptrPartie->plateau[coup.arrivee.ligne][coup.arrivee.colonne] =
      ptrPartie->plateau[coup.depart.ligne][coup.depart.colonne];
  ptrPartie->plateau[coup.depart.ligne][coup.depart.colonne] = CASE_VIDE;
  ptrPartie->nbCoups++;
}


void changerJoueur(Partie *ptrPartie) { ptrPartie->tour = 1 - ptrPartie->tour; }
