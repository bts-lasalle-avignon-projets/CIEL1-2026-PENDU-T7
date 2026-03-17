#include "view.h"
#include <iostream>
using namespace std;

void afficherTitre()
{
    cout << "================" << endl;
    cout << "   Pendu v1.0   " << endl;
    cout << "================" << endl;
}

void demanderNomJoueur(char *nom)
{
    cout << "Entrer votre nom : ";
    cin >> nom;
}

void afficherMotATrouver(char *motATrouver)
{
    int i = 0;
    cout << "Mot à trouver : ";
    while(motATrouver[i] != '\0')
    {
        cout << motATrouver[i] << " ";
        i++;
    }
    cout << endl;
}

void afficherErreurs(int erreurs, int erreursMax)
{
    cout << "Erreurs : " << erreurs << "/" << erreursMax << endl;
}

char demanderLettre()
{
    char lettre;

    cout << "Propose une lettre : ";
    cin >> lettre;

    return lettre;
}

void afficherVictoire(char *nom, int erreurs, int erreursMax)
{
    cout << "Bravo " << nom << ", vous avez gagner avec " << erreurs << " / " << erreursMax << " erreurs!" << endl;
}

void afficherDefaite(char *nom, char *motSecret)
{
    cout << "Dommage " << nom << ", vous avez perdu, le mot était " << motSecret << "." << endl;
}

void afficherLettreIncorrecte()
{
    cout << "Lettre invalide!" << endl;
}

