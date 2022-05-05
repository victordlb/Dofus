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

void deplacement(t_joueur** tabjoueur, int indice, int nbrjoueur)
{
    t_cases** tabcases;
    tabcases = chargement_map();
    BITMAP* fond;
    BITMAP* personnage;
    BITMAP* buffer;
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    fond = charger_map(tabcases);
    for(int i=0; i<nbrjoueur; i++)
    {
        if(tabjoueur[i]->classes.PV == 70)
            personnage = load_bitmap("luffy standby.bmp", NULL);
        else if(tabjoueur[i]->classes.PV == 65)
            personnage = load_bitmap("robin standby.bmp", NULL);
        else if(tabjoueur[i]->classes.PV == 50)
            personnage = load_bitmap("sanji standby.bmp", NULL);
        else if(tabjoueur[i]->classes.PV == 100)
            personnage = load_bitmap("franky standby.bmp", NULL);
        draw_sprite(fond, personnage, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y-50);
    }
    if(tabjoueur[indice]->classes.PV == 70)
        personnage = load_bitmap("luffy standby.bmp", NULL);
    else if(tabjoueur[indice]->classes.PV == 65)
        personnage = load_bitmap("robin standby.bmp", NULL);
    else if(tabjoueur[indice]->classes.PV == 50)
        personnage = load_bitmap("sanji standby.bmp", NULL);
    else if(tabjoueur[indice]->classes.PV == 100)
        personnage = load_bitmap("franky standby.bmp", NULL);
    for(int x=50; x<1400; x = x+50)
    {
        vline(fond, x, 0,800,makecol(255,255,255));
    }
    for(int y=0; y<800; y = y+50)
    {
        hline(fond, 0, y,1400, makecol(255,255,255));
    }
    int validation = 0;
    int done = 0;
    while(done == 0)
    {
        ///ici pour la map
        blit(fond, buffer,0,0,0,0,SCREEN_W, SCREEN_H);
        if(mouse_b&1 && possibilite_deplacement(tabcases, mouse_x, mouse_y, tabjoueur, indice)==1)
        {
            // faire un do while(oldmouse_y/50 -6 < mouse_y/50 < oldmouse_y +6 || oldmouse_x -6 < mouse_x - 6 < oldmouse_x +6);

            tabjoueur[indice]->classes.cord_x = tabcases[mouse_y/50][mouse_x/50].x;
            tabjoueur[indice]->classes.cord_y = tabcases[mouse_y/50][mouse_x/50].y;
            validation = 1;
        }
        if(validation == 1)
        {
            draw_sprite(buffer, personnage, tabjoueur[indice]->classes.cord_x, tabjoueur[indice]->classes.cord_y-50);
            done = 1;
        }
        blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
        if(mouse_b&1 && possibilite_deplacement(tabcases, mouse_x, mouse_y, tabjoueur, indice)==1)
        {
            tabjoueur[indice]->classes.cord_x = tabcases[mouse_y/50][mouse_x/50].x;
            tabjoueur[indice]->classes.cord_y= tabcases[mouse_y/50][mouse_x/50].y;
            validation = 1;
        }
        if(validation == 1)
        {
            draw_sprite(buffer, personnage, tabjoueur[indice]->classes.cord_x, tabjoueur[indice]->classes.cord_y-50);
            done = 1;
        }
        clear_bitmap(buffer);
    }
    Sleep(1000);
    destroy_bitmap(fond);
    destroy_bitmap(personnage);
    destroy_bitmap(buffer);
}

