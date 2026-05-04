#include "view.h"
#include "model.h"
#include <iostream>
using namespace std;

void afficherTitre()
{
    cout << "================" << endl;
    cout << "   Pendu v" << VERSION << endl;
    cout << "================" << endl;
}

void demanderNomJoueur(char* nom)
{
    cout << "Entrer votre nom : ";
    cin >> nom;
}

void afficherMotATrouver(char* motATrouver)
{
    cout << "Mot à trouver : ";
    for(int i = 0; motATrouver[i] != '\0'; i++)
    {
        cout << motATrouver[i] << " ";
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
    cout << "Proposez une lettre : ";
    cin >> lettre;
    return lettre;
}

void afficherVictoire(char* nom, int tentatives, char* motSecret)
{
    cout << "Bravo " << nom << ", vous avez gagné en " << tentatives
         << " tentatives. Le mot était bien " << motSecret << "." << endl;
}

void afficherDefaite(char* nom, char* motSecret)
{
    cout << "Dommage " << nom << ", vous avez perdu. Le mot était " << motSecret << "." << endl;
}

void afficherLettreIncorrecte()
{
    cout << "Lettre invalide !" << endl;
}

char rejouerPartie()
{
    char reponse;
    do
    {
        cout << "Voulez-vous rejouer ? (O/N) ";
        cin >> reponse;
    } while(reponse != 'O' && reponse != 'o' && reponse != 'N' && reponse != 'n');
    return reponse;
}
