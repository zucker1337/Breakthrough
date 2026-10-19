/**
 * @file jeu.c
 * @brief breakthrough plateau saisie des coups et alternance des joueurs
 */

// stdio pour printf scanf puts getchar
#include <stdio.h>
// string pour strcpy qui copie un texte dans un tableau de char
#include <string.h>
// stdbool pour avoir le type bool avec true et false
#include <stdbool.h>

// notre module d'exemple qui contient afficheSep
#include "./lib/exemple.h"

/**
 * @brief nombre de lignes et de colonnes du plateau
 *
 * le plateau est carré donc une seule constante suffit
 * c'est le seul endroit à changer pour jouer sur un plateau plus grand
 */
// define remplace le mot TAILLE par 8 partout dans le code avant la compilation
#define TAILLE 8

// il y a toujours 2 joueurs donc 2 cases dans le tableau des joueurs
#define NB_JOUEURS 2

// un nom fait au plus 29 lettres plus le caractère de fin de texte
#define TAILLE_NOM 30

/* ======================================================================
   les types qu'on fabrique nous même
   ====================================================================== */

// enum donne des noms aux nombres
// CASE_VIDE vaut 0 PION_BLANC vaut 1 PION_NOIR vaut 2
// typedef permet ensuite d'écrire juste Contenu comme on écrit int
typedef enum { CASE_VIDE, PION_BLANC, PION_NOIR } Contenu;

// la raison pour laquelle un coup est accepté ou refusé
// COUP_OK vaut 0 COUP_HORS_PLATEAU vaut 1 et ainsi de suite
typedef enum {
  COUP_OK,                   // le coup est bon
  COUP_HORS_PLATEAU,         // une case est en dehors du plateau
  COUP_PAS_SON_PION,         // la case de départ n'a pas un pion du joueur
  COUP_MAUVAIS_DEPLACEMENT,  // pas une case vers l'avant
  COUP_TOUT_DROIT_OCCUPE,    // tout droit sur une case pas vide
  COUP_SUR_SON_PION          // on arrive sur son propre pion
} Verdict;

// struct regroupe plusieurs variables en un seul paquet
// une Case c'est deux int collés ensemble la ligne et la colonne
typedef struct {
  int ligne;    ///< ligne dans le tableau de 0 à TAILLE - 1
  int colonne;  ///< colonne dans le tableau de 0 à TAILLE - 1
} Case;

// un Coup c'est deux Case la case de départ et la case d'arrivée
// exemple B2 B3 donne depart = (6 1) et arrivee = (5 1)
typedef struct {
  Case depart;   ///< case du pion que le joueur veut avancer
  Case arrivee;  ///< case visée par le joueur
} Coup;

// un Joueur c'est un nom et la couleur de ses pions
typedef struct {
  char nom[TAILLE_NOM];  ///< nom affiché dans les messages
  Contenu pion;          ///< PION_BLANC ou PION_NOIR
} Joueur;

// une Partie c'est tout l'état du jeu dans un seul paquet
// le plateau les deux joueurs à qui c'est le tour et le nombre de coups
// on écrit Partie partie comme on écrirait int x
typedef struct {
  char plateau[TAILLE][TAILLE];  ///< contenu de chaque case
  Joueur joueur[NB_JOUEURS];     ///< les deux joueurs
  int tour;                      ///< 0 ou 1 le joueur qui doit jouer
  int nbCoups;                   ///< nombre de coups valides déjà joués
} Partie;

/* ======================================================================
   les prototypes
   on annonce les fonctions avant main pour que le compilateur les connaisse
   le code de chaque fonction est écrit plus bas
   ====================================================================== */

// Partie* ptrPartie veut dire ptrPartie contient l'adresse d'une Partie
// pareil que int* ptr qui contient l'adresse d'un int
// const veut dire que la fonction a le droit de lire la partie mais pas de la
// modifier

