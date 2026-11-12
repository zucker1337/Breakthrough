/**
 * @file partie.h
 * @brief Les types du jeu et ce qui concerne la partie entière.
 */
#pragma once

/// nombre de lignes et de colonnes du plateau
#define TAILLE 8

/// nombre de joueurs d'une partie
#define NB_JOUEURS 2

/// place réservée au nom d'un joueur
#define TAILLE_NOM 30

/// place réservée à un mot tapé au clavier
#define TAILLE_SAISIE 10

/// renvoyé par gagnant quand la partie n'est pas finie
#define PAS_DE_GAGNANT (-1)

/**
 * @brief ce que peut contenir une case du plateau
 */
typedef enum { CASE_VIDE, PION_BLANC, PION_NOIR } Contenu;

/**
 * @brief réponse rendue sur un coup
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
  /// ligne dans le tableau de 0 à TAILLE - 1
  int ligne;
  /// colonne dans le tableau de 0 à TAILLE - 1
  int colonne;
} Case;

/**
 * @brief un coup : la case de départ et la case visée
 */
typedef struct {
  /// case du pion que le joueur veut avancer
  Case depart;
  /// case visée par le joueur
  Case arrivee;
} Coup;

/**
 * @brief un joueur : son nom et son pion
 */
typedef struct {
  /// nom affiché dans les messages
  char nom[TAILLE_NOM];
  /// PION_BLANC ou PION_NOIR
  Contenu pion;
} Joueur;

/**
 * @brief la partie : le plateau les joueurs le tour et les coups joués
 */
typedef struct {
  /// contenu de chaque case
  char plateau[TAILLE][TAILLE];
  /// les deux joueurs
  Joueur joueur[NB_JOUEURS];
  /// 0 ou 1 : le joueur qui doit jouer
  int tour;
  /// nombre de coups valides déjà joués
  int nbCoups;
} Partie;

/**
 * @brief donne son pion et un nom par défaut à chaque joueur
 *
 * @param ptrPartie la partie à remplir
 */
void preparerJoueurs(Partie *ptrPartie);

/**
 * @brief remet la partie à son état de départ sans toucher aux noms
 *
 * @param ptrPartie la partie à remettre à zéro
 */
void nouvellePartie(Partie *ptrPartie);

/**
 * @brief passe le tour à l'autre joueur
 *
 * @param ptrPartie la partie en cours
 */
void changerJoueur(Partie *ptrPartie);

/**
 * @brief donne le pion du joueur dont c'est le tour
 *
 * @param partie la partie en cours
 * @return PION_BLANC ou PION_NOIR
 */
Contenu pionDuTour(Partie partie);

/**
 * @brief cherche le gagnant de la partie
 *
 * un joueur gagne si un de ses pions atteint la dernière rangée adverse
 * ou si son adversaire n'a plus de pions ou ne peut plus jouer
 * il n'y a pas de match nul à Breakthrough
 *
 * @param partie la partie en cours
 * @return l'indice du gagnant ou PAS_DE_GAGNANT si la partie continue
 */
int gagnant(Partie partie);
