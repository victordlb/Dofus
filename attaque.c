#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <synchapi.h>
#include <string.h>
#include "header.h"

void combat(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* fond, int choix)
{
    afficherSort(tabjoueur, indice, fond);
    BITMAP* buffer;
    BITMAP* croix;
    croix = load_bitmap("documents/props/logo croix.bmp", NULL);
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    draw_sprite(fond, croix, 1320, 740);
    blit(fond, screen,0,0,0,0,SCREEN_W, SCREEN_H);
    int done = 0;
    int done2 =0;
    BITMAP* select = load_bitmap("documents/props/css.bmp", NULL);
    while(done == 0)
    {
        if(mouse_b&1)
        {
            /// info sort
            if(mouse_y > 710 && mouse_y < 730)
            {
                if(mouse_x > 490 && mouse_x < 510)
                {
                    buffer = chargement_fond(tabcases,choix);
                    chargement_perso(tabjoueur,indice,nbrjoueur,buffer, 0);
                    afficherSort(tabjoueur, indice, buffer);
                    info_sort(tabjoueur,indice,1,buffer);
                    clear_bitmap(buffer);
                    blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    Sleep(500);
                }
                if(mouse_x > 565 && mouse_x < 585)
                {
                    buffer = chargement_fond(tabcases,choix);
                    chargement_perso(tabjoueur,indice,nbrjoueur,buffer,0);
                    afficherSort(tabjoueur, indice, buffer);
                    info_sort(tabjoueur, indice, 2, buffer);
                    clear_bitmap(buffer);
                    blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    Sleep(500);
                }
                if(mouse_x > 640 && mouse_x < 660)
                {
                    buffer = chargement_fond(tabcases,choix);
                    chargement_perso(tabjoueur,indice,nbrjoueur,buffer,0);
                    afficherSort(tabjoueur, indice, buffer);
                    info_sort(tabjoueur, indice, 3, buffer);
                    clear_bitmap(buffer);
                    blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    Sleep(500);
                }
                if(mouse_x > 715 && mouse_x < 735)
                {
                    buffer = chargement_fond(tabcases,choix);
                    chargement_perso(tabjoueur,indice,nbrjoueur,buffer,0);
                    afficherSort(tabjoueur, indice, buffer);
                    info_sort(tabjoueur, indice, 4, buffer);
                    clear_bitmap(buffer);
                    blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    Sleep(500);
                }
                if(mouse_x > 792 && mouse_x < 812)
                {
                    buffer = chargement_fond(tabcases,choix);
                    chargement_perso(tabjoueur,indice,nbrjoueur,buffer,0);
                    afficherSort(tabjoueur, indice, buffer);
                    info_sort(tabjoueur, indice, 5, buffer);
                    clear_bitmap(buffer);
                    blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    Sleep(500);
                }
                ///

            }
            if(mouse_x>502 && mouse_x<572 && mouse_y>737 && mouse_y<800)
            {
                if(tabjoueur[indice]->classes.PA - tabjoueur[indice]->classes.mesattaques[0].consequence_PA >=0)
                {
                    clear_bitmap(fond);
                    fond = chargement_fond(tabcases,choix);
                    draw_sprite(fond, select, 495, 730);
                    porteSort(tabcases, tabjoueur, indice, 0, fond);
                    chargement_perso(tabjoueur,indice,nbrjoueur,fond,0);
                    blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    while(done2 == 0)
                    {
                        done2 = lancerattaque(tabcases,tabjoueur,indice,nbrjoueur,0, fond);
                        blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                        //chargement_perso(tabjoueur,indice,nbrjoueur,fond,0);
                        //blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    }
                    done = 1;
                }
                else
                {
                    done = 1;
                }
            }
            if(mouse_x>577 && mouse_x<647 && mouse_y>737 && mouse_y<800)
            {
                if(tabjoueur[indice]->classes.PA - tabjoueur[indice]->classes.mesattaques[1].consequence_PA >=0)
                {
                    clear_bitmap(fond);
                    fond = chargement_fond(tabcases,choix);
                    draw_sprite(fond, select, 495 + (1*75), 730);
                    porteSort(tabcases, tabjoueur, indice, 1, fond);
                    chargement_perso(tabjoueur,indice,nbrjoueur,fond,0);
                    blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    while(done2 == 0)
                    {
                        done2 = lancerattaque(tabcases,tabjoueur,indice,nbrjoueur,1,fond);
                        blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                        //chargement_perso(tabjoueur,indice,nbrjoueur,fond,0);
                        //blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    }
                    done = 1;
                }
                else
                {
                    done = 1;
                }
            }
            if(mouse_x>652 && mouse_x<722 && mouse_y>737 && mouse_y<800)
            {
                if(tabjoueur[indice]->classes.PA - tabjoueur[indice]->classes.mesattaques[2].consequence_PA >=0)
                {
                    clear_bitmap(fond);
                    fond = chargement_fond(tabcases,choix);
                    draw_sprite(fond, select, 495 + (2*75), 730);
                    porteSort(tabcases, tabjoueur, indice, 2, fond);
                    chargement_perso(tabjoueur,indice,nbrjoueur,fond,0);
                    blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    while(done2 == 0)
                    {
                        done2 = lancerattaque(tabcases,tabjoueur,indice,nbrjoueur,2, fond);
                        blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                        //chargement_perso(tabjoueur,indice,nbrjoueur,fond,0);
                        //blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    }
                    done = 1;
                }
                else
                {
                    done = 1;
                }
            }
            if(mouse_x>727 && mouse_x<797 && mouse_y>737 && mouse_y<800)
            {
                if(tabjoueur[indice]->classes.PA - tabjoueur[indice]->classes.mesattaques[3].consequence_PA >=0)
                {
                    clear_bitmap(fond);
                    fond = chargement_fond(tabcases,choix);
                    draw_sprite(fond, select, 495 + (3*75), 730);
                    porteSort(tabcases, tabjoueur, indice, 3, fond);
                    chargement_perso(tabjoueur,indice,nbrjoueur,fond,0);
                    blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    while(done2 == 0)
                    {
                        done2 = lancerattaque(tabcases,tabjoueur,indice,nbrjoueur,3,fond);
                        blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                        //chargement_perso(tabjoueur,indice,nbrjoueur,fond,0);
                        //blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    }
                    done = 1;
                }
                else
                {
                    done = 1;
                }
            }
            if(mouse_x>802 && mouse_x<872 && mouse_y>737 && mouse_y<800)
            {
                if(tabjoueur[indice]->classes.PA - 1 >=0)
                {
                    clear_bitmap(fond);
                    fond = chargement_fond(tabcases,choix);
                    draw_sprite(fond, select, 495 + (3*75), 730);
                    dessinportemelee(tabjoueur,tabcases,indice,8,fond);
                    chargement_perso(tabjoueur,indice,nbrjoueur,fond,0);
                    blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    while(done2 == 0)
                    {
                        done2 = lancerattaque(tabcases,tabjoueur,indice,nbrjoueur,8,fond);
                        blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                        //chargement_perso(tabjoueur,indice,nbrjoueur,fond,0);
                        //blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
                    }
                    done = 1;
                }
                else
                {
                    done = 1;
                }
            }
            if(mouse_x > 1320 && mouse_x < 1350 && mouse_y >740 && mouse_y < 770)
            {
                done = 1;
            }
        }

    }
    Sleep(1000);
    destroy_bitmap(select);
    destroy_bitmap(croix);
}


void afficherSort(t_joueur** tabjoueur, int indice, BITMAP* fond)
{
    BITMAP* sort1;
    BITMAP* sort2;
    BITMAP* sort3;
    BITMAP* sort4;
    BITMAP* poing = load_bitmap("documents/perso/poing.bmp", NULL);
    BITMAP* logo_info = load_bitmap("documents/props/logo info.bmp", NULL);
    draw_sprite(fond, logo_info, 490, 710);
    draw_sprite(fond, logo_info, 565, 710);
    draw_sprite(fond, logo_info, 640, 710);
    draw_sprite(fond, logo_info, 715, 710);
    draw_sprite(fond, logo_info,792, 710);
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
    destroy_bitmap(sort1);
    destroy_bitmap(sort2);
    destroy_bitmap(sort3);
    destroy_bitmap(sort4);
    destroy_bitmap(poing);
    destroy_bitmap(logo_info);
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

int possibmelee(t_joueur** tabjoueur,int X, int Y, t_cases** tabcases, int indice,int numsort)
{
    int Ycase = tabcases[Y/50][X/50].y/50;
    int Xcase = tabcases[Y/50][X/50].x/50;
    int Yjoueur = tabjoueur[indice]->classes.cord_y/50;
    int Xjoueur = tabjoueur[indice]->classes.cord_x/50;
    if(tabcases[Y/50][X/50].obstacle == 0)
    {
        if((Xcase == Xjoueur && Ycase == Yjoueur-1) || (Xcase == Xjoueur-1 && Ycase == Yjoueur) ||(Xcase == Xjoueur && Ycase == Yjoueur+1)||(Xcase == Xjoueur+1 && Ycase == Yjoueur))
        {
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}

void dessinportemelee(t_joueur** tabjoueur, t_cases** tabcases, int indice,int numsort, BITMAP* fond)
{
    for(int i = 0; i<16; i++)
    {
        for(int j=0; j<28; j++)
        {
            if(possibmelee(tabjoueur,tabcases[i][j].x, tabcases[i][j].y, tabcases, indice, numsort) == 1)
            {
                if(tabcases[i][j].x != tabjoueur[indice]->classes.cord_x || tabcases[i][j].y != tabjoueur[indice]->classes.cord_y)
                {
                    rectfill(fond, tabcases[i][j].x+5, tabcases[i][j].y+5, tabcases[i][j].x+45,tabcases[i][j].y+45, makecol(50,130,246));
                }
            }
        }
    }
}

int lancerattaque(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, int numsort, BITMAP* fond)
{
    BITMAP* anime;
    anime = load_bitmap("documents/props/anime feu.bmp", NULL);
    if(mouse_b&1)
    {
        if(tabjoueur[indice]->classes.mesattaques[numsort].type == 1)
        {
            if(possibcroix(tabcases,mouse_x, mouse_y,tabjoueur,indice,numsort) == 1)
            {
                tabjoueur[indice]->classes.PA = tabjoueur[indice]->classes.PA - tabjoueur[indice]->classes.mesattaques[numsort].consequence_PA;
                //if(tabjoueur[indice]->classes.PA >= tabjoueur[indice]->classes.mesattaques[numsort].consequence_PA)
               // {
                    for(int i = 0; i<nbrjoueur; i++)
                    {
                        if(tabjoueur[i]->classes.cord_x/50 == mouse_x/50 && tabjoueur[i]->classes.cord_y/50 == mouse_y/50)
                        {
                            if(rand()%tabjoueur[indice]->classes.mesattaques[numsort].modulo_echec != 5)
                            {
                                tabjoueur[i]->classes.PV -= tabjoueur[indice]->classes.mesattaques[numsort].degats;
                                draw_sprite(fond, anime, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y+5);
                                printf("%s : %d", tabjoueur[i]->pseudo, tabjoueur[i]->classes.PV);
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
                    }
                    printf("personne sur cette case\n");
                    return 1;
                /*}
                else
                {
                    printf("pas assez de PA");
                    return 1;
                }*/
            }
            else
                return 0;
        }
        else if(tabjoueur[indice]->classes.mesattaques[numsort].type == 2 || tabjoueur[indice]->classes.mesattaques[numsort].type == 3)
        {
            if(possibcercle(tabjoueur,mouse_x, mouse_y,tabcases,indice,numsort) == 1)
            {
                tabjoueur[indice]->classes.PA = tabjoueur[indice]->classes.PA - tabjoueur[indice]->classes.mesattaques[numsort].consequence_PA;
                //if(tabjoueur[indice]->classes.PA >= tabjoueur[indice]->classes.mesattaques[numsort].consequence_PA)
                //{
                    for(int i = 0; i<nbrjoueur; i++)
                    {
                        if(tabjoueur[i]->classes.cord_x/50 == mouse_x/50 && tabjoueur[i]->classes.cord_y/50 == mouse_y/50)
                        {
                            if(rand()%tabjoueur[indice]->classes.mesattaques[numsort].modulo_echec != 5)
                            {
                                tabjoueur[i]->classes.PV -= tabjoueur[indice]->classes.mesattaques[numsort].degats;
                                draw_sprite(fond, anime, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y+5);
                                printf("%s : %d\n", tabjoueur[i]->pseudo, tabjoueur[i]->classes.PV);
                                if(tabjoueur[i]->classes.PV <=0)
                                {
                                    tabjoueur[i]->perdu = 1;
                                }
                                return 1;
                            }
                            else
                            {
                                printf("raté\n");
                                return 1;
                            }
                        }
                    }
                    printf("personne sur cette case\n");
                    return 1;
                //}
                /*else
                {
                    printf("pas assez de PA");
                    return 1;
                }*/
            }
            else
                return 0;
        }
        else
        {
            if(possibmelee(tabjoueur,mouse_x,mouse_y,tabcases,indice,8) == 1)
            {
                tabjoueur[indice]->classes.PA = tabjoueur[indice]->classes.PA - 1;
                for(int i = 0; i<nbrjoueur; i++)
                {
                    if(tabjoueur[i]->classes.cord_x/50 == mouse_x/50 && tabjoueur[i]->classes.cord_y/50 == mouse_y/50)
                    {
                        tabjoueur[i]->classes.PV -= 3;
                        draw_sprite(fond, anime, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y+5);
                        printf("%s : %d\n", tabjoueur[i]->pseudo, tabjoueur[i]->classes.PV);
                        if(tabjoueur[i]->classes.PV <=0)
                        {
                            tabjoueur[i]->perdu = 1;
                        }
                        return 1;
                    }
                }
                printf("personne sur cette case\n");
                return 1;
            }
        }
        return 0;
    }
    else
        return 0;
    destroy_bitmap(anime);
}

void info_sort(t_joueur** tabjoueur, int indice, int num_info, BITMAP* fond)
{
    BITMAP* info;
    BITMAP* logo_croix;
    logo_croix = load_bitmap("documents/props/logo croix.bmp", NULL);
    char cheminement[500];
    int pos_x;
    int pos_y;
    int pos_x_bis;
    int pos_y_bis;
    int stop = 0;
    if(num_info == 5)
    {
        strcpy(cheminement, "documents/perso/info5.bmp");
    }
    if(strcmp(tabjoueur[indice]->classes.nom, "luffy")==0)
    {
        if(num_info == 1)
        {
            strcpy(cheminement, "documents/perso/luffy/sortL/info1.bmp");
        }
        if(num_info == 2)
        {
            strcpy(cheminement, "documents/perso/luffy/sortL/info2.bmp");
        }
        if(num_info == 3)
        {
            strcpy(cheminement, "documents/perso/luffy/sortL/info3.bmp");
        }
        if(num_info == 4)
        {
            strcpy(cheminement, "documents/perso/luffy/sortL/info4.bmp");
        }
    }
    if(strcmp(tabjoueur[indice]->classes.nom, "robin")==0)
    {
        if(num_info == 1)
        {
            strcpy(cheminement, "documents/perso/robin/sortR/info1.bmp");
        }
        if(num_info == 2)
        {
            strcpy(cheminement, "documents/perso/robin/sortR/info2.bmp");
        }
        if(num_info == 3)
        {
            strcpy(cheminement, "documents/perso/robin/sortR/info3.bmp");
        }
        if(num_info == 4)
        {
            strcpy(cheminement, "documents/perso/robin/sortR/info4.bmp");
        }
    }
    if(strcmp(tabjoueur[indice]->classes.nom, "sanji")==0)
    {
        if(num_info == 1)
        {
            strcpy(cheminement, "documents/perso/sanji/sortS/info1.bmp");
        }
        if(num_info == 2)
        {
            strcpy(cheminement, "documents/perso/sanji/sortS/info2.bmp");
        }
        if(num_info == 3)
        {
            strcpy(cheminement, "documents/perso/sanji/sortS/info3.bmp");
        }
        if(num_info == 4)
        {
            strcpy(cheminement, "documents/perso/sanji/sortS/info4.bmp");
        }
    }
    if(strcmp(tabjoueur[indice]->classes.nom, "franky")==0)
    {
        if(num_info == 1)
        {
            strcpy(cheminement, "documents/perso/franky/sortF/info1.bmp");
        }
        if(num_info == 2)
        {
            strcpy(cheminement, "documents/perso/franky/sortF/info2.bmp");
        }
        if(num_info == 3)
        {
            strcpy(cheminement, "documents/perso/franky/sortF/info3.bmp");
        }
        if(num_info == 4)
        {
            strcpy(cheminement, "documents/perso/franky/sortF/info4.bmp");
        }
    }
    pos_y = 600;
    pos_y_bis = 590;
    if(num_info == 1)
    {
        pos_x = 502;
        pos_x_bis = 717;
    }
    if(num_info == 2)
    {
        pos_x = 577;
        pos_x_bis = 802;
    }
    if(num_info == 3)
    {
        pos_x = 652;
        pos_x_bis = 877;
    }
    if(num_info == 4)
    {
        pos_x = 727;
        pos_x_bis = 952;
    }
    if(num_info == 5)
    {
        pos_x = 802;
        pos_x_bis = 1027;
    }
    info = load_bitmap(cheminement, NULL);
    draw_sprite(fond, info, pos_x, pos_y);
    draw_sprite(fond, logo_croix, pos_x_bis, pos_y_bis);
    while(stop == 0)
    {
        blit(fond, screen,0,0,0,0,SCREEN_W,SCREEN_H);
        if(mouse_b&1)
        {
            if(mouse_y > 590 && mouse_y < 620 && mouse_x > pos_x_bis && mouse_x < pos_x_bis+30)
            {
                stop = 9;
            }
        }
    }
    destroy_bitmap(info);
    destroy_bitmap(logo_croix);
}

