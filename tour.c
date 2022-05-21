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
        // deplacement(tabjoueur, random-1,nbrjoueur);
        choix_action(tabjoueur,random-1,nbrjoueur);
        printf("joueur %d : %s a vous de jouer(saisir un entier)\n", tabjoueur[random-1]->classes.ID, tabjoueur[random-1]->classes.nom);
        //scanf("%d", &entier);
        if(tabjoueur[random-1]->classes.PV <= 0)
        {
            tabjoueur[random-1]->perdu = 1;
            compteur++;
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

void compte_temps(float temps, BITMAP* buffer)
{
    BITMAP* chrono;
    if(temps < 1)
    {
        chrono = load_bitmap("documents/props/chrono 0.bmp", NULL);
    }
    if(temps <2 && temps >= 1)
    {
        chrono = load_bitmap("documents/props/chrono 1.bmp", NULL);
    }
    if(temps <3 && temps >= 2)
    {
        chrono = load_bitmap("documents/props/chrono 2.bmp", NULL);
    }
    if(temps <4 && temps >= 3)
    {
        chrono = load_bitmap("documents/props/chrono 3.bmp", NULL);
    }
    if(temps <5 && temps >= 4)
    {
        chrono = load_bitmap("documents/props/chrono 4.bmp", NULL);
    }
    if(temps <6 && temps >= 5)
    {
        chrono = load_bitmap("documents/props/chrono 5.bmp", NULL);
    }
    if(temps <7 && temps >= 6)
    {
        chrono = load_bitmap("documents/props/chrono 6.bmp", NULL);
    }
    if(temps <8 && temps >= 7)
    {
        chrono = load_bitmap("documents/props/chrono 7.bmp", NULL);
    }
    if(temps <9 && temps >= 8)
    {
        chrono = load_bitmap("documents/props/chrono 8.bmp", NULL);
    }
    if(temps <10 && temps >= 9)
    {
        chrono = load_bitmap("documents/props/chrono 9.bmp", NULL);
    }
    if(temps <11 && temps >= 10)
    {
        chrono = load_bitmap("documents/props/chrono 10.bmp", NULL);
    }
    if(temps <12 && temps >= 11)
    {
        chrono = load_bitmap("documents/props/chrono 11.bmp", NULL);
    }
    if(temps <13 && temps >= 12)
    {
        chrono = load_bitmap("documents/props/chrono 12.bmp", NULL);
    }
    if(temps <14 && temps >= 13)
    {
        chrono = load_bitmap("documents/props/chrono 13.bmp", NULL);
    }
    if(temps <15 && temps >= 14)
    {
        chrono = load_bitmap("documents/props/chrono 14.bmp", NULL);
    }
    if(temps >= 15)
    {
        chrono = load_bitmap("documents/props/chrono 15.bmp", NULL);
    }
    draw_sprite(buffer, chrono, 0,754);
    destroy_bitmap(chrono);
}

void choix_action(t_joueur** tabjoueur, int indice, int nbrjoueur)
{
    t_cases** tabcases;
    BITMAP* fond;
    BITMAP* buffer;
    tabcases = chargement_map();
    fond = chargement_fond(tabcases);
    float temps = 0;
    chargement_perso(tabjoueur,indice,nbrjoueur,fond);
    dessin_haut_arbre(fond,tabcases);
    blit(fond, screen,0,0,0,0,SCREEN_W, SCREEN_H);
    int done = 0;
    time_t start, end;
    time(&start);
    while(done == 0)
    {
        if(mouse_b&1)
        {
            if(mouse_x > 1340 && mouse_x < 1380 && mouse_y >5 && mouse_y < 45)
            {
                menu_pause(tabjoueur,nbrjoueur,indice);
                blit(fond, screen,0,0,0,0,SCREEN_W, SCREEN_H);
            }
            if(mouse_x > 1250 && mouse_x < 1300 && mouse_y >750 && mouse_y < 800)
            {
                deplacement(tabcases,tabjoueur,indice,nbrjoueur,fond);
            }
            if(mouse_x > 1300 && mouse_x < 1350 && mouse_y >750 && mouse_y < 800)
            {
                buffer = chargement_fond(tabcases);
                chargement_perso(tabjoueur,indice,nbrjoueur, buffer);
                dessin_haut_arbre(buffer,tabcases);
                combat(tabcases,tabjoueur,indice,nbrjoueur,buffer);
                clear_bitmap(buffer);
                blit(fond, screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }
            if(mouse_x > 1350 && mouse_x < 1400 && mouse_y >750 && mouse_y < 800)
            {
                done = 2;
            }
            Sleep(500);
        }
        time(&end);
        temps = difftime(end, start);
        compte_temps(temps,screen);
        if(temps > 15)
        {
            done = 2;
        }
    }
}
