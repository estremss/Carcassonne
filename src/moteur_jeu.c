#include <stdio.h>
#include "game_structures.h"
#include "fct_carcassonne.h"
#include "affichage.h"
//#include "raylib.h"

#define NB_TUILES 72
#define GRN "\e[1;92m"
#define RESET "\e[0m"
#define REDB "\e[0;101m"
#define GRNB "\e[0;102m"
#define YELB "\e[0;103m"
#define BLUB "\e[0;104m"
#define MAGB "\e[0;105m"
#define CYNB "\e[0;106m"
#define WHTB "\e[0;107m"

int nb_tours = 0, nb_joueurs, nb_ia;
int h = 143, b = 0, g = 143, d = 0;

struct tuile_s Pile[NB_TUILES];  // la pile de tuiles
struct tuile_s Grille[143][143]; // la grille de jeu
struct joueur_s Joueurs[5];

int main(void)
{
    /*
    InitWindow(1920, 1080, "Carcassonne");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 50, 50, 30, BLACK);

        EndDrawing();
    }
    CloseWindow();
    */
    parseur_csv("tuiles_base_simplifiees.csv", Pile);
    affichage_accueil();
    affichage_menu();
    parametre_partie(Pile, Grille, &nb_joueurs, &nb_ia);
    nb_tours++;

    // Boucle de gameplay
    while (nb_tours < 72)
    {
        affichage(Grille, Pile, nb_tours, nb_joueurs, Joueurs, &h, &b, &g, &d);
        interface_joueur(Grille, Pile, &nb_tours, nb_joueurs, Joueurs);
    }
    
    return 0;
}
