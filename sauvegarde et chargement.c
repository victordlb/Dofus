#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <synchapi.h>
#include <string.h>
#include <sys/stat.h>
#include "header.h"

void sauvegarde(t_joueur** tabjoueur, int nbrjoueur,int indice)
{
    char* nom;
    char* trajet;
    char tpm[500];
    trajet = "sauvegarde/";
    nom = saisie_nom_sauvegarde();
    printf("%s\n", trajet);
    strcat(strcpy(tpm, trajet), nom);
    printf("%s\n", tpm);
    mkdir(tpm);
    //trajet = tpm;
    printf("test1\n");
    sauvegarde_tabjoueur(tabjoueur,nbrjoueur, tpm);
    sauvegarde_nbrjoueur(nbrjoueur, tpm);
    sauvegarde_tour(indice,tpm);
}

void sauvegarde_tabjoueur(t_joueur** tabjoueur, int nbrjoueur, char* trajet)
{
    for(int i=0; i<nbrjoueur; i++)
    {
        char* nom;
        char tpm[500];
        if(i == 0)
        {
            nom = "/saveInfoJoueur1.txt";
        }
        if(i == 1)
        {
            nom = "/saveInfoJoueur2.txt";
        }
        if(i == 2)
        {
            nom = "/saveInfoJoueur3.txt";
        }
        if(i == 3)
        {
            nom = "/saveInfoJoueur4.txt";
        }
        printf("test1\n");
        strcat(strcpy(tpm, trajet), nom);
        printf("test1\n");
        printf("%s\n", tpm);
        FILE* fichier1 = NULL;
        fichier1 = fopen(tpm, "wba");
        if(fichier1 == NULL)
        {
            printf("Erreur de creation du fichier\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            fprintf(fichier1, "%s\n", tabjoueur[i]->pseudo);
            fprintf(fichier1, "%s\n", tabjoueur[i]->classes.nom);
            fprintf(fichier1, "%d %d %d %d %d %d %d",  tabjoueur[i]->perdu, tabjoueur[i]->classes.PV,tabjoueur[i]->classes.PM,tabjoueur[i]->classes.PA,tabjoueur[i]->classes.ID, tabjoueur[i]->classes.cord_x, tabjoueur[i]->classes.cord_y);
        }
        fclose(fichier1);
    }
}

void sauvegarde_nbrjoueur(int nbrjoueur, char* trajet)
{
    char* nom;
    char tpm[500];
    nom = "/saveNbrjoueur.txt";
    strcat(strcpy(tpm,trajet), "/saveNbrjoueur.txt");
    FILE* fichier2 = NULL;
    printf("%s\n", tpm);
    fichier2 = fopen(tpm, "wba");
    if(fichier2 == NULL)
    {
        printf("Erreur de creation du fichier\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(fichier2, "%d", nbrjoueur);
    }
    fclose(fichier2);
}

void sauvegarde_tour(int indice, char* trajet)
{
    char* nom;
    char tpm[500];
    nom = "/saveTour.txt";
    strcat(strcpy(tpm, trajet), "/saveTour.txt");
    FILE* fichier3 = NULL;
    printf("%s\n", tpm);
    fichier3 = fopen(tpm, "wba");
    if(fichier3 == NULL)
    {
        printf("Erreur de creation du fichier\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(fichier3, "%d", indice);
    }
    fclose(fichier3);
}

int chargement_nbrjoueur(char* nom)
{
    char* trajet;
    int validation = 2;
    int nbrjoueur;
    trajet = "sauvegarde/";
    char* nom2;
    char tampon2[500];
    nom2 = "/saveNbrjoueur.txt";
    FILE* fichier2;
    strcat(strcpy(tampon2, trajet), nom);
    strcat(tampon2, nom2);
    printf("%s\n", tampon2);
    fichier2 = fopen(tampon2, "rb");
    if(fichier2 == NULL)
    {
        printf("Ce fichier n'existe pas\n");
        validation = 0;
    }
    if(validation != 0)
    {
        fscanf(fichier2,"%d",&nbrjoueur);
        fclose(fichier2);
        printf("nbr :%d\n", nbrjoueur);
    }
    return nbrjoueur;
}

int chargement_indice(char* nom)
{
    char* trajet;
    int validation = 2;
    int indice;
    trajet = "sauvegarde/";
    char* nom3;
    char tampon3[500];
    nom3 = "/saveTour.txt";
    FILE* fichier3;
    strcat(strcpy(tampon3, trajet), nom);
    strcat(tampon3, nom3);
    printf("%s\n", tampon3);
    fichier3 = fopen(tampon3, "rb");
    if(fichier3 == NULL)
    {
        printf("Ce fichier n'existe pas\n");
        validation = 0;
    }
    if(validation != 0)
    {
        fscanf(fichier3,"%d",&indice);
        fclose(fichier3);
        printf("indice :%d\n", indice);
    }
    return indice;
}

t_joueur** chargement_infoJoueur(char* nom, int nbrjoueur)
{
    char nom1[500];
    char nom2[500];
    char nom3[500];
    char nom4[500];
    int validation = 2;
    t_joueur** tab;
    FILE* fichier1;
    FILE* fichier2;
    FILE* fichier3;
    FILE* fichier4;
    tab = (t_joueur**)malloc(sizeof(t_joueur*)*1);
    tab = (t_joueur*)malloc(sizeof(t_joueur)*nbrjoueur+1);
    for(int j = 0; j<nbrjoueur; j++)
    {
        if(tab[j] == NULL)
            printf("erreur\n");
    }
    char tampon1[500];
    char* trajet;
    trajet = "sauvegarde/";
    strcat(strcpy(tampon1, trajet), nom);
    printf("tampon %s\n", tampon1);
    char tpm1[500];
    char tpm2[500];
    char tpm3[500];
    char* tpm_pseudo;
    char* tpm_nom_classe;
    char* tpm_pseudo1;
    char* tpm_nom_classe1;
    char* tpm_pseudo2;
    char* tpm_nom_classe2;
    char* tpm_pseudo3;
    char* tpm_nom_classe3;
    for(int i=0; i<nbrjoueur; i++)
    {
        printf("i :%d\n", i);
        tpm_pseudo = (char*)malloc(sizeof(char)*500);
        tpm_nom_classe = (char*)malloc(sizeof(char)*500);
        tpm_pseudo1 = (char*)malloc(sizeof(char)*500);
        tpm_nom_classe1 = (char*)malloc(sizeof(char)*500);
        tpm_pseudo2 = (char*)malloc(sizeof(char)*500);
        tpm_nom_classe2 = (char*)malloc(sizeof(char)*500);
        tpm_pseudo3 = (char*)malloc(sizeof(char)*500);
        tpm_nom_classe3 = (char*)malloc(sizeof(char)*500);
        printf("slt\n");
        if(i == 0)
        {
            strcpy(nom1, "/saveInfoJoueur1.txt" );
            //nom1 = "/saveInfoJoueur1.txt";
            strcpy(tpm1, tampon1);
            strcat(tampon1, nom1);
            printf("%s\n", nom1);
            printf("%s\n", tampon1);
            fichier1 = fopen(tampon1, "r+");
            if(fichier1 == NULL)
            {
                printf("Ce fichier n'existe pas\n");
            }
            else
            {
                char* test;
                printf("test1\n");
                fgets(tpm_pseudo, 500, fichier1);
                printf("nom :%s\n", tpm_pseudo);
                test = (char*)malloc(sizeof(char)*(strlen(tpm_pseudo)) +1 );
                strcpy(test, tpm_pseudo);
                printf("nom :%s\n", test);
                printf("test4\n");

                tab[i]->pseudo = (char*)malloc(sizeof(char)*(strlen(tpm_pseudo)) +1 );
                printf("test6\n");
                strcpy(tab[i]->pseudo, tpm_pseudo);
                printf("nom :%s\n", tab[i]->pseudo);

                fgets(tpm_nom_classe, 500, fichier1);
                printf("test5\n");
                tab[i]->classes.nom = (char*)malloc(sizeof(char)*(strlen(tpm_nom_classe)) +1 );
                strcpy(tab[i]->classes.nom, tpm_nom_classe);
                printf(" nom %s\n", tab[i]->classes.nom);

                printf("test3\n");

                fscanf(fichier1, "%d %d %d %d %d %d %d", &tab[i]->perdu, &tab[i]->classes.PV, &tab[i]->classes.PM, &tab[i]->classes.PA, &tab[i]->classes.ID, &tab[i]->classes.cord_x, &tab[i]->classes.cord_y);
                printf("PV :%d\n", tab[i]->classes.PV);
                printf("test2\n");
                test = NULL;
            }
            fclose(fichier1);
        }
        else if(i==1)
        {
            strcpy(nom2, "/saveInfoJoueur2.txt" );
            //nom1 = "/saveInfoJoueur2.txt";
            strcpy(tpm2, tpm1);
            printf("%s\n", tpm2);
            strcat(tpm1, nom2);
            printf("%s\n", tpm1);
            fichier2 = fopen(tpm1, "r+");
            if(fichier2 == NULL)
            {
                printf("Ce fichier n'existe pas\n");
            }
            else
            {
                char* test;
                printf("test1\n");
                fgets(tpm_pseudo1, 500, fichier2);
                printf("nom :%s\n", tpm_pseudo1);
                test = (char*)malloc(sizeof(char)*(strlen(tpm_pseudo1)) +1 );
                strcpy(test, tpm_pseudo1);
                printf("nom :%s\n", test);
                printf("test4\n");

                tab[i]->pseudo = (char*)malloc(sizeof(char)*(strlen(tpm_pseudo1)) +1 );
                printf("test6\n");
                strcpy(tab[i]->pseudo, tpm_pseudo1);
                printf("nom :%s\n", tab[i]->pseudo);

                fgets(tpm_nom_classe1, 500, fichier2);
                printf("test5\n");
                tab[i]->classes.nom = (char*)malloc(sizeof(char)*(strlen(tpm_nom_classe1)) +1 );
                strcpy(tab[i]->classes.nom, tpm_nom_classe1);
                printf(" nom %s\n", tab[i]->classes.nom);

                printf("test3\n");

                fscanf(fichier2, "%d %d %d %d %d %d %d", &tab[i]->perdu, &tab[i]->classes.PV, &tab[i]->classes.PM, &tab[i]->classes.PA, &tab[i]->classes.ID, &tab[i]->classes.cord_x, &tab[i]->classes.cord_y);
                printf("PV :%d\n", tab[i]->classes.PV);
                printf("test2\n");
                test = NULL;
            }
            fclose(fichier2);
        }
        else if(i==2)
        {
           // tab[i] = (t_joueur*)malloc(sizeof(t_joueur));
            printf("pap\n");
            strcpy(nom3, "/saveInfoJoueur3.txt" );
            //nom1 = "/saveInfoJoueur3.txt";
            strcpy(tpm3, tpm2);
            printf("%s\n", tpm3);
            strcat(tpm2, nom3);
            printf("%s\n", tpm2);
            fichier3 = fopen(tpm2, "r+");
            if(fichier3 == NULL)
            {
                printf("Ce fichier n'existe pas\n");
            }
            else
            {
                char* test;
                printf("test1\n");
                fgets(tpm_pseudo2, 500, fichier3);
                printf("nom :%s\n", tpm_pseudo2);
                test = (char*)malloc(sizeof(char)*(strlen(tpm_pseudo2)) +1 );
                strcpy(test, tpm_pseudo2);
                printf("nom :%s\n", test);
                printf("test4\n");

                tab[i]->pseudo = (char*)malloc(sizeof(char)*(strlen(tpm_pseudo2)) +1 );
                printf("test6\n");
                strcpy(tab[i]->pseudo, tpm_pseudo2);
                printf("nom :%s\n", tab[i]->pseudo);

                fgets(tpm_nom_classe2, 500, fichier3);
                printf("test5\n");
                tab[i]->classes.nom = (char*)malloc(sizeof(char)*(strlen(tpm_nom_classe2)) +1 );
                strcpy(tab[i]->classes.nom, tpm_nom_classe2);
                printf(" nom %s\n", tab[i]->classes.nom);

                printf("test3\n");

                fscanf(fichier3, "%d %d %d %d %d %d %d", &tab[i]->perdu, &tab[i]->classes.PV, &tab[i]->classes.PM, &tab[i]->classes.PA, &tab[i]->classes.ID, &tab[i]->classes.cord_x, &tab[i]->classes.cord_y);
                printf("PV :%d\n", tab[i]->classes.PV);
                printf("test2\n");
                test = NULL;
            }
            fclose(fichier3);

        }
        else if(i==3)
        {
            strcpy(nom4, "/saveInfoJoueur4.txt" );
            //nom1 = "/saveInfoJoueur4.txt";
            strcat(tpm3, nom4);
            printf("%s\n", tpm3);
            fichier4 = fopen(tpm3, "r+");
            if(fichier4 == NULL)
            {
                printf("Ce fichier n'existe pas\n");
            }
            else
            {
                char* test;
                printf("test1\n");
                fgets(tpm_pseudo3, 500, fichier4);
                printf("nom :%s\n", tpm_pseudo3);
                test = (char*)malloc(sizeof(char)*(strlen(tpm_pseudo3)) +1 );
                strcpy(test, tpm_pseudo3);
                printf("nom :%s\n", test);
                printf("test4\n");

                tab[i]->pseudo = (char*)malloc(sizeof(char)*(strlen(tpm_pseudo3)) +1 );
                printf("test6\n");
                strcpy(tab[i]->pseudo, tpm_pseudo3);
                printf("nom :%s\n", tab[i]->pseudo);

                fgets(tpm_nom_classe3, 500, fichier4);
                printf("test5\n");
                tab[i]->classes.nom = (char*)malloc(sizeof(char)*(strlen(tpm_nom_classe3)) +1 );
                strcpy(tab[i]->classes.nom, tpm_nom_classe3);
                printf(" nom %s\n", tab[i]->classes.nom);

                printf("test3\n");

                fscanf(fichier4, "%d %d %d %d %d %d %d", &tab[i]->perdu, &tab[i]->classes.PV, &tab[i]->classes.PM, &tab[i]->classes.PA, &tab[i]->classes.ID, &tab[i]->classes.cord_x, &tab[i]->classes.cord_y);
                printf("PV :%d\n", tab[i]->classes.PV);
                printf("test2\n");
                test = NULL;
            }
            fclose(fichier4);
        }
        tpm_nom_classe = NULL;
        tpm_pseudo = NULL;
        tpm_nom_classe1 = NULL;
        tpm_pseudo1 = NULL;
        tpm_nom_classe2 = NULL;
        tpm_pseudo2 = NULL;
        tpm_nom_classe3 = NULL;
        tpm_pseudo3 = NULL;
        printf("joueur suivant\n");
    }
    return tab;
}

t_charge chargement()
{
    t_charge maCharge;
    char* nom;
    char* nom1;
    char* nom2;
    char* nom3;
    char* tpm;
    char* trajet;
    trajet = "sauvegarde/";
    char tampon1[500];
    char tampon2[500];
    char tampon3[500];
    FILE* fichier1;
    FILE* fichier2;
    FILE* fichier3;
    int validation = 1;
    nom2 = "/saveNbrjoueur.txt";
    nom3 = "/saveTour.txt";
    nom = saisie_nom_chargement();
    //tpm = tampon;
    strcat(strcpy(tampon1, trajet), nom);
    strcat(strcpy(tampon2, trajet), nom);
    strcat(strcpy(tampon3, trajet), nom);
    printf("%s\n", tampon1);
    // tampon = tpm;
    strcat(tampon2, nom2);
    printf("%s\n", tampon2);
    fichier2 = fopen(tampon2, "rb");
    //tampon = tpm;
    strcat(tampon3, nom3);
    printf("%s\n", tampon3);
    fichier3 = fopen(tampon3, "rb");
    if(fichier2 == NULL)
    {
        printf("Ce fichier n'existe pas\n");
        validation = 0;
    }
    if(fichier3 == NULL)
    {
        printf("Ce fichier n'existe pas\n");
        validation = 0;
    }
    if(validation != 0)
    {
        printf("test\n");
        fscanf(fichier2,"%d",&maCharge.nbrjoueur);
        fclose(fichier2);
        //fread(&maCharge.nbrjoueur, sizeof(int), 1, fichier2);
        printf("nbr :%d\n", maCharge.nbrjoueur);
        printf("test\n");
        //fread(maCharge.tabjoueur, sizeof(t_joueur), maCharge.nbrjoueur, fichier1);
        /*for(int i=0; i<maCharge.nbrjoueur;i++)
        {
            printf("Joueur %d,%s\n", maCharge.tabjoueur[i]->classes.ID, maCharge.tabjoueur[i]->pseudo);
        }*/
        printf("test\n");
        fscanf(fichier3, "%d", &maCharge.indice);
        fclose(fichier3);
        //fread(&maCharge.indice, sizeof(int), 1, fichier3);
        printf("indice :%d\n", maCharge.indice);
        printf("test\n");
    }
    char tpm1[500];
    char tpm2[500];
    char tpm3[500];
    char tpm_pseudo[500];
    char tpm_nom_classe[500];
    for(int i=0; i<maCharge.nbrjoueur; i++)
    {
        if(i == 0)
        {
            //strcpy(nom1, "/saveInfoJoueur1.txt" );
            nom1 = "/saveInfoJoueur1.txt";
            strcpy(tpm1, tampon1);
            strcat(tampon1, nom1);
            printf("%s\n", nom1);
            printf("%s\n", tampon1);
            fichier1 = fopen(tampon1, "rb");
        }
        else if(i==1)
        {
            //strcpy(nom1, "/saveInfoJoueur2.txt" );
            nom1 = "/saveInfoJoueur2.txt";
            strcpy(tpm2, tpm1);
            printf("%s\n", tpm2);
            strcat(tpm1, nom1);
            printf("%s\n", tpm1);
            fichier1 = fopen(tpm1, "rb");
        }
        else if(i==2)
        {
            //strcpy(nom1, "/saveInfoJoueur3.txt" );
            nom1 = "/saveInfoJoueur3.txt";
            strcpy(tpm3, tpm2);
            strcat(tpm2, nom1);
            printf("%s\n", tpm2);
            fichier1 = fopen(tpm2, "rb");
        }
        else if(i==3)
        {
            //strcpy(nom1, "/saveInfoJoueur4.txt" );
            nom1 = "/saveInfoJoueur4.txt";
            strcat(tpm3, nom1);
            printf("%s\n", tpm3);
            fichier1 = fopen(tpm3, "rb");
        }
        if(fichier1 == NULL)
        {
            printf("Ce fichier n'existe pas\n");
        }
        else
        {
            printf("test1\n");
            fgets(tpm_pseudo, 500, fichier1);
            printf("test4\n");
            fgets(tpm_nom_classe, 500, fichier1);
            printf("test5\n");
            maCharge.tabjoueur[i]->pseudo = (char*)malloc((strlen(tpm_pseudo) +1 )* sizeof(char));
            printf("test6\n");
            strcpy(maCharge.tabjoueur[i]->pseudo, tpm_pseudo);
            printf("test7\n");
            maCharge.tabjoueur[i]->classes.nom = (char*)malloc((strlen(tpm_nom_classe) +1 )* sizeof(char));
            strcpy(maCharge.tabjoueur[i]->classes.nom, tpm_nom_classe);
            printf("test3\n");

            fscanf(fichier1, "%d %d %d %d %d %d %d", &maCharge.tabjoueur[i]->perdu, &maCharge.tabjoueur[i]->classes.PV, &maCharge.tabjoueur[i]->classes.PM, &maCharge.tabjoueur[i]->classes.PA, &maCharge.tabjoueur[i]->classes.ID, &maCharge.tabjoueur[i]->classes.cord_x, &maCharge.tabjoueur[i]->classes.cord_y);
            printf("test2\n");
        }
        fclose(fichier1);
    }
    return maCharge;
}

char* saisie_nom_sauvegarde()
{
    BITMAP* fond;
    fond = load_bitmap("documents/fond/fond sauvegarde.bmp", NULL);
    char* pseudo;
    int touche, touche1, touche2;
    int i=0;
    char masaisie[21]; // stockage de la totalité de la saisie
    char lastsaisie[2];    // stockage la derniere touche saisie
    masaisie[20]=0;
    lastsaisie[1]=0;
    clear_keybuf();
    textprintf_ex(fond, font, 400, 250, makecol(255,255,255),0,"DONNER UN NOM A VOTRE PARTIE : (entree pour valider)");
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

char* saisie_nom_chargement()
{
    BITMAP* fond;
    fond = load_bitmap("documents/fond/fond sauvegarde.bmp", NULL);
    char* pseudo;
    int touche, touche1, touche2;
    int i=0;
    char masaisie[21]; // stockage de la totalité de la saisie
    char lastsaisie[2];    // stockage la derniere touche saisie
    masaisie[20]=0;
    lastsaisie[1]=0;
    clear_keybuf();
    textprintf_ex(fond, font, 400, 250, makecol(255,255,255),0,"TAPER LE NOM DE LA PARTIE QUE VOUS VOULEZ CHARGER : (entree pour valider)");
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
