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

void afficherMotATrouver(char *motATrouver);
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

char demanderLettre()
{
    char lettre;

    cout << "Propose une lettre : ";
    cin >> lettre;

    return lettre;
}
