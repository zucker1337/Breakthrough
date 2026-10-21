/**
 * @file regles.c
 * @brief Affichage des règles du jeu Breakthrough.
 *
 * Contient la fonction qui présente aux joueurs
 * les règles et les conditions de victoire.
 */

#include <stdio.h>
#include "regles.h"

/**
 * @brief Affiche les règles du jeu.
 *
 * Présente les déplacements autorisés et les conditions
 * permettant de gagner une partie.
 */
void afficherRegles()
{
    printf("=== REGLES DE BREAKTHROUGH ===\n");
    printf("Chaque joueur avance ses pions vers le camp adverse.\n");
    printf("Un pion avance d'une case vers l'avant, tout droit ou en diagonale.\n");
    printf("Tout droit, la case d'arrivee doit etre vide.\n");
    printf("En diagonale, on peut capturer un pion adverse.\n");
    printf("Il est interdit de reculer ou de capturer tout droit.\n");
    printf("Le premier joueur qui atteint la derniere rangee adverse gagne.\n");
}