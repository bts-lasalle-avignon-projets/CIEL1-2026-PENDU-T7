#include "controller.h"
#include "view.h"
#include "model.h"
#ifdef DEBUG_CONTROLLER
#include <iostream>
#endif

void jouer()
{
    char nom[MAX_LETTRES];
    afficherTitre();
    demanderNomJoueur(nom);
    jouerPartie(nom);
}

void jouerPartie(char *nom)
{
    Partie partie;
    initialiserPartie(&partie);
    while(!testerVictoire(&partie) && !testerDefaite(&partie))
    {
        afficherMotATrouver(partie.motATrouver);
        afficherErreurs(partie.erreurs, partie.erreursMax);
        mettreAJourJeu(&partie);
    }
    afficherResultatPartie(&partie, nom);
}

void mettreAJourJeu(Partie *partie)
{
    char lettre = demanderLettre();
    int resultatTestLettre = verifierLettre(partie, lettre);
    if(resultatTestLettre == 1)
    {
        mettreAJourMotATrouver(partie, lettre);
    }
    else if(resultatTestLettre == -1)
    {
        afficherLettreIncorrecte();
    }
    else
    {
        partie->erreurs++;
    }
}

void afficherResultatPartie(Partie *partie, char *nom)
{
    if(testerVictoire(partie))
    {
        afficherVictoire(nom, partie->erreurs, partie->erreursMax);
    }
    else
    {
        afficherDefaite(nom, partie->motSecret);
    }
}
