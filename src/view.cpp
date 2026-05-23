#include "view.h"
#include "model.h"
#include <iostream>
#include <cstring>
#include <cstdio>
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

void afficherMenu()
{
    cout << "\n-- Menu principal --" << endl;
    cout << "  " << MENU_JOUER << ". Jouer" << endl;
    cout << "  " << MENU_REGLES << ". Règles du jeu" << endl;
    cout << "  " << MENU_QUITTER << ". Quitter" << endl;
}

int choisirMenu()
{
    int choix = 0;
    do
    {
        cout << "Votre choix (1-" << NB_CHOIX_MENU << ") : ";
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
    } while(choix < MENU_JOUER || choix > MENU_QUITTER);
    return choix;
}

void afficherRegles()
{
    cout << "\n========== Règles du jeu ==========" << endl;
    cout << "Le but est de deviner un mot secret lettre par lettre." << endl;
    cout << "- La première et la dernière lettre du mot sont révélées." << endl;
    cout << "- Proposez une lettre ou le mot entier à chaque tour." << endl;
    cout << "- Une lettre absente du mot coûte une erreur." << endl;
    cout << "- Un mot entier incorrect coûte aussi une erreur." << endl;
    cout << "- Les lettres correctes s'affichent en vert," << endl;
    cout << "  les lettres incorrectes en rouge." << endl;
    cout << "- La partie est perdue si vous atteignez le nombre" << endl;
    cout << "  maximum d'erreurs selon la difficulté choisie :" << endl;
    cout << "    Facile    : " << (int)FACILE << " erreurs max" << endl;
    cout << "    Normal    : " << (int)NORMAL << " erreurs max" << endl;
    cout << "    Difficile : " << (int)DIFFICILE << " erreurs max" << endl;
    cout << "====================================" << endl;
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

void afficherTemps(int secondes)
{
    int minutes = secondes / 60;
    int secs    = secondes % 60;
    if(minutes > 0)
    {
        cout << "Temps : " << minutes << " min " << secs << " sec" << endl;
    }
    else
    {
        cout << "Temps : " << secs << " sec" << endl;
    }
}

void afficherVictoire(char* nom, int tentatives, char* motSecret, int secondes)
{
    cout << "\033[32m"
         << "Bravo " << nom << ", vous avez gagné en " << tentatives << " tentative"
         << (tentatives > 1 ? "s" : "") << ". Le mot était bien " << motSecret << "."
         << "\033[0m" << endl;
    afficherTemps(secondes);
}

void afficherScores(Score scores[], int nbScores)
{
    cout << "\n===== Meilleurs scores =====" << endl;
    if(nbScores == 0)
    {
        cout << "Aucun score enregistré." << endl;
    }
    else
    {
        cout << "  #  Nom            Mot            Erreurs  Tentatives  Temps   Thème         "
                "Difficulté"
             << endl;
        cout << "  -- -------------- -------------- -------- ----------- ------- ------------- "
                "----------"
             << endl;
        for(int i = 0; i < nbScores; i++)
        {
            int  minutes = scores[i].temps / 60;
            int  secs    = scores[i].temps % 60;
            char temps[16];
            if(minutes > 0)
            {
                sprintf(temps, "%dm%02ds", minutes, secs);
            }
            else
            {
                sprintf(temps, "%ds", secs);
            }
            printf("  %-2d %-14s %-14s %-8d %-11d %-7s %-13s %d erreurs max\n",
                   i + 1,
                   scores[i].nom,
                   scores[i].mot,
                   scores[i].erreurs,
                   scores[i].tentatives,
                   temps,
                   scores[i].theme,
                   scores[i].difficulte);
        }
    }
    cout << "============================" << endl;
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
