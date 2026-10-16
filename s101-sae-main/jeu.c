/**
 * @file jeu.c
 * @brief Breakthrough : plateau, saisie des coups et alternance des joueurs.
 */

#include <stdio.h>
#include <string.h>

#include "./lib/exemple.h"

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
 * @brief une case du plateau repérée par sa ligne et sa colonne
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
 * @brief un joueur : son nom et son pion
 */
typedef struct {
  char nom[TAILLE_NOM];  ///< nom affiché dans les messages
  Contenu pion;          ///< PION_BLANC ou PION_NOIR
} Joueur;

/**
 * @brief la partie : le plateau les joueurs le tour et les coups joués
 */
typedef struct {
  char plateau[TAILLE][TAILLE];  ///< contenu de chaque case
  Joueur joueur[NB_JOUEURS];     ///< les deux joueurs
  int tour;                      ///< 0 ou 1 : le joueur qui doit jouer
  int nbCoups;                   ///< nombre de coups valides déjà joués
} Partie;

void afficherRegles();
int choisirMode();
void deuxJoueurs(Joueur joueur[NB_JOUEURS]);
void initialiserPartie(Partie *ptrPartie, int mode);
void afficherPlateau(const Partie *ptrPartie);
void annoncerTour(const Partie *ptrPartie);
void jouerPartie(Partie *ptrPartie);

bool estDansPlateau(int lig, int col);
int direction(Contenu pion);
Verdict verifierCoup(const Partie *ptrPartie, Coup coup);
void afficherRefus(Verdict verdict);
bool peutJouer(const Partie *ptrPartie);

void viderLigne();
int lireCase(Case *ptrCase);
bool saisirCoup(const Partie *ptrPartie, Coup *ptrCoup);
void jouerCoup(Partie *ptrPartie, Coup coup);
void changerJoueur(Partie *ptrPartie);

/**
 * @brief point d'entrée du programme
 *
 * affiche les règles puis demande le mode de jeu et lit les prénoms
 * prépare la partie et la déroule jusqu'à ce qu'un joueur soit bloqué
 *
 * @return 0 quand le programme s'est bien terminé
 */
int main() {
  // afficheSep est déclarée dans lib/exemple.h et définie dans lib/exemple.c
  afficheSep();

  Partie partie;

  afficherRegles();

  int mode = choisirMode();
  initialiserPartie(&partie, mode);
  jouerPartie(&partie);

  afficheSep();

  return 0;
}

/**
 * @brief affiche les règles du jeu
 */
void afficherRegles() {
  printf(
      "A son tour, un joueur déplace un de ses pions d'une case vers l'avant : "
      "tout droit ou en diagonale.\nUn pion avance tout droit uniquement si "
      "la case d'arrivée est vide\nUn pion avance en diagonale sur une case "
      "vide, ou sur une case occupée par un pion adverse qui est alors eliminé "
      "(retiré du plateau)\nOn ne prend jamais tout droit et on ne recule "
      "jamais\n");
}

/**
 * @brief demande le mode de jeu et renvoie le choix
 *
 * le mode 1 fait jouer 2 joueurs et le mode 2 fait jouer contre l'ordinateur
 * toute autre réponse est ramenée au mode 2
 *
 * @return 1 pour une partie à 2 joueurs et 2 pour une partie contre
 * l'ordinateur
 */
int choisirMode() {
  int choix = 0;
  puts("Choisir un mode: 1. Pour 2 joueurs, 2. Contre l'ordinateur. ");
  scanf("%d", &choix);

  if (choix != 1) {
    choix = 2;
  }

  return choix;
}

/**
 * @brief demande le prénom des 2 joueurs
 *
 * @param joueur le tableau des joueurs dont les noms sont remplis
 */
void deuxJoueurs(Joueur joueur[NB_JOUEURS]) {
  for (int i = 0; i < NB_JOUEURS; i++) {
    printf("Nom du Joueur %d : ", i + 1);

    // 29 caractères au maximum pour laisser la place au zéro final
    scanf("%29s", joueur[i].nom);
  }
}

