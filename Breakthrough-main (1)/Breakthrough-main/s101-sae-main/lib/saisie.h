/**
 * @file saisie.h
 * @brief Tout ce que le jeu lit au clavier : mode, noms des joueurs, coups.
 */
#pragma once

#include "types.h"

/**
 * @brief résultat de la lecture d'une case au clavier
 */
typedef enum {
  LECTURE_OK,         ///< une case comme B2 a été lue
  LECTURE_ILLISIBLE,  ///< quelque chose a été tapé mais ce n'est pas une case
  LECTURE_FINIE       ///< il n'y a plus rien à lire
} Lecture;

int choisirMode();
void initialiserJoueurs(Joueur joueur[NB_JOUEURS], int mode);
void deuxJoueurs(Joueur joueur[NB_JOUEURS]);
void viderLigne();
Lecture lireCase(Case *ptrCase);
bool saisirCoup(const Partie *ptrPartie, Coup *ptrCoup);
