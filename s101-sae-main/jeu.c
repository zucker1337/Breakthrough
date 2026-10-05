/**
 * @file jeu.c
 * @brief Point d'entrée du jeu : démonstration de l'utilisation d'un module
 * du dossier lib/.
 */


#include <stdio.h>

#include "./lib/exemple.h"

void afficherRegles();
int plateau(int mat[8][8]);

int main() {
  // afficheSep est déclarée dans lib/exemple.h et définie dans lib/exemple.c
   afficheSep();

  
  int choix, mat[8][8];
  puts("Choisir un mode: 1. Pour 2 joueurs, 2. Contre l'ordinateur. ");
  scanf("%d", &choix);
  afficherRegles();
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

int plateau(int mat[8][8]) {



  // pour afficher les index des cases en lettre EN HAUT
  char Colonnelettre = 'A';

  printf("   ");
  for (int i = 0; i < 8; i++) {
    printf("  %c", Colonnelettre);
    Colonnelettre++;
  }
  
  printf("\n");



  // affiche le tableau avec les 0 ainsi que les index des lignes
  int Ligne = 8;

  printf("\n");
  for (int ligne = 0; ligne < 8; ligne++) {
    

    printf("%d    ", Ligne);
    Ligne--;

    for (int colonne = 0; colonne < 8; colonne++) {

      mat[ligne][colonne] = 0;
      
      printf("%d  ", mat[ligne][colonne]);

    }

    printf("\n");
  }





  printf("\n");
  // pour afficher les index des cases en lettre EN BAS
  char LigneBas = 'A';

  printf("   ");
  for (int i = 0; i < 8; i++) {
    printf("  %c", LigneBas);
    LigneBas++;
  }
  
  printf("\n");
  

  return 0;
}