/**
 * @brief prépare une partie neuve
 *
 * place les pions de départ remplit les deux joueurs et remet les compteurs
 * à zéro
 *
 * @param ptrPartie la partie à préparer
 * @param mode 1 pour deux joueurs et 2 pour une partie contre l'ordinateur
 */
void initialiserPartie(Partie *ptrPartie, int mode) {
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      // 2 premières lignes : noirs, 2 dernières : blancs, sinon vide
      if (ligne < 2) {
        ptrPartie->plateau[ligne][colonne] = PION_NOIR;
      } else if (ligne >= TAILLE - 2) {
        ptrPartie->plateau[ligne][colonne] = PION_BLANC;
      } else {
        ptrPartie->plateau[ligne][colonne] = CASE_VIDE;
      }
    }
  }

  // les blancs commencent donc ils sont le joueur d'indice 0
  ptrPartie->joueur[0].pion = PION_BLANC;
  ptrPartie->joueur[1].pion = PION_NOIR;
  strcpy(ptrPartie->joueur[0].nom, "Joueur 1");
  strcpy(ptrPartie->joueur[1].nom, "Ordinateur");

  if (mode == 1) {
    deuxJoueurs(ptrPartie->joueur);
  } else {
    printf("Vous jouez contre l'ordinateur \n");
  }

  ptrPartie->tour = 0;
  ptrPartie->nbCoups = 0;
}

/**
 * @brief affiche le plateau de la partie sans la modifier
 *
 * les lettres des colonnes sont affichées en haut et en bas du plateau
 * les numéros de lignes sont affichés à gauche et à droite
 * une case vide s'affiche 0 un pion blanc s'affiche B et un pion noir N
 *
 * @param ptrPartie la partie dont on affiche le plateau
 */
void afficherPlateau(const Partie *ptrPartie) {
  // pour afficher les index des cases en lettre EN HAUT
  char Colonnelettre = 'A';

  printf("   ");
  for (int i = 0; i < TAILLE; i++) {
    printf("  %c", Colonnelettre);
    Colonnelettre++;
  }

  printf("\n");

  // affiche le tableau avec les 0 ainsi que les index des lignes
  int Ligne = TAILLE;

  printf("\n");
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    printf("%d    ", Ligne);

    for (int colonne = 0; colonne < TAILLE; colonne++) {
      // affiche N pour noir & B pour blanc, 0 pour vide
      if (ptrPartie->plateau[ligne][colonne] == PION_NOIR) {
        printf("N  ");
      } else if (ptrPartie->plateau[ligne][colonne] == PION_BLANC) {
        printf("B  ");
      } else {
        printf("0  ");
      }
    }

    // index de la ligne à droite
    printf("  %d", Ligne);
    Ligne--;

    printf("\n");
  }

  printf("\n");
  // pour afficher les index des cases en lettre EN BAS
  char LigneBas = 'A';

  printf("   ");
  for (int i = 0; i < TAILLE; i++) {
    printf("  %c", LigneBas);
    LigneBas++;
  }

  printf("\n");
}

/**
 * @brief annonce le joueur dont c'est le tour
 *
 * @param ptrPartie la partie en cours
 */
void annoncerTour(const Partie *ptrPartie) {
  printf("\nC'est à %s de jouer (coup numéro %d)\n",
         ptrPartie->joueur[ptrPartie->tour].nom, ptrPartie->nbCoups + 1);
}

/**
 * @brief dit si une case se trouve dans le plateau
 *
 * @param lig le numéro de ligne à tester
 * @param col le numéro de colonne à tester
 * @return true si la case est dans le plateau et false sinon
 */
bool estDansPlateau(int lig, int col) {
  if (lig >= 0 && lig < TAILLE && col >= 0 && col < TAILLE) {
    return true;
  }

  return false;
}

