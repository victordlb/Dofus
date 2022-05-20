#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "header.h"

void combat(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* fond)
{
    afficherSort(tabjoueur, indice, fond);
    int done = 0;
    int done2 =0;
    BITMAP* select = load_bitmap("documents/props/css.bmp", NULL);
    while(done == 0)
    {
        if(mouse_b&1)
        {
            if(mouse_x>502 && mouse_x<572 && mouse_y>737 && mouse_y<800)
            {
                draw_sprite(fond, select, 495, 730);
                porteSort(tabcases, tabjoueur, indice, 0, fond);
                blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                while(done2 == 0)
                {
                    done2 = lancerattaque(tabcases,tabjoueur,indice,nbrjoueur,0);
                }
                done = 1;
            }
            if(mouse_x>577 && mouse_x<647 && mouse_y>737 && mouse_y<800)
            {
                draw_sprite(fond, select, 495 + (1*75), 730);
                porteSort(tabcases, tabjoueur, indice, 1, fond);
                blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                while(done2 == 0)
                {
                    done2 = lancerattaque(tabcases,tabjoueur,indice,nbrjoueur,1);
                }
                done = 1;
            }
            if(mouse_x>652 && mouse_x<722 && mouse_y>737 && mouse_y<800)
            {
                draw_sprite(fond, select, 495 + (2*75), 730);
                porteSort(tabcases, tabjoueur, indice, 2, fond);
                blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                while(done2 == 0)
                {
                    done2 = lancerattaque(tabcases,tabjoueur,indice,nbrjoueur,2);
                }
                done = 1;
            }
            if(mouse_x>727 && mouse_x<797 && mouse_y>737 && mouse_y<800)
            {
                draw_sprite(fond, select, 495 + (3*75), 730);
                porteSort(tabcases, tabjoueur, indice, 3, fond);
                blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                while(done2 == 0)
                {
                    done2 = lancerattaque(tabcases,tabjoueur,indice,nbrjoueur,3);
                }
                done = 1;
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
    if(tabjoueur[indice]->classes.mesattaques[numsort].type == 1)
    {
        dessinportecroix(tabjoueur,tabcases,indice,numsort,fond);
    }
    else if(tabjoueur[indice]->classes.mesattaques[numsort].type == 2 || tabjoueur[indice]->classes.mesattaques[numsort].type == 3)
    {
        dessinportecercle(tabjoueur,tabcases,indice,numsort,fond);
    }
}

void dessinportecroix(t_joueur** tabjoueur, t_cases** tabcases, int indice,int numsort, BITMAP* fond)
{
    for(int i = 0; i<16; i++)
    {
        for(int j=0; j<28; j++)
        {
            if(possibcroix(tabcases, tabcases[i][j].x, tabcases[i][j].y, tabjoueur, indice, numsort) == 1)
            {
                if(tabcases[i][j].x != tabjoueur[indice]->classes.cord_x || tabcases[i][j].y != tabjoueur[indice]->classes.cord_y)
                {
                    rectfill(fond, tabcases[i][j].x+5, tabcases[i][j].y+5, tabcases[i][j].x+45,tabcases[i][j].y+45, makecol(50,130,246));
                }
            }
        }
    }
}

void dessinportecercle(t_joueur** tabjoueur, t_cases** tabcases, int indice,int numsort, BITMAP* fond)
{
    for(int i = 0; i<16; i++)
    {
        for(int j=0; j<28; j++)
        {
            if(possibcercle(tabjoueur,tabcases[i][j].x, tabcases[i][j].y, tabcases, indice, numsort) == 1)
            {
                if(tabcases[i][j].x != tabjoueur[indice]->classes.cord_x || tabcases[i][j].y != tabjoueur[indice]->classes.cord_y)
                {
                    rectfill(fond, tabcases[i][j].x+5, tabcases[i][j].y+5, tabcases[i][j].x+45,tabcases[i][j].y+45, makecol(50,130,246));
                }
            }
        }
    }
}

int possibcroix(t_cases** tabcases,int X, int Y, t_joueur** tabjoueur, int indice, int numsort)
{
    int Ycase = tabcases[Y/50][X/50].y/50;
    int Xcase = tabcases[Y/50][X/50].x/50;
    int Yjoueur = tabjoueur[indice]->classes.cord_y/50;
    int Xjoueur = tabjoueur[indice]->classes.cord_x/50;
    if(tabcases[Y/50][X/50].obstacle == 0)
    {
        if((Xcase == Xjoueur && Ycase == Yjoueur-1) || (Xcase == Xjoueur-1 && Ycase == Yjoueur) ||(Xcase == Xjoueur && Ycase == Yjoueur+1)||(Xcase == Xjoueur+1 && Ycase == Yjoueur))
        {
            return 0;
        }
        else
        {
            if(Xcase > (Xjoueur)-tabjoueur[indice]->classes.mesattaques[numsort].porte && Xcase < (Xjoueur)+tabjoueur[indice]->classes.mesattaques[numsort].porte && Ycase == Yjoueur)
            {
                return 1;
            }
            else if(Ycase > (Yjoueur)-tabjoueur[indice]->classes.mesattaques[numsort].porte && Ycase < (Yjoueur)+tabjoueur[indice]->classes.mesattaques[numsort].porte && Xcase == Xjoueur)
            {
                return 1;
            }
            else
                return 0;
        }
    }
    else
        return 0;
}

int possibcercle(t_joueur** tabjoueur,int X, int Y, t_cases** tabcases, int indice,int numsort)
{
    int Ycase = tabcases[Y/50][X/50].y/50;
    int Xcase = tabcases[Y/50][X/50].x/50;
    int Yjoueur = tabjoueur[indice]->classes.cord_y/50;
    int Xjoueur = tabjoueur[indice]->classes.cord_x/50;
    if(tabcases[Y/50][X/50].obstacle == 0)
    {
        if((Xcase == Xjoueur-1 && Ycase == Yjoueur-1) || (Xcase == Xjoueur && Ycase == Yjoueur-1) || (Xcase == Xjoueur+1 && Ycase == Yjoueur-1) || (Xcase == Xjoueur-1 && Ycase == Yjoueur) || (Xcase == Xjoueur && Ycase == Yjoueur) || (Xcase == Xjoueur+1 && Ycase == Yjoueur) || (Xcase == Xjoueur-1 && Ycase == Yjoueur+1)||(Xcase == Xjoueur && Ycase == Yjoueur+1)||(Xcase == Xjoueur+1 && Ycase == Yjoueur+1))
        {
            return 0;
        }
        else
        {
            if(Xcase > (Xjoueur)-tabjoueur[indice]->classes.mesattaques[numsort].porte && Xcase < (Xjoueur)+tabjoueur[indice]->classes.mesattaques[numsort].porte && Ycase > (Yjoueur)-tabjoueur[indice]->classes.mesattaques[numsort].porte && Ycase < (Yjoueur)+tabjoueur[indice]->classes.mesattaques[numsort].porte)
            {
                return 1;
            }
            else
                return 0;
        }
    }
    else
        return 0;
}

int lancerattaque(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, int numsort)
{
    if(mouse_b&1)
    {
        if(tabjoueur[indice]->classes.mesattaques[numsort].type == 1)
        {
            if(possibcroix(tabcases,mouse_x, mouse_y,tabjoueur,indice,numsort) == 1)
            {
                if(tabjoueur[indice]->classes.PA >= tabjoueur[indice]->classes.mesattaques[numsort].consequence_PA)
                {
                    for(int i = 0; i<nbrjoueur; i++)
                    {
                        if(tabjoueur[i]->classes.cord_x/50 == mouse_x/50 && tabjoueur[i]->classes.cord_y/50 == mouse_y/50)
                        {
                            if(rand()%tabjoueur[indice]->classes.mesattaques[numsort].modulo_echec != 5)
                            {
                                tabjoueur[i]->classes.PV -= tabjoueur[indice]->classes.mesattaques[numsort].degats;
                                if(tabjoueur[i]->classes.PV <=0)
                                {
                                    tabjoueur[i]->perdu = 1;
                                }
                                return 1;
                            }
                            else
                            {
                                printf("raté");
                                return 1;
                            }
                        }
                        else
                        {
                            printf("Personne n'est sur cette case");
                            return 1;
                        }
                    }
                }
                else
                {
                    printf("pas assez de PA");
                    return 1;
                }
            }
            else
                return 0;
        }
        else
        {
            if(possibcercle(tabjoueur,mouse_x, mouse_y,tabcases,indice,numsort) == 1)
            {
                if(tabjoueur[indice]->classes.PA >= tabjoueur[indice]->classes.mesattaques[numsort].consequence_PA)
                {
                    for(int i = 0; i<nbrjoueur; i++)
                    {
                        if(tabjoueur[i]->classes.cord_x/50 == mouse_x/50 && tabjoueur[i]->classes.cord_y/50 == mouse_y/50)
                        {
                            if(rand()%tabjoueur[indice]->classes.mesattaques[numsort].modulo_echec != 5)
                            {
                                tabjoueur[i]->classes.PV -= tabjoueur[indice]->classes.mesattaques[numsort].degats;
                                if(tabjoueur[i]->classes.PV <=0)
                                {
                                    tabjoueur[i]->perdu = 1;
                                }
                                return 1;
                            }
                            else
                            {
                                printf("raté");
                                return 1;
                            }
                        }
                        else
                        {
                            printf("Personne n'est sur cette case");
                            return 1;
                        }
                    }
                }
                else
                {
                    printf("pas assez de PA");
                    return 1;
                }
            }
            else
                return 0;
        }
        return 0;
    }
    else
        return 0;
}



