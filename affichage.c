#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <synchapi.h>
#include <string.h>
#include "header.h"

/// initialisation d'allegro
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
    BITMAP* curseur_souris = load_bitmap("documents/props/curseur ace.bmp", NULL); // utilisation d'une autre souris que de la souris de base
    set_mouse_sprite(curseur_souris);
    show_mouse(screen);
    destroy_bitmap(curseur_souris);
}

/// affichage d'un logo au lancement du jeu
void logo()
{
    int pixel = 0;
    int pixel2 = 0;
    int pixel3 = 0;
    int color = 0;
    int color1 = 0;
    BITMAP* dofus;
    BITMAP* mugiwara_edition;
    dofus = load_bitmap("documents/fond/dofus.bmp", NULL);
    mugiwara_edition = load_bitmap("documents/fond/mugiwara edition.bmp", NULL);
    BITMAP* fond;
    fond = load_bitmap("documents/fond/fond logo.bmp", NULL);
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

/// affichage du menu principal et choix de l'action a faire
void menu_principal()
{
    int couleur1 = 0;
    int couleur2 = 0;
    int couleur3 = 0;
    int couleur4 = 0;
    int stop = 0;
    BITMAP* fond;
    fond = load_bitmap("documents/fond/menu_principal.bmp", NULL);
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
            t_joueur** tab_joueur;
            int choix;
            int choix_mapa;
            int nbrjoueur;
            int premier_joueur;
            nvlpartie :
            nbrjoueur = nombre_joueur();
            choix_mapa = choix_map();
            tab_joueur = initialisation_joueur(nbrjoueur,choix_mapa);
            for(int x = 0; x<nbrjoueur; x++)
            {
                printf("joueur %d : %s\n", tab_joueur[x]->classes.ID, tab_joueur[x]->classes.nom);
            }
            premier_joueur = random_commencer(nbrjoueur);
            recommencer:
            tour(tab_joueur, nbrjoueur, premier_joueur-1, 0,choix_mapa);
            classement(tab_joueur,nbrjoueur);
            choix = menu_fin_de_jeu();
            if(choix == 1)
            {
                for(int t=0; t<nbrjoueur;t++)
                {
                    tab_joueur[t]->classes.PV = tab_joueur[t]->classes.PV_init;
                    tab_joueur[t]->ordre = 0;
                }
                goto recommencer;
            }
            if(choix == 2)
            {
                goto nvlpartie;
            }
            if(choix == 3)
            {
                quitter();
                stop = 1;
            }
        }
        if(couleur3 == makecol(255,0,0) && mouse_b&1)
        {
            t_joueur** tabjoueur;
            int nbrjoueur;
            int premier_joueur;
            char* nom;
            nom = saisie_nom_chargement();
            //t_charge Unecharge;
            printf("testdebut\n");
            nbrjoueur = chargement_nbrjoueur(nom);
            premier_joueur = chargement_indice(nom);
            //tabjoueur = chargement_infoJoueur_bis(nom, nbrjoueur);
            //Unecharge = chargement();
            printf("testfin\n");
            /*tabjoueur = Unecharge.tabjoueur;
            nbrjoueur = Unecharge.nbrjoueur;
            premier_joueur = Unecharge.indice;*/
            for(int x = 0; x<nbrjoueur; x++)
            {
                printf("joueur %d : %s\n", tabjoueur[x]->classes.ID, tabjoueur[x]->classes.nom);
            }
            tour(tabjoueur, nbrjoueur, premier_joueur, 0,1);
        }
        if(couleur4 == makecol(255,0,0) && mouse_b&1)
        {
            quitter();
            stop = 1;
        }
    }
    destroy_bitmap(fond);
}

