#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <synchapi.h>
#include "header.h"

int random_commencer(int nbr)
{
    int random = 0;
    random = rand()%nbr+1;
    return random;
}

void tour(t_joueur** tabjoueur, int nbrjoueur, int random, int compteur)
{
    if(compteur == nbrjoueur-1)
    {
        for(int i=0; i<nbrjoueur; i++)
        {
            if(tabjoueur[i]->perdu != 1)
            {
                printf("joueur %d :%s, vous avez gagner !\n", tabjoueur[i]->classes.ID, tabjoueur[i]->classes.nom);
            }
        }
    }
    else if(tabjoueur[random-1]->perdu != 1)
    {
        int entier;
        deplacement(tabjoueur, random-1,nbrjoueur);
        printf("joueur %d : %s a vous de jouer(saisir un entier)\n", tabjoueur[random-1]->classes.ID, tabjoueur[random-1]->classes.nom);
        //scanf("%d", &entier);
        if(entier == 2)
        {
            tabjoueur[random-1]->perdu = 1;
            compteur++;
        }
        if(entier == 3)
        {
            menu_pause(tabjoueur, nbrjoueur);
        }
        if(random == nbrjoueur)
        {
            tour(tabjoueur, nbrjoueur, 1, compteur);
        }
        else
        {
            tour(tabjoueur, nbrjoueur, random + 1, compteur);
        }
    }
    else
    {
        tour(tabjoueur, nbrjoueur, random + 1, compteur);
    }
}

