#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

typedef struct attaque
{
    char* nom;
    int consequence_PA;
    int modulo_echec;
    int degats;
    int type;  //1 = croix, 2 = cercle, 3 = zone + cercle
    int porte;
    int consequence_PM; //1 = plus de mouvement, 0 = rien, 2 = avance de cases, 3 = plus 5 PM
    int effet_spe; // 1 = augmentation echec, 2 = blessure, 3 = defense, 4 = critique, 5 = enflamme, 6 = bloque les PM
}t_attaque;

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

typedef struct cases
{
    int x;
    int y;
    int obstacle;
    int cases;
    int indice;
}t_cases;

/// fin de la partie : on sauvegarde le pseudo avec la classe qu'il a choisit et son niveau
/// début d'une prochaine partie : si on reconnait le pseudo et qu'il choisi la meme classe on lui indique le niveau
typedef struct joueur
{
    char* pseudo;
    t_classe classes;
    int perdu;
    int ordre;
}t_joueur;

typedef struct chemin
{
    int x;
    int y;
    int taille;
}t_chemin;


typedef struct charge
{
    t_joueur** tabjoueur;
    int nbrjoueur;
    int indice;
}t_charge;

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

///LA MAP
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
void sauvegarde_nbrjoueur(int nbrjoueur, char* trajet);
void sauvegarde_tour(int indice, char* trajet);
void sauvegarde_choixmap(int choix, char* trajet);
t_charge chargement();
char* saisie_nom_sauvegarde();
char* saisie_nom_chargement();
t_joueur** chargement_infoJoueur(char* nom, int nbrjoueur);
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
