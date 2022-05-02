#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

typedef struct joueur
{
    char* nom;
    int ID;
    int PV;
    int PM;
    int PA;
    int perdu;
}t_joueur;

typedef struct cases
{
    int x;
    int y;
    int obstacle;
}t_cases;

void initialisation();
void logo();
void menu_principal();
void lancement();
void quitter();
void regle();
int nombre_joueur();
t_joueur** choix_perso(int nbr_joueur);
int random_commencer(int nbr);
void tour(t_joueur** tabjoueur, int nbrjoueur, int random, int compteur);
void menu_pause(t_joueur** tabjoueur, int nbrjoueur);
void infojoueur(t_joueur** tabjoueur, int nbrjoueur);
void dessin_ligne();
t_cases** chargement_map();
void deplacement();
int possibilite_deplacement(t_cases** tabcases,int X, int Y);
int testvert(int vert);
int testrouge(int rouge);
int testbleu(int bleu);

#endif // HEADER_H_INCLUDED
