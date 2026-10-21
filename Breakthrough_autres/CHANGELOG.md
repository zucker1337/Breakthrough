# Changelog

Toutes les évolutions notables du projet, semaine par semaine, la plus
récente en haut. Format inspiré de
[Keep a Changelog](https://keepachangelog.com/fr/1.1.0/). Chaque changement
précise qui l'a réalisé avec une mention `@prénom` ; un changement
réalisé à plusieurs cite tous ses auteurs : `(@prénom1, @prénom2)`.

## Semaine 4 -- 19/10/26

### Modifié

- Lecture d'une case à l'aide de `scanf("%9s", ...)` & `atoi`, à la place du retour de `scanf` : une entrée bizarre donne une case hors du plateau, donc refusée comme les autres (@Mohammad)

- Constante `TAILLE_SAISIE` pour la place que prend une case tapée au clavier (@Solomo)

- Supprimer `viderLigne` (@Solomon)

- Retour de la case par `lireCase` et du coup par `saisirCoup`, à la place des pointeurs passés en paramètre (@Solomon, @Mohammad)

### Corrigé

- Retours sur le rendu de la semaine 3 :
  - pénalité hors-cours : plus de retour de `scanf` ni de `EOF` dans le code (@Mohammad, @Solomon)
  - une seule entrée pour la semaine 3 (@Solon)

## Semaine 3 -- 16/10/26

(@Solomon et @Chaima étaient absents en cours le 16/10, ils ont travaillé
en distanciel)

### Ajouté

- Procédure `annoncerTour` affiche le prénom du joueur dont c'est le tour l'annonce se fait plus dans `choisirMode` (@Mohammad)

- Dossier `output/` : deux scénarios de saisie et les deux traces d'exécution correspondantes avec la commande pour les régénérer (@Solomon)

- Structures `Case`, `Coup`, `Joueur` et `Partie` : les informations qui vont ensemble sont regroupées et les fonctions s'échangent les unités au lieu des longues listes de paramètres (@Solomon)

- Enumérations `Contenu` (`CASE_VIDE`, `PION_BLANC`, `PION_NOIR`) et `Verdict` : ce que contient une case et la raison du refus d'un coup sont maintenant plus des nombres écrits directement dans le code (@Solomon)

- Procédure `initialiserPartie` : va placer les pions de départ et remplire les 2 joueurs avec leur nom et leur pion et va remettre le tour et le compteur de coups à 0 (@Solomon)

- Procédures `jouerPartie` et `changerJoueur` : après chaque coup valide le tour passe à l'autre joueur qui sera appelé avec son nom (@Solomon)

- Fonction `peutJouer` : parcourt les pions du joueur et leurs 3 cases d'arrivée pour savoir s'il lui reste un coup jouable et la partie s'arrête quand c'est plus le cas (@Solomon, @Mohammad)

- Fonction `verifierCoup` et procédure `afficherRefus` : un coup en dehors du plateau parti d'une case qui n'est pas à soi qui ne va pas d'une seule case vers l'avant qui avance tout droit sur une case occupée ou qui arrive sur un de ses propres pions est refusé avec un message qui explique pourquoi puis le joueur pourra rejouer (@Mohammad)

- Fonction `lireCase` et procédure `viderLigne` : ils lisent une case tapée `B2` ou `b2` et jettent une saisie illisible sans bloquer le programme (@Chaima)

- Fonction `saisirCoup` : redemande son coup au joueur tant que le coup est refusé (@Chaima)

- Procédure `jouerCoup` : permet de placer le coup sur le plateau et retire le pion adverse mangé et compte un coup de plus (@Chaima)

- Constantes `NB_JOUEURS` et `TAILLE_NOM` à la place du 2 et du 30 écrits directement dans le code (@Mohammad)

### Modifié

- `main` affiche maintenant les règles avant de demander le mode comme l'annonce le `README.md` (@Mohammad)

- Schéma de décomposition du `README.md` mis à jour : `int choisirMode()`, `deuxJoueurs` et `annoncerTour` sont appelées depuis `main` et les paramètres pointeurs sont ont pour prefix `ptr` (@Mohammad, @Solomon)

- `afficherPlateau` et `annoncerTour` reçoivent la partie entière et non plus le plateau ou le tableau des prénoms séparément (@Chaima)

- `annoncerTour` affiche aussi le numéro du coup en cours, lu dans le champ `nbCoups` de la partie (@Solomon)

- `deuxJoueurs` écrit les prénoms dans le tableau de `Joueur` de la partie (@Solomon)

- `simulerDeplacementPion` est supprimée donc le coup écrit à la main donc on en a plus besoin pour que les joueurs saisissent leurs coups (@Mohammad)

### Corrigé

- Retours sur le rendu de la semaine 2 :
  - `choisirMode` ne fait plus qu'une seule chose : elle demande le mode et le renvoie (`int choisirMode()` au lieu de `void`) la lecture des prénoms et l'annonce du tour sont remontées dans `main` (@Mohammad)
  - les prénoms sont déclarés dans `main` et sont donc plus perdus à la sortie de `choisirMode` et ils resteront disponibles pendant toute la partie (@Mohammad)
  - `simulerDeplacementPion` écrit `mat[TAILLE - 2][3]` et `mat[TAILLE - 3][3]` au lieu de `mat[6][3]` et `mat[5][3]` : le coup D2 -> D3 reste juste quelle que soit la valeur de `TAILLE` (@Mohammad, @Chaima)
  - les passages `[À compléter...]` et `[...]` du `README.md` sont remplacés par leur contenu réel (fonctionnalités valorisées) , organisation du projet, jeux d'essais (@Solomon)

- Les variables `choix` et `a` sont initialisées avant d'être lues par `scanf` (@Mohammad)

## Semaine 2 -- 09/10/26

### Ajouté

- Création du tableau rempli de 0 d'une taille finie (@Solomon)

- Ajout des index pour définir les cases du plateau : colonnes = lettres & lignes = nombres (@Mohammad, @Chaima)

- Fonctionnalité de taille de tableau variable à l'aide de `#define TAILLE x` (@Chaima)

- Ajout du scanf pour récupérer le prénom de 2 joueurs dans le cas où l'on joue contre des humains (@Solomon)

- Placement des pions de départ (Noirs sur les 2 premières lignes, Blancs sur les 2 dernières) et affichage `N` / `B` à la place des valeurs 2 / 1 (@Mohammad, @Solomon)

- Affichage du nom du joueur dont c'est le tour (C'est à … de jouer) (@Solomon)

