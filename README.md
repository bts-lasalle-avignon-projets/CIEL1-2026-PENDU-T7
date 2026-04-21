# Mini-projet BTS CIEL IR1 2026 : PENDU

# Mini-projet : pendu
- [Mini-projet : Pendu](#mini-projet--pendu)
  - [Présentation](#présentation)
  - [Déroulement d'une partie](#déroulement-dune-partie)
  - [Utilisation](#utilisation)
  - [Itérations](#itérations)
    - [Itération 1](#itération-1)
    - [Itération 2](#itération-2)
    - [Itération 3](#itération-3)
  - [Changelog](#changelog)
    - [Version 1.0](#version-10)
  - [TODO](#todo)
  - [Équipe de développement](#équipe-de-développement)

---

## Présentation

Le pendu est un jeu consistant à trouver un mot en devinant quelles sont les lettres qui le composent. Le jeu se joue traditionnellement à deux, avec un papier et un crayon, selon un déroulement bien particulier. Quand le dessin est terminé on voit un bonhomme allumette qui se pend. L’origine du jeu du pendu est inconnue. En Grande-Bretagne, il semble avoir fait son apparition pendant l’époque victorienne, vers la fin du XIXe siècle.

## Déroulement d'une partie

Il s’agit de réaliser un logiciel permettant de jouer des parties du jeu du Pendu. Ce jeu se jouant traditionnellement à deux, on aura ici un utilisateur
(le joueur) contre la machine :

Les deux joueurs dans cet exemple s’appellent Stéphane et Julien : 
La machine : elle a la charge de choisir un mot à découvrir et de le proposer au joueur sous une forme où les lettres à découvrir sont masquées. C’est la machine qui fixe les « règles du jeu » en déterminant un nombre de coups maximum pour le découvrir et en comptant les erreurs. Le joueur : il demande à jouer une partie du jeu du pendu. Il a un nombre maximum de tentatives (qui correspondent au dessin du pendu ) pour découvrir ce mot mystère.

Julien pense à un mot et dessine une rangée de tirets, chacun correspondant à une lettre de ce mot.
Stéphane annonce une lettre.
La lettre fait-elle partie du mot ?
Oui : Julien l’inscrit à sa place autant de fois qu’elle se trouve dans le mot.
Non : Julien dessine le premier trait du pendu.
Le jeu se poursuit jusqu'à ce que :
Stéphane gagne la partie en trouvant toutes les lettres du mot ou en le devinant correctement.
Julien gagne la partie en complétant le dessin du pendu.

## Utilisation

```bash
$ make

$ ./pickomino.out
```

![](./images/pendu_V1.gif)

---

## Itérations

### Itération 1

- Jouer une partie ou plusieurs parties
- Afficher le déroulement d'une partie
- Saisir le nom du joueur

### Itération 2

- choisir le thème (les mots pour chaque thème sont conservés dans des fichiers)
- visualiser les lettres proposées
- gérer un niveau de difficulté 

### Itération 3

- Chronométrer la partie
- Sauvegarder les meileurs scores

## Changelog

### Version 1.0

- [x] Rejouer une partie
- [x] Lancer une partie
- [x] Mettre à jour le jeu/mot à trouver
- [x] Choisir un nom de joueur
- [x] Choisir le mot au hasard
- [x] Demander une lettre ou un mot
- [x] Vérifier si la lettre existe et/ou dans le mot
- [x] Afficher une victoire ou une défaite

## TODO

- [ ] Remplacer les types char en string
- [ ] Pouvoir choisir des thèmes
- [ ] Implémenter une fonction permettant de vérifier si le mot saisi est le mot secret
- [ ] Visualiser les lettres proposées


## Équipe de développement

- BORGEL LAMARQUE Antonin
- GREINER Jovan

---
&copy; 2026-2027 BTS LaSalle Avignon
