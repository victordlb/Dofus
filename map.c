#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <synchapi.h>
#include "header.h"

void dessin_ligne()
{
    BITMAP* fond;
    fond = load_bitmap("map monde.bmp", NULL);
    while(!key[KEY_ESC])
    {
        blit(fond, screen,0,0,0,0,SCREEN_W, SCREEN_H);
        for(int x=50; x<1400; x = x+50)
        {
            vline(fond, x, 0,800,makecol(255,255,255));
        }
        for(int y=0; y<800; y = y+50)
        {
            hline(fond, 0, y,1400, makecol(255,255,255));
        }
    }
    destroy_bitmap(fond);
}

t_cases** chargement_map()
{
    t_cases** tabcases = (t_cases**)malloc(16 * sizeof(t_cases*));
    FILE* pf = fopen("map.txt", "r+");
    if(pf == NULL)
    {
        printf("Erreur d'ouverture\n");
    }
    for(int x = 0; x< 16; x++)
    {
        tabcases[x] = (t_cases*)malloc(28 * sizeof(t_cases));
    }
    int colonne =0;
    int ligne = 0;
    for(int i =0; i<16; i++)
    {
        colonne = 0;
        for(int j=0; j<28; j++)
        {
            tabcases[i][j].x = colonne;
            tabcases[i][j].y = ligne;
            colonne = colonne +50;
            fscanf(pf, "%d", &tabcases[i][j].obstacle);
        }
        ligne = ligne +50;
    }
    fclose(pf);
    return tabcases;
}

void deplacement(t_joueur** tabjoueur, int indice)
{
    t_cases** tabcases;
    tabcases = chargement_map();
    BITMAP* fond;
    BITMAP* personnage;
    BITMAP* buffer;
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    fond = load_bitmap("map monde.bmp", NULL);
    if(tabjoueur[indice-1]->classes.PV == 70)
        personnage = load_bitmap("luffy standby.bmp", NULL);
    else if(tabjoueur[indice-1]->classes.PV == 65)
        personnage = load_bitmap("robin standby.bmp", NULL);
    else if(tabjoueur[indice-1]->classes.PV == 50)
        personnage = load_bitmap("sanji standby.bmp", NULL);
    else if(tabjoueur[indice-1]->classes.PV == 100)
        personnage = load_bitmap("franky standby.bmp", NULL);
    for(int x=50; x<1400; x = x+50)
    {
        vline(fond, x, 0,800,makecol(255,255,255));
    }
    for(int y=0; y<800; y = y+50)
    {
        hline(fond, 0, y,1400, makecol(255,255,255));
    }
    int premier_x;
    int premier_y;
    int validation = 0;
    while(!key[KEY_ESC])
    {
        ///ici pour la map
        blit(fond, buffer,0,0,0,0,SCREEN_W, SCREEN_H);
        if(mouse_b&1 && possibilite_deplacement(tabcases, mouse_x, mouse_y)==1)
        {
            premier_x = tabcases[mouse_y/50][mouse_x/50].x;
            premier_y = tabcases[(mouse_y/50)-1][(mouse_x/50)-1].y;
            //Sleep(500);
            validation = 1;
        }
        if(validation == 1)
        {
            draw_sprite(buffer, personnage, premier_x, premier_y);
        }
        blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
        if(mouse_b&1 && possibilite_deplacement(tabcases, mouse_x, mouse_y)==1)
        {
            premier_x = tabcases[mouse_y/50][mouse_x/50].x;
            premier_y = tabcases[(mouse_y/50)-1][(mouse_x/50)-1].y;
            draw_sprite(screen, personnage, premier_x, premier_y);
            Sleep(500);
            validation = 1;
        }
        if(validation == 1)
        {
            draw_sprite(buffer, personnage, premier_x, premier_y);
            Sleep(500);
        }
        clear_bitmap(buffer);
    }
    destroy_bitmap(fond);
    destroy_bitmap(personnage);
    destroy_bitmap(buffer);
}

int possibilite_deplacement(t_cases** tabcases,int X, int Y)
{
    if(tabcases[Y/50][X/50].obstacle == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int testvert(int vert)
{
    int pourcentage = (100*vert)/255;
    if(pourcentage > 75)
        return vert;
    else if(pourcentage <= 75 && pourcentage > 50)
        return vert+25;
    else if(pourcentage <= 50 && pourcentage > 25)
        return vert+50;
    else
        return vert+75;
}

int testrouge(int rouge)
{
    int pourcentage = (100*rouge)/255;
    if(pourcentage > 75)
        return rouge;
    else if(pourcentage <= 75 && pourcentage > 50)
        return rouge+25;
    else if(pourcentage <= 50 && pourcentage > 25)
        return rouge+50;
    else
        return rouge+75;
}

int testbleu(int bleu)
{
    int pourcentage = (100*bleu)/255;
    if(pourcentage > 75)
        return bleu;
    else if(pourcentage <= 75 && pourcentage > 50)
        return bleu+25;
    else if(pourcentage <= 50 && pourcentage > 25)
        return bleu+50;
    else
        return bleu+75;
}