/**
 * @brief donne le sens dans lequel un pion avance
 *
 * @param pion PION_BLANC ou PION_NOIR
 * @return -1 pour les blancs qui montent vers la ligne 0 et 1 pour les noirs
 */
int direction(Contenu pion) {
  if (pion == PION_BLANC) {
    return -1;
  }

  return 1;
}

/**
 * @brief vérifie un coup pour le joueur dont c'est le tour
 *
 * @param ptrPartie la partie en cours
 * @param coup le coup à vérifier
 * @return COUP_OK si le coup est jouable sinon la raison du refus
 */
Verdict verifierCoup(const Partie *ptrPartie, Coup coup) {
  if (!estDansPlateau(coup.depart.ligne, coup.depart.colonne) ||
      !estDansPlateau(coup.arrivee.ligne, coup.arrivee.colonne)) {
    return COUP_HORS_PLATEAU;
  }

  Contenu pion = ptrPartie->joueur[ptrPartie->tour].pion;

  if (ptrPartie->plateau[coup.depart.ligne][coup.depart.colonne] != pion) {
    return COUP_PAS_SON_PION;
  }

  // écart de colonnes en valeur absolue
  int ecart = coup.arrivee.colonne - coup.depart.colonne;
  if (ecart < 0) {
    ecart = -ecart;
  }

  if (coup.arrivee.ligne != coup.depart.ligne + direction(pion) || ecart > 1) {
    return COUP_MAUVAIS_DEPLACEMENT;
  }

  char contenuArrivee = ptrPartie->plateau[coup.arrivee.ligne][coup.arrivee.colonne];

  if (ecart == 0 && contenuArrivee != CASE_VIDE) {
    return COUP_TOUT_DROIT_OCCUPE;
  }

  if (contenuArrivee == pion) {
    return COUP_SUR_SON_PION;
  }

  return COUP_OK;
}

/**
 * @brief explique au joueur pourquoi son coup est refusé
 *
 * @param verdict le verdict rendu par verifierCoup
 */
void afficherRefus(Verdict verdict) {
  switch (verdict) {
    case COUP_HORS_PLATEAU:
      printf("Coup refusé : une des deux cases est en dehors du plateau\n");
      break;

    case COUP_PAS_SON_PION:
      printf("Coup refusé : la case de départ ne contient pas un de vos pions\n");
      break;

    case COUP_MAUVAIS_DEPLACEMENT:
      printf(
          "Coup refusé : un pion avance d'une seule case vers l'avant, tout "
          "droit ou en diagonale\n");
      break;

    case COUP_TOUT_DROIT_OCCUPE:
      printf("Coup refusé : on n'avance tout droit que sur une case vide\n");
      break;

    case COUP_SUR_SON_PION:
      printf("Coup refusé : la case d'arrivée contient déjà un de vos pions\n");
      break;

    default:
      break;
  }
}

/**
 * @brief dit si le joueur dont c'est le tour a encore un coup jouable
 *
 * @param ptrPartie la partie en cours
 * @return true s'il reste au moins un coup valide et false sinon
 */
bool peutJouer(const Partie *ptrPartie) {
  Contenu pion = ptrPartie->joueur[ptrPartie->tour].pion;
  Coup coup;

  for (int ligne = 0; ligne < TAILLE; ligne++) {
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      if (ptrPartie->plateau[ligne][colonne] == pion) {
        coup.depart.ligne = ligne;
        coup.depart.colonne = colonne;

        // les 3 cases devant le pion : diagonale gauche, tout droit, diagonale droite
        for (int ecart = -1; ecart <= 1; ecart++) {
          coup.arrivee.ligne = ligne + direction(pion);
          coup.arrivee.colonne = colonne + ecart;

          if (verifierCoup(ptrPartie, coup) == COUP_OK) {
            return true;
          }
        }
      }
    }
  }

  return false;
}