void afficherRegles();
int choisirMode();
void deuxJoueurs(Joueur joueur[NB_JOUEURS]);
void initialiserPartie(Partie* ptrPartie, int mode);
void afficherPlateau(const Partie* ptrPartie);
void annoncerTour(const Partie* ptrPartie);
void jouerPartie(Partie* ptrPartie);

bool estDansPlateau(int lig, int col);
int direction(Contenu pion);
Verdict verifierCoup(const Partie* ptrPartie, Coup coup);
void afficherRefus(Verdict verdict);
bool peutJouer(const Partie* ptrPartie);

void viderLigne();
int lireCase(Case* ptrCase);
bool saisirCoup(const Partie* ptrPartie, Coup* ptrCoup);
void jouerCoup(Partie* ptrPartie, Coup coup);
void changerJoueur(Partie* ptrPartie);

/* ======================================================================
   main le programme commence ici
   ====================================================================== */

int main() {
  // afficheSep est déclarée dans lib/exemple.h et définie dans lib/exemple.c
  afficheSep();

  // on crée la variable partie de type Partie
  // elle existe en mémoire quelque part avec une adresse qu'on note &partie
  Partie partie;

  afficherRegles();

  // mode vaut 1 pour deux joueurs ou 2 contre l'ordinateur
  int mode = choisirMode();

  // on donne l'adresse de partie avec le &
  // comme ça la fonction peut remplir la vraie partie et pas une copie
  initialiserPartie(&partie, mode);

  // pareil ici la fonction modifie la vraie partie à chaque coup
  jouerPartie(&partie);

  afficheSep();

  return 0;
}

/* ======================================================================
   début de partie
   ====================================================================== */

// affiche juste un texte avec les règles
void afficherRegles() {
  printf(
      "A son tour, un joueur déplace un de ses pions d'une case vers l'avant : "
      "tout droit ou en diagonale.\nUn pion avance tout droit uniquement si "
      "la case d'arrivée est vide\nUn pion avance en diagonale sur une case "
      "vide, ou sur une case occupée par un pion adverse qui est alors eliminé "
      "(retiré du plateau)\nOn ne prend jamais tout droit et on ne recule "
      "jamais\n");
}

// demande le mode au joueur et le renvoie
int choisirMode() {
  int choix = 0;
  puts("Choisir un mode: 1. Pour 2 joueurs, 2. Contre l'ordinateur. ");

  // &choix donne l'adresse de choix pour que scanf écrive dedans
  scanf("%d", &choix);

  // tout ce qui n'est pas 1 est considéré comme le mode 2
  if (choix != 1) {
    choix = 2;
  }

  return choix;
}

// demande le prénom des deux joueurs
// joueur est le tableau des 2 joueurs qui se trouve dans la partie
// un tableau passé à une fonction n'est pas copié donc on remplit le vrai
void deuxJoueurs(Joueur joueur[NB_JOUEURS]) {
  for (int i = 0; i < NB_JOUEURS; i++) {
    // i vaut 0 puis 1 donc on affiche Joueur 1 puis Joueur 2
    printf("Nom du Joueur %d : ", i + 1);

    // 29 caractères au maximum pour laisser la place au zéro final
    // pas de & devant joueur[i].nom car un tableau est déjà une adresse
    scanf("%29s", joueur[i].nom);
  }
}