void premier_placement(t_joueur** tabjoueur, int nbrjoueur)
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
        if(tabjoueur[i]->classes.PV == 70)
            personnage = load_bitmap("luffy standby.bmp", NULL);
        else if(tabjoueur[i]->classes.PV == 65)
            personnage = load_bitmap("robin standby.bmp", NULL);
        else if(tabjoueur[i]->classes.PV == 50)
            personnage = load_bitmap("sanji standby.bmp", NULL);
        else if(tabjoueur[i]->classes.PV == 100)
            personnage = load_bitmap("franky standby.bmp", NULL);
        time_t start, end;
        time(&start);
        while(done==0 && temps <=16)
        {
            if(mouse_b&1 && tabcases[mouse_y/50][mouse_x/50].obstacle == 0)
            {
                tabjoueur[i]->classes.cord_x = tabcases[mouse_y/50][mouse_x/50].x;
                tabjoueur[i]->classes.cord_y = tabcases[mouse_y/50][mouse_x/50].y;
                tabcases[mouse_y/50][mouse_x/50].obstacle = 1;
                validation = 1;
            }
            if(validation == 1)
            {
                draw_sprite(fond, personnage, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y-50);
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
                    tabjoueur[i]->classes.cord_x = tabcases[rand()%16][rand()%28].x;
                    tabjoueur[i]->classes.cord_y = tabcases[rand()%16][rand()%28].y;
                }
                while(tabcases[tabjoueur[i]->classes.cord_x/50][tabjoueur[i]->classes.cord_y/50].obstacle==1);
                validation = 1;
            }
        }
    }
    Sleep(1000);
    destroy_bitmap(personnage);
    destroy_bitmap(fond);
}
///(tabjoueur[indice]->classes.cord_x/50)- (tabjoueur[indice]->classes.PM/2) <= (X/50) && (X/50) <= (tabjoueur[indice]->classes.cord_x/50)- (tabjoueur[indice]->classes.PM/2) &&
int possibilite_deplacement(t_cases** tabcases,int X, int Y, t_joueur** tabjoueur, int indice)
{
    if(tabcases[Y/50][X/50].obstacle == 0)
    {
        if(tabjoueur[indice]->classes.cord_x/50 == X/50)
        {
            if((tabjoueur[indice]->classes.cord_y/50) + tabjoueur[indice]->classes.PM >= Y/50 && Y/50 >= (tabjoueur[indice]->classes.cord_y/50) - tabjoueur[indice]->classes.PM)
            {
                printf("Possible\n");
                return 1;
            }
            else
            {
                printf("Impossible\n");
                return 0;
            }
        }
        else if(tabjoueur[indice]->classes.cord_y/50 == Y/50 )
        {
            if( (tabjoueur[indice]->classes.cord_x/50) + tabjoueur[indice]->classes.PM >= X/50 && X/50 >= (tabjoueur[indice]->classes.cord_x/50) - tabjoueur[indice]->classes.PM)
            {
                printf("Possible\n");
                return 1;
            }
            else
            {
                printf("Impossible\n");
                return 0;
            }
        }
        else if((((tabjoueur[indice]->classes.cord_x/50) + (tabjoueur[indice]->classes.cord_y/50)) - tabjoueur[indice]->classes.PM <= (X/50)+(Y/50) && (X/50)+(Y/50) <=  ((tabjoueur[indice]->classes.cord_x/50)+ (tabjoueur[indice]->classes.cord_y/50)) + tabjoueur[indice]->classes.PM) && (((tabjoueur[indice]->classes.cord_x/50) - (tabjoueur[indice]->classes.PM/2)) <= X/50 && ((tabjoueur[indice]->classes.cord_y/50) + (tabjoueur[indice]->classes.PM/2)) >= Y/50) && (((tabjoueur[indice]->classes.cord_x/50) + (tabjoueur[indice]->classes.PM/2)) >= X/50 && ((tabjoueur[indice]->classes.cord_y/50) - (tabjoueur[indice]->classes.PM/2)) <= Y/50))
        {
            printf("Possible\n");
            return 1;
        }
        else
        {
            printf("Impossible\n");
            return 0;
        }
    }
    else
    {
        printf("Impossible\n");
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

///Calcul de l'itineraire (pas encore tester mais logiquement fonctionnel)
t_cases* itineraire(t_cases** tabcases, t_joueur** tabjoueur, int indice, int finishx, int finishy)
{
    t_cases* chemin = (t_cases*)malloc(tabjoueur[indice]->classes.PM * sizeof(t_cases));
    t_cases* tampon = (t_cases*)malloc(tabjoueur[indice]->classes.PM * sizeof(t_cases));
    int maxChemin = tabjoueur[indice]->classes.PM;
    int X = tabjoueur[indice]->classes.cord_x;
    int Y = tabjoueur[indice]->classes.cord_y;
    int alea = 0;
    int comp = 0;
    int oldcomp = 0;
    for(int i = 0; i<100; i++)
    {
        while(comp < maxChemin)
        {
            if(X == finishx && Y == finishy)
            {
                if(comp <= oldcomp)
                    chemin = tampon;
            }
            else
            {
                alea = rand()%4 + 1;
                if(alea == 1 && tabcases[(Y/50)-1][X/50].obstacle == 0)
                {
                    Y = (Y/50)-1;
                    tampon[comp].x = X;
                    tampon[comp].y = Y;
                    comp +=1;
                }
                if(alea == 2 && tabcases[Y/50][(X/50)+1].obstacle == 0)
                {
                    X = (X/50)+1;
                    tampon[comp].x = X;
                    tampon[comp].y = Y;
                    comp +=1;
                }
                if(alea == 3 && tabcases[(Y/50)+1][X/50].obstacle == 0)
                {
                    Y = (Y/50)+1;
                    tampon[comp].x = X;
                    tampon[comp].y = Y;
                    comp +=1;
                }
                if(alea == 2 && tabcases[Y/50][(X/50)-1].obstacle == 0)
                {
                    X = (X/50)-1;
                    tampon[comp].x = X;
                    tampon[comp].y = Y;
                    comp +=1;
                }
            }
        }
    }
    tampon = NULL;
    free(tampon);
    return chemin;
}
