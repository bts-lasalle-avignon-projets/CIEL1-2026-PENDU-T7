#ifndef MODEL_H
#define MODEL_H

#define MAX_LETTRES 15

struct Partie
{
    char motSecret[MAX_LETTRES];
    char motATrouver[MAX_LETTRES];
    int erreurs;
    int erreursMax;
};

void choisirMotSecret(Partie *partie);

#endif // MODEL_H
