#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <synchapi.h>
#include "header.h"

void premier_placement(t_joueur** tabjoueur, int nbrjoueur)
{
    BITMAP* fond ;
    t_cases** tabcases;
    tabcases = chargement_map();
    BITMAP* personnage;
    float temps = 0;
    int validation = 0;
    int done = 0;
    int defx;
    int defy;
    for(int i=0; i<nbrjoueur; i++)
    {
        fond = charger_map(tabcases);
        chargement_perso(tabjoueur,i,nbrjoueur,fond);
        dessin_haut_arbre(fond, tabcases);
        temps = 0;
        textprintf_ex(fond, font, 500,20,makecol(0,0,0), -1, "CHOISISSEZ VOTRE POSITION DE DEPART (vous avez 15secondes)");
        done = 0;
        validation = 0;
        if(strcmp(tabjoueur[i]->classes.nom, "luffy")==0)
        {
            personnage = load_bitmap("documents/perso/luffy/luffy standby.bmp", NULL);
            defx = 10;
            defy = 6;
        }
        else if(strcmp(tabjoueur[i]->classes.nom, "robin")==0)
        {
            personnage = load_bitmap("documents/perso/robin/robin standby.bmp", NULL);
            defx = 18;
            defy = 8;
        }
        else if(strcmp(tabjoueur[i]->classes.nom,"sanji") == 0)
        {
            personnage = load_bitmap("documents/perso/sanji/sanji standby.bmp", NULL);
            defx = 16;
            defy = 3;
        }
        else if(strcmp(tabjoueur[i]->classes.nom, "franky") == 0)
        {
            personnage = load_bitmap("documents/perso/franky/franky standby.bmp", NULL);
            defx = 14;
            defy = 12;
        }
        time_t start, end;
        time(&start);
        while(done==0)
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
                dessin_haut_arbre(fond, tabcases);
                Sleep(500);
                done = 1;
            }
            blit(fond, screen,0,0,0,0,SCREEN_W,SCREEN_H);
            time(&end);
            temps = difftime(end, start);
            compte_temps(temps,fond);
            if(temps > 15)
            {
                tabjoueur[i]->classes.cord_x = tabcases[defy][defx].x;
                tabjoueur[i]->classes.cord_y = tabcases[defy][defx].y;
                validation = 1;
            }
        }
        clear_bitmap(fond);
    }
    Sleep(1000);
    destroy_bitmap(personnage);
    destroy_bitmap(fond);
}