// prépare la partie avant le premier coup
void initialiserPartie(Partie* ptrPartie, int mode) {
  // on parcourt toutes les cases ligne par ligne
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      // ptrPartie->plateau veut dire le plateau de la partie qui est à cette
      // adresse c'est pareil que (*ptrPartie).plateau

      // 2 premières lignes noirs
      if (ligne < 2) {
        ptrPartie->plateau[ligne][colonne] = PION_NOIR;
      }
      // 2 dernières lignes blancs
      else if (ligne >= TAILLE - 2) {
        ptrPartie->plateau[ligne][colonne] = PION_BLANC;
      }
      // le reste est vide
      else {
        ptrPartie->plateau[ligne][colonne] = CASE_VIDE;
      }
    }
  }

  // les blancs commencent donc ils sont le joueur d'indice 0
  ptrPartie->joueur[0].pion = PION_BLANC;
  ptrPartie->joueur[1].pion = PION_NOIR;

  // noms par défaut utilisés en mode contre l'ordinateur
  strcpy(ptrPartie->joueur[0].nom, "Joueur 1");
  strcpy(ptrPartie->joueur[1].nom, "Ordinateur");

  // en mode 2 joueurs on remplace les noms par les vrais prénoms
  if (mode == 1) {
    deuxJoueurs(ptrPartie->joueur);
  } else {
    printf("Vous jouez contre l'ordinateur \n");
  }

  // c'est au joueur 0 les blancs de commencer
  ptrPartie->tour = 0;
  // aucun coup joué pour l'instant
  ptrPartie->nbCoups = 0;
}

/* ======================================================================
   affichage
   ====================================================================== */

// const parce qu'afficher ne doit rien changer au plateau
void afficherPlateau(const Partie* ptrPartie) {
  // pour afficher les index des cases en lettre en haut
  char Colonnelettre = 'A';

  printf("   ");
  for (int i = 0; i < TAILLE; i++) {
    printf("  %c", Colonnelettre);
    // un char est un nombre donc 'A' + 1 donne 'B' puis 'C' etc
    Colonnelettre++;
  }

  printf("\n");

  // numéro de rangée affiché il commence à TAILLE en haut et descend
  // la ligne 0 du tableau s'affiche donc comme la rangée 8
  int Ligne = TAILLE;

  printf("\n");
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    // numéro de la rangée à gauche
    printf("%d    ", Ligne);

    for (int colonne = 0; colonne < TAILLE; colonne++) {
      // dans le tableau on a 0 1 ou 2 et on affiche une lettre à la place
      // N pour noir B pour blanc 0 pour vide
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
  // pour afficher les index des cases en lettre en bas
  char LigneBas = 'A';

  printf("   ");
  for (int i = 0; i < TAILLE; i++) {
    printf("  %c", LigneBas);
    LigneBas++;
  }

  printf("\n");
}

// dit à qui c'est de jouer
void annoncerTour(const Partie* ptrPartie) {
  // ptrPartie->tour vaut 0 ou 1
  // donc ptrPartie->joueur[ptrPartie->tour].nom est le nom du joueur qui doit
  // jouer nbCoups + 1 car si 0 coup a été joué on en est au coup numéro 1
  printf("\nC'est à %s de jouer (coup numéro %d)\n",
         ptrPartie->joueur[ptrPartie->tour].nom, ptrPartie->nbCoups + 1);
}

/* ======================================================================
   vérification des coups
   ====================================================================== */

// renvoie true si la case (lig col) existe sur le plateau
bool estDansPlateau(int lig, int col) {
  if (lig >= 0 && lig < TAILLE && col >= 0 && col < TAILLE) {
    return true;
  }

  return false;
}

// sens dans lequel avance un pion
// les blancs sont en bas et montent donc leur ligne diminue de 1
// les noirs sont en haut et descendent donc leur ligne augmente de 1
int direction(Contenu pion) {
  if (pion == PION_BLANC) {
    return -1;
  }

  return 1;
}

// regarde si un coup respecte les règles et renvoie la raison du refus
// les tests sont faits dans l'ordre et on s'arrête au premier problème
Verdict verifierCoup(const Partie* ptrPartie, Coup coup) {
  // test 1 les deux cases doivent être dans le plateau
  // à faire en premier sinon on lirait le tableau en dehors de ses cases
  if (!estDansPlateau(coup.depart.ligne, coup.depart.colonne) ||
      !estDansPlateau(coup.arrivee.ligne, coup.arrivee.colonne)) {
    return COUP_HORS_PLATEAU;
  }

  // la couleur du joueur qui est en train de jouer
  Contenu pion = ptrPartie->joueur[ptrPartie->tour].pion;

  // test 2 la case de départ doit contenir un pion de ce joueur
  if (ptrPartie->plateau[coup.depart.ligne][coup.depart.colonne] != pion) {
    return COUP_PAS_SON_PION;
  }

  // écart de colonnes en valeur absolue
  // 0 veut dire tout droit et 1 veut dire diagonale
  int ecart = coup.arrivee.colonne - coup.depart.colonne;
  if (ecart < 0) {
    ecart = -ecart;
  }

  // test 3 il faut avancer d'exactement une ligne dans le bon sens
  // et ne pas se décaler de plus d'une colonne
  if (coup.arrivee.ligne != coup.depart.ligne + direction(pion) || ecart > 1) {
    return COUP_MAUVAIS_DEPLACEMENT;
  }

  // ce qu'il y a sur la case d'arrivée 0 1 ou 2
  char contenuArrivee =
      ptrPartie->plateau[coup.arrivee.ligne][coup.arrivee.colonne];

  // test 4 tout droit la case doit être vide on ne prend jamais tout droit
  if (ecart == 0 && contenuArrivee != CASE_VIDE) {
    return COUP_TOUT_DROIT_OCCUPE;
  }

  // test 5 on ne peut pas arriver sur un de ses propres pions
  if (contenuArrivee == pion) {
    return COUP_SUR_SON_PION;
  }

  // si on arrive ici c'est une diagonale sur case vide ou sur un pion adverse
  // ou tout droit sur case vide donc le coup est bon
  return COUP_OK;
}

// affiche le message qui correspond à la raison du refus
void afficherRefus(Verdict verdict) {
  // switch teste la valeur de verdict et va directement au bon case
  switch (verdict) {
    case COUP_HORS_PLATEAU:
      printf("Coup refusé : une des deux cases est en dehors du plateau\n");
      break;  // break sort du switch sinon on continuerait dans le case suivant

    case COUP_PAS_SON_PION:
      printf(
          "Coup refusé : la case de départ ne contient pas un de vos pions\n");
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

    // COUP_OK arrive ici et on n'affiche rien
    default:
      break;
  }
}

// renvoie true s'il reste au moins un coup possible au joueur du tour
bool peutJouer(const Partie* ptrPartie) {
  Contenu pion = ptrPartie->joueur[ptrPartie->tour].pion;
  Coup coup;

  // on cherche tous les pions du joueur sur le plateau
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      if (ptrPartie->plateau[ligne][colonne] == pion) {
        coup.depart.ligne = ligne;
        coup.depart.colonne = colonne;

        // les 3 cases devant le pion diagonale gauche tout droit diagonale
        // droite ecart vaut -1 puis 0 puis 1
        for (int ecart = -1; ecart <= 1; ecart++) {
          coup.arrivee.ligne = ligne + direction(pion);
          coup.arrivee.colonne = colonne + ecart;

          // on réutilise verifierCoup pour ne pas réécrire les règles
          // dès qu'un coup marche on peut s'arrêter
          if (verifierCoup(ptrPartie, coup) == COUP_OK) {
            return true;
          }
        }
      }
    }
  }

  // on a tout essayé et rien ne marche
  return false;
}

