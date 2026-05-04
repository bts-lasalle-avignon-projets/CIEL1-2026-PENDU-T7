#ifndef MODEL_H
#define MODEL_H

#define VERSION        "2.0"
#define MAX_LETTRES    30
#define NB_MAX_ERREURS 8 // niveau facile
#define MAX_MOTS_THEME 100
#define NB_THEMES      4

enum EtatLettre
{
    LETTRE_INVALIDE,
    LETTRE_TROUVEE,
    LETTRE_ABSENTE,
    LETTRE_MAJUSCULE,
    LETTRE_DEJA_PROPOSEE
};

enum Difficulte
{
    FACILE    = 8,
    NORMAL    = 6,
    DIFFICILE = 4
};

struct Theme
{
    char nom[MAX_LETTRES];
    char fichier[64];
};

struct Partie
{
    char motSecret[MAX_LETTRES];
    char motATrouver[MAX_LETTRES];
    int  erreurs;
    int  erreursMax;
    char lettresProposees[27];
    int  nbLettresProposees;
};

// Thèmes
extern Theme themesDisponibles[NB_THEMES];

void       initialiserPartie(Partie* partie, int erreursMax);
void       choisirMotSecret(Partie* partie, int themeIndex);
void       initialiserMotATrouver(Partie* partie);
void       mettreAJourMotATrouver(Partie* partie, char lettre);
bool       testerVictoire(Partie* partie);
bool       testerDefaite(Partie* partie);
EtatLettre verifierLettre(Partie* partie, char lettre);
bool       testerRejouerPartie(char reponse);
void       ajouterLettreProposee(Partie* partie, char lettre);
bool       lettreDejaProposee(Partie* partie, char lettre);

#endif // MODEL_H
