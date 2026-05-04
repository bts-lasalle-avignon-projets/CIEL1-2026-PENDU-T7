#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "model.h"

void jouer();
void jouerPartie(char* nom, int themeIndex, int erreursMax);
void mettreAJourJeu(Partie* partie);
void gererResultatPartie(Partie* partie, char* nom);

#endif
