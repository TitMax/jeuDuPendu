/*
dico.c
------------
Par (nom de l'auteur du programme)
Date de création :  30/09/2017
Date de la dernière modification : 30/09/2017
Rôle : Fonction pour trouver un mot aléatoire dans le dico
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dico.h"

#define TAILLE_MAX 100

int motAleatoire (char *motSecret)
{
    int i = 0, nombreDeMots = 0, roulette = 0, caractereActuel = 0;

    FILE* dico = NULL;

    dico = fopen("dico.txt", "r");

    if (dico != NULL)
    {
        // On compte le nombre de mots présent dans le fichier
        do
        {
            caractereActuel = fgetc(dico);
            if (caractereActuel == '\n')
            nombreDeMots++;
        } while (caractereActuel != EOF);

        // On génère un nombre aléatoire
        srand(time(NULL));
        roulette = rand() % nombreDeMots;

        rewind(dico);   // On retourne au début du fichier

        while (i < roulette)
        {
            caractereActuel = fgetc(dico);
            if (caractereActuel == '\n')
            {
                i++;
            }
        }
        fgets (motSecret, TAILLE_MAX, dico);

        motSecret[strlen(motSecret) - 1] = '\0';

        fclose(dico);
        return 1;
    }
    else
    {
        printf("Impossible de continuer, dictionnaire inexistant.\n");
        exit(0);
    }
}