#ifndef VIEW_H
#define VIEW_H
#include "model.h"

void afficherTitre();
void afficherMenu();
void afficherRegles();
int  choisirMenu();
void demanderNomJoueur(char* nom);
int  choisirTheme();
int  choisirDifficulte();
void afficherMotATrouver(char* motATrouver);
void afficherErreurs(int erreurs, int erreursMax);
void afficherLettresProposees(Partie* partie);
void afficherPendu(int erreurs, int erreursMax);
void demanderSaisie(char* buffer, int taille);
char demanderLettre();
void afficherTemps(int secondes);
void afficherVictoire(char* nom, int tentatives, char* motSecret, int secondes);
void afficherDefaite(char* nom, char* motSecret);
void afficherLettreIncorrecte();
void afficherLettreDejaProposee();
void afficherMauvaisMot();
void afficherScores(Score scores[], int nbScores);
char rejouerPartie();

#endif
