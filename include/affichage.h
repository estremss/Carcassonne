#ifndef AFFICHAGE
#define AFFICHAGE
#include <stdlib.h>
#include "fct_carcassonne.h"
#include "game_structures.h"

void afficher_tuile_dbg(struct tuile_s t);

void afficher_ligne(struct tuile_s[143][143], int, int, int);

void afficher_ligne_couleur(struct tuile_s[143][143], int, int, int);

void affichage(struct tuile_s[143][143], struct tuile_s[72], int, int, struct joueur_s *, int *, int *, int *, int *);

void afficher_tuile_en_cours(struct tuile_s);

void afficher_tuile_en_cours_couleur(struct tuile_s);

void affichage_accueil(void);

void afficher_joueurs(int, int, struct joueur_s *);

void affichage_menu(void);

void affichage_fin(struct joueur_s *, int);


#endif // AFFICHAGE