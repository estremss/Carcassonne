#ifndef FCT_CARCASSONNE
#define FCT_CARCASSONNE

void parseur_csv(char *, struct tuile_s *);

void afficher_tuile_dbg(struct tuile_s t);

void melange(struct tuile_s *);

struct tuile_s depiler(struct tuile_s *, int);

void deplacer_tuile_en_derniere_position(struct tuile_s *, int);

void initialiser_partie(struct tuile_s *, struct tuile_s[143][143], int *, int *);

void afficher_ligne(struct tuile_s[143][143], int, int, int);

void affichage(struct tuile_s[143][143], struct tuile_s[72], int, int, struct joueur_s *, int *, int *, int *, int *);

void posable(struct tuile_s[143][143], struct tuile_s, int, int, int, int);

void rotation(struct tuile_s *);

void afficher_tuile_en_cours(struct tuile_s);

void poser_tuile(struct tuile_s[143][143], struct tuile_s[72], int);

void interface_joueur(struct tuile_s[143][143], struct tuile_s[72], int);

#endif // FCT_CARCASSONNE