- Fonction `simulerDeplacementPion` : simule un coup du joueur 1 puis réaffiche le plateau mis à jour puis annonce le tour du joueur 2 (@Mohammad)

- Fonction `estDansPlateau` : vérifie qu'une case (ligne, colonne) est dans le plateau, prévue pour la validation des coups mais pas encore utilisée (@Mohammad)

- Procédure `choisirMode` : demande le mode de jeu (1 = deux joueurs, 2 = contre l'ordinateur) ; le choix du mode n'est plus écrit directement dans `main`, conformément au schéma de décomposition (@Solomon)

- Commentaires Doxygen (`@brief`, `@param`, `@return`) sur les 8 fonctions de `jeu.c` et sur la constante `TAILLE` ; les 3 commentaires `//` qui répétaient le `@brief` placé juste en dessous ont été absorbés dans les blocs, `doxygen Doxyfile` ne signale plus aucun élément non documenté (@Solomon, @Chaima, @Mohammad)

### Modifié

- Affichage plus cohérent visuellement parlant avec espacements concernant le tableau (@Mohammad)

- Les noms des joueurs sont stockés dans `main` et passés à `deuxJoueurs` pour pouvoir être réutilisés dans les messages (@Mohammad, @Solomon)

- Séparation de `plateau` en deux fonctions `initialiserPlateau` (remise à l'état initial) et `afficherPlateau` (affichage seul), pour pouvoir placer des pions à la main avant l'affichage (@Mohammad, @Solomon)

- Description de la représentation du plateau et du schéma de décomposition mise à jour dans le `README.md` (@Mohammad, @Solomon)

- Le plateau passe de `int mat[TAILLE][TAILLE]` à `char mat[TAILLE][TAILLE]` car une case ne contient que 3 valeurs possibles (0, 1 et 2), un `char` (1 octet) suffit au lieu d'un `int` (4 octets), soit 64 octets au lieu de 256 pour le plateau (@Mohammad, @Solomon)

- Justification du choix de structure de données (tableau 2D, carré, de `char`) ajoutée dans le `README.md` (@Mohammad)

- Les noms des joueurs et l'annonce du tour sont déplacés de `main` vers `choisirMode` (@Solomon)

- Schéma de décomposition mis à jour dans le `README.md` : `choisirMode` appelle `deuxJoueurs`, et `choisirMode` renverra le mode choisi dans la version finale (@Mohammad)

### Corrigé

- Retours sur le rendu de la semaine 1 :
  - code du groupe corrigé dans le `README.md` : `G2C` au lieu de `G02` (@Mohammad)
  - stratégie prévue de l'adversaire automatique précisée dans le `README.md` (@Mohammad)

- Un nom de joueur trop long (plus de 29 caractères) pouvait déborder du tableau : la saisie est maintenant limitée (@Solomon)

- Retour sur le rendu de la semaine 2 : stratégie de l'adversaire automatique précisée dans le `README.md` (camp joué par l'ordinateur, liste des coups possibles, 6 niveaux de priorité, définition d'une case menacée, tirage au hasard en cas d'égalité) (@Mohammad)

## Semaine 1 -- 02/10/26

### Ajouté

- Choix du jeu : Breakthrough (@Mohammad, @Solomon, @Chaima)

- Règles du jeu et déroulement d'une partie décrits dans le `README.md` (@Mohammad, @Solomon, @Chaima)

- Choix de la représentation du plateau : tableau 2D d'entiers (@Mohammad, @Solomon, @Chaima)

- Schéma de décomposition du programme dans le `README.md` (@Mohammad, @Solomon, @Chaima)

- Fonction `afficherRegles` : affiche les règles du jeu au lancement (@Solomon)

- Menu de choix du mode au lancement : 1 = deux joueurs, 2 = contre l'ordinateur (@Solomon)

<!--
Dupliquez ce gabarit chaque semaine, en l'ajoutant tout en haut du fichier
(la semaine la plus récente en premier). Ne gardez que les sous-catégories
utiles à la semaine concernée.

## Semaine N -- JJ/MM/AA

### Ajouté

- ... (@prénom)

### Modifié

- ... (@prénom)

### Corrigé

- ... (@prénom)

-->
