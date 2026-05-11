#include "view.h"
#include "model.h"
#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

void afficherPendu(int erreurs, int erreursMax)
{
    int etape = (erreurs * NB_ETAPES_PENDU) / erreursMax;

    cout << "  +---+" << endl;
    cout << "  |   |" << endl;
    cout << "  |   " << (etape >= ETAPE_TETE ? "O" : " ") << endl;
    cout << "  |  " << (etape >= ETAPE_BRAS_GAUCHE ? "/" : " ")
         << (etape >= ETAPE_TRONC ? "|" : " ") << (etape >= ETAPE_BRAS_DROIT ? "\\" : " ") << endl;
    cout << "  |  " << (etape >= ETAPE_JAMBE_GAUCHE ? "/" : " ") << " "
         << (etape >= ETAPE_JAMBE_DROITE ? "\\" : " ") << endl;
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
    cout << "Entrer votre nom : ";
    cin >> nom;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        if(!(cin >> choix))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choix = 0;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
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
        cout << "Votre choix (1-" << NB_NIVEAUX << ") : ";
        if(!(cin >> choix))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choix = 0;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while(choix < 1 || choix > NB_NIVEAUX);

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

void demanderSaisie(char* buffer, int taille)
{
    bool saisieValide = false;
    do
    {
        cout << "Proposez une lettre ou le mot entier : ";
        cin.getline(buffer, taille);

        // Ignorer les lignes vides
        if(buffer[0] == '\0')
        {
            continue;
        }

        // Vérifier qu'il n'y a pas d'espace dans la saisie
        saisieValide = true;
        for(int i = 0; buffer[i] != '\0'; i++)
        {
            if(buffer[i] == ' ')
            {
                cout << "Lettre invalide ! Saisissez une lettre minuscule." << endl;
                saisieValide = false;
                break;
            }
        }
    } while(!saisieValide);
}

char demanderLettre()
{
    char lettre;
    cout << "Proposez une lettre : ";
    cin >> lettre;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return lettre;
}

void afficherVictoire(char* nom, int tentatives, char* motSecret)
{
    cout << "\033[32m"
         << "Bravo " << nom << ", vous avez gagné en " << tentatives << " tentative"
         << (tentatives > 1 ? "s" : "") << ". Le mot était bien " << motSecret << "."
         << "\033[0m" << endl;
}

void afficherDefaite(char* nom, char* motSecret)
{
    cout << "\033[31m"
         << "Dommage " << nom << ", vous avez perdu. Le mot était " << motSecret << "."
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

void afficherMauvaisMot()
{
    cout << "Mauvais mot !" << endl;
}

char rejouerPartie()
{
    char reponse;
    do
    {
        cout << "\nVoulez-vous rejouer ? (O/N) ";
        cin >> reponse;
    } while(reponse != 'O' && reponse != 'o' && reponse != 'N' && reponse != 'n');
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return reponse;
}
