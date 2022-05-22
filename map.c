#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <synchapi.h>
#include "header.h"

///TOUTES LES FONCTIONS DE CE .C METTENT EN PLACE LES MAPS DEPUIS UN FICHIER TEXTE ET UN TABLEAU DE CASES

///dessin de ligne horizontale et verticale (non utilisé dans le code final)
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

/// chargement du tableau de case et de ses caracteristique depuis un fichier texte
t_cases** chargement_map(int choix)
{
    t_cases** tabcases = (t_cases**)malloc(16 * sizeof(t_cases*));
    FILE* pf;
    if(choix == 1)
    {
        pf = fopen("documents/lamap/lamapa.txt", "r+");
    }
    else if(choix == 2)
    {
        pf = fopen("documents/lamap2/lamapa2.txt", "r+");
    }
    else if(choix == 3)
    {
        pf = fopen("documents/lamap3/lamapa3.txt", "r+");
    }
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
            if(choix == 1)
            {
                if(tabcases[i][j].cases <= 5)
                    tabcases[i][j].obstacle = 0;
                else
                    tabcases[i][j].obstacle = 1;
            }
            else if(choix == 2)
            {
                if(tabcases[i][j].cases < 4)
                    tabcases[i][j].obstacle = 0;
                else
                    tabcases[i][j].obstacle = 1;
            }
            else if(choix == 3)
            {
                if(tabcases[i][j].cases < 10)
                    tabcases[i][j].obstacle = 0;
                else
                    tabcases[i][j].obstacle = 1;
            }
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
    for(int b = 0; b<2; b++)
    {
        tabcases[15][b].obstacle = 1;
        tabcases[3][b].obstacle = 1;
        tabcases[4][b].obstacle = 1;
    }
    fclose(pf);
    return tabcases;
}

