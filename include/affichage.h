#ifndef AFFICHAGE
#define AFFICHAGE
#include <stdlib.h>
#include "fct_carcassonne.h"
#include "game_structures.h"

// Utilisée pour débuguer lors de la création de notre fonction d'affichage en couleur
void afficher_tuile_dbg(struct tuile_s t);

// Permet d'afficher une ligne l de la grille (sans couleur)
void afficher_ligne(struct tuile_s[143][143], int, int, int);

// Permet d'afficher une ligne l de la grille (en couleur) 
void afficher_ligne_couleur(struct tuile_s[143][143], int, int, int);

// Permet l'affichage complet de la grille (en couleur ou non selon les appels de fonction à l'intérieur)
void affichage(struct tuile_s[143][143], struct tuile_s[72], int, int, struct joueur_s *, int *, int *, int *, int *);

// Affiche la tuile en main (sans couleur)
void afficher_tuile_en_cours(struct tuile_s);

// Affiche la tuile en main (en couleur)
void afficher_tuile_en_cours_couleur(struct tuile_s);

// Affiche l'écran d'arrivée sur le jeu (ASCII Art Carcassonne)
void affichage_accueil(void);

// Affiche les informations sur les joueurs au dessus de la grille de jeu
void afficher_joueurs(int, int, struct joueur_s *);

// Affiche l'écran du choix du nombre de joueurs et d'IA
void affichage_menu(void);

// Affiche le tableau des scores
void affichage_fin(struct joueur_s *, int);

#endif // AFFICHAGE