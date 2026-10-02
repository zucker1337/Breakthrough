# Breakthrough

Jeu de plateau à deux joueurs, ou un joueur contre l'ordinateur : chaque camp fait avancer ses pions vers le camp adverse, le premier qui atteint la dernière rangée adverse gagne.

**Groupe** : `G02` -- Mohammad Epifanov, Solomon Fashanu Timileyin, Chaima Gabtni

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

    A B C D E F G H
  8 N N N N N N N N 8
  7 N N N N N N N N 7
  6 . . . . . . . . 6
  5 . . . . . . . . 5
  4 . . . . . . . . 4
  3 . . . . . . . . 3
  2 B B B B B B B B 2
  1 B B B B B B B B 1
    A B C D E F G H

Joueur Blanc, votre coup (ex : B2 B3) 

Adversaire automatique : [à compléter -- stratégie(s) réalisée(s)].

**Fonctionnalités valorisées** : [à compléter au fil du projet -- ex : taille
de plateau paramétrable, historique des coups, scores sur plusieurs parties].

## Compilation et exécution

Sous VSCode, la touche `F5` compile le fichier actif (`jeu.c`) avec tous les
modules du dossier `lib/` et lance l'exécutable.

En ligne de commande :

```bash
gcc -std=c23 -Wall -Werror jeu.c lib/*.c -o jeu -lm
./jeu
```

## Schéma de décomposition

Représentation du plateau : un tableau `int plateau[TAILLE][TAILLE]` où `0` =
case vide, `1` = pion blanc, `2` = pion noir. Les Blancs (joueur 1) avancent
vers la ligne 0, les Noirs (joueur 2) vers la ligne `TAILLE - 1`.

```
main
├── void afficherRegles()
├── int choisirMode()                                  (1 = 2 joueurs, 2 = contre l'ordinateur)
├── int jouerPartie(int mode)                          (renvoie le numéro du gagnant)
│   ├── void initialiserPlateau(int plateau[TAILLE][TAILLE])
│   ├── void afficherPlateau(int plateau[TAILLE][TAILLE])
│   ├── void saisirCoup(int plateau[TAILLE][TAILLE], int joueur,
│   │                   int *ligDep, int *colDep, int *ligArr, int *colArr)
│   │   ├── bool lireCase(int *lig, int *col)          (scanf d'une case type "B2", conversion lettre/chiffre)
│   │   └── bool estCoupValide(int plateau[TAILLE][TAILLE], int joueur,
│   │                          int ligDep, int colDep, int ligArr, int colArr)
│   │       ├── bool estDansPlateau(int lig, int col)
│   │       └── int direction(int joueur)              (-1 pour les Blancs, +1 pour les Noirs)
│   ├── void choisirCoupOrdinateur(int plateau[TAILLE][TAILLE], int joueur,
│   │                              int *ligDep, int *colDep, int *ligArr, int *colArr)
│   │   └── bool estCoupValide(...)
│   ├── void jouerCoup(int plateau[TAILLE][TAILLE],
│   │                  int ligDep, int colDep, int ligArr, int colArr)
│   ├── int gagnant(int plateau[TAILLE][TAILLE], int joueurSuivant)   (0 si la partie continue)
│   │   ├── bool aAtteintDerniereRangee(int plateau[TAILLE][TAILLE], int joueur)
│   │   ├── int compterPions(int plateau[TAILLE][TAILLE], int joueur)
│   │   └── bool peutJouer(int plateau[TAILLE][TAILLE], int joueur)
│   │       └── bool estCoupValide(...)
│   └── int adversaire(int joueur)
├── void afficherGagnant(int joueur)
└── bool demanderRejouer()
```

## Organisation du projet

[À compléter quand le code sera réparti en modules dans `lib/`.]

| Fichier | Rôle |
| --- | --- |
| `jeu.c` | point d'entrée : menu, boucle des parties, rejouer |
| `lib/...` | [...] |

## Documentation

La documentation du code est générée par [Doxygen](https://www.doxygen.nl/)
dans le dossier `html/` :

```bash
doxygen Doxyfile
```

## Jeux d'essais

Les traces d'exécution (parties rejouées, résultats des mesures de
comparaison) se trouvent dans le dossier `output/`.

[À compléter : comment obtenir ces traces.]

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
