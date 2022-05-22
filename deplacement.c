#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <synchapi.h>
#include "header.h"

/// fonction qui determine la 1ere position des joueurs
void premier_placement(t_joueur** tabjoueur, int nbrjoueur,int choix)
{
    BITMAP* fond ;
    t_cases** tabcases;
    tabcases = chargement_map(choix);
    BITMAP* personnage;
    float temps = 0;
    int validation = 0;
    int done = 0;
    int defx;
    int defy;
    for(int i=0; i<nbrjoueur; i++)
    {
        fond = charger_map(tabcases,choix);
        chargement_perso(tabjoueur,i,nbrjoueur,fond,0);
        if(choix == 1)
        {
            dessin_haut_arbre(fond, tabcases);
        }
        temps = 0;
        textprintf_ex(fond, font, 500,20,makecol(0,0,0), -1, "CHOISISSEZ VOTRE POSITION DE DEPART (vous avez 15secondes)");
        done = 0;
        validation = 0;
        if(strcmp(tabjoueur[i]->classes.nom, "luffy")==0)
        {
            personnage = load_bitmap("documents/perso/luffy/luffy standby.bmp", NULL);
            if(choix == 1)
            {
                defx = 10;
                defy = 6;
            }
            else if(choix == 2)
            {
                defx = 4;
                defy = 12;
            }
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
            if(choix == 1)
            {
                defx = 16;
                defy = 3;
            }
            else if(choix == 2)
            {
                defx = 22;
                defy = 2;
            }
        }
        else if(strcmp(tabjoueur[i]->classes.nom, "franky") == 0)
        {
            personnage = load_bitmap("documents/perso/franky/franky standby.bmp", NULL);
            if(choix == 1)
            {
                defx = 14;
                defy = 12;
            }
            else if(choix == 2)
            {
                defx = 12;
                defy = 12;
            }
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
                if(choix == 1)
                {
                    dessin_haut_arbre(fond, tabcases);
                }
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

/// fonction appelé lorsque un joueur veut se deplacer, il pourra le faire ici
void deplacement(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* fond,int choix)
{
    //t_cases** tabcases;
    t_chemin* Lechemin;
    //tabcases = chargement_map();
    // BITMAP* fond;
    BITMAP* croix;
    croix = load_bitmap("documents/props/logo croix.bmp", NULL);
    BITMAP* personnage;
    BITMAP* buffer;
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if(strcmp(tabjoueur[indice]->classes.nom, "luffy")==0)
    {
        personnage = load_bitmap("documents/perso/luffy/luffy standby.bmp", NULL);
    }
    else if(strcmp(tabjoueur[indice]->classes.nom, "robin")==0)
    {
        personnage = load_bitmap("documents/perso/robin/robin standby.bmp", NULL);
    }
    else if(strcmp(tabjoueur[indice]->classes.nom,"sanji") == 0)
    {
        personnage = load_bitmap("documents/perso/sanji/sanji standby.bmp", NULL);
    }
    else if(strcmp(tabjoueur[indice]->classes.nom, "franky") == 0)
    {
        personnage = load_bitmap("documents/perso/franky/franky standby.bmp", NULL);
    }
    clear_bitmap(fond);
    fond = chargement_fond(tabcases, choix);
    int done = 0;
    int ind = 2;
    int val = 0;
    int cord_x;
    int cord_y;
    int etat;
    while(done == 0)
    {
        ///ici pour la map
        blit(fond, buffer,0,0,0,0,SCREEN_W, SCREEN_H);
        couleur_case_bis(tabjoueur,tabcases,indice,buffer);
        chargement_perso(tabjoueur,indice,nbrjoueur,buffer,0);
        if(choix == 1)
        {
            dessin_haut_arbre(buffer,tabcases);
        }
        draw_sprite(buffer, croix, 1270,740);
        if(mouse_b&1)
        {
            if(mouse_x > 1270 && mouse_x < 1300 && mouse_y > 740 && mouse_y < 770)
            {
                clear_bitmap(buffer);
                clear_bitmap(fond);
                fond = chargement_fond(tabcases, choix);
                blit(fond, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
                chargement_perso(tabjoueur,indice,nbrjoueur,buffer,0);
                if(choix == 1)
                {
                    dessin_haut_arbre(buffer,tabcases);
                }
                blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                done = 3;
            }
            if(possibilite_deplacement_bis(tabjoueur, tabcases,indice,mouse_x, mouse_y)==1)
            {
                cord_x = mouse_x;
                cord_y = mouse_y;
                Lechemin = djikstra(tabcases,tabjoueur[indice]->classes.cord_x/50, tabjoueur[indice]->classes.cord_y/50, mouse_x/50, mouse_y/50);
                if(Lechemin[0].taille == 1)
                {
                    val = 1;
                }
                tabjoueur[indice]->classes.PM = tabjoueur[indice]->classes.PM - Lechemin[0].taille;
                while(ind <= Lechemin[0].taille)
                {

                    tabjoueur[indice]->classes.cord_x = Lechemin[ind].x*50;
                    tabjoueur[indice]->classes.cord_y = Lechemin[ind].y*50;
                    clear_bitmap(buffer);
                    clear_bitmap(fond);
                    fond = chargement_fond(tabcases, choix);
                    blit(fond, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
                    if(Lechemin[ind+1].x == Lechemin[ind].x +1)
                    {
                        etat = 2;
                    }
                    if(Lechemin[ind+1].x == Lechemin[ind].x -1)
                    {
                        etat = 3;
                    }
                    if(Lechemin[ind+1].y == Lechemin[ind].y +1 || Lechemin[ind+1].y == Lechemin[ind].y -1)
                    {
                        etat = 1;
                    }
                    chargement_perso(tabjoueur,indice,nbrjoueur,buffer, etat);
                    if(choix == 1)
                    {
                        dessin_haut_arbre(buffer,tabcases);
                    }
                    blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    Sleep(500);
                    done = 1;
                    val = 1;
                    ind += 1;
                }
                if(val == 1)
                {
                    tabjoueur[indice]->classes.cord_x = tabcases[cord_y/50][cord_x/50].x;
                    tabjoueur[indice]->classes.cord_y = tabcases[cord_y/50][cord_x/50].y;
                    clear_bitmap(buffer);
                    clear_bitmap(fond);
                    fond = chargement_fond(tabcases, choix);
                    blit(fond, buffer, 0,0,0,0,SCREEN_W, SCREEN_H);
                    chargement_perso(tabjoueur,indice,nbrjoueur,buffer, 0);
                    if(choix == 1)
                    {
                        dessin_haut_arbre(buffer,tabcases);
                    }
                    blit(buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    Sleep(500);
                    done = 1;
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
    destroy_bitmap(croix);
}

/// fonction qui teste si le deplacement est possible à l'endroit ou le joueur a cliquer
int possibilite_deplacement_bis(t_joueur** tabjoueur, t_cases** tabcases, int indice, int X, int Y)
{
    t_chemin* Unchemin;
    if(tabcases[Y/50][X/50].obstacle == 0)
    {
        Unchemin = djikstra(tabcases,tabjoueur[indice]->classes.cord_x/50, tabjoueur[indice]->classes.cord_y/50, X/50, Y/50);
        if(Unchemin[0].taille <= tabjoueur[indice]->classes.PM)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

/// fonction qui parcours tout le tableau de case et colorie en vert les cases ou le deplacement est possible
void couleur_case_bis(t_joueur** tabjoueur, t_cases** tabcases, int indice, BITMAP* fond)
{
    t_chemin* Lechemin;
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<28; j++)
        {
            if(tabcases[i][j].obstacle == 0)
            {
                Lechemin = djikstra(tabcases,tabjoueur[indice]->classes.cord_x/50, tabjoueur[indice]->classes.cord_y/50,j,i);
                if(Lechemin[0].taille <= tabjoueur[indice]->classes.PM)
                {
                    if(tabcases[i][j].x != tabjoueur[indice]->classes.cord_x || tabcases[i][j].y != tabjoueur[indice]->classes.cord_y)
                    {
                        rectfill(fond, tabcases[i][j].x+5, tabcases[i][j].y+5, tabcases[i][j].x+45,tabcases[i][j].y+45, makecol(38,200,94));
                    }
                }
            }
            else
            {
                continue;
            }
        }
    }
}

/// théoreme des graphes/de djikstra qui determine le chemin le plus court pour aller d'un point A à un point B
t_chemin* djikstra(t_cases** tabcases, int pos_col_pers,int pos_lig_pers, int arrivee_col, int arrivee_lig)
{
    int pos_col_actuelle=pos_col_pers,pos_lig_actuelle=pos_lig_pers;
    int distance[16][28];
    int verif[16][28];
    int predecesseur_col[16][28],predecesseur_lig[16][28];
    //int arrivee_col, arrivee_lig;
    int new_col,new_lig;
    t_chemin* monchemin;


    for(int i=0; i<16; i++)
    {
        for(int j=0; j<28; j++)
        {
            distance[i][j]=1000;
            verif[i][j]=0;//non gris
            predecesseur_col[i][j]=-1;
            predecesseur_lig[i][j]=-1;
        }
    }
    distance[pos_lig_pers][pos_col_pers]=0;
    predecesseur_col[pos_lig_pers][pos_col_pers]=-2;
    predecesseur_lig[pos_lig_pers][pos_col_pers]=-2;
    verif[pos_lig_pers][pos_col_pers]=1;

    do
    {

        //predecesseur en haut
        if(pos_lig_actuelle-1 >= 0)//depassement tab
        {

            if(tabcases[pos_lig_actuelle-1][pos_col_actuelle].obstacle==0)//obstacle ?
            {

                if(distance[pos_lig_actuelle-1][pos_col_actuelle]>distance[pos_lig_actuelle][pos_col_actuelle]+1)//meilleur chemin ?
                {
                    //si oui

                    distance[pos_lig_actuelle-1][pos_col_actuelle]=distance[pos_lig_actuelle][pos_col_actuelle]+1;
                    predecesseur_col[pos_lig_actuelle-1][pos_col_actuelle]=pos_col_actuelle;
                    predecesseur_lig[pos_lig_actuelle-1][pos_col_actuelle]=pos_lig_actuelle;
                }
            }
        }

        //predecesseur a gauche
        if(pos_col_actuelle-1 >=0)//depassement tab
        {
            if(tabcases[pos_lig_actuelle][pos_col_actuelle-1].obstacle==0)//obstacle ?
            {
                if(distance[pos_lig_actuelle][pos_col_actuelle-1]>distance[pos_lig_actuelle][pos_col_actuelle]+1)//meilleur chemin ?
                {
                    //si oui
                    distance[pos_lig_actuelle][pos_col_actuelle-1]=distance[pos_lig_actuelle][pos_col_actuelle]+1;
                    predecesseur_col[pos_lig_actuelle][pos_col_actuelle-1]=pos_col_actuelle;
                    predecesseur_lig[pos_lig_actuelle][pos_col_actuelle-1]=pos_lig_actuelle;
                }
            }
        }


        //predecesseur en bas
        if(pos_lig_actuelle+1 < 16)//depassement tab
        {
            if(tabcases[pos_lig_actuelle+1][pos_col_actuelle].obstacle==0)//obstacle ?
            {
                if(distance[pos_lig_actuelle+1][pos_col_actuelle]>distance[pos_lig_actuelle][pos_col_actuelle]+1)//meilleur chemin ?
                {
                    //si oui
                    distance[pos_lig_actuelle+1][pos_col_actuelle]=distance[pos_lig_actuelle][pos_col_actuelle]+1;
                    predecesseur_col[pos_lig_actuelle+1][pos_col_actuelle]=pos_col_actuelle;
                    predecesseur_lig[pos_lig_actuelle+1][pos_col_actuelle]=pos_lig_actuelle;
                }
            }
        }


        //predecesseur a droite
        if(pos_col_actuelle+1 < 28)//depassement tab
        {
            if(tabcases[pos_lig_actuelle][pos_col_actuelle+1].obstacle==0)//obstacle ?
            {
                if(distance[pos_lig_actuelle][pos_col_actuelle+1]>distance[pos_lig_actuelle][pos_col_actuelle]+1)//meilleur chemin ?
                {
                    //si oui
                    distance[pos_lig_actuelle][pos_col_actuelle+1]=distance[pos_lig_actuelle][pos_col_actuelle]+1;
                    predecesseur_col[pos_lig_actuelle][pos_col_actuelle+1]=pos_col_actuelle;
                    predecesseur_lig[pos_lig_actuelle][pos_col_actuelle+1]=pos_lig_actuelle;
                }
            }
        }

        int minimum=1000;
        int indice_min_col,indice_min_lig;
        for(int i=0; i<16; i++)
        {
            for(int j=0; j<28; j++)
            {
                if(verif[i][j]==0)
                {
                    if(minimum>distance[i][j])
                    {
                        minimum=distance[i][j];
                        indice_min_col=j;
                        indice_min_lig=i;
                    }
                }

            }
        }

        verif[indice_min_lig][indice_min_col]=1;
        pos_lig_actuelle=indice_min_lig;
        pos_col_actuelle=indice_min_col;
    }
    while(verif[arrivee_lig][arrivee_col]==0);
    monchemin = (t_chemin*)malloc(sizeof(t_chemin)*1000 );
    monchemin[0].taille = distance[arrivee_lig][arrivee_col];
    int indice = distance[arrivee_lig][arrivee_col];
    new_col=predecesseur_col[arrivee_lig][arrivee_col];
    int tampon = 0;
    new_lig=predecesseur_lig[arrivee_lig][arrivee_col];
    while(new_col!=-2 && new_lig != -2)
    {
        tampon = new_col;
        monchemin[indice].x = new_col;
        monchemin[indice].y = new_lig;
        new_col = predecesseur_col[new_lig][new_col];
        new_lig = predecesseur_lig[new_lig][tampon];
        indice--;
    }

    return monchemin;
}

/// ANCIENNE FONCTION NON-UTILISE DANS LE CODE FINAL


/// test si le deplacement est possible a l'endroit ou le joueur a cliquer
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

/// colorisation des cases a l'endroit ou le deplacement est possible
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
