<!-- markdownlint-disable MD033 -->

# **Bibliothèque de gestion d'image vectorielle**

## Description

Cette bibliothèque a été développée dans le cadre d'un projet de deuxième année de licence en informatique à l'Université de Reims Champagne-Ardenne (URCA). Elle vise à fournir un backend pour la gestion d'images vectorielles en créant et manipulant des objets SVG. Notre bibliothèque offre des fonctionnalités comme l'ajout de formes géométriques telles que des segments de droite, des polygones réguliers, des rectangles, des ellipses/cercles, ainsi que la possibilité d'ajouter d'autres formes complexes. Elle permet également de gérer la sélection des formes, d'annuler et de rétablir des actions, d'exporter le canevas en cours d'édition au format SVG, et offre des fonctionnalités avancées telles que la transformation des formes par rotation, translation et changement d'échelle, ainsi que la coloration des formes.

Nous prévoyons également d'implémenter des fonctionnalités avancées telles que la gestion avancée des couleurs et des textures, l'exportation vers d'autres formats tels que LaTeX et Tikz, ainsi que la gestion de fichiers SVG. Notre bibliothèque respecte les bonnes pratiques de programmation, utilise le motif de programmation "singleton" pour l'interface publique, et prend en compte les exigences spécifiques du projet telles que l'organisation des formes par catégorie en fonction du nombre de côtés et la gestion de la mémoire pour éviter les fuites.

Nous espérons que cette bibliothèque sera utile pour ceux qui travaillent avec des images vectorielles et sommes ouverts aux contributions et aux commentaires pour l'améliorer davantage.

## Installation

1. Clonnez le dépôt git : `git clone ...'
2. Naviguez dans le dossier du projet : `cd ...'
3. Compilez le projet : `make'

## Utilisation

Pour compiler la blibliotheque, vous pouvez exécuter la commande `make` dans le dossier du projet. Cela construira la bibliothèque statique `libgraweditor.a` dans le dossier `lib/`, les fichiers objets dans le dossier `build/` ainsi que les executables de test.
<br>
Pour utiliser la bibliothèque, vous pouvez inclure le fichier `Grawink.h` dans votre projet et lier le fichier `libgraweditor.a` lors de la compilation. Vous pouvez également consulter les fichiers `test/` pour des exemples d'utilisation de la bibliothèque.
<br>
Pour mieux comprendre comment utiliser la bibliothèque, vous pouvez consulter les fichiers d'en-tête dans le dossier `include/` pour voir les fonctions disponibles et leurs descriptions, ainsi que les fichiers de sources `src\` qui montre en détail les fonctions.

## Structure du projet

Le projet est organisé de la manière suivante :
    <br>- `lib/` : contient la bibliothèque statique compilée (.a) qui est générée après la construction de la bibliothèque
    <br>&nbsp;&nbsp;&nbsp;&nbsp;- `libgraweditor.a`
    <br>- `build/` : contient tous les fichiers objets (.o) générés après la construction de la bibliothèque
    <br>&nbsp;&nbsp;&nbsp;&nbsp;- `... .o`
    <br>- `include/` : contient tous les fichiers d'en-tête (.h) utilisés dans la bibliothèque
    <br>&nbsp;&nbsp;&nbsp;&nbsp;- `... .h`
    <br>- `src/` : contient tous les fichiers sources (.cpp) de la bibliothèque
    <br>&nbsp;&nbsp;&nbsp;&nbsp;- `... .cpp`
    <br>- `test/` : contient tous les fichiers sources de test pour tester la bibliothèque
    <br>&nbsp;&nbsp;&nbsp;&nbsp;- `... .cpp`
    <br>- `out/` : contient tous les fichiers générés par les tests de la bibliothèque
    <br>&nbsp;&nbsp;&nbsp;&nbsp;- `svg/` : contient tous les svg générés par les tests de la bibliothèque
    <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- `... .svg`
    <br>&nbsp;&nbsp;&nbsp;&nbsp;- `Tikz/` : contient tous les fichiers Tikz générés par les tests de la bibliothèque
    <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- `... .tex`
    <br>&nbsp;&nbsp;&nbsp;&nbsp;- `... .ppm` : contient tous les fichiers image.ppm(image sans transparence) générés par les tests de la bibliothèque
    <br>&nbsp;&nbsp;&nbsp;&nbsp;- `... .pam` : contient tous les fichiers image.pam(image avec transparence) générés par les tests de la bibliothèque
    <br>- `log/` : contient tous les fichiers de log générés par les tests de la bibliothèque
    <br>&nbsp;&nbsp;&nbsp;&nbsp;- `... .log`
    <br>- `AUTHORS.md` : contient la liste des contributeurs et leurs contributions
    <br>- `makefile` : contient les règles de construction pour la bibliothèque et les tests
    <br>- `README.md` : contient la description du projet
    <br>- `Rapport.pdf` : contient le rapport du projet au format PDF
    <br>- `UML` : contient le diagrammes UML de la bibliothèque
    <br>- `... .exe` : multiples exécutables de test

## Tests

Pour tester la bibliothèque, vous pouvez exécuter la commande `make run EXEC=SVGCreate.exe` dans le dossier du projet. Cela construira la bibliothèque et exécutera tous les tests de la bibliothèque.
<br>
Les fichiers SVG générés par les tests sont stockés dans le dossier `out/svg/`.
<br>
Vous pouvez également consulter le dossier `test/` pour voir les fichiers sources de test.

## Contact

Pour toute question ou suggestion, n'hésitez pas à nous contacter à l'adresse suivante :

- MUNSCH Bryan <bryan.munsch@etudiant.univ-reims.fr>
- RYBAK Thomas <thomas.rybak@etudiant.univ-reims.fr>
