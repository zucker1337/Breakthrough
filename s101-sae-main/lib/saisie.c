/**
 * @file saisie.c
 * @brief Tout ce que le jeu lit au clavier.
 *
 * Les invites vont sur la sortie standard. Seules les vraies erreurs, comme
 * des saisies épuisées, vont sur la sortie d'erreur.
 */
#include "saisie.h"

#include <stdio.h>
#include <stdlib.h>

#include "affichage.h"
#include "coups.h"

/**
 * @brief arrête le jeu quand il n'y a plus rien à lire
 *
 * le message part sur la sortie d'erreur et le code de retour est 1 pour
 * dire que ça s'est mal passé
 */
static void arreterSaisies(void) {
  fprintf(stderr,
          "Erreur : les saisies sont épuisées, la partie est arrêtée\n");
  exit(1);
}

int choisirMode(void) {
  int choix = 0;

  puts("Choisir un mode: 1. Pour 2 joueurs, 2. Contre l'ordinateur. ");

  if (scanf("%d", &choix) != 1) {
    arreterSaisies();
  }

  if (choix != 1) {
    choix = 2;
    printf("Vous jouez contre l'ordinateur\n");
  }

  return choix;
}

int choisirStrategie(void) {
  int choix = 0;

  puts("Stratégie de l'ordinateur : 1. Au hasard, 2. Le meilleur coup. ");

  if (scanf("%d", &choix) != 1) {
    arreterSaisies();
  }

  if (choix != 1) {
    choix = 2;
  }

  return choix;
}

void demanderNoms(Partie* ptrPartie) {
  for (int i = 0; i < NB_JOUEURS; i++) {
    printf("Nom du Joueur %d : ", i + 1);

    // 29 caractères au maximum pour laisser la place au zéro final
    if (scanf("%29s", ptrPartie->joueur[i].nom) != 1) {
      arreterSaisies();
    }
  }
}

Case lireCase(void) {
  Case caseLue = {0, 0};
  char mot[TAILLE_SAISIE] = "";

  if (scanf("%9s", mot) != 1) {
    arreterSaisies();
  }

  // on accepte aussi les lettres minuscules
  if (mot[0] >= 'a' && mot[0] <= 'z') {
    mot[0] = mot[0] - 'a' + 'A';
  }

  caseLue.colonne = mot[0] - 'A';
  caseLue.ligne = TAILLE - atoi(&mot[1]);

  return caseLue;
}

Coup saisirCoup(Partie partie) {
  Coup coup;
  Verdict verdict = COUP_HORS_PLATEAU;

  while (verdict != COUP_OK) {
    printf("%s, votre coup (ex : B2 B3) : ", partie.joueur[partie.tour].nom);

    coup.depart = lireCase();
    coup.arrivee = lireCase();

    verdict = verifierCoup(partie, coup);
    afficherRefus(verdict);
  }

  return coup;
}

bool demanderRejouer(void) {
  char reponse[TAILLE_SAISIE] = "";

  printf("\nUne autre partie ? (o/n) : ");

  if (scanf("%9s", reponse) != 1) {
    arreterSaisies();
  }

  if (reponse[0] == 'o' || reponse[0] == 'O') {
    return true;
  }

  return false;
}
