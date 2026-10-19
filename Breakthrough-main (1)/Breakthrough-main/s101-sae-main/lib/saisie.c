/**
 * @file saisie.c
 * @brief Tout ce que le jeu lit au clavier : mode, noms des joueurs, coups.
 */
#include "saisie.h"

#include <stdio.h>
#include <string.h>

#include "affichage.h"
#include "regles.h"


int choisirMode() {
  int choix = 0;
  puts("Choisir un mode: 1. Pour 2 joueurs, 2. Contre l'ordinateur. ");
  scanf("%d", &choix);

  if (choix != 1) {
    choix = 2;
  }

  return choix;
}


void initialiserJoueurs(Joueur joueur[NB_JOUEURS], int mode) {
  strcpy(joueur[0].nom, "Joueur 1");
  strcpy(joueur[1].nom, "Ordinateur");

  if (mode == 1) {
    deuxJoueurs(joueur);
  } else {
    printf("Vous jouez contre l'ordinateur \n");
  }
}


void deuxJoueurs(Joueur joueur[NB_JOUEURS]) {
  for (int i = 0; i < NB_JOUEURS; i++) {
    printf("Nom du Joueur %d : ", i + 1);

    // 29 caractères au maximum pour laisser la place au zéro final
    scanf("%29s", joueur[i].nom);
  }
}


void viderLigne() {
  // saute tout jusqu'au retour à la ligne, puis le retour à la ligne lui-même
  scanf("%*[^\n]");
  scanf("%*c");
}


Lecture lireCase(Case *ptrCase) {
  // 0 veut dire "rien lu" : scanf ne touche pas la variable s'il n'a rien pu lire
  char lettre = 0;
  int rangee = 0;

  scanf(" %c", &lettre);

  // aucune lettre lue : il n'y a plus rien à lire
  if (lettre == 0) {
    return LECTURE_FINIE;
  }

  scanf("%d", &rangee);

  // pas de nombre après la lettre (ou rangée 0 qui n'existe pas) : saisie illisible
  if (rangee == 0) {
    viderLigne();
    return LECTURE_ILLISIBLE;
  }

  // on accepte aussi les lettres minuscules
  if (lettre >= 'a' && lettre <= 'z') {
    lettre = lettre - 'a' + 'A';
  }

  ptrCase->colonne = lettre - 'A';
  ptrCase->ligne = TAILLE - rangee;

  return LECTURE_OK;
}


bool saisirCoup(const Partie *ptrPartie, Coup *ptrCoup) {
  Verdict verdict = COUP_HORS_PLATEAU;

  while (verdict != COUP_OK) {
    printf("%s, votre coup (ex : B2 B3) : ",
           ptrPartie->joueur[ptrPartie->tour].nom);

    Lecture lecture = lireCase(&ptrCoup->depart);
    if (lecture == LECTURE_OK) {
      lecture = lireCase(&ptrCoup->arrivee);
    }

    if (lecture == LECTURE_FINIE) {
      return false;
    }

    if (lecture == LECTURE_ILLISIBLE) {
      printf("Coup refusé : il faut taper deux cases comme B2 B3\n");
    } else {
      verdict = verifierCoup(ptrPartie, *ptrCoup);
      afficherRefus(verdict);
    }
  }

  return true;
}
