# SAE1
# [BREAKTHROUGH]

> 

> Jeu de BREAKTHROUGH est un jeu de stratégie abstrait pour deux joueurs, il ressemble énormement au jeux des Dames.  Chaque joueur déplace une pièce par coup. Une pièce peut être déplacée d'une case vers l'avant, tout droit ou en diagonale, si la case d'arrivée est vide. Une pièce peut aussi être déplacée vers une case occupée par une pièce adverse, si la case d'arrivée se trouve à une case en diagonale et en avant.
>
> Débrief du client: « Je veux un jeu de plateau jouable en console, à deux joueurs, avec détection de victoire et parties rejouables, plus un adversaire automatique. Le choix du jeu et des fonctionnalités supplémentaires est libre. »

**Groupe** : Solomon FASHANU, Mohammad EPIFANOV, Chaima GABTNI

## Description

Breakthrough est un jeu de stratégie de plateau créé par Dan Troyka en 2000. Il gagna le concours du meilleur design de jeu de plateau 8x8, et il a quelques similitudes avec les Dames, mais la stratégie est différente. 
La partie se joue sur un plateau carré de 8x8 cases avec des pièces blanches et noires. Le but du jeu est d'atteindre la rangée de départ de l'adversaire, la plus éloignée du joueur. Cela signifie que le joueur blanc doit atteindre la 8e rangée et que le joueur noir doit atteindre la 1ère rangée pour gagner la partie.
## Compilation et exécution

Sous VSCode, la touche `F5` compile le fichier actif (`jeu.c`) avec tous les
modules du dossier `lib/` et lance l'exécutable.

En ligne de commande :
S
```bash
# TODO: adaptez si votre point d'entrée ou vos options de compilation changent
gcc -std=c23 -Wall -Werror jeu.c lib/*.c -o jeu -lm
./jeu
```

[Précisez ici toute dépendance ou option particulière propre à votre projet :
bibliothèque externe, arguments de lancement, mode de jeu...]

## Schéma de décomposition

[Remplacez l'arbre ci-dessous par celui de votre jeu : une ligne par
fonction, avec sa signature, décalée sous la fonction qui l'appelle. Mettez-le
à jour si votre découpage en fonctions évolue.]

```
main
├── [type nomFonction(paramètres)]
│   ├── [type sousFonction(paramètres)]
│   └── [...]
└── [...]
```

## Organisation du projet

[Décrivez vos modules du dossier `lib/` et leur responsabilité.]

| Fichier | Rôle |
| --- | --- |
| `jeu.c` | [point d'entrée du jeu] |
| `lib/...` | [...] |

## Documentation

La documentation du code est générée par [Doxygen](https://www.doxygen.nl/)
dans le dossier `html/` :

```bash
doxygen Doxyfile
```

[Remplacez la valeur de `PROJECT_NAME` dans le `Doxyfile` par le nom de votre
jeu.]

## Jeux d'essais

Les traces d'exécution (parties rejouées, résultats des mesures de
comparaison) se trouvent dans le dossier `output/`.

Vous devrez expliquer comment obtenir ces traces.

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

