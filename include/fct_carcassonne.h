#ifndef FCT_CARCASSONNE
#define FCT_CARCASSONNE
#include "game_structures.h"

void parseur_csv(char *, struct tuile_s *);

void afficher_tuile_dbg(struct tuile_s t);

void melange(struct tuile_s *);

struct tuile_s depiler(struct tuile_s *, int);

int deplacer_tuile_en_derniere_position(struct tuile_s *, int, struct tuile_s[143][143], int, int, int, int);

void parametre_partie(struct tuile_s *, struct tuile_s[143][143], int *, int *);

void afficher_ligne(struct tuile_s[143][143], int, int, int);

void afficher_ligne_couleur(struct tuile_s[143][143], int, int, int);

void affichage(struct tuile_s[143][143], struct tuile_s[72], int, int, struct joueur_s *, int *, int *, int *, int *);

int posable(struct tuile_s[143][143], struct tuile_s, int, int, int, int);

void rotation(struct tuile_s *);

void afficher_tuile_en_cours(struct tuile_s);

void afficher_tuile_en_cours_couleur(struct tuile_s);

void poser_tuile(struct tuile_s[143][143], struct tuile_s[72], int *, int, struct joueur_s *);

void interface_joueur(struct tuile_s[143][143], struct tuile_s[72], int *, int, struct joueur_s *);

void affichage_accueil(void);

void afficher_joueurs(int, int, struct joueur_s *);

void poser_pion(struct tuile_s[143][143], struct joueur_s *, int, int, int, int);

int verif_route(struct tuile_s[143][143], int, int, int, int, int);

int verif_route_iteratif(struct tuile_s[143][143], int, int, int);

void pts_route(struct tuile_s[143][143], int, int, int, struct joueur_s *);

void pts_abbaye(struct tuile_s [143][143], int , int , struct joueur_s *, int , int );

struct position T_direction_route(int, int, int);

#endif // FCT_CARCASSONNE
