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
    char* nom;
    char tpm[500];
    nom = "/saveInfoJoueur.txt";
    printf("test1\n");
    strcat(strcpy(tpm, trajet), nom);
    printf("test1\n");
    printf("%s\n", tpm);
    FILE* fichier = NULL;
    fichier = fopen(tpm, "wba");
    if(fichier == NULL)
    {
        printf("Erreur de creation du fichier\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        fwrite(tabjoueur, sizeof(t_joueur), nbrjoueur, fichier);
    }
    fclose(fichier);
}

void sauvegarde_nbrjoueur(int nbrjoueur, char* trajet)
{
    char* nom;
    char tpm[500];
    nom = "/saveNbrjoueur.bin";
    strcat(strcpy(tpm,trajet), "/saveNbrjoueur.bin");
    FILE* fichier = NULL;
    fichier = fopen(tpm, "wba");
    if(fichier == NULL)
    {
        printf("Erreur de creation du fichier\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        fwrite(&nbrjoueur, sizeof(int), 1, fichier);
    }
    fclose(fichier);
}

void sauvegarde_tour(int indice, char* trajet)
{
    char* nom;
    char tpm[500];
    nom = "/saveTour.bin";
    strcat(strcpy(tpm, trajet), "/saveTour.bin");
    FILE* fichier = NULL;
    fichier = fopen(tpm, "wba");
    if(fichier == NULL)
    {
        printf("Erreur de creation du fichier\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        fwrite(&indice, sizeof(int), 1, fichier);
    }
    fclose(fichier);
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
    nom1 = "/saveInfoJoueur.bin";
    nom2 = "/saveNbrjoueur.bin";
    nom3 = "/saveTour.bin";
    nom = saisie_nom_chargement();
    //tpm = tampon;
    strcat(strcpy(tampon1, trajet), nom);
    strcat(strcpy(tampon2, trajet), nom);
    strcat(strcpy(tampon3, trajet), nom);
    printf("%s\n", tampon1);
    strcat(tampon1, nom1);
    printf("%s\n", tampon1);
    fichier1 = fopen(tampon1, "rb");
   // tampon = tpm;
    strcat(tampon2, nom2);
    printf("%s\n", tampon2);
    fichier2 = fopen(tampon2, "rb");
    //tampon = tpm;
    strcat(tampon3, nom3);
    printf("%s\n", tampon3);
    fichier3 = fopen(tampon3, "rb");
    if(fichier1 == NULL)
    {
        printf("Ce fichier n'existe pas\n");
        validation = 0;
    }
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
        fread(&maCharge.nbrjoueur, sizeof(int), 1, fichier2);
        printf("nbr :%d\n", maCharge.nbrjoueur);
        printf("test\n");
        fread(maCharge.tabjoueur, sizeof(t_joueur), maCharge.nbrjoueur, fichier1);
        /*for(int i=0; i<maCharge.nbrjoueur;i++)
        {
            printf("Joueur %d,%s\n", maCharge.tabjoueur[i]->classes.ID, maCharge.tabjoueur[i].pseudo);
        }*/
        printf("test\n");
        fread(&maCharge.indice, sizeof(int), 1, fichier3);
        printf("test\n");
    }
    fclose(fichier1);
    fclose(fichier2);
    fclose(fichier3);

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
