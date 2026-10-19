/**
 * @file exemple.c
 * @brief Module d'exemple : définitions des fonctions déclarées dans exemple.h.
 *
 * Ce module montre comment répartir le code dans le dossier lib/ ; remplacez-le
 * par vos propres modules.
 */
#include "exemple.h"

#include <stdio.h>

/**
 * @brief Affiche une ligne de séparation.
 *
 * Cette fonction affiche une ligne de séparation de 80 -
 */
void afficheSep() {
  printf("\n");
  for (int i = 0; i < 80; i++) {
    printf("-");
  }
  printf("\n");
}