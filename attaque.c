#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "header.h"

void combat(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* fond)
{
    afficherSort(tabjoueur, indice, fond);
    int done = 0;
    BITMAP* select = load_bitmap("documents/props/css.bmp", NULL);
    while(done == 0)
    {
        if(mouse_b&1)
        {
            if(mouse_x>502 && mouse_x<572 && mouse_y>737 && mouse_y<800)
            {
                draw_sprite(fond, select, 495, 730);
                blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                porteSort(tabcases, tabjoueur, indice, 0, fond);
                Sleep(1000);
                done =1;

            }
            if(mouse_x>577 && mouse_x<647 && mouse_y>737 && mouse_y<800)
            {
                draw_sprite(fond, select, 495 + (1*75), 730);
                blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                porteSort(tabcases, tabjoueur, indice, 1, fond);
                Sleep(1000);
                done =1;
            }
            if(mouse_x>652 && mouse_x<722 && mouse_y>737 && mouse_y<800)
            {
                draw_sprite(fond, select, 495 + (2*75), 730);
                blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                porteSort(tabcases, tabjoueur, indice, 2, fond);
                Sleep(1000);
                done =1;
            }
            if(mouse_x>727 && mouse_x<797 && mouse_y>737 && mouse_y<800)
            {
                draw_sprite(fond, select, 495 + (3*75), 730);
                blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                porteSort(tabcases, tabjoueur, indice, 3, fond);
                Sleep(1000);
                done =1;
            }
            if(mouse_x>802 && mouse_x<872 && mouse_y>737 && mouse_y<800)
            {
                draw_sprite(fond, select, 495 + (4*75), 730);
                blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                Sleep(1000);
                done =1;
            }
            if(mouse_x > 1250 && mouse_x < 1300 && mouse_y >750 && mouse_y < 800)
            {
                done = 1;
            }
        }
    }
    Sleep(1000);
    destroy_bitmap(select);
}


void afficherSort(t_joueur** tabjoueur, int indice, BITMAP* fond)
{
    BITMAP* sort1;
    BITMAP* sort2;
    BITMAP* sort3;
    BITMAP* sort4;
    BITMAP* poing = load_bitmap("documents/perso/poing.bmp", NULL);
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
    draw_sprite(fond, poing, 502 + (4*75), 737);
    blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
    clear_bitmap(sort1);
    clear_bitmap(sort2);
    clear_bitmap(sort3);
    clear_bitmap(sort4);
    clear_bitmap(poing);
}

void porteSort(t_cases** tabcases, t_joueur** tabjoueur, int indice, int numsort, BITMAP* fond)
{
    int paraTab[16][28] = {0};
    if(tabjoueur[indice]->classes.mesattaques[numsort].type == 1)
    {
        for(int i = 1; i<=tabjoueur[indice]->classes.mesattaques[numsort].porte; i++)
        {
            paraTab[tabjoueur[indice]->classes.cord_y-i][tabjoueur[indice]->classes.cord_x] = 1;
            paraTab[tabjoueur[indice]->classes.cord_y+i][tabjoueur[indice]->classes.cord_x] = 1;
            paraTab[tabjoueur[indice]->classes.cord_y][tabjoueur[indice]->classes.cord_x-i] = 1;
            paraTab[tabjoueur[indice]->classes.cord_y][tabjoueur[indice]->classes.cord_x+i] = 1;
        }
        for(int j = 0; j<16; j++)
        {
            for(int g = 0; g<28; g++)
            {
                if(paraTab[j][g] == 1 && tabcases[j][g].obstacle == 0)
                    rectfill(fond, tabcases[j][g].x+5, tabcases[j][g].y+5, tabcases[j][g].x+45,tabcases[j][g].y+45, makecol(50,130,246));
            }
        }

    }
}

