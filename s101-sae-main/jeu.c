/**
 * @file jeu.c
 * @brief Point d'entrée du jeu : démonstration de l'utilisation d'un module
 * du dossier lib/.
 */
#include <stdio.h>

#include "./lib/exemple.h"

int main() {
  // afficheSep est déclarée dans lib/exemple.h et définie dans lib/exemple.c
  afficheSep();

  printf("Hello world with separators!\n");

  afficheSep();

  return 0;
}