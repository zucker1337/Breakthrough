/**
 * @file partie.c
 * @brief Déroulement d'une partie : alternance des joueurs jusqu'à la fin.
 */
#include "partie.h"

#include <stdio.h>

#include "affichage.h"
#include "plateau.h"
#include "regles.h"
#include "saisie.h"


void jouerPartie(Partie *ptrPartie) {
  Coup coup;

  afficherPlateau(ptrPartie);

  while (peutJouer(ptrPartie)) {
    annoncerTour(ptrPartie);

    if (!saisirCoup(ptrPartie, &coup)) {
      printf("\nPlus rien à lire la partie s'arrete là\n");
      return;
    }

    jouerCoup(ptrPartie, coup);
    afficherPlateau(ptrPartie);
    changerJoueur(ptrPartie);
  }

  printf("\n%s ne peut plus jouer la partie est terminée après %d coups\n",
         ptrPartie->joueur[ptrPartie->tour].nom, ptrPartie->nbCoups);
}
