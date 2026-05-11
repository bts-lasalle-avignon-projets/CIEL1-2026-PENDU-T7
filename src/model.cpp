#include "model.h"
#include "view.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <ctime>

Theme themesDisponibles[NB_THEMES] = { { "Informatique", "themes/informatique.txt" },
                                       { "Animaux", "themes/animaux.txt" },
                                       { "Pays", "themes/pays.txt" },
                                       { "Sports", "themes/sports.txt" } };

static int chargerMots(const char* fichier, char mots[][MAX_LETTRES], int maxMots)
{
    FILE* f = fopen(fichier, "r");
    if(!f)
    {
        return 0;
    }
    int n = 0;
    while(n < maxMots && fgets(mots[n], MAX_LETTRES, f))
    {
        int len = strlen(mots[n]);
        if(len > 0 && mots[n][len - 1] == '\n')
        {
            mots[n][len - 1] = '\0';
        }
        if(strlen(mots[n]) > 0)
        {
            n++;
        }
    }
    fclose(f);
    return n;
}

void initialiserPartie(Partie* partie, int erreursMax)
{
    partie->erreurs            = 0;
    partie->erreursMax         = erreursMax;
    partie->nbLettresProposees = 0;
    memset(partie->lettresProposees, 0, sizeof(partie->lettresProposees));
}

void choisirMotSecret(Partie* partie, int themeIndex)
{
    char mots[MAX_MOTS_THEME][MAX_LETTRES];
    int  nbMots = chargerMots(themesDisponibles[themeIndex].fichier, mots, MAX_MOTS_THEME);

    if(nbMots == 0)
    {
        strcpy(partie->motSecret, "pendu");
        return;
    }

    srand((unsigned int)time(NULL));
    strcpy(partie->motSecret, mots[rand() % nbMots]);
}

void initialiserMotATrouver(Partie* partie)
{
    int longueur = strlen(partie->motSecret);
    for(int i = 0; i < longueur; i++)
    {
        // Dévoile première + dernière lettre
        if(i == 0 || i == longueur - 1)
        {
            partie->motATrouver[i] = partie->motSecret[i];
        }
        else
        {
            partie->motATrouver[i] = '_';
        }
    }
    partie->motATrouver[longueur] = '\0';
}

void mettreAJourMotATrouver(Partie* partie, char lettre)
{
    for(int i = 0; partie->motSecret[i] != '\0'; i++)
    {
        if(partie->motSecret[i] == lettre)
        {
            partie->motATrouver[i] = lettre;
        }
    }
}

bool testerVictoire(Partie* partie)
{
    return strcmp(partie->motSecret, partie->motATrouver) == 0;
}

bool testerDefaite(Partie* partie)
{
    return partie->erreurs >= partie->erreursMax;
}

bool lettreDejaProposee(Partie* partie, char lettre)
{
    for(int i = 0; i < partie->nbLettresProposees; i++)
    {
        if(partie->lettresProposees[i] == lettre)
        {
            return true;
        }
    }
    return false;
}

void ajouterLettreProposee(Partie* partie, char lettre)
{
    if(partie->nbLettresProposees < NB_LETTRES_ALPHA)
    {
        partie->lettresProposees[partie->nbLettresProposees++] = lettre;
        partie->lettresProposees[partie->nbLettresProposees]   = '\0';
    }
}

EtatLettre verifierLettre(Partie* partie, char lettre)
{
    if(!isalpha(lettre))
    {
        return LETTRE_INVALIDE;
    }

    if(isupper(lettre))
    {
        return LETTRE_MAJUSCULE;
    }

    if(lettreDejaProposee(partie, lettre))
    {
        return LETTRE_DEJA_PROPOSEE;
    }

    ajouterLettreProposee(partie, lettre);

    int longueurMot = strlen(partie->motSecret);
    for(int i = 0; i < longueurMot; i++)
    {
        if(partie->motSecret[i] == lettre)
        {
            return LETTRE_TROUVEE;
        }
    }
    return LETTRE_ABSENTE;
}

bool testerRejouerPartie(char reponse)
{
    return (reponse == 'o' || reponse == 'O');
}

void ajouterTentative(Partie* partie)
{
    partie->nbLettresProposees++;
}

bool devinerMot(Partie* partie, const char* mot)
{
    if(strcmp(partie->motSecret, mot) == 0)
    {
        strcpy(partie->motATrouver, partie->motSecret);
        return true;
    }
    return false;
}
