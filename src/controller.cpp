#include "controller.h"
#include "view.h"
#include "model.h"

void jouer()
{
    char nom[MAX_LETTRES];
    bool continuer = true;

    afficherTitre();
    demanderNomJoueur(nom);

    do
    {
        jouerPartie(nom);
        continuer = testerRejouerPartie(rejouerPartie());
    } while(continuer);
}

void jouerPartie(char* nom)
{
    Partie partie;
    initialiserPartie(&partie);
    while(!testerVictoire(&partie) && !testerDefaite(&partie))
    {
        afficherMotATrouver(partie.motATrouver);
        afficherErreurs(partie.erreurs, partie.erreursMax);
        mettreAJourJeu(&partie);
    }
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