/* ======================================================================
   saisie des coups
   ====================================================================== */

// lit et jette tous les caractères jusqu'à la fin de la ligne
// utile quand le joueur tape n'importe quoi pour repartir proprement
void viderLigne() {
  int c = getchar();

  // EOF veut dire qu'il n'y a plus rien à lire
  while (c != '\n' && c != EOF) {
    c = getchar();
  }
}

// lit une case tapée comme B2 et la range dans *ptrCase
// on passe l'adresse de la case pour que la fonction puisse la remplir
// renvoie le nombre de choses lues par scanf 2 si tout va bien
int lireCase(Case* ptrCase) {
  char lettre = 0;
  int rangee = 0;

  // l'espace avant %c saute les espaces et retours à la ligne
  // %c lit la lettre et %d lit le chiffre
  int lus = scanf(" %c%d", &lettre, &rangee);

  // si on n'a pas réussi à lire une lettre et un nombre
  if (lus != 2) {
    // on jette la fin de la ligne sauf s'il n'y a plus rien à lire
    if (lus != EOF) {
      viderLigne();
    }

    return lus;
  }

  // on accepte aussi les lettres minuscules
  // 'b' - 'a' vaut 1 puis + 'A' donne 'B'
  if (lettre >= 'a' && lettre <= 'z') {
    lettre = lettre - 'a' + 'A';
  }

  // conversion lettre en numéro de colonne 'A' donne 0 'B' donne 1 etc
  ptrCase->colonne = lettre - 'A';

  // conversion rangée affichée en ligne du tableau
  // la rangée 8 est la ligne 0 et la rangée 1 est la ligne 7
  ptrCase->ligne = TAILLE - rangee;

  return lus;
}

