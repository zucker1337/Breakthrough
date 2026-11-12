/**
 * @file ordinateur.c
 * @brief Les 2 stratégies de l'adversaire automatique.
 *
 * Ce module ne fait aucun affichage et aucune saisie. Il rend juste un coup,
 * et c'est main qui l'affiche et le joue.
 */
#include "ordinateur.h"

#include <stdlib.h>

#include "coups.h"
#include "plateau.h"

int listerCoups(Partie partie, Coup liste[MAX_COUPS]) {
  Contenu pion = pionDuTour(partie);
  int nb = 0;

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

        // on garde seulement les coups que la vérification accepte
        if (verifierCoup(partie, coup) == COUP_OK) {
          liste[nb] = coup;
          nb++;
        }
      }
    }
  }

  return nb;
}

Coup coupAuHasard(Partie partie) {
  Coup liste[MAX_COUPS];

  int nb = listerCoups(partie, liste);

  // il y a toujours au moins un coup sinon gagnant aurait arrêté la partie
  return liste[rand() % nb];
}

Coup meilleurCoup(Partie partie) {
  Coup liste[MAX_COUPS];
  Contenu pion = pionDuTour(partie);

  int nb = listerCoups(partie, liste);

  // la rangée qu'il faut atteindre pour gagner
  int rangeeGagnante = 0;
  if (direction(pion) == 1) {
    rangeeGagnante = TAILLE - 1;
  }

  // premier choix : un coup qui gagne tout de suite
  for (int i = 0; i < nb; i++) {
    if (liste[i].arrivee.ligne == rangeeGagnante) {
      return liste[i];
    }
  }

  // deuxième choix : manger un pion adverse
  // une case d'arrivée pas vide sur un coup valide c'est forcément l'adversaire
  for (int i = 0; i < nb; i++) {
    Case arrivee = liste[i].arrivee;

    if (partie.plateau[arrivee.ligne][arrivee.colonne] != CASE_VIDE) {
      return liste[i];
    }
  }

  // rien de mieux à faire donc on prend au hasard
  return liste[rand() % nb];
}

Coup coupOrdinateur(Partie partie, int strategie) {
  if (strategie == STRATEGIE_HASARD) {
    return coupAuHasard(partie);
  }

  return meilleurCoup(partie);
}