/// affichage d'une page de fin de jeu
void quitter()
{
    BITMAP* fond = load_bitmap("documents/fond/quitter.bmp", NULL);
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

/// affichage d'une page de regle du jeu
void regle()
{
    BITMAP* regle = load_bitmap("documents/fond/regle.bmp", NULL);
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

/// affichage d'une page de choix du nombre de joueur
int nombre_joueur()
{
    int nbr = 0;
    int couleur1 = 0;
    int couleur2 = 0;
    int couleur3 = 0;
    int stop = 0;
    BITMAP* fond = load_bitmap("documents/fond/question.bmp", NULL);
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

/// affichage d'une page de choix de classe et initialisation des infos en fonction du choix de la classe
t_classe choix_classe(t_joueur** tab_joueur,int i, int nbrjoueur)
{
    t_classe uneclasse;
    FILE* luf = NULL;
    FILE* san = NULL;
    FILE* rob = NULL;
    FILE* fra = NULL;
    BITMAP* fond = load_bitmap("documents/fond/choix.bmp", NULL);
    BITMAP* luffy = load_bitmap("documents/perso/luffy/choix_luffy.bmp", NULL);
    BITMAP* robin = load_bitmap("documents/perso/robin/choix_robin.bmp", NULL);
    BITMAP* sanji = load_bitmap("documents/perso/sanji/choix_sanji.bmp", NULL);
    BITMAP* franky = load_bitmap("documents/perso/franky/choix_franky.bmp", NULL);
    BITMAP* luffy_c = load_bitmap("documents/perso/luffy/choix_luffy_c.bmp", NULL);
    BITMAP* robin_c = load_bitmap("documents/perso/robin/choix_robin_c.bmp", NULL);
    BITMAP* sanji_c = load_bitmap("documents/perso/sanji/choix_sanji_c.bmp", NULL);
    BITMAP* franky_c = load_bitmap("documents/perso/franky/choix_franky_c.bmp", NULL);
    int stop = 0;
    int test1 = 0;
    int test2 = 0;
    int test3 = 0;
    int test4 = 0;
    int couleur1 = 0;
    int couleur2 = 0;
    int couleur3 = 0;
    int couleur4 = 0;
    for(int j=0; j< i; j++)
    {
        if(tab_joueur[j]->classes.PV==70)
        {
            test1 = 4;
        }
        else if(tab_joueur[j]->classes.PV==65)
        {
            test2 = 4;
        }
        else if(tab_joueur[j]->classes.PV==50)
        {
            test3 = 4;
        }
        else if(tab_joueur[j]->classes.PV==100)
        {
            test4 = 4;
        }
        else
        {
            test1 = 0;
            test2 = 0;
            test3 = 0;
            test4 = 0;
        }
    }
    while(stop == 0)
    {
        textprintf_ex(fond, font, 580, 50, makecol(0,0,0), -1, "CHOISISSEZ VOTRE MUGIWARA");
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
            luf = fopen("documents/perso/luffy/luffy.txt", "r+");
            if(luf == NULL)
            {
                printf("Erreur d'ouverture fichier luffy\n");
            }
            uneclasse.nom = (char*)malloc(5*sizeof(char));
            uneclasse.nom = "luffy";
            uneclasse.ID = i+1;
            fscanf(luf, "%d %d %d", &uneclasse.PV, &uneclasse.PM, &uneclasse.PA);
            uneclasse.PV_init = uneclasse.PV;
            uneclasse.PM_init = uneclasse.PM;
            uneclasse.PA_init = uneclasse.PA;
            fclose(luf);
            luf = NULL;
            uneclasse.mesattaques = (t_attaque*)malloc(4 * sizeof(t_attaque));
            char* cheminement;
            char* tmp;
            char* tmp2;
            for(int i = 1; i <=4; i++)
            {
                cheminement = (char*)malloc(sizeof(char) * 60);
                tmp = (char*)malloc(sizeof(char) * 6);
                tmp2 = (char*)malloc(sizeof(char) * 50);
                if(i == 1)
                {
                    strcpy(tmp,"1.txt");
                }
                else if(i == 2)
                {
                    strcpy(tmp,"2.txt");
                }
                else if(i == 3)
                {
                    strcpy(tmp,"3.txt");
                }
                else if(i == 4)
                {
                    strcpy(tmp,"4.txt");
                }
                strcpy(cheminement, "documents/perso/luffy/sortL/");
                strcat(cheminement, tmp);
                luf = fopen(cheminement, "r+");
                if(luf == NULL)
                {
                    printf("Erreur d'ouverture fichier luffy sort\n");
                }
                else
                {
                    fgets(tmp2, 50, luf);
                    uneclasse.mesattaques[i-1].nom = (char*)malloc(sizeof(char)*(strlen(tmp2))+1);
                    strcpy(uneclasse.mesattaques[i-1].nom, tmp2);
                    fscanf(luf,"%d %d %d %d %d %d %d", &uneclasse.mesattaques[i-1].consequence_PA, &uneclasse.mesattaques[i-1].modulo_echec, &uneclasse.mesattaques[i-1].degats, &uneclasse.mesattaques[i-1].type, &uneclasse.mesattaques[i-1].porte, &uneclasse.mesattaques[i-1].consequence_PM, &uneclasse.mesattaques[i-1].effet_spe);
                }
                cheminement = NULL;
                tmp = NULL;
                tmp2 = NULL;
                fclose(luf);
                luf = NULL;
            }
            clear_bitmap(luffy);
            Sleep(500);
            stop++;
        }
        if(couleur2 == makecol(255,0,0) && mouse_b&1)
        {
            rob = fopen("documents/perso/robin/robin.txt", "r+");
            if(rob == NULL)
            {
                printf("Erreur d'ouverture fichier robin\n");
            }
            uneclasse.nom = (char*)malloc(5*sizeof(char));
            uneclasse.nom = "robin";
            uneclasse.ID = i+1;
            fscanf(rob, "%d %d %d", &uneclasse.PV, &uneclasse.PM, &uneclasse.PA);
            uneclasse.PV_init = uneclasse.PV;
            uneclasse.PM_init = uneclasse.PM;
            uneclasse.PA_init = uneclasse.PA;
            fclose(rob);
            rob = NULL;
            uneclasse.mesattaques = (t_attaque*)malloc(4 * sizeof(t_attaque));
            char* cheminement;
            char* tmp;
            char* tmp2;
            for(int i = 1; i <=4; i++)
            {
                cheminement = (char*)malloc(sizeof(char) * 60);
                tmp = (char*)malloc(sizeof(char) * 6);
                tmp2 = (char*)malloc(sizeof(char) * 50);
                if(i == 1)
                {
                    strcpy(tmp,"1.txt");
                }
                else if(i == 2)
                {
                    strcpy(tmp,"2.txt");
                }
                else if(i == 3)
                {
                    strcpy(tmp,"3.txt");
                }
                else if(i == 4)
                {
                    strcpy(tmp,"4.txt");
                }
                strcpy(cheminement, "documents/perso/robin/sortR/");
                strcat(cheminement, tmp);
                rob = fopen(cheminement, "r+");
                if(rob == NULL)
                {
                    printf("Erreur d'ouverture fichier robin sort\n");
                }
                else
                {
                    fgets(tmp2, 50, rob);
                    uneclasse.mesattaques[i-1].nom = (char*)malloc(sizeof(char)*(strlen(tmp2))+1);
                    strcpy(uneclasse.mesattaques[i-1].nom, tmp2);
                    fscanf(rob,"%d %d %d %d %d %d %d", &uneclasse.mesattaques[i-1].consequence_PA, &uneclasse.mesattaques[i-1].modulo_echec, &uneclasse.mesattaques[i-1].degats, &uneclasse.mesattaques[i-1].type, &uneclasse.mesattaques[i-1].porte, &uneclasse.mesattaques[i-1].consequence_PM, &uneclasse.mesattaques[i-1].effet_spe);
                }
                cheminement = NULL;
                tmp = NULL;
                tmp2 = NULL;
                fclose(rob);
                rob = NULL;
            }
            clear_bitmap(robin);
            Sleep(500);
            stop++;
        }
        if(couleur3 == makecol(255,0,0) && mouse_b&1)
        {
            san = fopen("documents/perso/sanji/sanji.txt", "r+");
            if(san == NULL)
            {
                printf("Erreur d'ouverture fichier sanji\n");
            }
            uneclasse.nom = (char*)malloc(5*sizeof(char));
            uneclasse.nom = "sanji";
            uneclasse.ID = i+1;
            fscanf(san, "%d %d %d", &uneclasse.PV, &uneclasse.PM, &uneclasse.PA);
            uneclasse.PV_init = uneclasse.PV;
            uneclasse.PM_init = uneclasse.PM;
            uneclasse.PA_init = uneclasse.PA;
            fclose(san);
            san = NULL;
            uneclasse.mesattaques = (t_attaque*)malloc(4 * sizeof(t_attaque));
            char* cheminement;
            char* tmp;
            char* tmp2;
            for(int i = 1; i <=4; i++)
            {
                cheminement = (char*)malloc(sizeof(char) * 60);
                tmp = (char*)malloc(sizeof(char) * 6);
                tmp2 = (char*)malloc(sizeof(char) * 50);
                if(i == 1)
                {
                    strcpy(tmp,"1.txt");
                }
                else if(i == 2)
                {
                    strcpy(tmp,"2.txt");
                }
                else if(i == 3)
                {
                    strcpy(tmp,"3.txt");
                }
                else if(i == 4)
                {
                    strcpy(tmp,"4.txt");
                }
                strcpy(cheminement, "documents/perso/sanji/sortS/");
                strcat(cheminement, tmp);
                san = fopen(cheminement, "r+");
                if(san == NULL)
                {
                    printf("Erreur d'ouverture fichier sanji sort\n");
                }
                else
                {
                    fgets(tmp2, 50, san);
                    uneclasse.mesattaques[i-1].nom = (char*)malloc(sizeof(char)*(strlen(tmp2))+1);
                    strcpy(uneclasse.mesattaques[i-1].nom, tmp2);
                    fscanf(san,"%d %d %d %d %d %d %d", &uneclasse.mesattaques[i-1].consequence_PA, &uneclasse.mesattaques[i-1].modulo_echec, &uneclasse.mesattaques[i-1].degats, &uneclasse.mesattaques[i-1].type, &uneclasse.mesattaques[i-1].porte, &uneclasse.mesattaques[i-1].consequence_PM, &uneclasse.mesattaques[i-1].effet_spe);
                }
                cheminement = NULL;
                tmp = NULL;
                tmp2 = NULL;
                fclose(san);
                san = NULL;
            }
            clear_bitmap(sanji);
            Sleep(500);
            stop++;
        }
        if(couleur4 == makecol(255,0,0) && mouse_b&1)
        {
            fra = fopen("documents/perso/franky/franky.txt", "r+");
            if(fra == NULL)
            {
                printf("Erreur d'ouverture fichier franky\n");
            }
            uneclasse.nom = (char*)malloc(6*sizeof(char));
            uneclasse.nom = "franky";
            uneclasse.ID = i+1;
            fscanf(fra, "%d %d %d", &uneclasse.PV, &uneclasse.PM, &uneclasse.PA);
            uneclasse.PV_init = uneclasse.PV;
            uneclasse.PM_init = uneclasse.PM;
            uneclasse.PA_init = uneclasse.PA;
            fclose(fra);
            fra = NULL;
            uneclasse.mesattaques = (t_attaque*)malloc(4 * sizeof(t_attaque));
            char* cheminement;
            char* tmp;
            char* tmp2;
            for(int i = 1; i <=4; i++)
            {
                cheminement = (char*)malloc(sizeof(char) * 60);
                tmp = (char*)malloc(sizeof(char) * 6);
                tmp2 = (char*)malloc(sizeof(char) * 50);
                if(i == 1)
                {
                    strcpy(tmp,"1.txt");
                }
                else if(i == 2)
                {
                    strcpy(tmp,"2.txt");
                }
                else if(i == 3)
                {
                    strcpy(tmp,"3.txt");
                }
                else if(i == 4)
                {
                    strcpy(tmp,"4.txt");
                }
                strcpy(cheminement, "documents/perso/franky/sortF/");
                strcat(cheminement, tmp);
                fra = fopen(cheminement, "r+");
                if(fra == NULL)
                {
                    printf("Erreur d'ouverture fichier franky sort\n");
                }
                else
                {
                    fgets(tmp2, 50, fra);
                    uneclasse.mesattaques[i-1].nom = (char*)malloc(sizeof(char)*(strlen(tmp2))+1);
                    strcpy(uneclasse.mesattaques[i-1].nom, tmp2);
                    fscanf(fra,"%d %d %d %d %d %d %d", &uneclasse.mesattaques[i-1].consequence_PA, &uneclasse.mesattaques[i-1].modulo_echec, &uneclasse.mesattaques[i-1].degats, &uneclasse.mesattaques[i-1].type, &uneclasse.mesattaques[i-1].porte, &uneclasse.mesattaques[i-1].consequence_PM, &uneclasse.mesattaques[i-1].effet_spe);
                }
                cheminement = NULL;
                tmp = NULL;
                tmp2 = NULL;
                fclose(fra);
                fra = NULL;
            }
            clear_bitmap(franky);
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
    return uneclasse;
}

/// affichage d'un menu pause avec choix de l'action a faire
void menu_pause(t_joueur** tabjoueur, int nbrjoueur, int indice)
{
    BITMAP* fond;
    fond = load_bitmap("documents/fond/menu pause.bmp", NULL);
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
            sauvegarde(tabjoueur,nbrjoueur,indice);
        }
    }
    destroy_bitmap(fond);
}

/// affichage d'une page des infos joueur
void infojoueur(t_joueur** tabjoueur, int nbrjoueur)
{
    BITMAP* fond;
    fond = load_bitmap("documents/fond/info joueur.bmp", NULL);
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
                textprintf_ex(fond, font, x, 100, makecol(255,255,255), 0, "Joueur %d : %s", tabjoueur[i]->classes.ID,tabjoueur[i]->pseudo);
                textprintf_ex(fond, font, x, 140, makecol(255,255,255), 0, "Classe : %s",tabjoueur[i]->classes.nom);
                textprintf_ex(fond, font, x, 170, makecol(255,255,255), 0, "PV : %d", tabjoueur[i]->classes.PV);
                textprintf_ex(fond, font, x, 190, makecol(255,255,255), 0, "PA : %d", tabjoueur[i]->classes.PA);
                textprintf_ex(fond, font, x, 210, makecol(255,255,255), 0, "PM : %d", tabjoueur[i]->classes.PM);
                if(tabjoueur[i]->classes.PV <= 0)
                {
                    textprintf_ex(fond, font, x, 230, makecol(255,255,255), 0, "Etat : perdu");
                }
                else
                {
                    textprintf_ex(fond, font, x, 230, makecol(255,255,255), 0, "Etat : encore en vie");
                }
                x = x+300;
            }
        }
        compteur++;
    }
    destroy_bitmap(fond);
}

