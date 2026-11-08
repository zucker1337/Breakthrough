/**
 * @file partie.c
 * @brief Les types du jeu et ce qui concerne la partie entière.
 *
 * Ce module ne fait aucun affichage et aucune saisie. C'est lui qui répond à
 * la question "y a-t-il un vainqueur ?".
 */
#include "partie.h"

#include <string.h>

#include "coups.h"
#include "plateau.h"

void preparerJoueurs(Partie *ptrPartie) {
  // les blancs commencent donc ils sont le joueur d'indice 0
  ptrPartie->joueur[0].pion = PION_BLANC;
  ptrPartie->joueur[1].pion = PION_NOIR;
  strcpy(ptrPartie->joueur[0].nom, "Joueur 1");
  strcpy(ptrPartie->joueur[1].nom, "Ordinateur");
}

void nouvellePartie(Partie *ptrPartie) {
  initialiserPlateau(ptrPartie);
  ptrPartie->tour = 0;
  ptrPartie->nbCoups = 0;
}

void changerJoueur(Partie *ptrPartie) { ptrPartie->tour = 1 - ptrPartie->tour; }

Contenu pionDuTour(Partie partie) { return partie.joueur[partie.tour].pion; }

int gagnant(Partie partie) {
  int autre = 1 - partie.tour;

  // le joueur qui vient de jouer est celui qui peut avoir atteint le bout
  if (aAtteintDerniereRangee(partie, partie.joueur[autre].pion)) {
    return autre;
  }

  if (aAtteintDerniereRangee(partie, pionDuTour(partie))) {
    return partie.tour;
  }

  // le joueur du tour est mangé ou bloqué donc l'autre gagne
  if (compterPions(partie, pionDuTour(partie)) == 0) {
    return autre;
  }

  if (!peutJouer(partie)) {
    return autre;
  }

  return PAS_DE_GAGNANT;
}
