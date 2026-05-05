#include "model.h"
#include "view.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <ctime>

char mots[][MAX_LETTRES] = { "ordinateur", "clavier",       "linux", "processus", "python",
                             "windows",    "programmation", "java",  "souris" };

void initialiserPartie(Partie* partie)
{
    partie->erreurs    = 0;
    partie->erreursMax = NB_MAX_ERREURS;
    choisirMotSecret(partie);
    initialiserMotATrouver(partie);
}

void choisirMotSecret(Partie* partie)
{
    int nbMots = sizeof(mots) / sizeof(mots[0]);
    srand(time(NULL));
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

EtatLettre verifierLettre(Partie* partie, char lettre)
{
    if(!isalpha(lettre))
    {
        return LETTRE_INVALIDE;
    }
    if(isupper(lettre))
    {
        lettre = tolower(lettre);
    }

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