/// affichage d'une page de saisie qui return une chaine de caractere
char* saisie_pseudo()
{
    BITMAP* fond;
    fond = load_bitmap("documents/fond/fond pseudo.bmp", NULL);
    char* pseudo;
    int touche, touche1, touche2;
    int i=0;
    char masaisie[21]; // stockage de la totalité de la saisie
    char lastsaisie[2];    // stockage la derniere touche saisie
    masaisie[20]=0;
    lastsaisie[1]=0;
    clear_keybuf();
    textprintf_ex(fond, font, 400, 250, makecol(255,255,255),0,"SAISIR VOTRE PSEUDO : (entree pour valider)");
    /* affichage curseur */
    textprintf_ex(fond,font,420+8*(i+1),300,makecol(255,255,255),0,"_");

    while(!key[KEY_ENTER] && !key[KEY_ENTER_PAD])
    {
        blit(fond, screen,0,0,0,0,SCREEN_W,SCREEN_H);
        touche=readkey();
        touche1=touche & 0xFF; // code ASCII
        touche2=touche >> 8;   // scancode
        // selection des touches (la selection est totalement arbitraire)
        if (( touche1>31 && touche1<58) || ( touche1>64 && touche1<123))
        {
            if (i>=20)
                i=20;
            else
            {
                masaisie[i]=touche1;
                lastsaisie[0]=touche1;
                masaisie[i+1]=0;
                /*  on affiche la touche saisie */
                textprintf_ex(fond,font,420+8*i,300,makecol(255,255,255),0,"%s",lastsaisie);
                i++;
                textprintf_ex(fond,font,420+8*i,300,makecol(255,255,255),0,"_");
            }
        }
        //* si effacement
        if ( touche2==KEY_BACKSPACE )
        {
            i--;
            if ( i<0 )
                i=0;
            textprintf_ex(fond,font,420+8*i,300,makecol(255,255,255),0,"_");
            textprintf_ex(fond,font,420+8*(i+1),300,makecol(255,255,255),0," ");
        }
        //* si validation
        if ( (touche2==KEY_ENTER_PAD) || (touche2==KEY_ENTER) )
        {
            textprintf_ex(fond,font,420+8*i,300,makecol(255,255,255),0," ");
            if (i==0)
                masaisie[0]=32; // space
            masaisie[i+1]=0;
        }
    }
    pseudo = (char*)malloc((strlen(masaisie)+1)*sizeof(char));
    if(pseudo != NULL)
    {
        strcpy(pseudo, masaisie);
    }
    clear_keybuf();
    clear_bitmap(fond);
    destroy_bitmap(fond);
    return pseudo;
}

