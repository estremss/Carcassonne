#ifndef FCT_CARCASSONNE
#define FCT_CARCASSONNE
#include "game_structures.h"

// Parse le fichier CSV de tuiles et les mets dans la pile
void parseur_csv(char *, struct tuile_s *);

// Mélange la pile de tuiles
void melange(struct tuile_s *);

// Dépile et retourne la tuile dépilée
struct tuile_s depiler(struct tuile_s *, int);

// Quand une tuile ne peut pas être posée sur le plateau, cette fonction la remet à la fin de la pile
int deplacer_tuile_en_derniere_position(struct tuile_s *, int, struct tuile_s[143][143], int, int, int, int);

// Initialise la partie : lecture du nombre de joueurs et d'IA, initialisation de la structure joueur_s, dépilement de la première tuile, puis mélange
void parametre_partie(struct tuile_s *, struct tuile_s[143][143], int *, int *, struct joueur_s *);

// Détermine le nombre de case sur la grille où la tuile en main est posable (dans une certaine rotation)
int posable(struct tuile_s[143][143], struct tuile_s, int, int, int, int);

// Rotation de tuile
void rotation(struct tuile_s *);

// Permet à l'utilisateur de poser une tuile
void poser_tuile(struct tuile_s[143][143], struct tuile_s[72], int *, int, struct joueur_s *, int, int, int, int);

// Interface dans lequel le joueur choisi de faire une rotation ou de poser une tuile
void interface_joueur(struct tuile_s[143][143], struct tuile_s[72], int *, int, struct joueur_s *, int, int, int, int);

// Propose au joueur de poser un pion après avoir posé une tuile s'il lui reste des pions
void poser_pion(struct tuile_s[143][143], struct joueur_s *, int, int, int, int);

// Renvoie 1 si le joueur peut poser un pion sur un certain côté de la tuile (qui est de la route), 0 sinon
int verif_route_iteratif(struct tuile_s[143][143], int, int, int);

// Compte les points que la route qui vient d'être posée rapporte
void pts_route(struct tuile_s[143][143], int, int, int, struct joueur_s *);

// Compte les points des routes sur lesquelles il reste des pions à la fin de la partie
void pts_route_FP(struct tuile_s[143][143], int, int, int, struct joueur_s *);

// Compte les points des abbayes (est appelée à chaque tour)
void pts_abbaye(struct tuile_s[143][143], int, int, struct joueur_s *, int, int);

// Compte les points des abbayes sur lesquelles il reste des pions à la fin de la partie
void pts_abbaye_FP(struct tuile_s[143][143], int, int, struct joueur_s *);

// Renvoie les coordonnées (et le côté par lequel elle est reliée) de la tuile voisine d'un côté de la tuile actuelle (EX : T_direction_route(70, 70, 2) == 71, 70, 0)
struct position T_direction_route(int, int, int);

// Encapsule les fonctions de comptage de points de fin de partie et fait les appels dans certains cas
void pts_FP(struct tuile_s[143][143], struct joueur_s *);

// Compte les points des villes récursivement
int parcours_pts_ville(struct tuile_s[143][143], int, int, struct joueur_s *, int, int, int *, int[5]);

void pts_ville(struct tuile_s[143][143], struct joueur_s *, int, int, int, int);

#endif // FCT_CARCASSONNE
