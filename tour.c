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

void tour(t_joueur** tabjoueur, int nbrjoueur, int indice, int compteur, int choix_mapa)
{
    if(tabjoueur[indice]->classes.PV > 0)
    {
        tabjoueur[indice]->classes.PA = tabjoueur[indice]->classes.PA_init;
        tabjoueur[indice]->classes.PM = tabjoueur[indice]->classes.PM_init;
        choix_action(tabjoueur,indice,nbrjoueur,choix_mapa);
        if(tabjoueur[indice]->classes.PV <=0)
        {
            compteur++;
            if(compteur == 1)
            {
                tabjoueur[indice]->ordre = nbrjoueur;
            }
            if(compteur == 2)
            {
                tabjoueur[indice]->ordre = nbrjoueur -1;
            }
            if(compteur == 3)
            {
                tabjoueur[indice]->ordre = nbrjoueur - 2;
            }
            if(compteur == nbrjoueur - 1)
            {
                for(int i=0; i<nbrjoueur; i++)
                {
                    if(tabjoueur[i]->classes.PV > 0)
                    {
                        tabjoueur[i]->ordre = 1;
                    }
                }
                return 0;
            }
        }
        if(indice + 1 == nbrjoueur)
        {
            tour(tabjoueur,nbrjoueur,0,compteur,choix_mapa);
        }
        else
        {
            tour(tabjoueur,nbrjoueur,indice+1,compteur,choix_mapa);
        }
    }
    else
    {
        tour(tabjoueur, nbrjoueur, indice+1, compteur,choix_mapa);
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

void choix_action(t_joueur** tabjoueur, int indice, int nbrjoueur,int choix)
{
    t_cases** tabcases;
    BITMAP* fond;
    BITMAP* buffer;
    tabcases = chargement_map(choix);
    fond = chargement_fond(tabcases,choix);
    float temps = 0;
    chargement_perso(tabjoueur,indice,nbrjoueur,fond,0);
    if(choix == 1)
    {
        dessin_haut_arbre(fond,tabcases);
    }
    blit(fond, screen,0,0,0,0,SCREEN_W, SCREEN_H);
    int done = 0;
    time_t start, end;
    time(&start);
    while(done == 0)
    {
        if(key[KEY_P])
        {
            tabjoueur[indice]->classes.PV = 0;
            Sleep(500);
            done = 8;
        }
        if(mouse_b&1)
        {
            if(mouse_x > 1340 && mouse_x < 1380 && mouse_y >5 && mouse_y < 45)
            {
                menu_pause(tabjoueur,nbrjoueur,indice);
                blit(fond, screen,0,0,0,0,SCREEN_W, SCREEN_H);
            }
            if(mouse_x > 1250 && mouse_x < 1300 && mouse_y >750 && mouse_y < 800)
            {
                deplacement(tabcases,tabjoueur,indice,nbrjoueur,fond,choix);
            }
            if(mouse_x > 1300 && mouse_x < 1350 && mouse_y >750 && mouse_y < 800)
            {
                buffer = chargement_fond(tabcases,choix);
                chargement_perso(tabjoueur,indice,nbrjoueur, buffer,0);
                if(choix == 1)
                {
                    dessin_haut_arbre(buffer,tabcases);
                }
                combat(tabcases,tabjoueur,indice,nbrjoueur,buffer,choix);
                clear_bitmap(buffer);
                fond = chargement_fond(tabcases,choix);
                chargement_perso(tabjoueur,indice,nbrjoueur, fond,0);
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
