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
   refusé avec un message explicatif et le joueur rejoue le coup. Une saisie
   qui ne ressemble à rien donne une case en dehors du plateau, elle est donc
   refusée comme les autres
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

**Adversaire automatique**

En mode « contre l'ordinateur », l'humain joue les Blancs (joueur 1, il
commence) et l'ordinateur joue les Noirs (joueur 2). L'ordinateur ne joue que
des coups valides, et son coup est affiché comme celui d'un joueur humain :

```
Ordinateur joue C7 D6
```

Pour choisir, il commence toujours par lister ses coups valides avec
`listerCoups` : il regarde chaque case du plateau, et pour chacun de ses pions
il essaie les 3 cases devant lui, puis il garde seulement celles que
`verifierCoup` accepte. Il y a au plus 16 pions fois 3 cases, donc 48 coups,
d'où le tableau de taille `2 * TAILLE * 3`.

**Les 2 approches comparées**

C'est le sous-problème qu'on a choisi de comparer. On passe d'une approche à
l'autre en répondant à la question posée au lancement, sans rien changer dans
le programme.

| Approche | Fonction | Comment elle choisit |
| --- | --- | --- |
| 1 : au hasard | `coupAuHasard` | elle prend un coup au hasard dans la liste, avec `rand() % nb` |
| 2 : le meilleur coup | `meilleurCoup` | elle cherche d'abord un coup qui gagne tout de suite, sinon un coup qui mange un pion adverse, sinon elle prend au hasard |

L'approche 1 regarde la liste une seule fois pour la construire. L'approche 2
la reparcourt jusqu'à 2 fois de plus pour chercher le coup gagnant puis la
prise, donc elle fait plus de travail.

Les essais `partie-05` et `partie-06` montrent la différence : contre
l'approche 1, les Blancs traversent le plateau en 11 coups sans être gênés,
alors que contre l'approche 2 l'ordinateur mange le pion dès qu'il passe à sa
portée et c'est lui qui gagne.

L'ordinateur n'est jamais appelé sans coup possible : si un joueur ne peut
plus jouer, `gagnant` le détecte (avec `peutJouer`) et la partie s'arrête
avant.

La graine du hasard est fixée avec `srand(GRAINE)` au début de `main`, pour
qu'une partie rejouée donne toujours le même résultat. Il suffit de mettre
`srand(time(NULL))` à la place pour avoir des parties différentes à chaque
lancement.

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

### Fonctions réalisées (semaine 5)

Le nom du module est indiqué devant chaque fonction.

```
main                                                    (jeu.c)
├── affichage : void afficherRegles(void)
├── saisie    : int choisirMode(void)                   (1 = deux joueurs, 2 = contre l'ordinateur)
├── partie    : void preparerJoueurs(Partie *ptrPartie) (donne son pion et un nom à chaque joueur)
├── saisie    : void demanderNoms(Partie *ptrPartie)    (mode 1 : demande les 2 prénoms)
├── saisie    : int choisirStrategie(void)              (mode 2 : 1 = au hasard, 2 = le meilleur coup)
│
└── pour chaque partie, tant que les joueurs veulent rejouer :
    ├── partie    : void nouvellePartie(Partie *ptrPartie)
    │   └── plateau : void initialiserPlateau(Partie *ptrPartie)
    ├── affichage : void afficherPlateau(Partie partie)
    │
    ├── pour chaque tour, tant que personne n'a gagné :
    │   ├── affichage : void annoncerTour(Partie partie)
    │   ├── si c'est à l'ordinateur de jouer :
    │   │   ├── ordinateur : Coup coupOrdinateur(Partie partie, int strategie)
    │   │   │   ├── ordinateur : Coup coupAuHasard(Partie partie)   (approche 1)
    │   │   │   ├── ordinateur : Coup meilleurCoup(Partie partie)      (approche 2)
    │   │   │   └── ordinateur : int listerCoups(Partie partie, Coup liste[MAX_COUPS])
    │   │   └── affichage : void afficherCoupOrdinateur(Partie partie, Coup coup)
    │   ├── sinon : saisie : Coup saisirCoup(Partie partie)  (redemande si le coup est refusé)
    │   │   ├── saisie    : Case lireCase(void)         (lit une case tapée comme B2)
    │   │   ├── coups     : Verdict verifierCoup(Partie partie, Coup coup)
    │   │   │   ├── plateau : bool estDansPlateau(int ligne, int colonne)
    │   │   │   ├── plateau : int direction(Contenu pion)
    │   │   │   └── partie  : Contenu pionDuTour(Partie partie)
    │   │   └── affichage : void afficherRefus(Verdict verdict)
    │   ├── coups     : void jouerCoup(Partie *ptrPartie, Coup coup)
    │   ├── affichage : void afficherPlateau(Partie partie)
    │   ├── partie    : void changerJoueur(Partie *ptrPartie)
    │   └── partie    : int gagnant(Partie partie)      (indice du gagnant ou PAS_DE_GAGNANT)
    │       ├── plateau : bool aAtteintDerniereRangee(Partie partie, Contenu pion)
    │       ├── plateau : int compterPions(Partie partie, Contenu pion)
    │       └── coups   : bool peutJouer(Partie partie)
    │           └── coups : Verdict verifierCoup(...)
    │
    ├── affichage : void afficherGagnant(Partie partie, int vainqueur)
    └── saisie    : bool demanderRejouer(void)
```

