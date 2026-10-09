# Changelog

Toutes les évolutions notables du projet, semaine par semaine, la plus
récente en haut. Format inspiré de
[Keep a Changelog](https://keepachangelog.com/fr/1.1.0/). Chaque changement
précise qui l'a réalisé avec une mention `@prénom` ; un changement
réalisé à plusieurs cite tous ses auteurs : `(@prénom1, @prénom2)`.

## Semaine 1 -- 02/10/26

### Ajouté

* Choix du jeu : Breakthrough (@Mohammad, @Solomon, @Chaima).

* Règles du jeu et déroulement d'une partie décrits dans le `README.md` (@Mohammad, @Solomon, @Chaima).

* Choix de la représentation du plateau : tableau 2D d'entiers (@Mohammad, @Solomon, @Chaima).

* Schéma de décomposition du programme dans le `README.md` (@Mohammad, @Solomon, @Chaima).


## Semaine 2 -- 05/10/26

### Ajouté

- Création du tableau remplis de 0 d'une taille finie (@Solomon)

- Ajout des index pour définir les cases du plateau : colonnes = Lettres & lignes = nombres (@Mohammad, @Chaima)

- Fonctionnalité de taille de tableau variable à l'aide de #define TAILLE x (@Chaima)

- Ajout du scanf pour récupérer le prénom de 2 joueurs dans le cas où l'on joue contre des humains (@Solomon)


### Modifié

- affichage plus cohérent visuellement parlant avec espacements concernant le tableau (@Mohammad)

- Les noms des joueurs sont stockés dans `main` et passés à `deuxJoueurs` pour pouvoir être réutilisés dans les messages (@Mohammad, @Solomon)

- Description de la représentation du plateau et du schéma de décomposition mise à jour dans le `README.md` (@Mohammad, @Solomon)

### Corrigé

- Retours sur le rendu de la semaine 1 :

- code du groupe corrigé dans le `README.md` : `G2C` au lieu de `G02` (@Mohammad)

- stratégie prévue de l'adversaire automatique précisée dans le `README.md` (@Mohammad)


## Semaine 2 -- 07/10/26

### Ajouté

- Placement des pions de départ (Noirs sur les 2 premières lignes, Blancs sur les 2 dernières) et affichage `N` / `B` à la place des valeurs 2 / 1 (@Mohammad, @Solomon)

- Affichage du nom du joueur dont c'est le tour (C'est à … de jouer) (@Solomon)

- Fonction `simulerDeplacementPion` : simule un coup du joueur 1 puis réaffiche le plateau mis à jour puis annonce le tour du joueur 2 (@Mohammad)

### Modifié 

- Séparation de `plateau` en deux fonctions `initialiserPlateau` (remise à l'état initial) et `afficherPlateau` (affichage seul), pour pouvoir placer des pions à la main avant l'affichage (@Mohammad, @Solomon)


### Corrigé

- Un nom de joueur trop long (plus de 20 caractères) pouvait déborder du tableau : la saisie est maintenant limitée (@Solomon)


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
