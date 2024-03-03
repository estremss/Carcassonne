#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

struct pion_s
{
    int idPion;        // -1 si appartient à personne, id joueur sinon
    char positionPion; // position du pion sur la tuile : {N, S, E, W} ou NULL
};

struct tuile_s
{
    int id;
    char cotes[4];
    char centre;
    int posee; // 1 si posée, 0 sinon
    struct pion_s pion;
    char jouable;
};

struct joueur_s
{
    int idJoueur, points, pionsPoses, actif;
};

#endif // GAME_STRUCTURES
