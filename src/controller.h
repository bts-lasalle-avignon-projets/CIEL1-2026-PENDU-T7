#ifndef CONTROLLER_H
#define CONTROLLER_H
//#define DEBUG_CONTROLLER
#include "model.h"

void jouer();
void jouerPartie(char *nom);
void mettreAJourJeu(Partie *partie);
void afficherResultatPartie(Partie *partie, char *nom);

#endif // CONTROLLER_H
