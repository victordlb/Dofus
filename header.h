#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

///structure de caracteristique d'attaque
typedef struct attaque
{
    char* nom;
    int consequence_PA;
    int modulo_echec;
    int degats;
    int type;  //1 = croix, 2 = cercle
    int porte;
    int consequence_PM; //fonctionnalité non utilisée
    int effet_spe; //fonctionnalité non utilisée
}t_attaque;

///structure de caracteristique de classe
typedef struct classe
{
    char* nom;
    int ID;
    int PV;
    int PM;
    int PA;
    int PV_init;
    int PM_init;
    int PA_init;
    t_attaque* mesattaques;
    int cord_x;
    int cord_y;
}t_classe;

///structure de caracteristique de cases
typedef struct cases
{
    int x;
    int y;
    int obstacle;
    int cases;
    int indice;
}t_cases;

///structure de caracteristique de joueur
typedef struct joueur
{
    char* pseudo;
    t_classe classes;
    int perdu;
    int ordre;
}t_joueur;

/// structure de caracteristique de chemin
typedef struct chemin
{
    int x;
    int y;
    int taille;
}t_chemin;


///affichage_allegro
void initialisation();
void logo();
int menu_principal();
void lancement();
void quitter();
void regle();
int nombre_joueur();
t_classe choix_classe(t_joueur** tab_joueur,int i, int nbrjoueur);
int menu_pause(t_joueur** tabjoueur, int nbrjoueur, int indice,int choix);
void infojoueur(t_joueur** tabjoueur, int nbrjoueur);
void classement(t_joueur** tabjoueur, int nbrjoueur);
int menu_fin_de_jeu();
int choix_map();

///tour_joueur
char* saisie_pseudo();
t_joueur** initialisation_joueur(int nbrjoueur,int choix);
int random_commencer(int nbr);
void tour(t_joueur** tabjoueur, int nbrjoueur, int indice, int compteur,int choix_mapa);
void choix_action(t_joueur** tabjoueur, int indice, int nbrjoueur,int choix);
void compte_temps(float temps, BITMAP* buffer);

///LES MAPS
void dessin_ligne();
t_cases** chargement_map(int choix);
BITMAP* charger_map(t_cases** tabcases, int choix);
void dessin_haut_arbre(BITMAP* fond, t_cases** tabcases);
int testvert(int vert);
int testrouge(int rouge);
int testbleu(int bleu);
BITMAP* chargement_fond(t_cases** tabcases,int choix);
void chargement_perso(t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* buffer, int etat);

///deplacement
void deplacement(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* fond, int choix);
void premier_placement(t_joueur** tabjoueur, int nbrjoueur,int choix);
t_chemin* djikstra(t_cases** tabcases, int pos_col_pers,int pos_lig_pers, int arrivee_col, int arrivee_lig);
void couleur_case_bis(t_joueur** tabjoueur, t_cases** tabcases, int indice, BITMAP* fond);
int possibilite_deplacement_bis(t_joueur** tabjoueur, t_cases** tabcases, int indice, int X, int Y);
//ancienne fonction de deplacement non-utilisee dans le code final
void couleur_case(t_joueur** tabjoueur, t_cases** tabcases, int indice, BITMAP* fond);
t_chemin* itineraire(t_cases** tabcases, t_joueur** tabjoueur, int indice, int finishx, int finishy);
int possibilite_deplacement(t_cases** tabcases,int X, int Y, t_joueur** tabjoueur, int indice);

///sauvegarde et chargement
void sauvegarde(t_joueur** tabjoueur, int nbrjoueur,int indice, int choix);
void sauvegarde_tabjoueur(t_joueur** , int nbrjoueur, char* trajet);
void sauvegarde_tabjoueur_bis(t_joueur** tabjoueur, int nbrjoueur, char* trajet);
void sauvegarde_nbrjoueur(int nbrjoueur, char* trajet);
void sauvegarde_tour(int indice, char* trajet);
void sauvegarde_choixmap(int choix, char* trajet);

char* saisie_nom_sauvegarde();
char* saisie_nom_chargement();

t_joueur** chargement_infoJoueur(char* nom, int nbrjoueur);
t_joueur** chargement_infoJoueur_bis(char* nom, int nbrjoueur);
int chargement_indice(char* nom);
int chargement_nbrjoueur(char* nom);
int chargement_choix_map(char* nom);

///Combat
void chargerSort(t_joueur** tabjoueur, int indice);
void combat(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* fond, int choix);
void afficherSort(t_joueur** tabjoueur, int indice, BITMAP* fond);
void porteSort(t_cases** tabcases, t_joueur** tabjoueur, int indice, int numsort, BITMAP* fond);
void dessinportecroix(t_joueur** tabjoueur, t_cases** tabcases, int indice,int numsort, BITMAP* fond);
int possibcroix(t_cases** tabcases,int X, int Y, t_joueur** tabjoueur, int indice, int numsort);
void dessinportecercle(t_joueur** tabjoueur, t_cases** tabcases, int indice,int numsort, BITMAP* fond);
int possibcercle(t_joueur** tabjoueur,int X, int Y, t_cases** tabcases, int indice,int numsort);
int possibmelee(t_joueur** tabjoueur,int X, int Y, t_cases** tabcases, int indice,int numsort);
void dessinportemelee(t_joueur** tabjoueur, t_cases** tabcases, int indice,int numsort, BITMAP* fond);
int lancerattaque(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, int numsort, BITMAP* fond);
void info_sort(t_joueur** tabjoueur, int indice, int num_info, BITMAP* fond);

#endif // HEADER_H_INCLUDED
