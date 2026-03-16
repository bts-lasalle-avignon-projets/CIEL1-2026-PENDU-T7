#ifndef VIEW_H
#define VIEW_H

#include <string>

void afficherTitre();
void demanderNomJoueur(char *nom);
void afficherMotATrouver(char *motATrouver);
void afficherErreurs(int erreurs, int erreursMax);
char demanderLettre();
void afficherVictoire(char *nom, int erreurs, int erreursMax);
void afficherDefaite(char *nom, char *motSecret);

#endif // VIEW_H
