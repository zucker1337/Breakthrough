/**
 * @file jeu.c
 * @brief Point d'entrée du jeu : démonstration de l'utilisation d'un module
 * du dossier lib/.
 */


#include <stdio.h>

#include "./lib/exemple.h"

// taille variable du tableau
#define TAILLE 8

void deuxJoueurs();
void afficherRegles();
int plateau(int mat[TAILLE][TAILLE]);

int main() {
  // afficheSep est déclarée dans lib/exemple.h et définie dans lib/exemple.c
   afficheSep();


  int choix, mat[TAILLE][TAILLE];
  puts("Choisir un mode: 1. Pour 2 joueurs, 2. Contre l'ordinateur. ");
  scanf("%d", &choix);
  afficherRegles();
  
  switch (choix) {
    case 1:
      deuxJoueurs();
      break;

    default:
      printf("Vous jouez contre l'ordinateur \n");
  }
  plateau(mat);
  afficheSep();

  return 0;
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

int plateau(int mat[TAILLE][TAILLE]) {



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

      // 2 premières lignes : noirs (2), 2 dernières : blancs (1), sinon vide (0)
      if (ligne < 2) {
        mat[ligne][colonne] = 2;
      } else if (ligne >= TAILLE - 2) {
        mat[ligne][colonne] = 1;
      } else {
        mat[ligne][colonne] = 0;
      }

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


  return 0;
}


void deuxJoueurs() {
  char nom1[20], nom2[20];
  puts("\nEntrez votre nom joueur 1");
  scanf("%s", nom1);
  puts("\nEntrez votre nom joueur 2");
  scanf("%s", nom2);
  printf("\n");
}
