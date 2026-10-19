/**
 * @file affichage.c
 * @brief Tout ce que le jeu écrit à l'écran : règles, plateau, tour, refus.
 */
#include "affichage.h"

#include <stdio.h>


void afficheSep() {
  printf("\n");
  for (int i = 0; i < 80; i++) {
    printf("-");
  }
  printf("\n");
}


void afficherRegles() {
  printf(
      "A son tour, un joueur déplace un de ses pions d'une case vers l'avant : "
      "tout droit ou en diagonale.\nUn pion avance tout droit uniquement si "
      "la case d'arrivée est vide\nUn pion avance en diagonale sur une case "
      "vide, ou sur une case occupée par un pion adverse qui est alors eliminé "
      "(retiré du plateau)\nOn ne prend jamais tout droit et on ne recule "
      "jamais\n");
}


void afficherPlateau(const Partie *ptrPartie) {
  // pour afficher les index des cases en lettre EN HAUT
  char Colonnelettre = 'A';

  printf("   ");
  for (int i = 0; i < TAILLE; i++) {
    printf("  %c", Colonnelettre);
    Colonnelettre++;
  }

  printf("\n");

  // affiche le tableau avec les 0 ainsi que les index des lignes
  int Ligne = TAILLE;

  printf("\n");
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    printf("%d    ", Ligne);

    for (int colonne = 0; colonne < TAILLE; colonne++) {
      // affiche N pour noir & B pour blanc, 0 pour vide
      if (ptrPartie->plateau[ligne][colonne] == PION_NOIR) {
        printf("N  ");
      } else if (ptrPartie->plateau[ligne][colonne] == PION_BLANC) {
        printf("B  ");
      } else {
        printf("0  ");
      }
    }

    // index de la ligne à droite
    printf("  %d", Ligne);
    Ligne--;

    printf("\n");
  }

  printf("\n");
  // pour afficher les index des cases en lettre EN BAS
  char LigneBas = 'A';

  printf("   ");
  for (int i = 0; i < TAILLE; i++) {
    printf("  %c", LigneBas);
    LigneBas++;
  }

  printf("\n");
}


void annoncerTour(const Partie *ptrPartie) {
  printf("\nC'est à %s de jouer (coup numéro %d)\n",
         ptrPartie->joueur[ptrPartie->tour].nom, ptrPartie->nbCoups + 1);
}


void afficherRefus(Verdict verdict) {
  switch (verdict) {
    case COUP_HORS_PLATEAU:
      printf("Coup refusé : une des deux cases est en dehors du plateau\n");
      break;

    case COUP_PAS_SON_PION:
      printf("Coup refusé : la case de départ ne contient pas un de vos pions\n");
      break;

    case COUP_MAUVAIS_DEPLACEMENT:
      printf(
          "Coup refusé : un pion avance d'une seule case vers l'avant, tout "
          "droit ou en diagonale\n");
      break;

    case COUP_TOUT_DROIT_OCCUPE:
      printf("Coup refusé : on n'avance tout droit que sur une case vide\n");
      break;

    case COUP_SUR_SON_PION:
      printf("Coup refusé : la case d'arrivée contient déjà un de vos pions\n");
      break;

    default:
      break;
  }
}
