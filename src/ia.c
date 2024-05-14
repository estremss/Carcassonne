#define NB_TUILES 72
#include "ia.h"

// IA Niveau 0 (pose une tuile et un pion dès qu'elle peut)
void tour_ia(struct tuile_s Grille[143][143], struct tuile_s Pile[NB_TUILES], int *nb_tours, int nb_joueurs, struct joueur_s *Joueur, int h, int b, int g, int d)
{
    int i, j, k;

    for (k = 0; k < 3; k++)
    {
        for (i = h; i < b; i++)
            for (j = g; i < d; j++)
                if (Grille[i][j].jouable == 'O')
                {
                    // poser_tuile(Grille, Pile, nb_tours, nb_joueurs, Joueur, h, b, g, d);
                    // return;
                }
        rotation(&Pile[*nb_tours]);
    }
}