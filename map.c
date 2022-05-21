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
    FILE* pf = fopen("documents/lamap/lamapa.txt", "r+");
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
    for(int z=9 ; z<18; z++)
    {
        tabcases[14][z].obstacle = 1;
        tabcases[15][z].obstacle = 1;
    }
    for(int g = 0; g<6; g++)
    {
        tabcases[1][g].obstacle = 1;
    }
    for(int a = 25; a<28; a++)
    {
        tabcases[15][a].obstacle = 1;
    }
    for(int b = 0; b<3; b++)
    {
        tabcases[15][b].obstacle = 1;
    }
    fclose(pf);
    return tabcases;
}

BITMAP* charger_map(t_cases** tabcases)
{
    BITMAP* un = load_bitmap("documents/lamap/1.bmp", NULL);
    BITMAP* deux = load_bitmap("documents/lamap/2.bmp", NULL);
    BITMAP* trois = load_bitmap("documents/lamap/3.bmp", NULL);
    BITMAP* quatre = load_bitmap("documents/lamap/4.bmp", NULL);
    BITMAP* cinq = load_bitmap("documents/lamap/5.bmp", NULL);
    BITMAP* six = load_bitmap("documents/lamap/6.bmp", NULL);
    BITMAP* sept = load_bitmap("documents/lamap/7.bmp", NULL);
    BITMAP* huit = load_bitmap("documents/lamap/8.bmp", NULL);
    BITMAP* neuf = load_bitmap("documents/lamap/9.bmp", NULL);
    BITMAP* zero = load_bitmap("documents/lamap/0.bmp", NULL);
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

void dessin_haut_arbre(BITMAP* fond, t_cases** tabcases)
{
    BITMAP* cinq = load_bitmap("documents/lamap/5.bmp", NULL);
    for(int i=0; i<16;i++)
    {
        for(int j=0; j<28;j++)
        {
            if(tabcases[i][j].cases == 5)
            {
                draw_sprite(fond, cinq, tabcases[i][j].x, tabcases[i][j].y);
            }
        }
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


BITMAP* chargement_fond(t_cases** tabcases)
{
    BITMAP* fond;
    fond = charger_map(tabcases);
    return fond;
}

void chargement_perso(t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* buffer)
{
    BITMAP* personnage;
    BITMAP* tete_perso;
    BITMAP* tete_perso_c;
    BITMAP* curseur;
    BITMAP* casesort = load_bitmap("documents/props/case sort.bmp", NULL);
    BITMAP* fond;
    BITMAP* pause;
    BITMAP* pv;
    pv = load_bitmap("documents/props/pv barre.bmp", NULL);
    pause = load_bitmap("documents/props/pause.bmp", NULL);
    curseur = load_bitmap("documents/props/curseur_perso.bmp", NULL);
    fond = load_bitmap("documents/fond/fond tete.bmp", NULL);
    BITMAP* logodpl;
    logodpl = load_bitmap("documents/props/logo deplacement.bmp", NULL);
    BITMAP* logoatt;
    logoatt = load_bitmap("documents/props/logo attaque.bmp", NULL);
    BITMAP* logopass;
    logopass = load_bitmap("documents/props/logo passtour.bmp", NULL);
    BITMAP* cadre;
    cadre = load_bitmap("documents/props/cadre blanc.bmp", NULL);
    int x;
    int pourcent_pv;
    int cord_pourcent_pv;
    draw_sprite(buffer, fond, 10,10);
    draw_sprite(buffer, pause, 1340,5);
    draw_sprite(buffer, cadre, 1250,750);
    draw_sprite(buffer, cadre, 1300,750);
    draw_sprite(buffer, cadre, 1350,750);
    draw_sprite(buffer, logodpl, 1260,760);
    draw_sprite(buffer, logoatt, 1310, 760);
    draw_sprite(buffer, logopass, 1360,760);
    for(int i=0; i<nbrjoueur; i++)
    {
        if(strcmp(tabjoueur[i]->classes.nom, "luffy")==0)
        {
            personnage = load_bitmap("documents/perso/luffy/luffy standby.bmp", NULL);
            tete_perso = load_bitmap("documents/perso/luffy/luffy tour.bmp", NULL);
            tete_perso_c = load_bitmap("documents/perso/luffy/luffy tour_c.bmp", NULL);
        }
        else if(strcmp(tabjoueur[i]->classes.nom, "robin")==0)
        {
            personnage = load_bitmap("documents/perso/robin/robin standby.bmp", NULL);
            tete_perso = load_bitmap("documents/perso/robin/robin tour.bmp", NULL);
            tete_perso_c = load_bitmap("documents/perso/robin/robin tour_c.bmp", NULL);
        }
        else if(strcmp(tabjoueur[i]->classes.nom,"sanji") == 0)
        {
            personnage = load_bitmap("documents/perso/sanji/sanji standby.bmp", NULL);
            tete_perso = load_bitmap("documents/perso/sanji/sanji tour.bmp", NULL);
            tete_perso_c = load_bitmap("documents/perso/sanji/sanji tour_c.bmp", NULL);
        }
        else if(strcmp(tabjoueur[i]->classes.nom, "franky") == 0)
        {
            personnage = load_bitmap("documents/perso/franky/franky standby.bmp", NULL);
            tete_perso = load_bitmap("documents/perso/franky/franky tour.bmp", NULL);
            tete_perso_c = load_bitmap("documents/perso/franky/franky tour_c.bmp", NULL);
        }
        if(tabjoueur[i]->classes.ID == 1)
            x = 20;
        else if(tabjoueur[i]->classes.ID == 2)
            x = 90;
        else if(tabjoueur[i]->classes.ID == 3)
            x = 160;
        else if(tabjoueur[i]->classes.ID == 4)
            x = 230;
        if(indice == tabjoueur[i]->classes.ID-1)
        {
            draw_sprite(buffer, curseur, x +20, 65);
            draw_sprite(buffer, tete_perso, x, 20);
        }
        draw_sprite(buffer, personnage, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y-50);
        draw_sprite(buffer, pv,tabjoueur[i]->classes.cord_x-10, tabjoueur[i]->classes.cord_y-65 );
        pourcent_pv = (tabjoueur[i]->classes.PV*100)/tabjoueur[i]->classes.PV_init;
        cord_pourcent_pv = (36*pourcent_pv)/100;
        cord_pourcent_pv = cord_pourcent_pv + 8;
        rectfill(buffer,tabjoueur[i]->classes.cord_x+8, tabjoueur[i]->classes.cord_y-61, tabjoueur[i]->classes.cord_x+cord_pourcent_pv, tabjoueur[i]->classes.cord_y-54, makecol(10,224,44));
        if(indice != tabjoueur[i]->classes.ID-1)
            draw_sprite(buffer, tete_perso_c, x, 20);
        for(int i = 0 ; i<5; i++)
        {
            draw_sprite(buffer, casesort, 495 + (i*75), 730);
        }
    }
    destroy_bitmap(fond);
    destroy_bitmap(personnage);
    destroy_bitmap(tete_perso);
    destroy_bitmap(tete_perso_c);
    destroy_bitmap(casesort);
    destroy_bitmap(curseur);
    destroy_bitmap(pause);
    destroy_bitmap(logoatt);
    destroy_bitmap(logodpl);
    destroy_bitmap(logopass);
    destroy_bitmap(cadre);
}