Une fonction qui modifie la partie reçoit un pointeur `Partie *ptrPartie`,
parce que sans pointeur elle ne travaillerait que sur une copie et la
modification serait perdue. Une fonction qui lit seulement reçoit la partie
elle-même, `Partie partie`, ce qui évite les flèches et se lit avec un simple
point.

`gagnant`, `verifierCoup` et `peutJouer` sont dans les modules de logique :
elles répondent sans rien afficher et sans rien lire au clavier.

### Ce qu'il reste à faire

Les mesures : compter le nombre de tours de boucle de chaque approche selon la
taille du plateau, et faire jouer les 2 approches l'une contre l'autre sur
beaucoup de parties pour voir laquelle gagne le plus. Les résultats iront dans
`output/` et la synthèse dans ce fichier.

## Organisation du projet

`jeu.c` ne contient plus que le programme principal. Tout le reste est réparti
dans `lib/`, avec un fichier `.h` pour les déclarations et un `.c` pour le
code.

Les trois premiers modules sont la **logique du jeu** : ils ne contiennent
aucun `printf` et aucun `scanf`. On peut donc leur demander si un coup est
valide, et sinon pourquoi, ou s'il y a un vainqueur, sans rien afficher ni
rien lire au clavier. C'est ce qui permettra de faire jouer l'ordinateur à la
place d'un joueur.

| Fichier | Rôle |
| --- | --- |
| `jeu.c` | programme principal : enchaîne les parties et les tours |
| `lib/partie.h` | les types du jeu (`Contenu`, `Verdict`, `Case`, `Coup`, `Joueur`, `Partie`) et les constantes |
| `lib/partie.c` | mise en place des joueurs, changement de tour, recherche du vainqueur |
| `lib/plateau.h` / `lib/plateau.c` | le plateau : placement des pions de départ, sens d'avance, comptage des pions, dernière rangée atteinte |
| `lib/coups.h` / `lib/coups.c` | les coups : un coup est-il valide et sinon pourquoi, déplacement d'un pion, reste-t-il un coup jouable |
| `lib/ordinateur.h` / `lib/ordinateur.c` | les 2 stratégies de l'adversaire automatique et la liste de ses coups valides |
| `lib/affichage.h` / `lib/affichage.c` | tout ce qui est écrit sur la sortie standard : séparation, règles, plateau, tour, refus, résultat |
| `lib/saisie.h` / `lib/saisie.c` | tout ce qui est lu au clavier, et les erreurs sur la sortie d'erreur |
| `Doxyfile` | configuration de la documentation Doxygen |
| `output/` | jeux d'essais : saisies, sortie et erreurs de chaque partie rejouée |

Les types sont dans `partie.h` parce que tout tourne autour de la structure
`Partie` : les autres modules incluent ce fichier, donc aucun module n'a
besoin d'inclure un autre module pour connaître les types.

## Documentation

La documentation du code est générée par [Doxygen](https://www.doxygen.nl/)
dans le dossier `html/` :

```bash
doxygen Doxyfile
```

## Jeux d'essais

Une partie peut être rejouée automatiquement : les saisies des joueurs sont
lues dans un fichier au lieu d'être retapées au clavier. Les essais sont dans
le dossier `output/`.

Chaque essai porte un nom et donne trois fichiers :

| Extension | Contenu |
| --- | --- |
| `.in` | les saisies des joueurs, une par ligne |
| `.out` | ce que le jeu écrit sur la sortie standard : invites, plateau, refus, résultat |
| `.err` | ce que le jeu écrit sur la sortie d'erreur, donc uniquement les vraies erreurs |

**Pour rejouer un essai** (ici le premier) :

```bash
./jeu < output/partie-01.in > output/partie-01.out 2> output/partie-01.err
```

`<` branche le fichier de saisies sur l'entrée, `>` récupère la sortie
standard et `2>` récupère la sortie d'erreur. Les deux flux restent dans deux
fichiers séparés.

Pour rejouer les six essais d'un coup :

```bash
for n in 01 02 03 04 05 06; do
  ./jeu < output/partie-$n.in > output/partie-$n.out 2> output/partie-$n.err
done
```

### Les essais enregistrés

| Essai | Ce qu'il couvre | Code de retour |
| --- | --- | --- |
| `partie-01` | 2 joueurs : les 5 coups refusés possibles, puis victoire des Blancs | 0 |
| `partie-02` | 2 joueurs : victoire des Noirs | 0 |
| `partie-03` | 2 joueurs : deux parties enchaînées, chaque camp gagne une fois | 0 |
| `partie-04` | 2 joueurs : les saisies s'arrêtent au milieu de la partie | 1 |
| `partie-05` | contre l'ordinateur, approche 1 au hasard : les Blancs gagnent en 11 coups | 0 |
| `partie-06` | contre l'ordinateur, approche 2 le meilleur coup : l'ordinateur gagne en 32 coups | 0 |

Il n'y a pas d'essai de match nul parce qu'il n'y a pas de match nul à
Breakthrough.

**Quand les saisies s'arrêtent avant la fin de la partie**, le jeu ne redemande
pas indéfiniment : il écrit `Erreur : les saisies sont épuisées, la partie est
arrêtée` sur la sortie d'erreur et s'arrête avec le code de retour 1. C'est ce
que montre `partie-04`, le seul essai dont le fichier `.err` n'est pas vide.

L'ordinateur tire ses coups au hasard, mais la graine est fixée avec
`srand(GRAINE)`, donc un essai rejoué donne exactement le même résultat à
chaque fois.

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