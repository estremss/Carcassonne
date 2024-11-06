#ifndef AFFICHAGE
#define AFFICHAGE

#include <stdlib.h>
#include <stdio.h>
#include "fct_carcassonne.h"
#include "game_structures.h"

// ----------- ANSI COLORS -----------

#define RESET "\e[0m"

// Bold high intensity text
#define BLK "\e[1;90m"
#define RED "\e[1;91m"
#define GRN "\e[1;92m"
#define YEL "\e[1;93m"
#define BLU "\e[1;94m"
#define MAG "\e[1;95m"
#define CYN "\e[1;96m"
#define WHT "\e[1;97m"

// Backgrounds High Intensity
#define BLKHB "\e[0;100m"
#define REDB "\e[0;101m"
#define GRNB "\e[0;102m"
#define YELB "\e[0;103m"
#define BLUB "\e[0;104m"
#define MAGB "\e[0;105m"
#define CYNB "\e[0;106m"
#define WHTB "\e[0;107m"

// Regular backgrounds
#define REDBL "\e[41m"
#define YELBL "\e[43m"
#define BLUBL "\e[44m"
#define MAGBL "\e[45m"
#define CYNBL "\e[46m"
#define WHTBL "\e[47m"
#define BLKBL "\e[40m"

// ------------------------------------

// Underline
#define UWHT "\e[4;37m"

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