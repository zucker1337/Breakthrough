/**
 * @file coups.c
 * @brief Les coups : vérification et déplacement des pions.
 *
 * Ce module ne fait aucun affichage et aucune saisie. Il dit si un coup est
 * valide et sinon pourquoi, donc il peut servir à un joueur humain comme à
 * l'ordinateur.
 */
#include "coups.h"

#include "plateau.h"

Verdict verifierCoup(Partie partie, Coup coup) {
  Case depart = coup.depart;
  Case arrivee = coup.arrivee;
  Contenu pion = pionDuTour(partie);

  // on vérifie d'abord les cases sinon on lirait en dehors du tableau
  if (!estDansPlateau(depart.ligne, depart.colonne) ||
      !estDansPlateau(arrivee.ligne, arrivee.colonne)) {
    return COUP_HORS_PLATEAU;
  }

  // on ne déplace que ses propres pions
  if (partie.plateau[depart.ligne][depart.colonne] != pion) {
    return COUP_PAS_SON_PION;
  }

  // de combien de colonnes le pion se décale
  int ecart = arrivee.colonne - depart.colonne;
  if (ecart < 0) {
    ecart = -ecart;
  }

  // une seule case vers l'avant et au plus une colonne de côté
  if (arrivee.ligne != depart.ligne + direction(pion) || ecart > 1) {
    return COUP_MAUVAIS_DEPLACEMENT;
  }

  // ce qu'il y a sur la case visée
  char cible = partie.plateau[arrivee.ligne][arrivee.colonne];

  // ecart valant 0 veut dire tout droit et tout droit ne prend jamais
  if (ecart == 0 && cible != CASE_VIDE) {
    return COUP_TOUT_DROIT_OCCUPE;
  }

  // en diagonale on peut manger un pion adverse mais pas le sien
  if (cible == pion) {
    return COUP_SUR_SON_PION;
  }

  return COUP_OK;
}

void jouerCoup(Partie *ptrPartie, Coup coup) {
  Case depart = coup.depart;
  Case arrivee = coup.arrivee;

  // le pion qu'on est en train de déplacer
  char pionQuiBouge = ptrPartie->plateau[depart.ligne][depart.colonne];

  // on le pose sur la case d'arrivée et un pion adverse est écrasé donc mangé
  ptrPartie->plateau[arrivee.ligne][arrivee.colonne] = pionQuiBouge;

  // le pion a quitté sa case de départ qui devient vide
  ptrPartie->plateau[depart.ligne][depart.colonne] = CASE_VIDE;

  // un coup valide de plus dans la partie
  ptrPartie->nbCoups++;
}

bool peutJouer(Partie partie) {
  Contenu pion = pionDuTour(partie);

  // on passe sur toutes les cases du plateau pour trouver ses pions
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      // cette case n'est pas un de ses pions donc on passe à la suivante
      if (partie.plateau[ligne][colonne] != pion) {
        continue;
      }

      // les 3 cases devant le pion : -1 et 1 en diagonale 0 tout droit
      for (int ecart = -1; ecart <= 1; ecart++) {
        Coup coup;

        coup.depart.ligne = ligne;
        coup.depart.colonne = colonne;
        coup.arrivee.ligne = ligne + direction(pion);
        coup.arrivee.colonne = colonne + ecart;

        // un seul coup accepté suffit pour dire que le joueur peut jouer
        if (verifierCoup(partie, coup) == COUP_OK) {
          return true;
        }
      }
    }
  }

  // aucun pion n'avait de case où aller
  return false;
}
