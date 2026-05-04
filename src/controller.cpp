#include "controller.h"
#include "view.h"
#include "model.h"

void jouer()
{
    char nom[MAX_LETTRES];
    bool continuer = true;

    afficherTitre();
    demanderNomJoueur(nom);

    int themeIndex = choisirTheme();
    int erreursMax = choisirDifficulte();

    do
    {
        jouerPartie(nom, themeIndex, erreursMax);
        char rep  = rejouerPartie();
        continuer = testerRejouerPartie(rep);
        if(continuer)
        {
            // Permet de changer de thème et/ou de difficulté entre les parties
            themeIndex = choisirTheme();
            erreursMax = choisirDifficulte();
        }
    } while(continuer);
}

void jouerPartie(char* nom, int themeIndex, int erreursMax)
{
    Partie partie;
    initialiserPartie(&partie, erreursMax);
    choisirMotSecret(&partie, themeIndex);
    initialiserMotATrouver(&partie);

    while(!testerVictoire(&partie) && !testerDefaite(&partie))
    {
        afficherPendu(partie.erreurs, partie.erreursMax);
        afficherMotATrouver(partie.motATrouver);
        afficherLettresProposees(&partie);
        afficherErreurs(partie.erreurs, partie.erreursMax);
        mettreAJourJeu(&partie);
    }

    afficherPendu(partie.erreurs, partie.erreursMax);
    gererResultatPartie(&partie, nom);
}

void mettreAJourJeu(Partie* partie)
{
    char       lettre   = demanderLettre();
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

void gererResultatPartie(Partie* partie, char* nom)
{
    if(testerVictoire(partie))
    {
        afficherVictoire(nom, partie->erreurs, partie->motSecret);
    }
    else
    {
        afficherDefaite(nom, partie->motSecret);
    }
}
