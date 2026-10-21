/**
 * @file jeu.c
 * @brief Point d'entrée du jeu Breakthrough.
 *
 * Affiche les règles, initialise le déroulement du jeu
 * et lance les parties.
 */
#include <stdio.h>
#include <stdbool.h>

#include "gagnant.h"
#include "joueur.h"
#include "partie.h"

static void afficheSep() {
    puts("--------------------------------------------------");
}



int main() {
    afficheSep();
    void afficherRegles();
    Partie partie;
    bool rejouer = true;

    afficherRegles();

    int mode = choisirMode();
    nommerJoueurs(&partie, mode);

    while (rejouer) {
        initialiserPartie(&partie);
        int vainqueur = jouerPartie(&partie);
        afficherGagnant(&partie, vainqueur);
        rejouer = demanderRejouer();
    }

    afficheSep();
    return 0;
}
