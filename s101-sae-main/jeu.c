/**
 * @file jeu.c
 * @brief Programme principal du jeu Breakthrough.
 *
 * Ce fichier ne fait que l'enchaînement des parties. Le plateau, les coups,
 * la partie et l'ordinateur sont dans lib/, l'affichage et la saisie aussi.
 */

#include <stdlib.h>

#include "lib/affichage.h"
#include "lib/coups.h"
#include "lib/ordinateur.h"
#include "lib/partie.h"
#include "lib/saisie.h"

/**
 * @brief point d'entrée du programme
 *
 * affiche les règles puis demande le mode une seule fois
 * en mode 2 demande aussi la stratégie de l'ordinateur
 * enchaîne ensuite les parties tant que les joueurs veulent rejouer
 *
 * @return 0 quand le programme s'est bien terminé
 */
int main(void) {
  Partie partie;
  bool rejouer = true;
  int strategie = STRATEGIE_HASARD;

  // graine fixe pour qu'une partie rejouée donne toujours le même résultat
  srand(GRAINE);

  afficherSeparation();
  afficherRegles();

  int mode = choisirMode();
  preparerJoueurs(&partie);

  if (mode == 1) {
    demanderNoms(&partie);
  } else {
    strategie = choisirStrategie();
  }

  while (rejouer) {
    nouvellePartie(&partie);
    afficherPlateau(partie);

    int vainqueur = PAS_DE_GAGNANT;

    while (vainqueur == PAS_DE_GAGNANT) {
      annoncerTour(partie);

      Coup coup;

      // en mode 2 le joueur d'indice 1 est l'ordinateur
      if (mode == 2 && partie.tour == 1) {
        coup = coupOrdinateur(partie, strategie);
        afficherCoupOrdinateur(partie, coup);
      } else {
        coup = saisirCoup(partie);
      }

      jouerCoup(&partie, coup);
      afficherPlateau(partie);
      changerJoueur(&partie);

      vainqueur = gagnant(partie);
    }

    afficherGagnant(partie, vainqueur);
    rejouer = demanderRejouer();
  }

  afficherSeparation();

  return 0;
}
