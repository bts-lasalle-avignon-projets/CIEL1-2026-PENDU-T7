#include "controller.h"
#include "view.h"
#include "model.h"
#include <cctype>
#include <cstring>
#include <ctime>
using namespace std;

void jouer()
{
    afficherTitre();
    gererMenu();
}

void gererMenu()
{
    int choix;
    do
    {
        afficherMenu();
        choix = choisirMenu();

        switch(choix)
        {
            case MENU_JOUER:
            {
                char nom[MAX_NOM_JOUEUR];
                demanderNomJoueur(nom);
                int  themeIndex = choisirTheme();
                int  erreursMax = choisirDifficulte();
                bool continuer  = true;
                do
                {
                    jouerPartie(nom, themeIndex, erreursMax);
                    continuer = testerRejouerPartie(rejouerPartie());
                    if(continuer)
                    {
                        themeIndex = choisirTheme();
                        erreursMax = choisirDifficulte();
                    }
                } while(continuer);

                // Afficher les meilleurs scores après la session
                Score scores[TOP_SCORES];
                int   nbScores = chargerScores(scores, TOP_SCORES);
                afficherScores(scores, nbScores);
                break;
            }
            case MENU_REGLES:
                afficherRegles();
                break;
            case MENU_QUITTER:
                break;
        }
    } while(choix != MENU_QUITTER);
}

void jouerPartie(char* nom, int themeIndex, int erreursMax)
{
    Partie partie;
    initialiserPartie(&partie, erreursMax);
    choisirMotSecret(&partie, themeIndex);
    initialiserMotATrouver(&partie);

    time_t debut = time(NULL);

    while(!testerVictoire(&partie) && !testerDefaite(&partie))
    {
        afficherPendu(partie.erreurs, partie.erreursMax);
        afficherMotATrouver(partie.motATrouver);
        afficherLettresProposees(&partie);
        afficherErreurs(partie.erreurs, partie.erreursMax);
        mettreAJourJeu(&partie);
    }

    int secondes = (int)(time(NULL) - debut);

    afficherPendu(partie.erreurs, partie.erreursMax);
    gererResultatPartie(&partie, nom, themeIndex, secondes);
}

void mettreAJourJeu(Partie* partie)
{
    char saisie[MAX_LETTRES];
    demanderSaisie(saisie, MAX_LETTRES);

    // Si saisie > 1 char, c'est une tentative de mot
    if(strlen(saisie) > 1)
    {
        ajouterTentative(partie);
        if(!devinerMot(partie, saisie))
        {
            partie->erreurs++;
            afficherMauvaisMot();
        }
        return;
    }

    // Sinon traitement normal d'une lettre
    char       lettre   = saisie[0];
    EtatLettre resultat = verifierLettre(partie, lettre);

    switch(resultat)
    {
        case LETTRE_TROUVEE:
            mettreAJourMotATrouver(partie, lettre);
            break;
        case LETTRE_ABSENTE:
            partie->erreurs++;
            break;
        case LETTRE_DEJA_PROPOSEE:
            afficherLettreDejaProposee();
            break;
        case LETTRE_MAJUSCULE:
            break;
        case LETTRE_INVALIDE:
        default:
            afficherLettreIncorrecte();
            break;
    }
}

void gererResultatPartie(Partie* partie, char* nom, int themeIndex, int secondes)
{
    if(testerVictoire(partie))
    {
        afficherVictoire(nom, partie->nbLettresProposees, partie->motSecret, secondes);

        Score score;
        strncpy(score.nom, nom, MAX_NOM_JOUEUR - 1);
        strncpy(score.mot, partie->motSecret, MAX_LETTRES - 1);
        strncpy(score.theme, themesDisponibles[themeIndex].nom, MAX_LETTRES - 1);
        score.nom[MAX_NOM_JOUEUR - 1] = '\0';
        score.mot[MAX_LETTRES - 1]    = '\0';
        score.theme[MAX_LETTRES - 1]  = '\0';
        score.erreurs                 = partie->erreurs;
        score.tentatives              = partie->nbLettresProposees;
        score.temps                   = secondes;
        score.difficulte              = partie->erreursMax;
        sauvegarderScore(&score);
    }
    else
    {
        afficherDefaite(nom, partie->motSecret);
    }
}
