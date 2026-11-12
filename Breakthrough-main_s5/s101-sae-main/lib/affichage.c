/**
 * @file affichage.c
 * @brief Tout ce que le jeu écrit sur la sortie standard.
 *
 * Les messages du jeu vont sur stdout. Les vraies erreurs vont sur stderr et
 * sont dans le module saisie.
 */
#include "affichage.h"

#include <stdio.h>

/// largeur de la ligne de séparation
#define LARGEUR_SEPARATION 80

void afficherSeparation(void) {
  printf("\n");
  for (int i = 0; i < LARGEUR_SEPARATION; i++) {
    printf("-");
  }
  printf("\n");
}

void afficherRegles(void) {
  printf(
      "A son tour, un joueur déplace un de ses pions d'une case vers l'avant : "
      "tout droit ou en diagonale.\nUn pion avance tout droit uniquement si "
      "la case d'arrivée est vide\nUn pion avance en diagonale sur une case "
      "vide, ou sur une case occupée par un pion adverse qui est alors eliminé "
      "(retiré du plateau)\nOn ne prend jamais tout droit et on ne recule "
      "jamais\n");
}

void afficherPlateau(Partie partie) {
  // les lettres des colonnes en haut
  char lettre = 'A';

  printf("   ");
  for (int i = 0; i < TAILLE; i++) {
    printf("  %c", lettre);
    lettre++;
  }

  printf("\n\n");

  // la rangée 8 est en haut donc le numéro descend quand la ligne monte
  int rangee = TAILLE;

  for (int ligne = 0; ligne < TAILLE; ligne++) {
    printf("%d    ", rangee);

    for (int colonne = 0; colonne < TAILLE; colonne++) {
      if (partie.plateau[ligne][colonne] == PION_NOIR) {
        printf("N  ");
      } else if (partie.plateau[ligne][colonne] == PION_BLANC) {
        printf("B  ");
      } else {
        printf("0  ");
      }
    }

    printf("  %d\n", rangee);
    rangee--;
  }

  printf("\n");

  // les mêmes lettres en bas
  lettre = 'A';

  printf("   ");
  for (int i = 0; i < TAILLE; i++) {
    printf("  %c", lettre);
    lettre++;
  }

  printf("\n");
}

void annoncerTour(Partie partie) {
  Joueur joueur = partie.joueur[partie.tour];

  printf("\nC'est à %s de jouer (coup numéro %d)\n", joueur.nom,
         partie.nbCoups + 1);
}

void afficherCoupOrdinateur(Partie partie, Coup coup) {
  Joueur joueur = partie.joueur[partie.tour];

  // on repasse des indices du tableau aux reperes affiches autour du plateau
  printf("%s joue %c%d %c%d\n", joueur.nom, 'A' + coup.depart.colonne,
         TAILLE - coup.depart.ligne, 'A' + coup.arrivee.colonne,
         TAILLE - coup.arrivee.ligne);
}

void afficherRefus(Verdict verdict) {
  switch (verdict) {
    case COUP_HORS_PLATEAU:
      printf("Coup refusé : une des deux cases est en dehors du plateau\n");
      break;

    case COUP_PAS_SON_PION:
      printf(
          "Coup refusé : la case de départ ne contient pas un de vos pions\n");
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

void afficherGagnant(Partie partie, int vainqueur) {
  Joueur joueur = partie.joueur[vainqueur];

  printf("\n%s gagne la partie en %d coups\n", joueur.nom, partie.nbCoups);
}