void classement(t_joueur** tabjoueur, int nbrjoueur)
{
    BITMAP* fond;
    fond = load_bitmap("documents/fond/fond classement.bmp", NULL);
    int done = 0;
    int y = 200;
    int compteur = 0;
    while(done == 0)
    {
        blit(fond, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
        textprintf_ex(fond, font, 1050, 750,makecol(0,0,0),-1 ,"Clique droit pour quitter le classement");
        textprintf_ex(fond, font, 1030, 150,makecol(0,0,0),-1,"CLASSEMENT");
        if(mouse_b&2)
        {
            done = 5;
        }
        else if(compteur == 0)
        {
            for(int i=0; i<nbrjoueur;i++)
            {
                textprintf_ex(fond, font, 900, y,makecol(0,0,0),-1,"Joueur : %s", tabjoueur[i]->pseudo );
                textprintf_ex(fond, font, 900, y+20,makecol(0,0,0),-1,"Vous aviez choisi comme mugiwara : %s", tabjoueur[i]->classes.nom );
                textprintf_ex(fond, font, 900, y+40,makecol(0,0,0),-1,"Votre rang : %d/%djoueurs", tabjoueur[i]->ordre, nbrjoueur );
                y = y+100;
            }
        }
        compteur++;
    }
    destroy_bitmap(fond);
}

int menu_fin_de_jeu()
{
    BITMAP* fond;
    fond = load_bitmap("documents/fond/fond fin.bmp", NULL);
    int done = 0;
    int couleur1;
    int couleur2;
    int couleur3;
    int retour = 0;
    while(done == 0)
    {
        blit(fond, screen,0,0,0,0,SCREEN_W,SCREEN_H);
        textprintf_ex(fond, font, 600, 50, makecol(0,0,0), -1, "QUE VOULEZ-VOUS FAIRE ?");
        if(mouse_x < 170 || mouse_x > (250 + text_length(font, "Recommencer la meme partie")) || mouse_y < 120 || mouse_y > (120 + text_height(font)))
        {
            couleur1 = makecol(0,0,0);
        }
        else
        {
            couleur1 = makecol(255,0,0);
        }
        if(mouse_x < 520 || mouse_x > (600 + text_length(font, "Commencer une nouvelle partie")) || mouse_y < 120 || mouse_y > (120 + text_height(font)))
        {
            couleur2 = makecol(0,0,0);
        }
        else
        {
            couleur2 = makecol(255,0,0);
        }
        if(mouse_x < 1020 || mouse_x > (1100 + text_length(font, "Quitter ce jeu")) || mouse_y < 120 || mouse_y > (120 + text_height(font)))
        {
            couleur3 = makecol(0,0,0);
        }
        else
        {
            couleur3 = makecol(255,0,0);
        }
        textprintf_ex(fond,font, 250,120,couleur1,-1, "Recommencer la meme partie");
        circlefill(fond, 180, 120, 10, couleur1);
        textprintf_ex(fond, font, 600, 120, couleur2, -1, "Commencer une nouvelle partie");
        circlefill(fond, 530, 120, 10, couleur2);
        textprintf_ex(fond, font, 1100, 120, couleur3, -1, "Quitter ce jeu");
        circlefill(fond, 1030, 120, 10, couleur3);
        if(couleur1 == makecol(255,0,0) && mouse_b&1)
        {
            retour = 1;
            done = 3;
        }
        if(couleur2 == makecol(255,0,0) && mouse_b&1)
        {
            retour = 2;
            done = 3;
        }
        if(couleur3 == makecol(255,0,0) && mouse_b&1)
        {
            retour = 3;
            done = 3;
        }
    }
    return retour;
    destroy_bitmap(fond);
}

int choix_map()
{
    BITMAP* fond;
    BITMAP* map1;
    BITMAP* map2;
    fond = load_bitmap("documents/fond/fond choix map.bmp", NULL);
    map1 = load_bitmap("documents/props/map1.bmp", NULL);
    map2 = load_bitmap("documents/props/map2.bmp", NULL);
    int couleur1;
    int couleur2;
    int done = 0;
    int retour = 0;
    while(done == 0)
    {
        draw_sprite(fond, map1, 100,250);
        draw_sprite(fond,map2,800,250);
        blit(fond, screen,0,0,0,0,SCREEN_W,SCREEN_H);
        textprintf_ex(fond, font, 600, 50, makecol(0,0,0), -1, "CHOISISSEZ VOTRE MAP");
        if(mouse_x < 220 || mouse_x > (300 + text_length(font, "Archipel Sabaody")) || mouse_y < 550 || mouse_y > (550 + text_height(font)))
        {
            couleur1 = makecol(0,0,0);
        }
        else
        {
            couleur1 = makecol(255,0,0);
        }
        if(mouse_x < 970 || mouse_x > (1050 + text_length(font, "Alabasta")) || mouse_y < 550 || mouse_y > (550 + text_height(font)))
        {
            couleur2 = makecol(0,0,0);
        }
        else
        {
            couleur2 = makecol(255,0,0);
        }
        textprintf_ex(fond,font, 300,550,couleur1,-1, "Archipel Sabaody");
        circlefill(fond, 230, 550, 10, couleur1);
        textprintf_ex(fond, font, 1050, 550, couleur2, -1, "Alabasta");
        circlefill(fond, 980, 550, 10, couleur2);
        if(couleur1 == makecol(255,0,0) && mouse_b&1)
        {
            retour = 1;
            done = 3;
        }
        if(couleur2 == makecol(255,0,0) && mouse_b&1)
        {
            retour = 2;
            done = 3;
        }
    }
    return retour;
    destroy_bitmap(fond);
    destroy_bitmap(map1);
    destroy_bitmap(map2);
}
