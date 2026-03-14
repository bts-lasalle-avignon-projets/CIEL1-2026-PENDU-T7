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

char demanderLettre()
{
    char lettre;

    cout << "Propose une lettre : ";
    cin >> lettre;

    return lettre;
}