/**
 * @brief vide la fin de la ligne restée dans l'entrée
 */
void viderLigne() {
  int c = getchar();

  while (c != '\n' && c != EOF) {
    c = getchar();
  }
}

/**
 * @brief lit une case tapée au clavier comme B2
 *
 * @param ptrCase la case qui reçoit la ligne et la colonne lues
 * @return 2 si la case est lue et EOF à la fin de l'entrée sinon la saisie
 * est illisible
 */
int lireCase(Case *ptrCase) {
  char lettre = 0;
  int rangee = 0;
  int lus = scanf(" %c%d", &lettre, &rangee);

  if (lus != 2) {
    if (lus != EOF) {
      viderLigne();
    }

    return lus;
  }

  // on accepte aussi les lettres minuscules
  if (lettre >= 'a' && lettre <= 'z') {
    lettre = lettre - 'a' + 'A';
  }

  ptrCase->colonne = lettre - 'A';
  ptrCase->ligne = TAILLE - rangee;

  return lus;
}

/**
 * @brief demande un coup au joueur jusqu'à ce qu'il soit valide
 *
 * @param ptrPartie la partie en cours
 * @param ptrCoup le coup qui reçoit les deux cases saisies
 * @return true si un coup valide a été saisi et false si l'entrée est finie
 */
bool saisirCoup(const Partie *ptrPartie, Coup *ptrCoup) {
  Verdict verdict = COUP_HORS_PLATEAU;

  while (verdict != COUP_OK) {
    printf("%s, votre coup (ex : B2 B3) : ",
           ptrPartie->joueur[ptrPartie->tour].nom);

    int lus = lireCase(&ptrCoup->depart);
    if (lus == 2) {
      lus = lireCase(&ptrCoup->arrivee);
    }

    if (lus == EOF) {
      return false;
    }

    if (lus != 2) {
      printf("Coup refusé : il faut taper deux cases comme B2 B3\n");
    } else {
      verdict = verifierCoup(ptrPartie, *ptrCoup);
      afficherRefus(verdict);
    }
  }

  return true;
}

/**
 * @brief place un coup valide sur le plateau
 *
 * le pion quitte sa case de départ et un pion adverse présent sur la case
 * d'arrivée est retiré du plateau
 *
 * @param ptrPartie la partie en cours
 * @param coup le coup à jouer
 */
void jouerCoup(Partie *ptrPartie, Coup coup) {
  ptrPartie->plateau[coup.arrivee.ligne][coup.arrivee.colonne] =
      ptrPartie->plateau[coup.depart.ligne][coup.depart.colonne];
  ptrPartie->plateau[coup.depart.ligne][coup.depart.colonne] = CASE_VIDE;
  ptrPartie->nbCoups++;
}

/**
 * @brief passe la main à l'autre joueur
 *
 * @param ptrPartie la partie en cours
 */
void changerJoueur(Partie *ptrPartie) { ptrPartie->tour = 1 - ptrPartie->tour; }

/**
 * @brief déroule la partie en faisant alterner les deux joueurs
 *
 * la partie s'arrête quand le joueur dont c'est le tour n'a plus aucun coup
 * jouable
 *
 * @param ptrPartie la partie à dérouler
 */
void jouerPartie(Partie *ptrPartie) {
  Coup coup;

  afficherPlateau(ptrPartie);

  while (peutJouer(ptrPartie)) {
    annoncerTour(ptrPartie);

    if (!saisirCoup(ptrPartie, &coup)) {
      printf("\nPlus rien à lire, la partie s'arrête ici\n");
      return;
    }

    jouerCoup(ptrPartie, coup);
    afficherPlateau(ptrPartie);
    changerJoueur(ptrPartie);
  }

  printf("\n%s ne peut plus jouer, la partie est terminée après %d coups\n",
         ptrPartie->joueur[ptrPartie->tour].nom, ptrPartie->nbCoups);
}
