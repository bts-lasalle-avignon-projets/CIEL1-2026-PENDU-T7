#include "view.h"
#include "model.h"
#include <iostream>
#include <cstring>
using namespace std;

void afficherPendu(int erreurs, int erreursMax)
{
    int etape = (erreurs * 6) / erreursMax;

    cout << "  +---+" << endl;
    cout << "  |   |" << endl;
    cout << "  |   " << (etape >= 1 ? "O" : " ") << endl;
    cout << "  |  " << (etape >= 3 ? "/" : " ") << (etape >= 2 ? "|" : " ")
         << (etape >= 4 ? "\\" : " ") << endl;
    cout << "  |  " << (etape >= 5 ? "/" : " ") << " " << (etape >= 6 ? "\\" : " ") << endl;
    cout << "  |" << endl;
    cout << "=========" << endl;
}

void afficherTitre()
{
    cout << "==================" << endl;
    cout << "   Pendu v" << VERSION << endl;
    cout << "==================" << endl;
}

void demanderNomJoueur(char* nom)
{
    cout << "Entrez votre nom : ";
    cin >> nom;
}

int choisirTheme()
{
    cout << "\n-- Choisissez un theme --" << endl;
    for(int i = 0; i < NB_THEMES; i++)
    {
        cout << "  " << (i + 1) << ". " << themesDisponibles[i].nom << endl;
    }
    int choix = 0;
    do
    {
        cout << "Votre choix (1-" << NB_THEMES << ") : ";
        cin >> choix;
    } while(choix < 1 || choix > NB_THEMES);
    return choix - 1;
}

int choisirDifficulte()
{
    cout << "\n-- Choisissez un niveau de difficulté --" << endl;
    cout << "  1. Facile   (" << (int)FACILE << " erreurs max)" << endl;
    cout << "  2. Normal   (" << (int)NORMAL << " erreurs max)" << endl;
    cout << "  3. Difficile(" << (int)DIFFICILE << " erreurs max)" << endl;
    int choix = 0;
    do
    {
        cout << "Votre choix (1-3) : ";
        cin >> choix;
    } while(choix < 1 || choix > 3);

    switch(choix)
    {
        case 1:
            return (int)FACILE;
        case 2:
            return (int)NORMAL;
        default:
            return (int)DIFFICILE;
    }
}

void afficherMotATrouver(char* motATrouver)
{
    cout << "\nMot à trouver : ";
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

void afficherLettresProposees(Partie* partie)
{
    if(partie->nbLettresProposees == 0)
    {
        cout << "Lettres proposées : (aucune)" << endl;
        return;
    }
    cout << "Lettres proposées : ";
    for(int i = 0; i < partie->nbLettresProposees; i++)
    {
        char l         = partie->lettresProposees[i];
        bool dansLeMot = false;
        for(int j = 0; partie->motATrouver[j] != '\0'; j++)
        {
            if(partie->motATrouver[j] == l)
            {
                dansLeMot = true;
                break;
            }
        }
        if(dansLeMot)
        {
            cout << "\033[32m" << l << "\033[0m "; // vert
        }
        else
        {
            cout << "\033[31m" << l << "\033[0m "; // rouge
        }
    }
    cout << endl;
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
    cout << "\033[32m" // vert
         << "Bravo " << nom << " ! Vous avez gagné en " << tentatives
         << " erreur(s). Le mot était : " << motSecret << "."
         << "\033[0m" << endl;
}

void afficherDefaite(char* nom, char* motSecret)
{
    cout << "\033[31m" // rouge
         << "Dommage " << nom << ", vous avez perdu. Le mot était : " << motSecret << "."
         << "\033[0m" << endl;
}

void afficherLettreIncorrecte()
{
    cout << "Lettre invalide ! Saisissez une lettre minuscule." << endl;
}

void afficherLettreDejaProposee()
{
    cout << "Vous avez déjà proposé cette lettre !" << endl;
}

char rejouerPartie()
{
    char reponse;
    cout << "\nVoulez-vous rejouer ? (O/N) ";
    cin >> reponse;
    return reponse;
}
