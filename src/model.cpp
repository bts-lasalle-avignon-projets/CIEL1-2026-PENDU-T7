#include "model.h"
#include "view.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <ctime>

Theme themesDisponibles[NB_THEMES] = { { "Informatique", "themes/informatique.txt" },
                                       { "Animaux", "themes/animaux.txt" },
                                       { "Pays", "themes/pays.txt" },
                                       { "Sports", "themes/sports.txt" } };

static int chargerMots(const char* fichier, char mots[][MAX_LETTRES], int maxMots)
{
    FILE* f = fopen(fichier, "r");
    if(!f)
    {
        return 0;
    }
    int n = 0;
    while(n < maxMots && fgets(mots[n], MAX_LETTRES, f))
    {
        int len = strlen(mots[n]);
        if(len > 0 && mots[n][len - 1] == '\n')
        {
            mots[n][len - 1] = '\0';
        }
        if(strlen(mots[n]) > 0)
        {
            n++;
        }
    }
    fclose(f);
    return n;
}

void initialiserPartie(Partie* partie, int erreursMax)
{
    partie->erreurs            = 0;
    partie->erreursMax         = erreursMax;
    partie->nbLettresProposees = 0;
    memset(partie->lettresProposees, 0, sizeof(partie->lettresProposees));
}

void choisirMotSecret(Partie* partie, int themeIndex)
{
    char mots[MAX_MOTS_THEME][MAX_LETTRES];
    int  nbMots = chargerMots(themesDisponibles[themeIndex].fichier, mots, MAX_MOTS_THEME);

    if(nbMots == 0)
    {
        strcpy(partie->motSecret, "PENDU");
        return;
    }

    srand((unsigned int)time(NULL));
    strcpy(partie->motSecret, mots[rand() % nbMots]);

    for(int i = 0; partie->motSecret[i] != '\0'; i++)
    {
        partie->motSecret[i] = toupper(partie->motSecret[i]);
    }
}

void initialiserMotATrouver(Partie* partie)
{
    int longueur = strlen(partie->motSecret);
    for(int i = 0; i < longueur; i++)
    {
        // Dévoile première + dernière lettre
        if(i == 0 || i == longueur - 1)
        {
            partie->motATrouver[i] = partie->motSecret[i];
        }
        else
        {
            partie->motATrouver[i] = '_';
        }
    }
    partie->motATrouver[longueur] = '\0';
}

void mettreAJourMotATrouver(Partie* partie, char lettre)
{
    lettre = toupper(lettre);
    for(int i = 0; partie->motSecret[i] != '\0'; i++)
    {
        if(partie->motSecret[i] == lettre)
        {
            partie->motATrouver[i] = lettre;
        }
    }
}

bool testerVictoire(Partie* partie)
{
    return strcmp(partie->motSecret, partie->motATrouver) == 0;
}

bool testerDefaite(Partie* partie)
{
    return partie->erreurs >= partie->erreursMax;
}

bool lettreDejaProposee(Partie* partie, char lettre)
{
    for(int i = 0; i < partie->nbLettresProposees; i++)
    {
        if(partie->lettresProposees[i] == lettre)
        {
            return true;
        }
    }
    return false;
}

void ajouterLettreProposee(Partie* partie, char lettre)
{
    if(partie->nbLettresProposees < NB_LETTRES_ALPHA)
    {
        partie->lettresProposees[partie->nbLettresProposees++] = lettre;
        partie->lettresProposees[partie->nbLettresProposees]   = '\0';
    }
}

EtatLettre verifierLettre(Partie* partie, char lettre)
{
    if(!isalpha(lettre))
    {
        return LETTRE_INVALIDE;
    }

    lettre = toupper(lettre);

    if(lettreDejaProposee(partie, lettre))
    {
        return LETTRE_DEJA_PROPOSEE;
    }

    ajouterLettreProposee(partie, lettre);

    int longueurMot = strlen(partie->motSecret);
    for(int i = 0; i < longueurMot; i++)
    {
        if(partie->motSecret[i] == lettre)
        {
            return LETTRE_TROUVEE;
        }
    }
    return LETTRE_ABSENTE;
}

bool testerRejouerPartie(char reponse)
{
    return (reponse == 'o' || reponse == 'O');
}

void ajouterTentative(Partie* partie)
{
    partie->nbLettresProposees++;
}

bool devinerMot(Partie* partie, const char* mot)
{
    char motMaj[MAX_LETTRES];
    strncpy(motMaj, mot, MAX_LETTRES - 1);
    motMaj[MAX_LETTRES - 1] = '\0';
    for(int i = 0; motMaj[i] != '\0'; i++)
    {
        motMaj[i] = toupper(motMaj[i]);
    }

    if(strcmp(partie->motSecret, motMaj) == 0)
    {
        strcpy(partie->motATrouver, partie->motSecret);
        return true;
    }
    return false;
}

int chargerScores(Score scores[], int maxScores)
{
    FILE* f = fopen(FICHIER_SCORES, "r");
    if(!f)
    {
        return 0;
    }
    int n = 0;
    while(n < maxScores && fscanf(f,
                                  "%29s %29s %d %d %d %29s %d",
                                  scores[n].nom,
                                  scores[n].mot,
                                  &scores[n].erreurs,
                                  &scores[n].tentatives,
                                  &scores[n].temps,
                                  scores[n].theme,
                                  &scores[n].difficulte) == 7)
        n++;
    fclose(f);
    return n;
}

void trierScores(Score scores[], int nbScores)
{
    // Tri par erreurs croissant, puis temps croissant
    for(int i = 0; i < nbScores - 1; i++)
    {
        for(int j = i + 1; j < nbScores; j++)
        {
            if(scores[j].erreurs < scores[i].erreurs ||
               (scores[j].erreurs == scores[i].erreurs && scores[j].temps < scores[i].temps))
            {
                Score tmp = scores[i];
                scores[i] = scores[j];
                scores[j] = tmp;
            }
        }
    }
}

void sauvegarderScore(Score* score)
{
    Score scores[TOP_SCORES];
    int   nbScores = chargerScores(scores, TOP_SCORES);

    if(nbScores < TOP_SCORES)
    {
        scores[nbScores++] = *score;
    }
    else
    {
        // Remplacer le pire score si le nouveau est meilleur
        int pire = 0;
        for(int i = 1; i < nbScores; i++)
        {
            if(scores[i].erreurs > scores[pire].erreurs ||
               (scores[i].erreurs == scores[pire].erreurs && scores[i].temps > scores[pire].temps))
            {
                pire = i;
            }
        }
        if(score->erreurs < scores[pire].erreurs ||
           (score->erreurs == scores[pire].erreurs && score->temps < scores[pire].temps))
        {
            scores[pire] = *score;
        }
        else
        {
            return;
        }
    }

    trierScores(scores, nbScores);

    FILE* f = fopen(FICHIER_SCORES, "w");
    if(!f)
    {
        return;
    }
    for(int i = 0; i < nbScores; i++)
    {
        fprintf(f,
                "%s %s %d %d %d %s %d\n",
                scores[i].nom,
                scores[i].mot,
                scores[i].erreurs,
                scores[i].tentatives,
                scores[i].temps,
                scores[i].theme,
                scores[i].difficulte);
    }
    fclose(f);
}
