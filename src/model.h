#ifndef MODEL_H
#define MODEL_H

#define VERSION            "2.0"
#define MAX_LETTRES        30
#define NB_MAX_ERREURS     8 // niveau facile
#define MAX_MOTS_THEME     100
#define NB_THEMES          4
#define MAX_FICHIER        64 // taille max du chemin de fichier d'un thème
#define NB_LETTRES_ALPHA   26 // nombre lettres alphabet
#define NB_ETAPES_PENDU    6  // nb étapes affichage pendu
#define ETAPE_TETE         1
#define ETAPE_TRONC        2
#define ETAPE_BRAS_GAUCHE  3
#define ETAPE_BRAS_DROIT   4
#define ETAPE_JAMBE_GAUCHE 5
#define ETAPE_JAMBE_DROITE NB_ETAPES_PENDU
#define NB_NIVEAUX         3 // nb niveaux difficulté

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
    char fichier[MAX_FICHIER];
};

struct Partie
{
    char motSecret[MAX_LETTRES];
    char motATrouver[MAX_LETTRES];
    int  erreurs;
    int  erreursMax;
    char lettresProposees[NB_LETTRES_ALPHA + 1];
    int  nbLettresProposees;
};

// thèmes
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
bool       devinerMot(Partie* partie, const char* mot);

#endif // MODEL_H
