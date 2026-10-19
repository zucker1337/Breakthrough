/**
 * @file types.h
 * @brief Constantes, énumérations et structures partagées par tous les
 * modules du jeu.
 */
#pragma once

/**
 * @brief nombre de lignes et de colonnes du plateau
 *
 * le plateau est carré donc une seule constante suffit
 * c'est le seul endroit à changer pour jouer sur un plateau plus grand
 */
#define TAILLE 8

/**
 * @brief nombre de joueurs d'une partie
 */
#define NB_JOUEURS 2

/**
 * @brief place réservée au nom d'un joueur
 */
#define TAILLE_NOM 30

/**
 * @brief ce que peut contenir une case du plateau
 */
typedef enum { CASE_VIDE, PION_BLANC, PION_NOIR } Contenu;

/**
 * @brief verdict rendu sur un coup saisi
 */
typedef enum {
  COUP_OK,
  COUP_HORS_PLATEAU,
  COUP_PAS_SON_PION,
  COUP_MAUVAIS_DEPLACEMENT,
  COUP_TOUT_DROIT_OCCUPE,
  COUP_SUR_SON_PION
} Verdict;

/**
 * @brief une case du plateau
 */
typedef struct {
  int ligne;    ///< ligne dans le tableau de 0 à TAILLE - 1
  int colonne;  ///< colonne dans le tableau de 0 à TAILLE - 1
} Case;

/**
 * @brief un coup : la case de départ et la case visée
 */
typedef struct {
  Case depart;   ///< case du pion que le joueur veut avancer
  Case arrivee;  ///< case visée par le joueur
} Coup;

/**
 * @brief un joueur : son nom et la couleur de ses pions
 */
typedef struct {
  char nom[TAILLE_NOM];  ///< nom affiché dans les messages
  Contenu pion;          ///< PION_BLANC ou PION_NOIR
} Joueur;

/**
 * @brief tout ce qu'il faut savoir sur une partie en cours
 */
typedef struct {
  char plateau[TAILLE][TAILLE];  ///< contenu de chaque case
  Joueur joueur[NB_JOUEURS];     ///< les deux joueurs
  int tour;                      ///< 0 ou 1 : le joueur qui doit jouer
  int nbCoups;                   ///< nombre de coups valides déjà joués
} Partie;
