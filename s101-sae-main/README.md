# Breakthrough

Jeu de plateau à deux joueurs, ou un joueur contre l'ordinateur : chaque camp fait avancer ses pions vers le camp adverse, le premier qui atteint la dernière rangée adverse gagne.

**Groupe** : `G2C` -- Mohammad Epifanov, Solomon Fashanu Timileyin, Chaima Gabtni

## Description

Breakthrough se joue sur un plateau de 8 × 8 cases. Chaque joueur commence
avec 16 pions placés sur ses deux premières rangées : les Blancs (B) en bas,
les Noirs (N) en haut. Les Blancs jouent en premier.

**Règles** :

- A son tour, un joueur déplace un de ses pions d'une case vers l'avant : tout droit ou en diagonale
- Un pion avance tout droit uniquement si la case d'arrivée est vide
- Un pion avance en diagonale sur une case vide, ou sur une case occupée par un pion adverse qui est alors "mangé" (retiré du plateau)
- On ne prend jamais tout droit et on ne recule jamais

**Fin de partie** : un joueur gagne dès que :

- l'un de ses pions atteint la dernière rangée adverse
- ou son adversaire n'a plus aucun pion
- ou son adversaire ne peut plus jouer aucun coup

Il n'y a donc pas de match nul à Breakthrough.

Déroulement d'une partie :

1. Le programme affiche les règles puis demande le mode : deux joueurs ou
   contre l'ordinateur
2. A chaque tour le plateau est affiché et le joueur saisit son coup sous la
   forme case_depart case_arrivee, par exemple "B2 B3", un coup invalide
   (hors plateau, pas son pion, mauvaise direction, case occupée...) est
   refusé avec un message explicatif et le joueur rejoue le coup
3. Quand un joueur gagne le programme l'annonce et propose de rejouer

Exemple d'affichage :

         A  B  C  D  E  F  G  H

    8    N  N  N  N  N  N  N  N    8
    7    N  N  N  N  N  N  N  N    7
    6    0  0  0  0  0  0  0  0    6
    5    0  0  0  0  0  0  0  0    5
    4    0  0  0  0  0  0  0  0    4
    3    0  0  0  0  0  0  0  0    3
    2    B  B  B  B  B  B  B  B    2
    1    B  B  B  B  B  B  B  B    1

         A  B  C  D  E  F  G  H

Mohammad, votre coup (ex : B2 B3) : 

**Adversaire automatique** (stratégie prévue, pas encore réalisée)

En mode « contre l'ordinateur », l'humain joue les Blancs (joueur 1, il
commence) et l'ordinateur joue les Noirs (joueur 2, il avance vers la ligne
`TAILLE - 1`, soit `direction = +1`).

*Étape 1 : lister tous les coups valides.* L'ordinateur parcourt toutes les
cases du plateau. Pour chaque case `(lig, col)` qui contient un de ses pions,
il essaie les 3 cases d'arrivée possibles : `(lig + 1, col - 1)`,
`(lig + 1, col)` et `(lig + 1, col + 1)`. Il ne garde que celles acceptées
par `estCoupValide`. Il y a au plus 16 pions × 3 = 48 coups, on les range
dans des tableaux de taille `2 * TAILLE * 3`.

*Étape 2 : donner une priorité à chaque coup* (1 = meilleur). Un coup reçoit
la première priorité de la liste dont il remplit la condition :

