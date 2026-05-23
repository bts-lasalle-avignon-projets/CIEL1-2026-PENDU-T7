#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "model.h"

void jouer();
void gererMenu();
void jouerPartie(char* nom, int themeIndex, int erreursMax);
void mettreAJourJeu(Partie* partie);
void gererResultatPartie(Partie* partie, char* nom, int themeIndex, int secondes);

#endif
