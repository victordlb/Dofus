#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <synchapi.h>
#include <string.h>
#include "header.h"

///lancement du jeu
void lancement()
{
    srand(time(NULL));
    initialisation();
    logo();
    menu_principal();
}

///initialisation du tableau de joueur avec choix de caractéristique pour chaque joueur
t_joueur** initialisation_joueur(int nbrjoueur,int choix)
{
    t_joueur** tabjoueur;
    tabjoueur =(t_joueur**)malloc(nbrjoueur * sizeof(t_joueur*));
    for(int i = 0; i<nbrjoueur; i++)
    {
        tabjoueur[i] = (t_joueur*)malloc(sizeof(t_joueur));
        tabjoueur[i]->pseudo = saisie_pseudo();
        tabjoueur[i]->classes = choix_classe(tabjoueur,i, nbrjoueur);
        tabjoueur[i]->perdu = 0;
    }
    premier_placement(tabjoueur, nbrjoueur,choix);
    return tabjoueur;
}
