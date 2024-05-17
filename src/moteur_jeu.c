#include <stdio.h>
#include "game_structures.h"
#include "fct_carcassonne.h"
#include "affichage.h"

#define NB_TUILES 72

int nb_tours = 0, nb_joueurs, nb_ia;
int h = 143, b = 0, g = 143, d = 0; // variables globales qui identifient les coordonnées extrémales de la grille

struct tuile_s Pile[NB_TUILES];  // la pile de tuiles
struct tuile_s Grille[143][143]; // la grille de jeu
struct joueur_s Joueurs[5];      // Le tableau de joueurs

int main(void)
{
    parseur_csv("tuiles_base_simplifiees.csv", Pile);
    affichage_accueil();
    affichage_menu();
    parametre_partie(Pile, Grille, &nb_joueurs, &nb_ia, Joueurs);
    nb_joueurs += nb_ia;
    nb_tours++;

    // Boucle de gameplay
    while (nb_tours < 71)
    {
        deplacer_tuile_en_derniere_position(Pile, nb_tours, Grille, h, b, g, d);
        affichage(Grille, Pile, nb_tours, nb_joueurs, Joueurs, &h, &b, &g, &d);
        if (Joueurs[(nb_tours - 1) % nb_joueurs].ia == 0)
            interface_joueur(Grille, Pile, &nb_tours, nb_joueurs, Joueurs, h, b, g, d);
        else
        {
            poser_tuile(Grille, Pile, &nb_tours, nb_joueurs, Joueurs, h, b, g, d);
        }
    }
    pts_FP(Grille, Joueurs);
    affichage_fin(Joueurs, nb_joueurs);

    return 0;
}