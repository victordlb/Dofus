#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "header.h"

void combat(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* fond)
{

}


void afficherSort(t_joueur** tabjoueur, int indice, BITMAP* fond)
{
    BITMAP* sort1;
    BITMAP* sort2;
    BITMAP* sort3;
    BITMAP* sort4;
    if(strcmp(tabjoueur[indice]->classes.nom, "luffy") == 0)
    {
        sort1 = load_bitmap("documents/perso/luffy/sortL/1.bmp", NULL);
        sort2 = load_bitmap("documents/perso/luffy/sortL/2.bmp", NULL);
        sort3 = load_bitmap("documents/perso/luffy/sortL/3.bmp", NULL);
        sort4 = load_bitmap("documents/perso/luffy/sortL/4.bmp", NULL);
    }
    else if(strcmp(tabjoueur[indice]->classes.nom, "robin") == 0)
    {
        sort1 = load_bitmap("documents/perso/robin/sortR/1.bmp", NULL);
        sort2 = load_bitmap("documents/perso/robin/sortR/2.bmp", NULL);
        sort3 = load_bitmap("documents/perso/robin/sortR/3.bmp", NULL);
        sort4 = load_bitmap("documents/perso/robin/sortR/4.bmp", NULL);
    }
    else if(strcmp(tabjoueur[indice]->classes.nom, "sanji") == 0)
    {
        sort1 = load_bitmap("documents/perso/sanji/sortS/1.bmp", NULL);
        sort2 = load_bitmap("documents/perso/sanji/sortS/2.bmp", NULL);
        sort3 = load_bitmap("documents/perso/sanji/sortS/3.bmp", NULL);
        sort4 = load_bitmap("documents/perso/sanji/sortS/4.bmp", NULL);
    }
    else if(strcmp(tabjoueur[indice]->classes.nom,"franky") == 0)
    {
        sort1 = load_bitmap("documents/perso/franky/sortF/1.bmp", NULL);
        sort2 = load_bitmap("documents/perso/franky/sortF/2.bmp", NULL);
        sort3 = load_bitmap("documents/perso/franky/sortF/3.bmp", NULL);
        sort4 = load_bitmap("documents/perso/franky/sortF/4.bmp", NULL);
    }
    else
        printf("oups");
    draw_sprite(fond, sort1, 502, 737);
    draw_sprite(fond, sort2, 502 + (1*75), 737);
    draw_sprite(fond, sort3, 502 + (2*75), 737);
    draw_sprite(fond, sort4, 502 + (3*75), 737);
    clear_bitmap(sort1);
    clear_bitmap(sort2);
    clear_bitmap(sort3);
    clear_bitmap(sort4);
}

