#include "model.h"
#include "view.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
using namespace std;

char mots[][MAX_LETTRES] = {"ordinateur", "clavier", "linux", "processus", "python", "windows", "programmation", "java", "souris"};

void initialiserPartie(Partie *partie)
{
    partie->erreurs = 0;
    partie->erreursMax = NB_MAX_ERREURS;
    choisirMotSecret(partie);
    initialiserMotATrouver(partie);
}

void choisirMotSecret(Partie *partie)
{
    int indiceMotSecret;
    int nbMots = sizeof(mots) / sizeof(mots[0]); // Nombre de mots dans le tableau.
    srand(time(NULL));
    indiceMotSecret = rand() % nbMots;
    strcpy(partie->motSecret, mots[indiceMotSecret]);
}

void initialiserMotATrouver(Partie *partie)
{
    int longueurMot = strlen(partie->motSecret);
    for(int i = 0; i < longueurMot; i++)
    {
        partie->motATrouver[i] = '_';
    }
    partie->motATrouver[longueurMot] = '\0';
}

void mettreAJourMotATrouver(Partie *partie, char lettre)
{
    int longueurMot = strlen(partie->motSecret);
    for(int i = 0; i < longueurMot; i++)
    {
        if(partie->motSecret[i] == lettre)
        {
            partie->motATrouver[i] = lettre;
        }
    }
}

bool testerVictoire(Partie *partie)
{
    return strcmp(partie->motSecret, partie->motATrouver) == 0;
}

bool testerDefaite(Partie *partie)
{
    return partie->erreurs >= partie->erreursMax;
}

int verifierLettre(Partie *partie, char lettre)
{
    if(!isalpha(lettre))
    {
        return -1;
    }
    lettre = tolower(lettre);
    int longueurMot = strlen(partie->motSecret);
    for(int i = 0; i < longueurMot; i++)
    {
        if(partie->motSecret[i] == lettre)
        {
            return 1;
        }
    }
    return 0;
}
