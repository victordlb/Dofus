#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

typedef struct attaque
{
    char* nom;
    int consequence_PA;
    int modulo_echec;
    int degats;
    int porte;
    int consequence_PM;
}t_attaque;

typedef struct classe
{
    char* nom;
    int ID;
    int PV;
    int PM;
    int PA;
    t_attaque** mesattaques;
    int cord_x;
    int cord_y;
}t_classe;

typedef struct cases
{
    int x;
    int y;
    int obstacle;
    int cases;
}t_cases;

/// fin de la partie : on sauvegarde le pseudo avec la classe qu'il a choisit et son niveau
/// début d'une prochaine partie : si on reconnait le pseudo et qu'il choisi la meme classe on lui indique le niveau
typedef struct joueur
{
    char* pseudo;
    t_classe classes;
    int perdu;
}t_joueur;


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
void menu_pause(t_joueur** tabjoueur, int nbrjoueur);
void infojoueur(t_joueur** tabjoueur, int nbrjoueur);
void dessin_ligne();
t_cases** chargement_map();
BITMAP* charger_map(t_cases** tabcases);

void deplacement(t_joueur** tabjoueur, int indice);
int possibilite_deplacement(t_cases** tabcases,int X, int Y);
int testvert(int vert);
int testrouge(int rouge);
int testbleu(int bleu);
t_joueur** initialisation_joueur(int nbrjoueur);
char* saisie_pseudo();

#endif // HEADER_H_INCLUDED
