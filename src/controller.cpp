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
    char reponse = rejouerPartieReponse();
    bool rejouer = testerRejouerPartie(reponse);
    while(rejouer)
    {
        jouerPartie(nom);
        char reponse = rejouerPartieReponse();
        rejouer = testerRejouerPartie(reponse);
    }
}

void jouerPartie(char *nom)
{
    Partie partie;
    initialiserPartie(&partie);
    while(!testerVictoire(&partie) && !testerDefaite(&partie))
    {
        afficherMotATrouver(partie.motATrouver);
        afficherErreurs(partie.erreurs, partie.erreursMax);
        char lettre = demanderLettre();
        int  resultatTestLettre =
          verifierLettre(&partie, lettre); // 1 si dans mot, 0 si pas dans le mot, -1 si pas une lettre
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
    afficherResultatPartie(&partie, nom);
}