| Priorité | Type de coup | Condition précise (Noirs, case d'arrivée `(la, ca)`) |
| --- | --- | --- |
| 1 | Coup gagnant | `la == TAILLE - 1` : le pion atteint la dernière rangée |
| 2 | Prise défensive | la case d'arrivée contient un pion blanc situé en ligne `1` : ce pion blanc gagnerait au tour suivant, il faut le manger |
| 3 | Prise sûre | coup en diagonale sur un pion blanc **et** case d'arrivée non menacée |
| 4 | Avance sûre | case d'arrivée vide **et** non menacée |
| 5 | Prise risquée | coup en diagonale sur un pion blanc, mais case d'arrivée menacée |
| 6 | Autre coup | tout autre coup valide (avance sur une case menacée) |

Une case `(la, ca)` est **menacée** si un pion blanc se trouve en
`(la + 1, ca - 1)` ou en `(la + 1, ca + 1)` (en vérifiant avec
`estDansPlateau`) : au tour suivant, ce pion blanc pourrait avancer en
diagonale sur la case et manger le pion noir.

*Étape 3 : choisir le coup.* L'ordinateur garde uniquement les coups qui ont
la meilleure priorité (la plus petite valeur) et en tire un au hasard avec
`rand() % nombreDeCoups`. `srand(time(NULL))` est appelé une seule fois au
début de `main`, pour que les parties ne soient pas toujours identiques.

L'ordinateur n'est jamais appelé sans coup possible : si un joueur ne peut
plus jouer, `gagnant` le détecte (avec `peutJouer`) et la partie s'arrête
avant.

**Fonctionnalités valorisées** : la taille du plateau est paramétrable par la
seule constante `TAILLE`, de 4 à 26, sans aucune autre modification du code.
Sont prévus pour la suite l'adversaire automatique à six niveaux de priorité
décrit ci-dessus et un historique des coups de la partie.

## Compilation et exécution

Sous VSCode, la touche `F5` compile le fichier actif (`jeu.c`) avec tous les
modules du dossier `lib/` et lance l'exécutable.

En ligne de commande :

```bash
gcc -std=c23 -Wall -Werror jeu.c lib/*.c -o jeu -lm
./jeu
```

## Schéma de décomposition

### Représentation du plateau

Le plateau est un tableau 2D carré de `char` : `char plateau[TAILLE][TAILLE]`,
rangé dans la structure `Partie` et transmis aux fonctions avec elle.

**Pourquoi ce choix de structure de données ?**

- **Un tableau à 2 dimensions** : le plateau est une grille, une case est
  repérée par une ligne et une colonne. Avec `mat[ligne][colonne]` on accède
  directement à n'importe quelle case, sans calcul d'indice. Les déplacements
  s'écrivent simplement : avancer = changer de ligne, diagonale = changer de
  ligne et de colonne (`colonne - 1` ou `colonne + 1`).
- **Un tableau carré (`TAILLE × TAILLE`)** : le plateau de Breakthrough a
  autant de lignes que de colonnes (8 × 8). Une seule constante `TAILLE`
  suffit donc pour les deux dimensions et pour toutes les boucles de
  parcours.
- **Le type `char` plutôt que `int`** : une case ne peut contenir que
  **3 valeurs** (`0`, `1` ou `2`). Un `int` occupe 4 octets alors qu'un
  `char` n'en occupe qu'1 et suffit largement (il va de -128 à 127). Le
  plateau 8 × 8 tient donc en **64 octets au lieu de 256**, soit 4 fois moins
  de mémoire, sans rien perdre.
- **On stocke des petits nombres (`0`, `1`, `2`) dans le `char`, pas des
  lettres (`'B'`, `'N'`)** : ainsi la valeur d'une case est directement le
  numéro du joueur qui l'occupe, ce qui simplifie les tests (`mat[l][c] ==
  joueur`). La conversion en lettres `B`/`N` n'est faite qu'à l'affichage,
  dans `afficherPlateau`.

**Conventions** :

- Taille : `#define TAILLE 8` en haut de `jeu.c`, seul endroit à modifier
  pour changer la taille du plateau (26 au maximum, à cause des lettres de
  colonnes A à Z).
- Contenu d'une case : `CASE_VIDE` (0), `PION_BLANC` (1) ou `PION_NOIR` (2),
  les trois noms de l'énumération `Contenu`. La valeur d'une case est donc
  aussi le numéro du joueur qui l'occupe.
- Ligne `0` du tableau = rangée 8 affichée en haut, ligne `TAILLE - 1` =
  rangée 1 affichée en bas. Colonne `0` = colonne A.
- État initial : les Noirs occupent les lignes `0` et `1`, les Blancs les
  lignes `TAILLE - 2` et `TAILLE - 1`, le reste est vide. Les Blancs
  (joueur 1) avancent vers la ligne 0, les Noirs (joueur 2) vers la ligne
  `TAILLE - 1`.
- Affichage : `PION_BLANC` est affiché `B`, `PION_NOIR` est affiché `N`,
  une case vide `0`.

### Les informations du jeu

Les informations qui vont ensemble sont regroupées dans des structures, pour
que le programme manipule chacune comme une seule unité. Les fonctions
s'échangent ces unités plutôt qu'une longue liste de paramètres : par exemple
`afficherPlateau` reçoit la partie, et non le plateau et le reste séparément.

```c
typedef enum { CASE_VIDE, PION_BLANC, PION_NOIR } Contenu;

typedef struct {
  int ligne;
  int colonne;
} Case;

typedef struct {
  Case depart;
  Case arrivee;
} Coup;

typedef struct {
  char nom[TAILLE_NOM];
  Contenu pion;
} Joueur;

typedef struct {
  char plateau[TAILLE][TAILLE];
  Joueur joueur[NB_JOUEURS];
  int tour;
  int nbCoups;
} Partie;
```

| Structure | Ce qu'elle regroupe |
| --- | --- |
| `Case` | une case du plateau : sa ligne et sa colonne |
| `Coup` | un coup : la case de départ et la case visée |
| `Joueur` | un joueur : son nom et son pion |
| `Partie` | le plateau, les deux joueurs, le joueur dont c'est le tour et le nombre de coups joués |

Le contenu d'une case et la raison du refus d'un coup sont nommés par deux
énumérations, `Contenu` et `Verdict`, au lieu d'être écrits en chiffres dans
le code.

### Fonctions réalisées (semaine 3)

```
main
├── void afficherRegles()                              (affiche les règles du jeu)
├── int choisirMode()                                  (demande le mode et le renvoie :
│                                                       1 = deux joueurs, 2 = contre l'ordinateur)
├── void initialiserPartie(Partie *ptrPartie, int mode)
│   │                                                  (place les pions, remplit les 2 joueurs,
│   │                                                   remet le tour et le compteur à zéro)
│   └── void deuxJoueurs(Joueur joueur[NB_JOUEURS])    (mode 1 : demande le prénom des 2 joueurs)
└── void jouerPartie(Partie *ptrPartie)                (fait alterner les joueurs jusqu'au blocage)
    ├── void afficherPlateau(const Partie *ptrPartie)  (affiche le plateau avec les lettres de colonnes
    │                                                   et les numéros de lignes, sans le modifier)
    ├── bool peutJouer(const Partie *ptrPartie)        (reste-t-il un coup jouable au joueur du tour ?)
    │   └── Verdict verifierCoup(...)
    ├── void annoncerTour(const Partie *ptrPartie)     (annonce le joueur dont c'est le tour)
    ├── bool saisirCoup(const Partie *ptrPartie, Coup *ptrCoup)
    │   │                                              (redemande un coup tant qu'il est refusé)
    │   ├── int lireCase(Case *ptrCase)                (lit une case tapée comme B2)
    │   │   └── void viderLigne()                      (jette la fin d'une saisie illisible)
    │   ├── Verdict verifierCoup(const Partie *ptrPartie, Coup coup)
    │   │   ├── bool estDansPlateau(int lig, int col)
    │   │   └── int direction(Contenu pion)            (-1 pour les Blancs, +1 pour les Noirs)
    │   └── void afficherRefus(Verdict verdict)        (explique pourquoi le coup est refusé)
    ├── void jouerCoup(Partie *ptrPartie, Coup coup)   (place le coup et compte un coup de plus)
    └── void changerJoueur(Partie *ptrPartie)          (passe la main à l'autre joueur)
```

Toutes ces fonctions reçoivent la partie entière : les prénoms, le plateau, le
tour et le nombre de coups restent disponibles du début à la fin. Celles qui ne
modifient rien reçoivent un `const Partie *`.

La détection du gagnant et l'adversaire automatique ne sont pas encore écrits :
la partie s'arrête pour l'instant quand le joueur dont c'est le tour n'a plus
aucun coup jouable.

### Décomposition prévue (fin de projet)

```
main
├── void afficherRegles()
├── int choisirMode()                                  (renvoie 1 = 2 joueurs, 2 = contre l'ordinateur)
├── void initialiserPartie(Partie *ptrPartie, int mode)
│   └── void deuxJoueurs(Joueur joueur[NB_JOUEURS])    (mode 1 : demande le prénom des 2 joueurs)
├── int jouerPartie(Partie *ptrPartie)                 (renvoie le numéro du gagnant)
│   ├── void afficherPlateau(const Partie *ptrPartie)
│   ├── void annoncerTour(const Partie *ptrPartie)
│   ├── bool saisirCoup(const Partie *ptrPartie, Coup *ptrCoup)
│   │   ├── int lireCase(Case *ptrCase)                (scanf d'une case type "B2", conversion lettre/chiffre)
│   │   │   └── void viderLigne()
│   │   ├── Verdict verifierCoup(const Partie *ptrPartie, Coup coup)
│   │   │   ├── bool estDansPlateau(int lig, int col)
│   │   │   └── int direction(Contenu pion)            (-1 pour les Blancs, +1 pour les Noirs)
│   │   └── void afficherRefus(Verdict verdict)
│   ├── Coup choisirCoupOrdinateur(const Partie *ptrPartie)
│   │   ├── Verdict verifierCoup(...)
│   │   ├── int prioriteCoup(const Partie *ptrPartie, Coup coup)
│   │   │                                              (1 à 6, voir stratégie de l'adversaire)
│   │   └── bool estMenacee(const Partie *ptrPartie, Case caseVisee)
│   │       └── bool estDansPlateau(int lig, int col)
│   ├── void jouerCoup(Partie *ptrPartie, Coup coup)
│   ├── void changerJoueur(Partie *ptrPartie)
│   ├── int gagnant(const Partie *ptrPartie)           (0 si la partie continue)
│   │   ├── bool aAtteintDerniereRangee(const Partie *ptrPartie, Contenu pion)
│   │   ├── int compterPions(const Partie *ptrPartie, Contenu pion)
│   │   └── bool peutJouer(const Partie *ptrPartie)
│   │       └── Verdict verifierCoup(...)
│   └── int adversaire(int tour)
├── void afficherGagnant(const Partie *ptrPartie)
└── bool demanderRejouer()
```

## Organisation du projet

Tout le jeu tient pour l'instant dans `jeu.c`. Les fonctions seront déplacées
vers des modules du dossier `lib/` au fur et à mesure qu'elles seront écrites.

| Fichier | Rôle |
| --- | --- |
| `jeu.c` | point d'entrée : règles, choix du mode, plateau, coups |
| `lib/exemple.h` | déclaration des fonctions du module d'exemple |
| `lib/exemple.c` | définition de `afficheSep`, la ligne de séparation |
| `Doxyfile` | configuration de la documentation Doxygen |
| `output/` | scénarios de saisie et traces d'exécution |

## Documentation

La documentation du code est générée par [Doxygen](https://www.doxygen.nl/)
dans le dossier `html/` :

```bash
doxygen Doxyfile
```

## Jeux d'essais

Les traces d'exécution se trouvent dans le dossier `output/`. Chaque trace est
obtenue en lisant les réponses au clavier depuis un fichier de scénario et en
redirigeant l'affichage du programme vers un fichier :

```bash
./jeu < output/scenario-2joueurs.txt > output/trace-2joueurs.txt
./jeu < output/scenario-ordinateur.txt > output/trace-ordinateur.txt
```

| Fichier | Contenu |
| --- | --- |
| `scenario-2joueurs.txt` | réponses saisies : mode 2 joueurs, les 2 prénoms, six saisies refusées puis neuf coups valides dont une prise |
| `trace-2joueurs.txt` | affichage complet du programme pour ce scénario |
| `scenario-ordinateur.txt` | réponses saisies : mode contre l'ordinateur puis trois coups valides |
| `trace-ordinateur.txt` | affichage complet du programme pour ce scénario |

## Journal des changements

Voir [CHANGELOG.md](./CHANGELOG.md).

## Licences

Ce projet utilise deux licences libres pour son contenu.

* Le contenu écrit est sous licence
  [CC-BY-SA](https://creativecommons.org/licenses/by-sa/4.0/), voir le fichier
  [LICENCE-CONTENT](./LICENCE-CONTENT).
* Les programmes et exemples de code sont sous licence
  [unlicence](https://unlicense.org), voir le fichier
  [LICENCE](./LICENCE).