#ifndef MODEL_H
#define MODEL_H

#define VERSION        "1.2"
#define MAX_LETTRES    15
#define NB_MAX_ERREURS 6

enum EtatLettre
{
    LETTRE_INVALIDE,
    LETTRE_TROUVEE,
    LETTRE_ABSENTE,
    LETTRE_MAJUSCULE
};

struct Partie
{
    char motSecret[MAX_LETTRES];
    char motATrouver[MAX_LETTRES];
    int  erreurs;
    int  erreursMax;
};

void       initialiserPartie(Partie* partie);
void       choisirMotSecret(Partie* partie);
void       initialiserMotATrouver(Partie* partie);
void       mettreAJourMotATrouver(Partie* partie, char lettre);
bool       testerVictoire(Partie* partie);
bool       testerDefaite(Partie* partie);
EtatLettre verifierLettre(Partie* partie, char lettre);
bool       testerRejouerPartie(char reponse);

#endif // MODEL_H
