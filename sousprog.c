#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <synchapi.h>
#include "header.h"

void initialisation()
{
    allegro_init();
    set_color_depth(desktop_color_depth());
    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,1400,800,0,0))!=0)
    {
        allegro_message("Pb de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    install_keyboard();
    install_mouse();
    show_mouse(screen);
}

void logo()
{
    int pixel = 0;
    int pixel2 = 0;
    int pixel3 = 0;
    int color = 0;
    int color1 = 0;
    BITMAP* dofus;
    BITMAP* mugiwara_edition;
    dofus = load_bitmap("dofus.bmp", NULL);
    mugiwara_edition = load_bitmap("mugiwara edition.bmp", NULL);
    BITMAP* fond;
    fond = load_bitmap("fond.bmp", NULL);
    for(int i = 0; i < SCREEN_W; i++)
    {
        for(int j = 0; j< SCREEN_H; j++)
        {
            pixel = getpixel(dofus, i, j);
            color = getpixel(dofus,i,j);
            color1 = getpixel(mugiwara_edition,i,j);
            pixel2 = getpixel(mugiwara_edition, i, j);
            pixel3 = makecol(255,255,255);
            if (pixel == pixel3)
            {
                putpixel(dofus, i, j, makecol(255,0,255));
            }
            if(pixel2 == pixel3)
            {
                putpixel(mugiwara_edition, i, j, makecol(255,0,255));
            }
            /// passer en blanc
            if(color == makecol(0,0,0))
            {
                putpixel(dofus, i,j, makecol(255,255,255));
            }
            if(color1 == makecol(0,0,0))
            {
                putpixel(mugiwara_edition,i,j, makecol(255,255,255));
            }
            ///
        }
    }
    draw_sprite(fond, dofus,450,200);
    draw_sprite(fond, mugiwara_edition, 300,370);
    blit(fond, screen,0,0,0,0, SCREEN_W, SCREEN_H);
    textprintf_ex(screen, font, 1200, 700, makecol(255,255,255), -1, "chargement");
    rest(1000);
    textprintf_ex(screen, font, 1300, 700, makecol(255,255,255), -1, ".");
    rest(1000);
    textprintf_ex(screen, font, 1315, 700, makecol(255,255,255), -1, ".");
    rest(1000);
    textprintf_ex(screen, font, 1330, 700, makecol(255,255,255), -1, ".");
    rest(1000);
    destroy_bitmap(fond);
    destroy_bitmap(dofus);
    destroy_bitmap(mugiwara_edition);
}

void menu_principal()
{
    t_joueur** tab_joueur;
    int couleur1 = 0;
    int couleur2 = 0;
    int couleur3 = 0;
    int couleur4 = 0;
    int stop = 0;
    BITMAP* fond;
    fond = load_bitmap("menu_luffy.bmp", NULL);
    while(stop == 0)
    {
        blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
        textprintf_ex(fond,font, 500,200,makecol(0,0,0),-1, "MENU PRINCIPAL");
        if(mouse_x < 420 || mouse_x > (500 + text_length(font, "Regles du jeu")) || mouse_y < 300 || mouse_y > (300 + text_height(font)))
        {
            couleur1 = makecol(0,0,0);
        }
        else
        {
            couleur1 = makecol(255,0,0);
        }
        if(mouse_x < 420 || mouse_x > (500 + text_length(font, "Nouvelle partie")) || mouse_y < 350 || mouse_y > (350 + text_height(font)))
        {
            couleur2 = makecol(0,0,0);
        }
        else
        {
            couleur2 = makecol(255,0,0);
        }
        if(mouse_x < 420 || mouse_x > (500 + text_length(font, "Charger une ancienne partie")) || mouse_y < 400 || mouse_y > (400 + text_height(font)))
        {
            couleur3 = makecol(0,0,0);
        }
        else
        {
            couleur3 = makecol(255,0,0);
        }
        if(mouse_x < 420 || mouse_x > (500 + text_length(font, "Quitter ce jeu")) || mouse_y < 450 || mouse_y > (450 + text_height(font)))
        {
            couleur4 = makecol(0,0,0);
        }
        else
        {
            couleur4 = makecol(255,0,0);
        }
        textprintf_ex(fond,font, 500,300,couleur1,-1, "Regles du jeu");
        circlefill(fond, 430, 300, 10, couleur1);
        textprintf_ex(fond, font, 500, 350, couleur2, -1, "Nouvelle partie");
        circlefill(fond, 430, 350, 10, couleur2);
        textprintf_ex(fond, font, 500, 400, couleur3, -1, "Charger une ancienne partie");
        circlefill(fond, 430, 400, 10, couleur3);
        textprintf_ex(fond, font, 500, 450, couleur4, -1, "Quitter ce jeu");
        circlefill(fond, 430, 450, 10, couleur4);
        if(couleur1 == makecol(255,0,0) && mouse_b&1)
        {
            regle();
        }
        if(couleur2 == makecol(255,0,0) && mouse_b&1)
        {
            /// a definir
            int nbr;
            int premier_joueur;
            nbr = nombre_joueur();
            tab_joueur = choix_perso(nbr);
            for(int x = 0; x<nbr; x++)
            {
                printf("joueur %d : %s\n", tab_joueur[x]->ID, tab_joueur[x]->nom);
            }
            premier_joueur = random_commencer(nbr);
            tour(tab_joueur, nbr, premier_joueur, 0);
            stop = 1;
        }
        if(couleur3 == makecol(255,0,0) && mouse_b&1)
        {
            /// a definir
            stop = 1;
        }
        if(couleur4 == makecol(255,0,0) && mouse_b&1)
        {
            quitter();
            stop = 1;
        }
    }
    destroy_bitmap(fond);
}

void lancement()
{
    initialisation();
    logo();
    menu_principal();
}

void quitter()
{
    BITMAP* fond = load_bitmap("quitter.bmp", NULL);
    {
        blit(fond, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
        textprintf_ex(screen, font, 700, 400, makecol(255,255,255),-1, "AU REVOIR");
        rest(1000);
        textprintf_ex(screen, font, 800, 400, makecol(255,255,255),-1, ".");
        rest(1000);
        textprintf_ex(screen, font, 815, 400, makecol(255,255,255),-1, ".");
        rest(1000);
        textprintf_ex(screen, font, 830, 400, makecol(255,255,255),-1, ".");
        rest(1000);
    }
    destroy_bitmap(fond);
}

void regle()
{
    BITMAP* regle = load_bitmap("regle.bmp", NULL);
    int stop = 0;
    while( stop == 0)
    {
        blit(regle, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
        if(mouse_b&2)
        {
            stop = 5;
        }
    }
    destroy_bitmap(regle);
}

int nombre_joueur()
{
    int nbr = 0;
    int couleur1 = 0;
    int couleur2 = 0;
    int couleur3 = 0;
    int stop = 0;
    BITMAP* fond = load_bitmap("question.bmp", NULL);
    while(stop == 0)
    {
        textprintf_ex(fond, font,400 - text_length(font, "COMBIEN DE JOUEUR ETES-VOUS ?"), 100, makecol(0,0,0), -1, "COMBIEN DE JOUEUR ETES-VOUS ?" );
        if(mouse_x < 190 || mouse_x > (250 + text_length(font, "2")) || mouse_y < 200 || mouse_y > (200 + text_height(font)))
        {
            couleur1 = makecol(0,0,0);
        }
        else
        {
            couleur1 = makecol(255,0,0);
        }
        if(mouse_x < 190 || mouse_x > (250 + text_length(font, "3")) || mouse_y < 250 || mouse_y > (250 + text_height(font)))
        {
            couleur2 = makecol(0,0,0);
        }
        else
        {
            couleur2 = makecol(255,0,0);
        }
        if(mouse_x < 190 || mouse_x > (250 + text_length(font, "4")) || mouse_y < 300 || mouse_y > (300 + text_height(font)))
        {
            couleur3 = makecol(0,0,0);
        }
        else
        {
            couleur3 = makecol(255,0,0);
        }
        textprintf_ex(fond,font, 250,200,couleur1,-1, "2");
        circlefill(fond, 200, 200, 10, couleur1);
        textprintf_ex(fond, font, 250, 250, couleur2, -1, "3");
        circlefill(fond, 200, 250, 10, couleur2);
        textprintf_ex(fond, font, 250, 300, couleur3, -1, "4");
        circlefill(fond, 200, 300, 10, couleur3);
        blit(fond, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
        if(couleur1 == makecol(255,0,0) && mouse_b&1)
        {
            nbr = 2;
            stop = 4;
        }
        if(couleur2 == makecol(255,0,0) && mouse_b&1)
        {
            nbr = 3;
            stop = 4;
        }
        if(couleur3 == makecol(255,0,0) && mouse_b&1)
        {
            nbr = 4;
            stop = 4;
        }
    }
    destroy_bitmap(fond);
    return nbr;
}

t_joueur** choix_perso(int nbr_joueur)
{
    t_joueur** tab_joueur = (t_joueur**)malloc(nbr_joueur * sizeof(t_joueur*));
    FILE* luf = NULL;
    FILE* san = NULL;
    FILE* rob = NULL;
    FILE* fra = NULL;
    BITMAP* fond = load_bitmap("choix.bmp", NULL);
    BITMAP* luffy = load_bitmap("luffy.bmp", NULL);
    BITMAP* robin = load_bitmap("robin.bmp", NULL);
    BITMAP* sanji = load_bitmap("sanji.bmp", NULL);
    BITMAP* franky = load_bitmap("franky.bmp", NULL);
    BITMAP* luffy_c = load_bitmap("luffy_c.bmp", NULL);
    BITMAP* robin_c = load_bitmap("robin_c.bmp", NULL);
    BITMAP* sanji_c = load_bitmap("sanji_c.bmp", NULL);
    BITMAP* franky_c = load_bitmap("franky_c.bmp", NULL);
    int stop = 0;
    int test1 = 0;
    int test2 = 0;
    int test3 = 0;
    int test4 = 0;
    int couleur1 = 0;
    int couleur2 = 0;
    int couleur3 = 0;
    int couleur4 = 0;
    while(stop != nbr_joueur)
    {
        textprintf_ex(fond, font, 570, 50, makecol(0,0,0), -1, "CHOISISSEZ 1 PAR 1 VOTRE MUGIWARA");
        if(mouse_x < 90 || mouse_x > (180 + text_length(font, "LUFFY")) || mouse_y < 180 || mouse_y > (180 + text_height(font)))
        {
            couleur1 = makecol(0,0,0);
        }
        else if(test1 == 0)
        {
            couleur1 = makecol(255,0,0);
        }
        if(mouse_x < 440 || mouse_x > (530 + text_length(font, "ROBIN")) || mouse_y < 180 || mouse_y > (180 + text_height(font)))
        {
            couleur2 = makecol(0,0,0);
        }
        else if(test2 == 0)
        {
            couleur2 = makecol(255,0,0);
        }
        if(mouse_x < 790 || mouse_x > (880 + text_length(font, "SANJI")) || mouse_y < 180 || mouse_y > (180 + text_height(font)))
        {
            couleur3 = makecol(0,0,0);
        }
        else if(test3 == 0)
        {
            couleur3 = makecol(255,0,0);
        }
        if(mouse_x < 1140 || mouse_x > (1230 + text_length(font, "FRANKY")) || mouse_y < 180 || mouse_y > (180 + text_height(font)))
        {
            couleur4 = makecol(0,0,0);
        }
        else if(test4 == 0)
        {
            couleur4 = makecol(255,0,0);
        }
        textprintf_ex(fond,font, 180,180,couleur1,-1, "LUFFY");
        circlefill(fond, 100, 180, 10, couleur1);
        if(test1 == 0)
        {
            draw_sprite(fond, luffy, 30, 200);
        }
        else
        {
            draw_sprite(fond, luffy_c, 30,200);
        }
        textprintf_ex(fond, font, 530, 180, couleur2, -1, "ROBIN");
        circlefill(fond, 450, 180, 10, couleur2);
        if(test2 == 0)
        {
            draw_sprite(fond, robin, 380, 200);
        }
        else
        {
            draw_sprite(fond, robin_c, 380, 200);
        }
        if(test3 == 0)
        {
            draw_sprite(fond, sanji, 730, 200);
        }
        else
        {
            draw_sprite(fond, sanji_c, 730, 200);
        }
        if(test4 == 0)
        {
            draw_sprite(fond, franky, 1080, 200);
        }
        else
        {
            draw_sprite(fond, franky_c, 1080, 200);
        }
        textprintf_ex(fond, font, 880, 180, couleur3, -1, "SANJI");
        circlefill(fond, 800, 180, 10, couleur3);
        textprintf_ex(fond, font, 1230, 180, couleur4, -1, "FRANKY");
        circlefill(fond, 1150, 180, 10, couleur4);
        blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
        if(couleur1 == makecol(255,0,0) && mouse_b&1)
        {
            luf = fopen("luffy.txt", "r+");
            if(luf == NULL)
            {
                printf("Erreur d'ouverture fichier luffy\n");
            }
            tab_joueur[stop] = (t_joueur*)malloc(sizeof(t_joueur));
            tab_joueur[stop]->nom = (char*)malloc(5*sizeof(char));
            tab_joueur[stop]->nom = "luffy";
            tab_joueur[stop]->ID = stop + 1;
            fscanf(luf, "%d %d %d", &tab_joueur[stop]->PV, &tab_joueur[stop]->PM, &tab_joueur[stop]->PA);
            fclose(luf);
            clear_bitmap(luffy);
            test1 = 4;
            Sleep(500);
            stop++;
        }
        if(couleur2 == makecol(255,0,0) && mouse_b&1)
        {
            rob = fopen("robin.txt", "r+");
            if(rob == NULL)
            {
                printf("Erreur d'ouverture fichier robin\n");
            }
            tab_joueur[stop] = (t_joueur*)malloc(sizeof(t_joueur));
            tab_joueur[stop]->nom = (char*)malloc(5*sizeof(char));
            tab_joueur[stop]->nom = "robin";
            tab_joueur[stop]->ID = stop + 1;
            fscanf(rob, "%d %d %d", &tab_joueur[stop]->PV, &tab_joueur[stop]->PM, &tab_joueur[stop]->PA);
            fclose(rob);
            clear_bitmap(robin);
            test2 = 4;
            Sleep(500);
            stop++;
        }
        if(couleur3 == makecol(255,0,0) && mouse_b&1)
        {
            san = fopen("sanji.txt", "r+");
            if(san == NULL)
            {
                printf("Erreur d'ouverture fichier sanji\n");
            }
            tab_joueur[stop] = (t_joueur*)malloc(sizeof(t_joueur));
            tab_joueur[stop]->nom = (char*)malloc(5*sizeof(char));
            tab_joueur[stop]->nom = "sanji";
            tab_joueur[stop]->ID = stop + 1;
            fscanf(san, "%d %d %d", &tab_joueur[stop]->PV, &tab_joueur[stop]->PM, &tab_joueur[stop]->PA);
            fclose(san);
            clear_bitmap(sanji);
            test3 = 4;
            Sleep(500);
            stop++;
        }
        if(couleur4 == makecol(255,0,0) && mouse_b&1)
        {
            fra = fopen("franky.txt", "r+");
            if(fra == NULL)
            {
                printf("Erreur d'ouverture fichier francky\n");
            }
            tab_joueur[stop] = (t_joueur*)malloc(sizeof(t_joueur));
            tab_joueur[stop]->nom = (char*)malloc(6*sizeof(char));
            tab_joueur[stop]->nom = "franky";
            tab_joueur[stop]->ID = stop + 1;
            fscanf(fra, "%d %d %d", &tab_joueur[stop]->PV, &tab_joueur[stop]->PM, &tab_joueur[stop]->PA);
            fclose(fra);
            clear_bitmap(franky);
            test4 = 4;
            Sleep(500);
            stop++;
        }
    }
    destroy_bitmap(fond);
    destroy_bitmap(luffy);
    destroy_bitmap(robin);
    destroy_bitmap(sanji);
    destroy_bitmap(franky);
    destroy_bitmap(luffy_c);
    destroy_bitmap(robin_c);
    destroy_bitmap(sanji_c);
    destroy_bitmap(franky_c);
    return tab_joueur;
}

void menu_pause(t_joueur** tabjoueur, int nbrjoueur)
{
    BITMAP* fond;
    fond = load_bitmap("menu pause.bmp", NULL);
    int couleur1 = 0;
    int couleur2 = 0;
    int couleur3 = 0;
    int couleur4 = 0;
    int couleur5 = 0;
    int stop = 0;
    while(stop == 0)
    {
        blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
        textprintf_ex(fond,font, 400,200,makecol(0,0,0),-1, "MENU PAUSE");
        if(mouse_x < 320 || mouse_x > (400 + text_length(font, "Continuer la partie en cours")) || mouse_y < 300 || mouse_y > (300 + text_height(font)))
        {
            couleur1 = makecol(0,0,0);
        }
        else
        {
            couleur1 = makecol(255,0,0);
        }
        if(mouse_x < 320 || mouse_x > (400 + text_length(font, "Regles du jeu")) || mouse_y < 350 || mouse_y > (350 + text_height(font)))
        {
            couleur2 = makecol(0,0,0);
        }
        else
        {
            couleur2 = makecol(255,0,0);
        }
        if(mouse_x < 320 || mouse_x > (400 + text_length(font, "Consulter les informations des joueurs")) || mouse_y < 400 || mouse_y > (400 + text_height(font)))
        {
            couleur3 = makecol(0,0,0);
        }
        else
        {
            couleur3 = makecol(255,0,0);
        }
        if(mouse_x < 320 || mouse_x > (400 + text_length(font, "Menu principal")) || mouse_y < 450 || mouse_y > (450 + text_height(font)))
        {
            couleur4 = makecol(0,0,0);
        }
        else
        {
            couleur4 = makecol(255,0,0);
        }
        if(mouse_x < 320 || mouse_x > (400 + text_length(font, "Sauvegarder la partie en cours")) || mouse_y < 500 || mouse_y > (500 + text_height(font)))
        {
            couleur5 = makecol(0,0,0);
        }
        else
        {
            couleur5 = makecol(255,0,0);
        }
        textprintf_ex(fond,font, 400,300,couleur1,-1, "Continuer la partie en cours");
        circlefill(fond, 330, 300, 10, couleur1);
        textprintf_ex(fond, font, 400, 350, couleur2, -1, "Regles du jeu");
        circlefill(fond, 330, 350, 10, couleur2);
        textprintf_ex(fond, font, 400, 400, couleur3, -1, "Consulter les informations des joueurs");
        circlefill(fond, 330, 400, 10, couleur3);
        textprintf_ex(fond, font, 400, 450, couleur4, -1, "Menu principal");
        circlefill(fond, 330, 450, 10, couleur4);
        textprintf_ex(fond, font, 400, 500, couleur5, -1, "Sauvegarder la partie en cours");
        circlefill(fond, 330, 500, 10, couleur5);
        if(couleur1 == makecol(255,0,0) && mouse_b&1)
        {
            /// a definir
            stop = 1;
        }
        if(couleur2 == makecol(255,0,0) && mouse_b&1)
        {
            regle();
        }
        if(couleur3 == makecol(255,0,0) && mouse_b&1)
        {
            infojoueur(tabjoueur, nbrjoueur);
        }
        if(couleur4 == makecol(255,0,0) && mouse_b&1)
        {
            Sleep(500);
            stop = 1;
            menu_principal();
        }
        if(couleur5 == makecol(255,0,0) && mouse_b&1)
        {
            stop = 1;
        }
    }
    destroy_bitmap(fond);
}

void infojoueur(t_joueur** tabjoueur, int nbrjoueur)
{
    BITMAP* fond;
    fond = load_bitmap("info joueur.bmp", NULL);
    int stop = 0;
    int x = 150;
    int compteur = 0;
    while(stop == 0)
    {
        blit(fond, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
        textprintf_ex(fond, font, 1000, 750,makecol(255,255,255), 0, "Clique droit pour retourner sur le menu pause");
        if(mouse_b&2)
        {
            stop = 4;
        }
        else if(compteur == 0)
        {
            for(int i=0; i<nbrjoueur; i++)
            {
                textprintf_ex(fond, font, x, 100, makecol(255,255,255), 0, "Joueur %d : %s", tabjoueur[i]->ID, tabjoueur[i]->nom);
                textprintf_ex(fond, font, x, 140, makecol(255,255,255), 0, "PV : %d", tabjoueur[i]->PV);
                textprintf_ex(fond, font, x, 160, makecol(255,255,255), 0, "PA : %d", tabjoueur[i]->PA);
                textprintf_ex(fond, font, x, 180, makecol(255,255,255), 0, "PM : %d", tabjoueur[i]->PM);
                if(tabjoueur[i]->perdu == 1)
                {
                    textprintf_ex(fond, font, x, 200, makecol(255,255,255), 0, "Etat : perdu");
                }
                else
                {
                    textprintf_ex(fond, font, x, 200, makecol(255,255,255), 0, "Etat : encore en vie");
                }
                x = x+300;
            }
        }
        compteur++;
    }
    destroy_bitmap(fond);
}
