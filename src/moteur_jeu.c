#include <stdio.h>
#include "game_structures.h"
#include "fct_carcassonne.h"

#define NB_TUILES 72

int nb_tours = 0, nb_joueurs, nb_ia;
int h = 143, b = 0, g = 143, d = 0;

struct tuile_s Pile[NB_TUILES];  // la pile de tuiles
struct tuile_s Grille[143][143]; // la grille de jeu
struct joueur_s Joueurs[5];

int main(void)
{

    parseur_csv("tuiles_base_simplifiees.csv", Pile);
    affichage_accueil();
    initialiser_partie(Pile, Grille, &nb_joueurs, &nb_ia);
    nb_tours++;

    // Boucle de gameplay
    while (nb_tours < 72)
    {
        affichage(Grille, Pile, nb_tours, nb_joueurs, Joueurs, &h, &b, &g, &d);
        interface_joueur(Grille, Pile, &nb_tours, nb_joueurs, Joueurs, &h, &b, &g, &d);
    }

    

    return 0;
}