/// dessin de la map en fonction de ses caracteristiques
BITMAP* charger_map(t_cases** tabcases, int choix)
{
    BITMAP* un;
    BITMAP* deux;
    BITMAP* trois;
    BITMAP* quatre;
    BITMAP* cinq ;
    BITMAP* six;
    BITMAP* sept ;
    BITMAP* huit ;
    BITMAP* neuf;
    BITMAP* zero;
    if(choix == 1)
    {
        un = load_bitmap("documents/lamap/1.bmp", NULL);
        deux = load_bitmap("documents/lamap/2.bmp", NULL);
        trois = load_bitmap("documents/lamap/3.bmp", NULL);
        quatre = load_bitmap("documents/lamap/4.bmp", NULL);
        cinq = load_bitmap("documents/lamap/5.bmp", NULL);
        six = load_bitmap("documents/lamap/6.bmp", NULL);
        sept = load_bitmap("documents/lamap/7.bmp", NULL);
        huit = load_bitmap("documents/lamap/8.bmp", NULL);
        neuf = load_bitmap("documents/lamap/9.bmp", NULL);
        zero = load_bitmap("documents/lamap/0.bmp", NULL);
    }
    if(choix == 2)
    {
        un = load_bitmap("documents/lamap2/1.bmp", NULL);
        deux = load_bitmap("documents/lamap2/2.bmp", NULL);
        trois = load_bitmap("documents/lamap2/3.bmp", NULL);
        quatre = load_bitmap("documents/lamap2/4.bmp", NULL);
        cinq = load_bitmap("documents/lamap2/5.bmp", NULL);
        six = load_bitmap("documents/lamap2/6.bmp", NULL);
        sept = load_bitmap("documents/lamap2/7.bmp", NULL);
        huit = load_bitmap("documents/lamap2/8.bmp", NULL);
        neuf = load_bitmap("documents/lamap2/9.bmp", NULL);
        zero = load_bitmap("documents/lamap2/0.bmp", NULL);
    }
    if(choix == 3)
    {
        un = load_bitmap("documents/lamap3/1.bmp", NULL);
        deux = load_bitmap("documents/lamap3/2.bmp", NULL);
        trois = load_bitmap("documents/lamap3/3.bmp", NULL);
        quatre = load_bitmap("documents/lamap3/10.bmp", NULL);
        cinq = load_bitmap("documents/lamap3/11.bmp", NULL);
        six = load_bitmap("documents/lamap3/12.bmp", NULL);
        sept = load_bitmap("documents/lamap3/7.bmp", NULL);
        huit = load_bitmap("documents/lamap3/8.bmp", NULL);
        neuf = load_bitmap("documents/lamap3/9.bmp", NULL);
        zero = load_bitmap("documents/lamap3/0.bmp", NULL);
    }
    BITMAP* fond = create_bitmap(SCREEN_W, SCREEN_H);
    for(int i =0; i<16; i++)
    {
        for(int j=0; j<28; j++)
        {
            if(choix != 3)
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
            else
            {
                if(tabcases[i][j].cases == 1)
                    draw_sprite(fond, un, tabcases[i][j].x, tabcases[i][j].y);
                if(tabcases[i][j].cases == 2)
                    draw_sprite(fond, deux, tabcases[i][j].x, tabcases[i][j].y);
                if(tabcases[i][j].cases == 3)
                    draw_sprite(fond, trois, tabcases[i][j].x, tabcases[i][j].y);
                if(tabcases[i][j].cases == 10)
                    draw_sprite(fond, quatre, tabcases[i][j].x, tabcases[i][j].y);
                if(tabcases[i][j].cases == 11)
                    draw_sprite(fond, cinq, tabcases[i][j].x, tabcases[i][j].y);
                if(tabcases[i][j].cases == 12)
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

/// dessin du haut des arbres de la map1 pour faire passer le joueur derriere
void dessin_haut_arbre(BITMAP* fond, t_cases** tabcases)
{
    BITMAP* cinq = load_bitmap("documents/lamap/5.bmp", NULL);
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<28; j++)
        {
            if(tabcases[i][j].cases == 5)
            {
                draw_sprite(fond, cinq, tabcases[i][j].x, tabcases[i][j].y);
            }
        }
    }
    destroy_bitmap(cinq);
}

///fonction non-utilisé qui colorise un element en vert
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

///fonction non-utilisé qui colorise un element en rouge
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

///fonction non-utilisé qui colorise un element en bleu
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

/// fonction qui dessine la map en fonction du tableau de case
BITMAP* chargement_fond(t_cases** tabcases,int choix)
{
    BITMAP* fond;
    fond = charger_map(tabcases,choix);
    return fond;
}

/// fonction qui affiche les différents element en plus de la map(joueur/curseur/etat des joueurs/....)
void chargement_perso(t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* buffer, int etat)
{
    BITMAP* personnage;
    BITMAP* tete_perso;
    BITMAP* tete_perso_c;
    BITMAP* curseur;
    BITMAP* casesort = load_bitmap("documents/props/case sort.bmp", NULL);
    BITMAP* fond;
    BITMAP* pause;
    BITMAP* pv;
    BITMAP* personnage1;
    BITMAP* personnage2;
    BITMAP* personnage4;
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
    rectfill(buffer, 5, 160, 120,230, makecol(255,185,61));
    textprintf_ex(buffer,font,8,170,makecol(255,255,255),-1,"%s", tabjoueur[indice]->pseudo);
    textprintf_ex(buffer,font,8,190,makecol(255,255,255),-1,"PV : %d", tabjoueur[indice]->classes.PV);
    textprintf_ex(buffer,font,8,200,makecol(255,255,255),-1,"PM : %d", tabjoueur[indice]->classes.PM);
    textprintf_ex(buffer,font,8,210,makecol(255,255,255),-1,"PA : %d", tabjoueur[indice]->classes.PA);
    for(int i=0; i<nbrjoueur; i++)
    {
        if(strcmp(tabjoueur[i]->classes.nom, "luffy")==0)
        {
            personnage = load_bitmap("documents/perso/luffy/luffy standby.bmp", NULL);
            personnage1 = load_bitmap("documents/perso/luffy/luffy jump.bmp", NULL);
            personnage2 = load_bitmap("documents/perso/luffy/luffy dep1.bmp", NULL);
            personnage4 = load_bitmap("documents/perso/luffy/luffy dead.bmp", NULL);

            tete_perso = load_bitmap("documents/perso/luffy/luffy tour.bmp", NULL);
            tete_perso_c = load_bitmap("documents/perso/luffy/luffy tour_c.bmp", NULL);
        }
        else if(strcmp(tabjoueur[i]->classes.nom, "robin")==0)
        {
            personnage = load_bitmap("documents/perso/robin/robin standby.bmp", NULL);
            personnage1 = load_bitmap("documents/perso/robin/robin jump.bmp", NULL);
            personnage2 = load_bitmap("documents/perso/robin/robin dep1.bmp", NULL);
            personnage4 = load_bitmap("documents/perso/robin/robin dead.bmp", NULL);

            tete_perso = load_bitmap("documents/perso/robin/robin tour.bmp", NULL);
            tete_perso_c = load_bitmap("documents/perso/robin/robin tour_c.bmp", NULL);
        }
        else if(strcmp(tabjoueur[i]->classes.nom,"sanji") == 0)
        {
            personnage = load_bitmap("documents/perso/sanji/sanji standby.bmp", NULL);
            personnage1 = load_bitmap("documents/perso/sanji/sanji jump.bmp", NULL);
            personnage2 = load_bitmap("documents/perso/sanji/sanji dep1.bmp", NULL);
            personnage4 = load_bitmap("documents/perso/sanji/sanji dead.bmp", NULL);

            tete_perso = load_bitmap("documents/perso/sanji/sanji tour.bmp", NULL);
            tete_perso_c = load_bitmap("documents/perso/sanji/sanji tour_c.bmp", NULL);
        }
        else if(strcmp(tabjoueur[i]->classes.nom, "franky") == 0)
        {
            personnage = load_bitmap("documents/perso/franky/franky standby.bmp", NULL);
            personnage1 = load_bitmap("documents/perso/franky/franky jump.bmp", NULL);
            personnage2 = load_bitmap("documents/perso/franky/franky dep1.bmp", NULL);
            personnage4 = load_bitmap("documents/perso/franky/franky dead.bmp", NULL);

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
        if(tabjoueur[i]->classes.PV <=0)
        {
            draw_sprite(buffer, personnage4, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y);
        }
        else if(indice != tabjoueur[i]->classes.ID-1)
        {
            draw_sprite(buffer, personnage, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y-50);
        }
        else
        {
            if(etat == 0)
            {
                draw_sprite(buffer, personnage, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y-50);
            }
            if(etat == 1)
            {
                draw_sprite(buffer, personnage1, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y-50);
            }
            if(etat == 2)
            {
                draw_sprite(buffer, personnage2, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y-50);
            }
            if(etat == 3)
            {
                draw_sprite_h_flip(buffer,personnage2,tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y-50);
            }
            if(etat == 4)
            {
                draw_sprite(buffer, personnage4, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y);
            }
        }
        pourcent_pv = (tabjoueur[i]->classes.PV*100)/tabjoueur[i]->classes.PV_init;
        cord_pourcent_pv = (36*pourcent_pv)/100;
        cord_pourcent_pv = cord_pourcent_pv + 8;
        if(tabjoueur[i]->classes.PV <= 0)
        {
            draw_sprite(buffer, pv,tabjoueur[i]->classes.cord_x-10, tabjoueur[i]->classes.cord_y-15 );
            rectfill(buffer,tabjoueur[i]->classes.cord_x+8, tabjoueur[i]->classes.cord_y-11, tabjoueur[i]->classes.cord_x+cord_pourcent_pv, tabjoueur[i]->classes.cord_y-4, makecol(10,224,44));
        }
        else
        {
            draw_sprite(buffer, pv,tabjoueur[i]->classes.cord_x-10, tabjoueur[i]->classes.cord_y-65 );
            rectfill(buffer,tabjoueur[i]->classes.cord_x+8, tabjoueur[i]->classes.cord_y-61, tabjoueur[i]->classes.cord_x+cord_pourcent_pv, tabjoueur[i]->classes.cord_y-54, makecol(10,224,44));
        }
        if(indice != tabjoueur[i]->classes.ID-1)
            draw_sprite(buffer, tete_perso_c, x, 20);
        for(int i = 0 ; i<5; i++)
        {
            draw_sprite(buffer, casesort, 495 + (i*75), 730);
        }
    }
    destroy_bitmap(fond);
    destroy_bitmap(personnage);
    destroy_bitmap(personnage1);
    destroy_bitmap(personnage2);
    destroy_bitmap(personnage4);
    destroy_bitmap(tete_perso);
    destroy_bitmap(tete_perso_c);
    destroy_bitmap(casesort);
    destroy_bitmap(curseur);
    destroy_bitmap(pause);
    destroy_bitmap(logoatt);
    destroy_bitmap(logodpl);
    destroy_bitmap(logopass);
    destroy_bitmap(cadre);
    destroy_bitmap(pv);
}

