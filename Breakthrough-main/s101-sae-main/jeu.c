/**
 * @file jeu.c
 * @brief Breakthrough : programme principal. Tout le reste du code est
 * réparti dans les modules du dossier lib/.
 */

#include "./lib/affichage.h"
#include "./lib/partie.h"
#include "./lib/plateau.h"
#include "./lib/saisie.h"


int main() {
  afficheSep();

  Partie partie;

  afficherRegles();

  int mode = choisirMode();
  initialiserJoueurs(partie.joueur, mode);
  initialiserPartie(&partie);
  jouerPartie(&partie);

  afficheSep();

  return 0;
}