void deplacement(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* fond)
{
    //t_cases** tabcases;
    t_chemin* Lechemin;
    //tabcases = chargement_map();
    // BITMAP* fond;
    BITMAP* personnage;
    BITMAP* buffer;
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if(strcmp(tabjoueur[indice]->classes.nom, "luffy")==0)
        personnage = load_bitmap("documents/perso/luffy/luffy standby.bmp", NULL);
    else if(strcmp(tabjoueur[indice]->classes.nom, "robin")==0)
        personnage = load_bitmap("documents/perso/robin/robin standby.bmp", NULL);
    else if(strcmp(tabjoueur[indice]->classes.nom,"sanji") == 0)
        personnage = load_bitmap("documents/perso/sanji/sanji standby.bmp", NULL);
    else if(strcmp(tabjoueur[indice]->classes.nom, "franky") == 0)
        personnage = load_bitmap("documents/perso/franky/franky standby.bmp", NULL);
    clear_bitmap(fond);
    fond = chargement_fond(tabcases);
    int done = 0;
    int ind = 0;
    // djikstra(tabcases,tabjoueur[indice]->classes.cord_x/50, tabjoueur[indice]->classes.cord_y/50);
    while(done == 0)
    {
        ///ici pour la map
        blit(fond, buffer,0,0,0,0,SCREEN_W, SCREEN_H);
        couleur_case(tabjoueur,tabcases,indice,buffer);
        chargement_perso(tabjoueur,indice,nbrjoueur,buffer);
        dessin_haut_arbre(buffer,tabcases);
        if(mouse_b&1)
        {
            if(possibilite_deplacement(tabcases, mouse_x, mouse_y, tabjoueur, indice)==1)
            {
                Lechemin = itineraire(tabcases,tabjoueur,indice,mouse_x, mouse_y);
                for(int i = 0; i<Lechemin[0].taille; i++)
                {
                    printf("coordonne :%d/%d\n", Lechemin[i].x, Lechemin[i].y);
                }
                while(ind < Lechemin[0].taille)
                {
                    tabjoueur[indice]->classes.cord_x = Lechemin[ind].x*50;
                    tabjoueur[indice]->classes.cord_y = Lechemin[ind].y*50;
                    clear_bitmap(buffer);
                    clear_bitmap(fond);
                    fond = chargement_fond(tabcases);
                    blit(fond, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
                    chargement_perso(tabjoueur,indice,nbrjoueur,buffer);
                    dessin_haut_arbre(buffer,tabcases);
                    draw_sprite(buffer, personnage, tabjoueur[indice]->classes.cord_x, tabjoueur[indice]->classes.cord_y-50);
                    dessin_haut_arbre(buffer,tabcases);
                    blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    Sleep(500);
                    done = 1;
                    ind += 1;
                }
            }
        }
        blit(buffer, screen,0,0,0,0,SCREEN_W, SCREEN_H);
        clear_bitmap(buffer);
    }
    Sleep(1000);
    destroy_bitmap(fond);
    destroy_bitmap(personnage);
    destroy_bitmap(buffer);
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

void couleur_case(t_joueur** tabjoueur, t_cases** tabcases, int indice, BITMAP* fond)
{
    t_chemin* Lechemin;
    for(int i = 0; i<16; i++)
    {
        for(int j=0; j<28; j++)
        {
            Lechemin = itineraire(tabcases,tabjoueur,indice, j*50, i*50);
            for(int z = 0; z< Lechemin[0].taille ; z++)
            {
                if(Lechemin[z].x == tabcases[i][j].x/50 && Lechemin[z].y == tabcases[i][j].y/50)
                {
                    if(possibilite_deplacement(tabcases, tabcases[i][j].x, tabcases[i][j].y,tabjoueur,indice)==1)
                    {
                        if(tabcases[i][j].x != tabjoueur[indice]->classes.cord_x || tabcases[i][j].y != tabjoueur[indice]->classes.cord_y)
                        {
                            if(tabcases[i][j].cases == 5)
                            {
                                hline(fond, tabcases[i][j].x, tabcases[i][j].y-2,tabcases[i][j].x+50, makecol(38,200,94));
                                hline(fond, tabcases[i][j].x, tabcases[i][j].y-1,tabcases[i][j].x+50, makecol(38,200,94));
                                hline(fond, tabcases[i][j].x, tabcases[i][j].y,tabcases[i][j].x+50, makecol(38,200,94));
                                vline(fond, tabcases[i][j].x, tabcases[i][j].y, tabcases[i][j].y+50, makecol(38,200,94));
                                vline(fond, tabcases[i][j].x+1, tabcases[i][j].y, tabcases[i][j].y+50, makecol(38,200,94));
                                vline(fond, tabcases[i][j].x-1, tabcases[i][j].y, tabcases[i][j].y+50, makecol(38,200,94));
                                vline(fond, tabcases[i][j].x+2, tabcases[i][j].y, tabcases[i][j].y+50, makecol(38,200,94));
                                vline(fond, tabcases[i][j].x+3, tabcases[i][j].y, tabcases[i][j].y+50, makecol(38,200,94));
                                vline(fond, tabcases[i][j].x+50, tabcases[i][j].y, tabcases[i][j].y+50, makecol(38,200,94));
                                vline(fond, tabcases[i][j].x+51, tabcases[i][j].y, tabcases[i][j].y+50, makecol(38,200,94));
                                vline(fond, tabcases[i][j].x+49, tabcases[i][j].y, tabcases[i][j].y+50, makecol(38,200,94));
                                vline(fond, tabcases[i][j].x+48, tabcases[i][j].y, tabcases[i][j].y+50, makecol(38,200,94));
                                vline(fond, tabcases[i][j].x+47, tabcases[i][j].y, tabcases[i][j].y+50, makecol(38,200,94));
                            }
                            else
                            {
                                rectfill(fond, tabcases[i][j].x+5, tabcases[i][j].y+5, tabcases[i][j].x+45,tabcases[i][j].y+45, makecol(38,200,94));
                            }
                        }
                    }
                }
            }
        }
    }
}

///Calcul de l'itineraire (pas encore tester mais logiquement fonctionnel)
t_chemin* itineraire(t_cases** tabcases, t_joueur** tabjoueur, int indice, int finishx, int finishy)
{
    t_chemin* Lechemin = (t_chemin*)malloc(tabjoueur[indice]->classes.PM * sizeof(t_chemin));
    int X = tabjoueur[indice]->classes.cord_x/50;
    int Y = tabjoueur[indice]->classes.cord_y/50;
    int maxPM = tabjoueur[indice]->classes.PM;
    int comp = 0;
    int stop = 0;
    int obst = 0;
    int obst2 = 0;
    while(stop != 1)
    {
        if((X == finishx/50 && Y == finishy/50) || comp == maxPM)
        {
            stop = 1;
        }
        else
        {
            if((X < finishx/50 && obst == 0) || obst2 == 1)
            {
                if(tabcases[Y][X+1].obstacle == 0)
                {
                    X += 1;
                    obst2 = 0;
                    Lechemin[comp].x = X;
                    Lechemin[comp].y = Y;
                    comp += 1;
                }
                else
                    obst = 1;
            }
            else if(X > finishx/50 && obst == 0)
            {
                if(tabcases[Y][X-1].obstacle == 0)
                {
                    X -= 1;
                    obst2 = 0;
                    Lechemin[comp].x = X;
                    Lechemin[comp].y = Y;
                    comp += 1;
                }
                else
                    obst = 1;
            }
            else if(Y < finishy/50 || obst == 1)
            {
                if(tabcases[Y+1][X].obstacle == 0)
                {
                    Y += 1;
                    obst = 0;
                    Lechemin[comp].x = X;
                    Lechemin[comp].y = Y;
                    comp += 1;
                }
                else
                    obst2 = 1;
            }
            else if(Y > finishy/50 || obst == 1)
            {
                if(tabcases[Y-1][X].obstacle == 0)
                {
                    Y -= 1;
                    obst = 0;
                    Lechemin[comp].x = X;
                    Lechemin[comp].y = Y;
                    comp += 1;
                }
                else
                    obst2 = 1;
            }
        }
    }
    Lechemin[0].taille = comp;
    return Lechemin;
}

void djikstra(t_cases** tabcases, int pos_x_pers,int pos_y_pers)
{
    int pos_x_actuelle=pos_x_pers,pos_y_actuelle=pos_y_pers;
    int distance[16][28];
    int verif[16][28];
    int predecesseur_x[16][28],predecesseur_y[16][28];
    int arrivee_x, arrivee_y;
    int new_x,new_y;



    for(int i=0; i<16; i++)
    {
        for(int j=0; j<28; j++)
        {
            distance[i][j]=1000;
            verif[i][j]=0;//non gris
            predecesseur_x[i][j]=-1;
            predecesseur_y[i][j]=-1;
            printf("%d\n", tabcases[i][j].obstacle);
        }
    }
    printf("coord_x :%d / coord_y :%d\n",pos_y_actuelle,pos_x_actuelle);

    printf("Saisir le sommet d'arrivee en x\n");
    scanf("%d",&arrivee_x);

    printf("Saisir le sommet d'arrivee en y\n");
    scanf("%d",&arrivee_y);

    distance[pos_y_pers][pos_x_pers]=0;
    predecesseur_x[pos_y_pers][pos_x_pers]=-2;
    predecesseur_y[pos_y_pers][pos_x_pers]=-2;
    verif[pos_y_pers][pos_x_pers]=1;

    do
    {

        //predecesseur a gauche
        if(pos_y_actuelle-1!=-1)//depassement tab
        {

            if(tabcases[pos_y_actuelle-1][pos_x_actuelle].obstacle==0)//obstacle ?
            {

                if(distance[pos_y_actuelle-1][pos_x_actuelle]>distance[pos_y_actuelle][pos_x_actuelle]+1)//meilleur chemin ?
                {
                    //si oui

                    distance[pos_y_actuelle-1][pos_x_actuelle]=distance[pos_y_actuelle][pos_x_actuelle]+1;
                    predecesseur_x[pos_y_actuelle-1][pos_x_actuelle]=pos_x_actuelle;
                    predecesseur_y[pos_y_actuelle-1][pos_x_actuelle]=pos_y_actuelle;
                    printf("test1 \n");
                }
            }
        }

        //predecesseur en haut
        if(pos_x_actuelle-1!=-1)//depassement tab
        {
            if(tabcases[pos_y_actuelle][pos_x_actuelle-1].obstacle==0)//obstacle ?
            {
                if(distance[pos_y_actuelle][pos_x_actuelle-1]>distance[pos_y_actuelle][pos_x_actuelle]+1)//meilleur chemin ?
                {
                    //si oui
                    distance[pos_y_actuelle][pos_x_actuelle-1]=distance[pos_y_actuelle][pos_x_actuelle]+1;
                    predecesseur_x[pos_y_actuelle][pos_x_actuelle-1]=pos_x_actuelle;
                    predecesseur_y[pos_y_actuelle][pos_x_actuelle-1]=pos_y_actuelle;
                }
            }
        }


        //predecesseur a droite
        if(pos_y_actuelle+1!=16)//depassement tab
        {
            if(tabcases[pos_y_actuelle+1][pos_x_actuelle].obstacle==0)//obstacle ?
            {
                if(distance[pos_y_actuelle+1][pos_x_actuelle]>distance[pos_y_actuelle][pos_x_actuelle]+1)//meilleur chemin ?
                {
                    //si oui
                    distance[pos_y_actuelle+1][pos_x_actuelle]=distance[pos_y_actuelle][pos_x_actuelle]+1;
                    predecesseur_x[pos_y_actuelle+1][pos_x_actuelle]=pos_x_actuelle;
                    predecesseur_y[pos_y_actuelle+1][pos_x_actuelle]=pos_y_actuelle;
                }
            }
        }


        //predecesseur en bas
        if(pos_x_actuelle+1!=28)//depassement tab
        {
            if(tabcases[pos_y_actuelle][pos_x_actuelle+1].obstacle==0)//obstacle ?
            {
                if(distance[pos_y_actuelle][pos_x_actuelle+1]>distance[pos_y_actuelle][pos_x_actuelle]+1)//meilleur chemin ?
                {
                    //si oui
                    distance[pos_y_actuelle][pos_x_actuelle+1]=distance[pos_y_actuelle][pos_x_actuelle]+1;
                    predecesseur_x[pos_y_actuelle][pos_x_actuelle+1]=pos_x_actuelle;
                    predecesseur_y[pos_y_actuelle][pos_x_actuelle+1]=pos_y_actuelle;
                }
            }
        }



        int minimum=1000;
        int indice_min_x,indice_min_y;
        for(int i=0; i<16; i++)
        {
            for(int j=0; j<28; j++)
            {
                if(verif[i][j]==0)
                {
                    if(minimum>distance[i][j])
                    {
                        minimum=distance[i][j];
                        indice_min_x=i;
                        indice_min_y=j;
                    }
                }

            }
        }


        verif[indice_min_x][indice_min_y]=1;
        pos_y_actuelle=indice_min_x;
        pos_x_actuelle=indice_min_y;


    }
    while(verif[arrivee_y][arrivee_x]==0);
    printf("test2\n");

    tabcases[arrivee_x][arrivee_y];
    printf("%dx %dy|",predecesseur_x[arrivee_y][arrivee_x],predecesseur_y[arrivee_y][arrivee_x]);
    printf("test3\n");
    int compteur = 0;
    do
    {

        new_x=predecesseur_x[predecesseur_y[arrivee_y][arrivee_x]][predecesseur_x[arrivee_y][arrivee_x]];

        new_y=predecesseur_y[predecesseur_y[arrivee_y][arrivee_x]][predecesseur_x[arrivee_y][arrivee_x]];

        printf("%dx %dy poids %d|\n",new_x,new_y,distance[new_x][new_y]);
        compteur++;


    }
    while(new_x!=-2 && compteur != 10);


}
