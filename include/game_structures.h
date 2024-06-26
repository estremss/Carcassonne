#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

struct pion_s
{
    int idPion;       // -1 si appartient à personne, id joueur sinon
    int positionPion; // position du pion sur la tuile : {0, 1, 2, 3, 4} ou NULL
};

struct tuile_s
{
    char cotes[4];
    char centre;
    int traitee[5]; // état de traitement du cote[i]
    int posee;      // 1 si posée, 0 sinon
    struct pion_s pion;
    char jouable;
    int visitee;
};

struct joueur_s
{
    int idJoueur, points, pionsPoses, ia; // ia = 0 : joueur, ia = 1 : ia
};

struct position
{
    int x, y, pere;
};

#endif // GAME_STRUCTURES