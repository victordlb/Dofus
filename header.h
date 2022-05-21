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
    int PV_init;
    int PM;
    int PA;
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
}t_joueur;

typedef struct chemin
{
    int x;
    int y;
    int taille;
}t_chemin;

/*typedef struct djikstra
{
    int chemin_trouve;
    int distance[16][28];
    int visite[16][28];
    int mapa[16][28];
    int predecesseur[16][28];
}t_djikstra;*/

typedef struct charge
{
    t_joueur** tabjoueur;
    int nbrjoueur;
    int indice;
}t_charge;

void initialisation();
void logo();
void menu_principal();
void lancement();
void quitter();
void regle();
int nombre_joueur();
t_classe choix_classe(t_joueur** tab_joueur,int i, int nbrjoueur);
int random_commencer(int nbr);
void tour(t_joueur** tabjoueur, int nbrjoueur, int random, int compteur);
void menu_pause(t_joueur** tabjoueur, int nbrjoueur, int indice);
void infojoueur(t_joueur** tabjoueur, int nbrjoueur);
void dessin_ligne();
t_cases** chargement_map();
BITMAP* charger_map(t_cases** tabcases);


void deplacement(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* fond);
int possibilite_deplacement(t_cases** tabcases,int X, int Y, t_joueur** tabjoueur, int indice);
int testvert(int vert);
int testrouge(int rouge);
int testbleu(int bleu);
t_joueur** initialisation_joueur(int nbrjoueur);
char* saisie_pseudo();
void premier_placement(t_joueur** tabjoueur, int nbrjoueur);
void couleur_case(t_joueur** tabjoueur, t_cases** tabcases, int indice, BITMAP* fond);

t_chemin* itineraire(t_cases** tabcases, t_joueur** tabjoueur, int indice, int finishx, int finishy);
BITMAP* chargement_fond(t_cases** tabcases);
void chargement_perso(t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* buffer);
void choix_action(t_joueur** tabjoueur, int indice, int nbrjoueur);

///sauvegarde et chargement
void sauvegarde(t_joueur** tabjoueur, int nbrjoueur,int indice);
void sauvegarde_tabjoueur(t_joueur** , int nbrjoueur, char* trajet);
void sauvegarde_nbrjoueur(int nbrjoueur, char* trajet);
void sauvegarde_tour(int indice, char* trajet);
t_charge chargement();
char* saisie_nom_sauvegarde();
char* saisie_nom_chargement();
void compte_temps(float temps, BITMAP* buffer);
t_joueur** chargement_infoJoueur(char* nom, int nbrjoueur);
int chargement_indice(char* nom);
int chargement_nbrjoueur(char* nom);

///Combat
void chargerSort(t_joueur** tabjoueur, int indice);
void combat(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, BITMAP* fond);
void afficherSort(t_joueur** tabjoueur, int indice, BITMAP* fond);
void porteSort(t_cases** tabcases, t_joueur** tabjoueur, int indice, int numsort, BITMAP* fond);
void dessinportecroix(t_joueur** tabjoueur, t_cases** tabcases, int indice,int numsort, BITMAP* fond);
int possibcroix(t_cases** tabcases,int X, int Y, t_joueur** tabjoueur, int indice, int numsort);
void dessinportecercle(t_joueur** tabjoueur, t_cases** tabcases, int indice,int numsort, BITMAP* fond);
int possibcercle(t_joueur** tabjoueur,int X, int Y, t_cases** tabcases, int indice,int numsort);
int lancerattaque(t_cases** tabcases, t_joueur** tabjoueur, int indice, int nbrjoueur, int numsort, BITMAP* fond);
void info_sort(t_joueur** tabjoueur, int indice, int num_info, BITMAP* fond);

#endif // HEADER_H_INCLUDED