// redemande un coup tant qu'il n'est pas valide
// le coup accepté est rangé dans *ptrCoup
// renvoie false seulement s'il n'y a plus rien à lire
bool saisirCoup(const Partie* ptrPartie, Coup* ptrCoup) {
  // on part d'un verdict faux pour entrer au moins une fois dans la boucle
  Verdict verdict = COUP_HORS_PLATEAU;

  while (verdict != COUP_OK) {
    printf("%s, votre coup (ex : B2 B3) : ",
           ptrPartie->joueur[ptrPartie->tour].nom);

    // &ptrCoup->depart est l'adresse de la case de départ du coup
    int lus = lireCase(&ptrCoup->depart);

    // on ne lit la case d'arrivée que si la première a été bien lue
    if (lus == 2) {
      lus = lireCase(&ptrCoup->arrivee);
    }

    // fin du fichier ou du clavier on abandonne
    if (lus == EOF) {
      return false;
    }

    if (lus != 2) {
      printf("Coup refusé : il faut taper deux cases comme B2 B3\n");
    } else {
      // *ptrCoup donne le coup lui même et pas son adresse
      verdict = verifierCoup(ptrPartie, *ptrCoup);
      // n'affiche rien si le coup est bon
      afficherRefus(verdict);
    }
  }

  return true;
}

/* ======================================================================
   déroulement de la partie
   ====================================================================== */

// déplace le pion sur le plateau
// pas de const ici car on modifie la partie
void jouerCoup(Partie* ptrPartie, Coup coup) {
  // on copie le pion de la case de départ vers la case d'arrivée
  // s'il y avait un pion adverse il est écrasé donc mangé
  ptrPartie->plateau[coup.arrivee.ligne][coup.arrivee.colonne] =
      ptrPartie->plateau[coup.depart.ligne][coup.depart.colonne];

  // la case de départ devient vide
  ptrPartie->plateau[coup.depart.ligne][coup.depart.colonne] = CASE_VIDE;

  // un coup de plus
  ptrPartie->nbCoups++;
}

// si tour vaut 0 il devient 1 et si tour vaut 1 il devient 0
void changerJoueur(Partie* ptrPartie) { ptrPartie->tour = 1 - ptrPartie->tour; }

// la boucle principale du jeu
// reçoit l'adresse de la partie créée dans main
void jouerPartie(Partie* ptrPartie) {
  Coup coup;

  afficherPlateau(ptrPartie);

  // tant que le joueur du tour a au moins un coup possible
  while (peutJouer(ptrPartie)) {
    annoncerTour(ptrPartie);

    // &coup donne l'adresse de coup pour que saisirCoup le remplisse
    if (!saisirCoup(ptrPartie, &coup)) {
      printf("\nPlus rien à lire, la partie s'arrête ici\n");
      return;
    }

    jouerCoup(ptrPartie, coup);
    afficherPlateau(ptrPartie);
    changerJoueur(ptrPartie);
  }

  // on sort de la boucle quand le joueur du tour est bloqué
  printf("\n%s ne peut plus jouer, la partie est terminée après %d coups\n",
         ptrPartie->joueur[ptrPartie->tour].nom, ptrPartie->nbCoups);
}