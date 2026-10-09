/**
 * @file jeu.c
 * @brief Point d'entrée du jeu : démonstration de l'utilisation d'un module
 * du dossier lib/.
 */

#include <stdio.h>

#include "./lib/exemple.h"

// taille variable du tableau
#define TAILLE 8

void deuxJoueurs(char joueur[2][30]);
void afficherRegles();
void initialiserPlateau(char mat[TAILLE][TAILLE]);
void afficherPlateau(char mat[TAILLE][TAILLE]);
void simulerDeplacementPion(char mat[TAILLE][TAILLE]);

void choisirMode();

bool estDansPlateau(int lig, int col);

int main() {
  // afficheSep est déclarée dans lib/exemple.h et définie dans lib/exemple.c
  afficheSep();

  char mat[TAILLE][TAILLE];

  choisirMode();
  afficherRegles();

  initialiserPlateau(mat);
  afficherPlateau(mat);

  simulerDeplacementPion(mat);
  afficherPlateau(mat);

  afficheSep();

  return 0;
}

void simulerDeplacementPion(char mat[TAILLE][TAILLE]) {
  // le coup va etre joué pour le joueur 1 puis cela indiquera que c'est au
  // joueur 2 de jouer
  //  on déplace un pion à la main pour vérifier l'affichage

  int jouer = 1;
  int a;
  printf("taper 1 pour jouer le coup: ");
  scanf("%d", &a);

  if (a == jouer) {
    mat[6][3] = 0;  // le pion blanc quitte D2
    mat[5][3] = 1;  // et arrive en D3

    printf("joueur 1 a fini son coup\n");
  }
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

// remet le plateau dans son état initial
void initialiserPlateau(char mat[TAILLE][TAILLE]) {
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      // 2 premières lignes : noirs (2), 2 dernières : blancs (1), sinon vide
      // (0)
      if (ligne < 2) {
        mat[ligne][colonne] = 2;
      } else if (ligne >= TAILLE - 2) {
        mat[ligne][colonne] = 1;
      } else {
        mat[ligne][colonne] = 0;
      }
    }
  }
}

// affiche le plateau tel qu'il est, sans le modifier
void afficherPlateau(char mat[TAILLE][TAILLE]) {
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
      if (mat[ligne][colonne] == 2) {
        printf("N  ");
      } else if (mat[ligne][colonne] == 1) {
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

void deuxJoueurs(char joueur[2][30]) {
  for (int i = 0; i < 2; i++) {
    printf("Nom du Joueur %d: \n ", i + 1);
    scanf("%29s", joueur[i]);
  }
}

bool estDansPlateau(int lig, int col) {
  if (lig >= 0 && lig < TAILLE && col >= 0 && col < TAILLE) {
    return true;
  }

  return false;
}

void choisirMode() {
  int choix;
  char joueur[2][30] = {"Joueur 1", "Ordinateur"};
  int tour = 0;
  puts("Choisir un mode: 1. Pour 2 joueurs, 2. Contre l'ordinateur. ");
  scanf("%d", &choix);
  switch (choix) {
    case 1:
      deuxJoueurs(joueur);
      break;

    default:
      printf("Vous jouez contre l'ordinateur \n");
      break;
  }
  printf("\nC'est à %s de jouer \n", joueur[tour]);

  // on passe au joueur 2 (sans suite pour l'instant)
  tour = 1 - tour;
  printf("\nC'est à %s de jouer \n", joueur[tour]);
}