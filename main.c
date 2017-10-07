/*
main.c
------------

Par (nom de l'auteur du programme)
Date de création :  29/09/2017
Date de la dernière modification : 29/09/2017

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
 
#define TAILLE_MAX 100
 
char lireCaractere();
 
int main(int argc, char* argv[])
{
    int continuerPartie = 1;
 
    while (continuerPartie != 0)       // On propose de rejouer une partie tant que le joueur n'a pas dit non.
    {
        char lettre = 0, motSecret[TAILLE_MAX] = {0}, *progressionMot = NULL, *verificationLettre = NULL, *verificationMot = 1;
        int i, nombreDeCoups = 10, longueurMot = 0;
 
        motAleatoire (motSecret);
 
        longueurMot = strlen(motSecret) + 1;
 
        progressionMot = malloc(longueurMot * sizeof(char)); // On alloue de la mémoire pour le tableau de la progression du joueur sur le mot
 
        for (i = 0; i < longueurMot - 1; i++)
        {
            progressionMot[i] = '*';
        }
        progressionMot[longueurMot-1] = '\0';
 
        printf("Bienvenue dans le Pendu !\n");
 
 
        while (nombreDeCoups > 0 && verificationMot != 0)
        {
            do
            {
                printf("\nIl vous reste %d coups a jouer\n", nombreDeCoups);
                printf("Quel est le mot secret ? ");
                for (i = 0; i < longueurMot; i++)
                {
                    printf("%c", progressionMot[i]);
                }
                printf("\nProposez un lettre : ");
                lettre = lireCaractere();
                verificationLettre = strchr(motSecret, lettre);
 
                for (i = 0; i < longueurMot; i++)
                {
                    if (lettre == motSecret[i])
                    {
                        progressionMot[i] = motSecret[i];
                    }
                }
                verificationMot = strcmp(motSecret, progressionMot);
                if (verificationMot == 0)
                {
                    break;
                }
            } while (verificationLettre != NULL);
            if (verificationMot != 0)
            {
                nombreDeCoups--;
            }
        }
        if (nombreDeCoups == 0)
        {
            printf("\n\nPerdu ! Le mot secret etait : %s", motSecret);
        }
        else
        {
            printf("\n\nGagne ! Le mot secret etait bien : %s", motSecret);
        }
 
        free(progressionMot);   // Libération de la mémoire allouée avec malloc
 
        printf ("\n\nVoulez vous refaire une partie ?\n0. Non\n1. Oui\n");
        scanf("%d", &continuerPartie);
 
    }
 
    return 0;
}
 
char lireCaractere()
{
    char caractere = 0;
 
    caractere = getchar();  // On lit le premier caractère
    caractere = toupper(caractere); // On met la lettre en majuscule si elle ne l'est pas déjà
 
    // On lit les autres caractères un à un jusqu'au \n (pour les effacer)
    while (getchar() != '\n') ;
 
    return caractere;    // On retourne le premier caractère qu'on a lu
}
 
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
