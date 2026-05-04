#ifndef VIEW_H
#define VIEW_H

void afficherTitre();
void demanderNomJoueur(char* nom);
void afficherMotATrouver(char* motATrouver);
void afficherErreurs(int erreurs, int erreursMax);
char demanderLettre();
void afficherVictoire(char* nom, int tentatives, char* motSecret);
void afficherDefaite(char* nom, char* motSecret);
void afficherLettreIncorrecte();
char rejouerPartie();

#endif
