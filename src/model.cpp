#include "model.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

char mots[][MAX_LETTRES] = {"ordinateur", "clavier", "linux", "processus", "python", "windows", "programmation", "java", "souris"};

void choisirMotSecret(Partie *partie)
{
    int indiceMotSecret;
    int nbMots = sizeof(mots) / sizeof(mots[0]); //Nombre de mots dans le tableau.
    srand(time(NULL));
    indiceMotSecret = rand() % nbMots;
    strcpy(partie->motSecret, mots[indiceMotSecret]);
}
