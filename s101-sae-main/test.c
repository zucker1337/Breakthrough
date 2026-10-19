#include <stdio.h>

void choisirMode();
void deuxJoueurs(char joueur[2][30]);

int main() {
  choisirMode();
  return 0;
}

void deuxJoueurs(char joueur[2][30]) {
  for (int i = 0; i < 2; i++) {
    printf("Nom du Joueur %d: \n ", i + 1);
    scanf("%29s", joueur[i]);
  }
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
