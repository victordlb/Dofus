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
                    draw_sprite(buffer, personnage, tabjoueur[indice]->classes.cord_x, tabjoueur[indice]->classes.cord_y-50);
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
                            rectfill(fond, tabcases[i][j].x+5, tabcases[i][j].y+5, tabcases[i][j].x+45,tabcases[i][j].y+45, makecol(38,200,94));
                        }
                    }
                }
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

void choix_action(t_joueur** tabjoueur, int indice, int nbrjoueur)
{
    t_cases** tabcases;
    BITMAP* fond;
    BITMAP* buffer;
    tabcases = chargement_map();
    fond = chargement_fond(tabcases);
    float temps = 0;
    chargement_perso(tabjoueur,indice,nbrjoueur,fond);
    blit(fond, screen,0,0,0,0,SCREEN_W, SCREEN_H);
    int done = 0;
    time_t start, end;
    time(&start);
    while(done == 0)
    {
        if(mouse_b&1)
        {
            if(mouse_x > 1340 && mouse_x < 1380 && mouse_y >5 && mouse_y < 45)
            {
                menu_pause(tabjoueur,nbrjoueur,indice);
                blit(fond, screen,0,0,0,0,SCREEN_W, SCREEN_H);
            }
            if(mouse_x > 1250 && mouse_x < 1300 && mouse_y >750 && mouse_y < 800)
            {
                deplacement(tabcases,tabjoueur,indice,nbrjoueur,fond);
            }
            if(mouse_x > 1300 && mouse_x < 1350 && mouse_y >750 && mouse_y < 800)
            {
                buffer = chargement_fond(tabcases);
                chargement_perso(tabjoueur,indice,nbrjoueur, buffer);
                combat(tabcases,tabjoueur,indice,nbrjoueur,buffer);
                clear_bitmap(buffer);
                blit(fond, screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }
            if(mouse_x > 1350 && mouse_x < 1400 && mouse_y >750 && mouse_y < 800)
            {
                done = 2;
            }
            Sleep(500);
        }
        time(&end);
        temps = difftime(end, start);
        compte_temps(temps,screen);
        if(temps > 15)
        {
            done = 2;
        }
    }


}


/*t_djikstra djikstra_init(t_joueur** tabjoueur, int indice)
{
    t_djikstra chemin;
    chemin.chemin_trouve = 0;
    for(int i=0; i<16; i++)
    {
        for(int j= 0; j<28; j++)
        {
            chemin.distance[i][j] = 99999;
            chemin.visite[i][j] = 0;
            if(chemin.mapa[i][j]== 8)
            {
                chemin.mapa[i][j] = 0;
            }
        }
    }
    chemin.distance[tabjoueur[indice]->classes.cord_y/50][tabjoueur[indice]->classes.cord_x/50] = 0;
    return chemin;
}

int djikstra_tout_parcourue(t_djikstra chemin)
{
    int toutparcouru = 1;
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<28; j++)
        {
            if(chemin.visite[i][j] == 0)
            {
                toutparcouru = 0;
            }
        }
    }
    return toutparcouru;
}*/


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

