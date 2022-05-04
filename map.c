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
    FILE* pf = fopen("lamapa.txt", "r+");
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
            fscanf(pf, "%d", &tabcases[i][j].cases);
            if(tabcases[i][j].cases <= 5)
                tabcases[i][j].obstacle = 0;
            else
                tabcases[i][j].obstacle = 1;
            tabcases[0][j].obstacle = 1;
        }
        ligne = ligne +50;
    }
    fclose(pf);
    return tabcases;
}

BITMAP* charger_map(t_cases** tabcases)
{
    BITMAP* un = load_bitmap("1.bmp", NULL);
    BITMAP* deux = load_bitmap("2.bmp", NULL);
    BITMAP* trois = load_bitmap("3.bmp", NULL);
    BITMAP* quatre = load_bitmap("4.bmp", NULL);
    BITMAP* cinq = load_bitmap("5.bmp", NULL);
    BITMAP* six = load_bitmap("6.bmp", NULL);
    BITMAP* sept = load_bitmap("7.bmp", NULL);
    BITMAP* huit = load_bitmap("8.bmp", NULL);
    BITMAP* neuf = load_bitmap("9.bmp", NULL);
    BITMAP* zero = load_bitmap("0.bmp", NULL);
    BITMAP* fond = create_bitmap(SCREEN_W, SCREEN_H);
    for(int i =0; i<16; i++)
    {
        for(int j=0; j<28; j++)
        {
            if(tabcases[i][j].cases == 1)
                draw_sprite(fond, un, tabcases[i][j].x, tabcases[i][j].y);
            if(tabcases[i][j].cases == 2)
                draw_sprite(fond, deux, tabcases[i][j].x, tabcases[i][j].y);
            if(tabcases[i][j].cases == 3)
                draw_sprite(fond, trois, tabcases[i][j].x, tabcases[i][j].y);
            if(tabcases[i][j].cases == 4)
                draw_sprite(fond, quatre, tabcases[i][j].x, tabcases[i][j].y);
            if(tabcases[i][j].cases == 5)
                draw_sprite(fond, cinq, tabcases[i][j].x, tabcases[i][j].y);
            if(tabcases[i][j].cases == 6)
                draw_sprite(fond, six, tabcases[i][j].x, tabcases[i][j].y);
            if(tabcases[i][j].cases == 7)
                draw_sprite(fond, sept, tabcases[i][j].x, tabcases[i][j].y);
            if(tabcases[i][j].cases == 8)
                draw_sprite(fond, huit, tabcases[i][j].x, tabcases[i][j].y);
            if(tabcases[i][j].cases == 9)
                draw_sprite(fond, neuf, tabcases[i][j].x, tabcases[i][j].y);
            if(tabcases[i][j].cases == 0)
                draw_sprite(fond, zero, tabcases[i][j].x, tabcases[i][j].y);
        }
    }
    destroy_bitmap(un);
    destroy_bitmap(deux);
    destroy_bitmap(trois);
    destroy_bitmap(quatre);
    destroy_bitmap(cinq);
    destroy_bitmap(six);
    destroy_bitmap(sept);
    destroy_bitmap(huit);
    destroy_bitmap(neuf);
    destroy_bitmap(zero);
    return fond;
}

void deplacement(t_joueur** tabjoueur, int indice)
{
    t_cases** tabcases;
    tabcases = chargement_map();
    BITMAP* fond;
    BITMAP* personnage;
    BITMAP* buffer;
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    fond = charger_map(tabcases);
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
            premier_y = tabcases[mouse_y/50][mouse_x/50].y;
            validation = 1;
        }
        if(validation == 1)
        {
            draw_sprite(buffer, personnage, premier_x, premier_y-50);
        }
        blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
        if(mouse_b&1 && possibilite_deplacement(tabcases, mouse_x, mouse_y)==1)
        {
            premier_x = tabcases[mouse_y/50][mouse_x/50].x;
            premier_y = tabcases[mouse_y/50][mouse_x/50].y;
            validation = 1;
        }
        if(validation == 1)
        {
            draw_sprite(buffer, personnage, premier_x, premier_y-50);
        }
        clear_bitmap(buffer);
    }
    destroy_bitmap(fond);
    destroy_bitmap(personnage);
    destroy_bitmap(buffer);
}

void premier_placement(t_joueur*** tabjoueur, int nbrjoueur)
{
    BITMAP* fond ;
    t_cases** tabcases;
    tabcases = chargement_map();
    fond = charger_map(tabcases);
    BITMAP* personnage;
    float temps = 0;
    int validation = 0;
    int done = 0;
    for(int i=0; i<nbrjoueur; i++)
    {
        temps = 0;
        textprintf_ex(fond, font, 300,20,makecol(0,0,0), -1, "CHOISISSEZ VOTRE POSITION DE DEPART DANS LE MEME ORDRE QUE VOS CHOIX DE PERSONNAGES (vous avez 15secondes)");
        done = 0;
        validation = 0;
        if((*tabjoueur)[i]->classes.PV == 70)
            personnage = load_bitmap("luffy standby.bmp", NULL);
        else if((*tabjoueur)[i]->classes.PV == 65)
            personnage = load_bitmap("robin standby.bmp", NULL);
        else if((*tabjoueur)[i]->classes.PV == 50)
            personnage = load_bitmap("sanji standby.bmp", NULL);
        else if((*tabjoueur)[i]->classes.PV == 100)
            personnage = load_bitmap("franky standby.bmp", NULL);
        time_t start, end;
        time(&start);
        while(done==0 && temps <=16)
        {
            if(mouse_b&1 && possibilite_deplacement(tabcases, mouse_x, mouse_y)==1)
            {
                (*tabjoueur)[i]->classes.cord_x = tabcases[mouse_y/50][mouse_x/50].x;
                (*tabjoueur)[i]->classes.cord_y = tabcases[mouse_y/50][mouse_x/50].y;
                tabcases[mouse_y/50][mouse_x/50].obstacle = 1;
                validation = 1;
            }
            if(validation == 1)
            {
                draw_sprite(fond, personnage, (*tabjoueur)[i]->classes.cord_x, (*tabjoueur)[i]->classes.cord_y-50);
                Sleep(500);
                done = 1;
            }
            blit(fond, screen,0,0,0,0,SCREEN_W,SCREEN_H);
            time(&end);
            temps = difftime(end, start);
            if(temps == 15)
            {
                do
                {
                    (*tabjoueur)[i]->classes.cord_x = tabcases[rand()%16][rand()%28].x;
                    (*tabjoueur)[i]->classes.cord_y = tabcases[rand()%16][rand()%28].y;
                }
                while(possibilite_deplacement(tabcases, (*tabjoueur)[i]->classes.cord_x, (*tabjoueur)[i]->classes.cord_y)==0);
                validation = 1;
            }
        }
    }
    Sleep(1000);
    destroy_bitmap(personnage);
    destroy_bitmap(fond);
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
