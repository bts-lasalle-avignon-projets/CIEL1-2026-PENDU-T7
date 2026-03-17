#ifndef MODEL_H
#define MODEL_H

#define MAX_LETTRES 15
#define NB_MAX_ERREURS 6

struct Partie
{
    char motSecret[MAX_LETTRES];
    char motATrouver[MAX_LETTRES];
    int erreurs;
    int erreursMax;
};

void initialiserPartie(Partie *partie);
void choisirMotSecret(Partie *partie);
void initialiserMotATrouver(Partie *partie);
void mettreAJourMotATrouver(Partie *partie, char lettre);
bool testerVictoire(Partie *partie);
bool testerDefaite(Partie *partie);
int  verifierLettre(Partie *partie, char lettre);
void afficherResultatPartie(Partie *partie, char *nom);

#endif //MODEL_H
