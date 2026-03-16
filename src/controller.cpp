#include "controller.h"
#include "view.h"
#ifdef DEBUG_CONTROLLER
#include <iostream>

void demarrerJeu()
{
    char nom[MAX_LETTRES];
    afficherTitre();
    demanderNomJoueur(nom);
    jouer(nom);
}

void jouer(char *nom)
{
    Partie partie;
    initialiserPartie(&partie);
    while(!testerVictoire(&partie) && !testerDefaite(&partie))
    {
        afficherMotATrouver(partie.motATrouver);
        afficherErreurs(partie.erreurs, partie.erreursMax);
        char lettre = demanderLettre();
        int resultatTestLettre = verifierLettre(&partie, lettre); // 1 si dans mot, 0 si pas dans le mot, -1 si pas une lettre
        if(resultatTestLettre == 1)
        {
            mettreAJourMotATrouver(&partie, lettre);
        }
        else if(resultatTestLettre == -1)
        {
            afficherLettreIncorrecte();
        }
        else
        {
            partie.erreurs++;
        }
    }
    if(testerVictoire(&partie))
    {
        afficherVictoire(nom, partie.erreurs, partie.erreursMax);
    }
    else
    {
        afficherDefaite(nom, partie.motSecret);
    }
}

#endif
