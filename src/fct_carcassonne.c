#include "fct_carcassonne.h"

#define NB_TUILES 72

int etat_verif_route = 0;

struct tuile_s depiler(struct tuile_s *Pile, int nb_tours)
// Cette fonction met la carte du tour courant en "posee = 1"
{
    Pile[nb_tours].posee = 1;
    Pile[nb_tours].jouable = 'X';

    return Pile[nb_tours];
}

void deplacer_tuile_en_derniere_position(struct tuile_s *Pile, int nb_tours, struct tuile_s Grille[143][143], int h, int b, int g, int d)
{
    int i, cnt_posable = 0;
    struct tuile_s save = Pile[nb_tours];

    for (i = 0; i < 4; i++)
    {
        cnt_posable += posable(Grille, save, h, b, g, d);
        rotation(&save);
    }

    if (cnt_posable == 0)
    {
        for (i = nb_tours; i < NB_TUILES - 1; i++) // - 1 car avec le i+1 on ferait un core dumped sinon
        {
            Pile[i] = Pile[i + 1];
        }
        Pile[NB_TUILES - 1] = save;
    }
}

void melange(struct tuile_s *Pile)
{
    int i, n = NB_TUILES;
    struct tuile_s save;
    srand((unsigned int)time(NULL));

    while (n > 1)
    {
        i = rand() % n;
        n--;
        save = Pile[n];
        Pile[n] = Pile[i];
        Pile[i] = save;
    }
}

void parametre_partie(struct tuile_s *Pile, struct tuile_s Grille[143][143], int *nb_joueurs, int *nb_ia, struct joueur_s *Joueur)
{
    int i = 0;

    printf("\v\v\v\v\v\tNombre de joueurs : ");
    scanf("%d", nb_joueurs);
    printf("\n\n\tNombre d'IA : ");
    scanf("%d", nb_ia);
    printf("\n");
    if (*nb_joueurs + *nb_ia < 2 || *nb_joueurs + *nb_ia > 5)
    {
        printf("\tLe nombre de joueurs doit être compris entre 2 et 5.\n");
        parametre_partie(Pile, Grille, nb_joueurs, nb_ia, Joueur);
    }

    for (i = 0; i < *nb_joueurs; i++)
        Joueur[i].ia = 0;

    for (i = *nb_joueurs; i < *nb_joueurs + *nb_ia; i++)
        Joueur[i].ia = 1;

    Grille[NB_TUILES][NB_TUILES] = depiler(Pile, 0);
    melange(Pile);
}

int posable(struct tuile_s Grille[143][143], struct tuile_s T, int h, int b, int g, int d) // 1 mars
{
    int i, j, cnt_posable = 0;
    for (i = h - 1; i <= b + 1; i++)
    {
        for (j = g - 1; j <= d + 1; j++)
        {
            if (Grille[i][j].posee == 0)
            {
                if (Grille[i - 1][j].posee == 1 || Grille[i][j + 1].posee == 1 || Grille[i + 1][j].posee == 1 || Grille[i][j - 1].posee == 1)
                {
                    // on check si c'est posable avec la compatibilité entre ville et blason
                    if (((T.cotes[0] == Grille[i - 1][j].cotes[2] || Grille[i - 1][j].posee == 0) || ((T.cotes[0] == 'v' || T.cotes[0] == 'b') && (Grille[i - 1][j].cotes[2] == 'v' || Grille[i - 1][j].cotes[2] == 'b' || Grille[i - 1][j].posee == 0))) &&
                        ((T.cotes[1] == Grille[i][j + 1].cotes[3] || Grille[i][j + 1].posee == 0) || ((T.cotes[1] == 'v' || T.cotes[1] == 'b') && (Grille[i][j + 1].cotes[3] == 'v' || Grille[i][j + 1].cotes[3] == 'b' || Grille[i][j + 1].posee == 0))) &&
                        ((T.cotes[2] == Grille[i + 1][j].cotes[0] || Grille[i + 1][j].posee == 0) || ((T.cotes[2] == 'v' || T.cotes[2] == 'b') && (Grille[i + 1][j].cotes[0] == 'v' || Grille[i + 1][j].cotes[0] == 'b' || Grille[i + 1][j].posee == 0))) &&
                        ((T.cotes[3] == Grille[i][j - 1].cotes[1] || Grille[i][j - 1].posee == 0) || ((T.cotes[3] == 'v' || T.cotes[3] == 'b') && (Grille[i][j - 1].cotes[1] == 'v' || Grille[i][j - 1].cotes[1] == 'b' || Grille[i][j - 1].posee == 0))))
                    {
                        Grille[i][j].jouable = 'O';
                        cnt_posable++;
                    }
                    else
                        Grille[i][j].jouable = 'X';
                }
                else
                    Grille[i][j].jouable = 'X';
            }
            else
                Grille[i][j].jouable = 'X';
        }
    }
    return cnt_posable;
}

void poser_tuile(struct tuile_s Grille[143][143], struct tuile_s Pile[NB_TUILES], int *nb_tours, int nb_joueurs, struct joueur_s *Joueur, int h, int b, int g, int d)
{
    int x = h, y = g, i = 0, x_tmp, y_tmp;

    if (Joueur[(*nb_tours - 1) % nb_joueurs].ia == 0)
    {
        printf("Entrez le numéro de la colonne : ");
        scanf("%d", &y);
        printf("Entrez le numéro de la ligne : ");
        scanf("%d", &x);
    }

    if (x > 2 * NB_TUILES - 2 || y > 2 * NB_TUILES - 2 || x < 0 || y < 0)
    {
        printf("Coordonnées inexistantes.");
        interface_joueur(Grille, Pile, nb_tours, nb_joueurs, Joueur, h, b, g, d);
    }

    int trouve;

    if (Joueur[(*nb_tours - 1) % nb_joueurs].ia == 1)
    {
        for (i = 0; i < 4; i++)
        {
            for (x = h - 1; x <= b + 1; x++)
            {
                for (y = g - 1; y <= d + 1; y++)
                {
                    if (Grille[x][y].jouable == 'O')
                    {
                        x_tmp = x;
                        y_tmp = y;
                        trouve = 1;
                        break;
                    }
                }
                if (trouve == 1)
                    break;
            }
            if (trouve == 1)
                break;
            rotation(&Pile[*nb_tours]);
            posable(Grille, Pile[*nb_tours], 1, 140, 1, 140);
        }
        x = x_tmp;
        y = y_tmp;
    }

    if (Grille[x][y].jouable == 'O')
    { // MODIFIER POUR QUE L'utilistaeur NE PUISSE PAS POSER PIONS SUR PRE ET APPLIQUER LE CHANGEMENT DE COULEUR DU PION
        Grille[x][y] = depiler(Pile, *nb_tours);

        if (Joueur[(*nb_tours - 1) % nb_joueurs].pionsPoses < 6)
            poser_pion(Grille, Joueur, *nb_tours, nb_joueurs, x, y);

        pts_abbaye(Grille, x, y, Joueur, *nb_tours, nb_joueurs);

        if (Grille[x][y].centre != 'r')
        {
            for (i = 0; i < 4; i++)
            {
                if (Grille[x][y].cotes[i] == 'r')
                {
                    pts_route(Grille, x, y, i, Joueur);
                }
            }
        }
        else
        {
            pts_route(Grille, x, y, 4, Joueur);
        }

        if (Grille[x][y].centre == 'v' || Grille[x][y].centre == 'b')
            pts_ville(Grille, Joueur, x, y);

        else
        {
            for (i = 0; i < 4; i++)
                if (Grille[x][y].cotes[i] == 'v' || Grille[x][y].cotes[i] == 'b')
                    pts_ville(Grille, Joueur, x, y);
        }

        *nb_tours += 1;
    }
    else
    {
        printf("\nLa tuile n'est pas jouable ici.\n\n");
        interface_joueur(Grille, Pile, nb_tours, nb_joueurs, Joueur, h, b, g, d);
    }
}

void poser_pion(struct tuile_s Grille[143][143], struct joueur_s *Joueur, int nb_tours, int nb_joueurs, int x, int y)
{
    int choixPoserPion = -1;

    if (Joueur[(nb_tours - 1) % nb_joueurs].ia == 0)
    {
        while (choixPoserPion != 0 && choixPoserPion != 1)
        {
            printf("\nVoulez-vous placer un pion sur la tuile ?\n(oui: 1 - non: 0) : ");
            scanf("%d", &choixPoserPion);
        }
    }
    else
        choixPoserPion = rand() % 4;

    if (choixPoserPion == 1)
    {
        int position = 0;

        if (Joueur[(nb_tours - 1) % nb_joueurs].ia == 0)
        {
            printf("Choisissez le côté où poser le pion :\n\t-0 : Haut\n\t-1 : Droite\n\t-2 : Bas \n\t-3 : Gauche \n\t-4 : Centre\n\t-5 : Annuler\n");
            scanf("%d", &position);
        }

        if (position == 5)
            return;

        while ((position == 0 && Grille[x][y].cotes[0] == 'p') ||
               (position == 2 && Grille[x][y].cotes[2] == 'p') ||
               (position == 1 && Grille[x][y].cotes[1] == 'p') ||
               (position == 3 && Grille[x][y].cotes[3] == 'p') ||
               (position == 4 && Grille[x][y].centre == 'p') ||
               (position == 4 && Grille[x][y].centre == 'V') ||
               (Grille[x][y].centre == 'r' && position == 4 && verif_route_iteratif(Grille, x, y, position) != 0) ||
               (position < 4 && Grille[x][y].cotes[position] == 'r' && verif_route_iteratif(Grille, x, y, position) != 0) ||
               ((Grille[x][y].centre == 'v' || Grille[x][y].centre == 'b') && position == 4 && pions_ville(Grille, x, y, position) == 0) ||
               ((Grille[x][y].cotes[position] == 'v' || Grille[x][y].cotes[position] == 'b') && position < 4 && pions_ville(Grille, x, y, position) == 0) ||
               (position < 0 || position > 4))
        {
            // DEBUG
            // if ((Grille[x][y].centre == 'r' && position == 4 && verif_route_iteratif(Grille, x, y, position) != 0) ||
            //     (position < 4 && Grille[x][y].cotes[position] == 'r' && verif_route_iteratif(Grille, x, y, position) != 0))
            // {
            //     printf("erreur fonction verif route iteratif\n");
            // }

            if (Joueur[(nb_tours - 1) % nb_joueurs].ia == 0)
            {
                printf("Le pion n'est pas posable ici.\n\n");
                printf("Choisissez le côté où poser le pion :\n\t-0 : Haut\n\t-1 : Droite\n\t-2 : Bas \n\t-3 : Gauche \n\t-4 : Centre\n\t-5 : Annuler\n");
                scanf("%d", &position);
            }
            else
                position++;

            if (position == 5)
                return;
        }

        Grille[x][y].pion.idPion = (nb_tours - 1) % nb_joueurs;
        Grille[x][y].pion.positionPion = position;
        Joueur[(nb_tours - 1) % nb_joueurs].pionsPoses++;
    }
}

struct position T_direction_route(int cote, int i, int j)
{
    struct position P = {0, 0, 0};

    switch (cote)
    {
    case 0:
        P.x = i - 1;
        P.y = j;
        P.pere = cote + 2;
        return P;
    case 1:
        P.x = i;
        P.y = j + 1;
        P.pere = cote + 2;
        return P;
    case 2:
        P.x = i + 1;
        P.y = j;
        P.pere = cote - 2;
        return P;
    case 3:
        P.x = i;
        P.y = j - 1;
        P.pere = cote - 2;
        return P;

    default:
        return P;
    }
}

int verif_route_iteratif(struct tuile_s Grille[143][143], int x, int y, int position_pion)
{
    struct position P;
    int direction_route = 0, direction_route2 = -1;

    if (Grille[x][y].centre != 'r')
    { // si c'est une fin de route
        while (direction_route < 4 && (direction_route != position_pion))
            direction_route++;
    }
    else
    { // si la route a deux directions
        while (direction_route < 4 && Grille[x][y].cotes[direction_route] != 'r')
            direction_route++;

        direction_route2 = direction_route + 1;
        while (Grille[x][y].cotes[direction_route2] != 'r')
            direction_route2++;
    }

    P = T_direction_route(direction_route, x, y);

    while (Grille[P.x][P.y].cotes[P.pere] == 'r' && (P.x != x || P.y != y)) // deuxième condition au cas où si la route devient une boucle avec la tuile qu'on veut poser
    {
        if (Grille[P.x][P.y].pion.positionPion == P.pere || (Grille[P.x][P.y].centre == 'r' && Grille[P.x][P.y].pion.positionPion == 4)) // condition d'arrêt FALSE: pion sur tuile d'arrivée ou au centre sur route
            return -1;

        if (Grille[P.x][P.y].centre != 'r') // condition d'arrêt TRUE : fin de route
            break;

        direction_route = (P.pere + 1) % 4;
        while (Grille[P.x][P.y].cotes[direction_route] != 'r')
            direction_route = (direction_route + 1) % 4;

        if (Grille[P.x][P.y].pion.positionPion == direction_route) // condition d'arrêt FALSE: si il y a un pion sur la direction où on veut aller
            return -1;

        P = T_direction_route(direction_route, P.x, P.y); // on peut continuer le traitement et donner la prochaine tuile à P
    }

    if (P.y == x && P.y == y) // si on a fait une boucle et qu'on revient à la tuile de départ
        return 0;

    // si la route a deux directions
    if (direction_route2 != -1)
    {
        P = T_direction_route(direction_route2, x, y);

        while (Grille[P.x][P.y].cotes[P.pere] == 'r')
        {
            if (Grille[P.x][P.y].pion.positionPion == P.pere || (Grille[P.x][P.y].centre == 'r' && Grille[P.x][P.y].pion.positionPion == 4)) // condition d'arrêt FALSE: pion sur tuile d'arrivée ou au centre sur route
                return -1;

            if (Grille[P.x][P.y].centre != 'r') // condition d'arrêt TRUE : fin de route
                break;

            direction_route2 = (P.pere + 1) % 4;
            while (Grille[P.x][P.y].cotes[direction_route2] != 'r')
                direction_route2 = (direction_route2 + 1) % 4;

            if (Grille[P.x][P.y].pion.positionPion == direction_route2) // condition d'arrêt FALSE: si il y a un pion sur la direction où on veut aller
                return -1;

            P = T_direction_route(direction_route2, P.x, P.y); // on peut continuer le traitement et donner la prochaine tuile à P
        }
    }

    return 0; // conventionnel
}

void pts_route(struct tuile_s Grille[143][143], int x, int y, int direction, struct joueur_s *Joueurs)
{
    int t_pion_pose[5] = {0, 0, 0, 0, 0}, i = 0, j, cnt_p = 1, direction1 = 0, direction2, max_pion = 1;
    struct position P, P1, P2;
    struct tuile_s G_Traitees[143][143];

    // trouver s'il y a de la route sur au moins un côté
    while (Grille[x][y].cotes[i] != 'r' && i < 4)
        i++;

    // arrêter la fonction s'il n'y a pas de route sur la tuile qui vient d'être posée
    if (i == 4 && Grille[x][y].centre != 'r')
        return;

    // copie du tableau
    for (i = 0; i < 143; i++)
        for (j = 0; j < 143; j++)
            G_Traitees[i][j] = Grille[i][j];

    // Détection pion sur première tuile (2 directions)
    if (Grille[x][y].centre == 'r')
    { // cas où il y a un pion sur la tuile qu'on vient de poser sur les côtés
        for (i = 0; i < 4; i++)
            if (Grille[x][y].pion.positionPion == i && Grille[x][y].cotes[i] == 'r')
            {
                t_pion_pose[Grille[x][y].pion.idPion] = 1;
                G_Traitees[x][y].traitee[i] = 1;
                G_Traitees[x][y].pion.idPion = -1;
                G_Traitees[x][y].pion.positionPion = -1;
            }

        // cas où il y a un pion sur la tuile qu'on vient de poser sur le centre
        if (Grille[x][y].pion.positionPion == 4 && Grille[x][y].centre == 'r')
        {
            t_pion_pose[Grille[x][y].pion.idPion] = 1;
            G_Traitees[x][y].traitee[4] = 1;
            G_Traitees[x][y].pion.idPion = -1;
            G_Traitees[x][y].pion.positionPion = -1;
        }
    }
    // Détections pion sur première tuile (fin de route)
    else if (Grille[x][y].pion.positionPion == direction)
    {
        t_pion_pose[Grille[x][y].pion.idPion] = 1;
        G_Traitees[x][y].traitee[4] = 1;
        G_Traitees[x][y].pion.idPion = -1;
        G_Traitees[x][y].pion.positionPion = -1;
    }

    // DEBUT PARCOURS

    // PARCOURS 1 direction
    // si la tuile qui vient d'être posée est une fin de route
    if (Grille[x][y].centre != 'r')
    {
        P = T_direction_route(direction, x, y);
        while (Grille[P.x][P.y].posee == 1 && (P.x != x || P.y != y))
        {
            cnt_p += 1;
            // si pion sur le côté d'arrivée
            if (Grille[P.x][P.y].pion.positionPion == P.pere)
            {
                t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                G_Traitees[P.x][P.y].traitee[P.pere] = 1;
                G_Traitees[P.x][P.y].pion.idPion = -1;
                G_Traitees[P.x][P.y].pion.positionPion = -1;
            }

            // si pion sur centre
            if (Grille[P.x][P.y].centre == 'r' && Grille[P.x][P.y].pion.positionPion == 4)
            {
                t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                G_Traitees[P.x][P.y].traitee[4] = 1;
                G_Traitees[P.x][P.y].pion.idPion = -1;
                G_Traitees[P.x][P.y].pion.positionPion = -1;
            }

            // si ce n'est pas une fin de route
            if (Grille[P.x][P.y].centre == 'r')
            {
                direction = (P.pere + 1) % 4;
                while (Grille[P.x][P.y].cotes[direction] != 'r')
                    direction = (direction + 1) % 4;

                if (Grille[P.x][P.y].pion.positionPion == direction)
                {
                    t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                    G_Traitees[P.x][P.y].traitee[direction] = 1;
                    G_Traitees[P.x][P.y].pion.positionPion = -1;
                    G_Traitees[P.x][P.y].pion.positionPion = -1;
                }
            }
            // si c'est une fin de route on break
            else
                break;

            // on détermine la prochaine tuile à parcourir
            P = T_direction_route(direction, P.x, P.y);
        }
    }

    // PARCOURS 2 directions
    // si ce n'est pas une fin de route
    else
    {
        while (Grille[x][y].cotes[direction1] != 'r')
            direction1++;

        direction2 = direction1 + 1;
        while (Grille[x][y].cotes[direction2] != 'r')
            direction2++;

        P = T_direction_route(direction1, x, y);

        while (Grille[P.x][P.y].posee == 1 && (P.x != x || P.y != y))
        {
            cnt_p += 1;
            // si pion sur le côté d'arrivée
            if (Grille[P.x][P.y].pion.positionPion == P.pere)
            {
                t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                G_Traitees[P.x][P.y].traitee[P.pere] = 1;
                G_Traitees[P.x][P.y].pion.idPion = -1;
                G_Traitees[P.x][P.y].pion.positionPion = -1;
            }

            // si pion sur centre
            if (Grille[P.x][P.y].centre == 'r' && Grille[P.x][P.y].pion.positionPion == 4)
            {
                t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                G_Traitees[P.x][P.y].traitee[4] = 1;
                G_Traitees[P.x][P.y].pion.idPion = -1;
                G_Traitees[P.x][P.y].pion.positionPion = -1;
            }

            // si ce n'est pas une fin de route
            if (Grille[P.x][P.y].centre == 'r')
            {
                direction1 = (P.pere + 1) % 4;
                while (Grille[P.x][P.y].cotes[direction1] != 'r')
                    direction1 = (direction1 + 1) % 4;

                if (Grille[P.x][P.y].pion.positionPion == direction1)
                {
                    t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                    G_Traitees[P.x][P.y].traitee[direction1] = 1;
                    G_Traitees[P.x][P.y].pion.positionPion = -1;
                    G_Traitees[P.x][P.y].pion.positionPion = -1;
                }
            }
            // si c'est une fin de route on break
            else
                break;

            // on détermine la prochaine tuile à parcourir
            P = T_direction_route(direction1, P.x, P.y);
        }

        if (Grille[P.x][P.y].posee == 0) // si on est sur une tuile non posée, c'est que la route n'est pas fermée donc on stop le traitement
            return;
        else
            P1 = P;

        if (P.x != x || P.y != y)
        {
            P = T_direction_route(direction2, x, y);

            while (Grille[P.x][P.y].posee == 1 && (P.x != x || P.y != y))
            {
                cnt_p += 1;
                // si pion sur le côté d'arrivée
                if (Grille[P.x][P.y].pion.positionPion == P.pere)
                {
                    t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                    G_Traitees[P.x][P.y].traitee[P.pere] = 1;
                    G_Traitees[P.x][P.y].pion.idPion = -1;
                    G_Traitees[P.x][P.y].pion.positionPion = -1;
                }

                // si pion sur centre
                if (Grille[P.x][P.y].centre == 'r' && Grille[P.x][P.y].pion.positionPion == 4)
                {
                    t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                    G_Traitees[P.x][P.y].traitee[4] = 1;
                    G_Traitees[P.x][P.y].pion.idPion = -1;
                    G_Traitees[P.x][P.y].pion.positionPion = -1;
                }

                // si ce n'est pas une fin de route
                if (Grille[P.x][P.y].centre == 'r')
                {
                    direction1 = (P.pere + 1) % 4;
                    while (Grille[P.x][P.y].cotes[direction1] != 'r')
                        direction1 = (direction1 + 1) % 4;

                    if (Grille[P.x][P.y].pion.positionPion == direction1)
                    {
                        t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                        G_Traitees[P.x][P.y].traitee[direction1] = 1;
                        G_Traitees[P.x][P.y].pion.positionPion = -1;
                        G_Traitees[P.x][P.y].pion.positionPion = -1;
                    }
                }
                // si c'est une fin de route on break
                else
                    break;

                // on détermine la prochaine tuile à parcourir
                P = T_direction_route(direction1, P.x, P.y);
            }
            P2 = P;
            if (P1.x == P2.x && P1.y == P2.y) // Pour ne pas compter deux fois si notre ville est une boucle (dans un certain cas)
                cnt_p -= 1;
        }
    }

    // cas où la dernière tuile est posee (donc fin de route)
    if (Grille[P.x][P.y].posee == 1)
    {
        // DEBUG
        // for (i = 0; i < 5; i++)
        //     printf("J%d : %d\t", i + 1, t_pion_pose[i]);

        for (i = 0; i < 5; i++)
            if (t_pion_pose[i] >= max_pion)
                max_pion = t_pion_pose[i];

        for (i = 0; i < 5; i++)
        {
            if (t_pion_pose[i] == max_pion)
                Joueurs[i].points += cnt_p;

            Joueurs[i].pionsPoses -= t_pion_pose[i];
        }

        for (i = 0; i < 143; i++)
            for (j = 0; j < 143; j++)
                Grille[i][j] = G_Traitees[i][j];
    }
}

void pts_route_FP(struct tuile_s Grille[143][143], int x, int y, int direction, struct joueur_s *Joueurs)
{
    int t_pion_pose[5] = {0, 0, 0, 0, 0}, i = 0, j, cnt_p = 1, direction1 = 0, direction2, max_pion = 1;
    struct position P, P1, P2;
    struct tuile_s G_Traitees[143][143];

    // trouver s'il y a de la route sur au moins un côté
    while (Grille[x][y].cotes[i] != 'r' && i < 4)
        i++;

    // arrêter la fonction s'il n'y a pas de route sur la tuile qui vient d'être posée
    if (i == 4 && Grille[x][y].centre != 'r')
        return;

    // copie du tableau
    for (i = 0; i < 143; i++)
        for (j = 0; j < 143; j++)
            G_Traitees[i][j] = Grille[i][j];

    // Détection pion sur première tuile (2 directions)
    if (Grille[x][y].centre == 'r')
    { // cas où il y a un pion sur la tuile qu'on vient de poser sur les côtés
        for (i = 0; i < 4; i++)
            if (Grille[x][y].pion.positionPion == i && Grille[x][y].cotes[i] == 'r')
            {
                t_pion_pose[Grille[x][y].pion.idPion] = 1;
            }
        G_Traitees[x][y].traitee[i] = 1;

        // cas où il y a un pion sur la tuile qu'on vient de poser sur le centre
        if (Grille[x][y].pion.positionPion == 4 && Grille[x][y].centre == 'r')
        {
            t_pion_pose[Grille[x][y].pion.idPion] = 1;
        }
        G_Traitees[x][y].traitee[4] = 1;
    }
    // Détections pion sur première tuile (fin de route)
    else if (Grille[x][y].pion.positionPion == direction)
    {
        t_pion_pose[Grille[x][y].pion.idPion] = 1;
    }
    G_Traitees[x][y].traitee[4] = 1;

    // DEBUT PARCOURS

    // PARCOURS 1 direction
    // si la tuile qui vient d'être posée est une fin de route
    if (Grille[x][y].centre != 'r')
    {
        P = T_direction_route(direction, x, y);
        while (Grille[P.x][P.y].posee == 1 && (P.x != x || P.y != y))
        {
            cnt_p += 1;
            // si pion sur le côté d'arrivée
            if (Grille[P.x][P.y].pion.positionPion == P.pere)
            {
                t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
            }
            G_Traitees[P.x][P.y].traitee[P.pere] = 1;

            // si pion sur centre
            if (Grille[P.x][P.y].centre == 'r' && Grille[P.x][P.y].pion.positionPion == 4)
            {
                t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
            }
            G_Traitees[P.x][P.y].traitee[4] = 1;

            // si ce n'est pas une fin de route
            if (Grille[P.x][P.y].centre == 'r')
            {
                direction = (P.pere + 1) % 4;
                while (Grille[P.x][P.y].cotes[direction] != 'r')
                    direction = (direction + 1) % 4;

                if (Grille[P.x][P.y].pion.positionPion == direction)
                {
                    t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                }
                G_Traitees[P.x][P.y].traitee[direction] = 1;
            }
            // si c'est une fin de route on break
            else
                break;

            // on détermine la prochaine tuile à parcourir
            P = T_direction_route(direction, P.x, P.y);
        }
    }

    // PARCOURS 2 directions
    // si ce n'est pas une fin de route
    else
    {
        while (Grille[x][y].cotes[direction1] != 'r')
            direction1++;

        direction2 = direction1 + 1;
        while (Grille[x][y].cotes[direction2] != 'r')
            direction2++;

        P = T_direction_route(direction1, x, y);

        while (Grille[P.x][P.y].posee == 1 && (P.x != x || P.y != y))
        {
            cnt_p += 1;
            // si pion sur le côté d'arrivée
            if (Grille[P.x][P.y].pion.positionPion == P.pere)
            {
                t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
            }
            G_Traitees[P.x][P.y].traitee[P.pere] = 1;

            // si pion sur centre
            if (Grille[P.x][P.y].centre == 'r' && Grille[P.x][P.y].pion.positionPion == 4)
            {
                t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
            }
            G_Traitees[P.x][P.y].traitee[4] = 1;

            // si ce n'est pas une fin de route
            if (Grille[P.x][P.y].centre == 'r')
            {
                direction1 = (P.pere + 1) % 4;
                while (Grille[P.x][P.y].cotes[direction1] != 'r')
                    direction1 = (direction1 + 1) % 4;

                if (Grille[P.x][P.y].pion.positionPion == direction1)
                {
                    t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                }
                G_Traitees[P.x][P.y].traitee[direction1] = 1;
            }
            // si c'est une fin de route on break
            else
                break;

            // on détermine la prochaine tuile à parcourir
            P = T_direction_route(direction1, P.x, P.y);
        }

        P1 = P;

        if (P.x != x || P.y != y)
        {
            P = T_direction_route(direction2, x, y);

            while (Grille[P.x][P.y].posee == 1 && (P.x != x || P.y != y))
            {
                cnt_p += 1;
                // si pion sur le côté d'arrivée
                if (Grille[P.x][P.y].pion.positionPion == P.pere)
                {
                    t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                }
                G_Traitees[P.x][P.y].traitee[P.pere] = 1;

                // si pion sur centre
                if (Grille[P.x][P.y].centre == 'r' && Grille[P.x][P.y].pion.positionPion == 4)
                {
                    t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                }
                G_Traitees[P.x][P.y].traitee[4] = 1;

                // si ce n'est pas une fin de route
                if (Grille[P.x][P.y].centre == 'r')
                {
                    direction1 = (P.pere + 1) % 4;
                    while (Grille[P.x][P.y].cotes[direction1] != 'r')
                        direction1 = (direction1 + 1) % 4;

                    if (Grille[P.x][P.y].pion.positionPion == direction1)
                    {
                        t_pion_pose[Grille[P.x][P.y].pion.idPion] += 1;
                    }
                    G_Traitees[P.x][P.y].traitee[direction1] = 1;
                }
                // si c'est une fin de route on break
                else
                    break;

                // on détermine la prochaine tuile à parcourir
                P = T_direction_route(direction1, P.x, P.y);
            }
            P2 = P;
            if (P1.x == P2.x && P1.y == P2.y)
                cnt_p -= 1;
        }
    }

    // printf("appel x : %d y : %d\t", x, y);
    // for (i = 0; i < 5; i++)
    //     printf("J%d : %d\t", i + 1, t_pion_pose[i]);
    // printf("\n");

    for (i = 0; i < 5; i++)
        if (t_pion_pose[i] >= max_pion)
            max_pion = t_pion_pose[i];

    for (i = 0; i < 5; i++)
    {
        if (t_pion_pose[i] == max_pion)
            Joueurs[i].points += cnt_p;

        Joueurs[i].pionsPoses -= t_pion_pose[i];
    }

    for (i = 0; i < 143; i++)
        for (j = 0; j < 143; j++)
            Grille[i][j] = G_Traitees[i][j];
}

void pts_ville_FP(struct tuile_s Grille[143][143], struct joueur_s *Joueurs, int x, int y)
{
    int i, j, max_pion = 1;
    struct tuile_s G_Traitees[143][143];
    int valide = 0;
    int pions_ville[5] = {0, 0, 0, 0, 0};

    // copie du tableau
    for (i = 0; i < 143; i++)
        for (j = 0; j < 143; j++)
            G_Traitees[i][j] = Grille[i][j];

    if (parcours_pts_ville_FP(G_Traitees, x, y, &valide, pions_ville) != 0)
    {
        for (i = 0; i < 5; i++)
            if (pions_ville[i] >= max_pion)
                max_pion = pions_ville[i];

        for (i = 0; i < 5; i++)
        {
            if (pions_ville[i] == max_pion)
                Joueurs[i].points += valide;

            Joueurs[i].pionsPoses -= pions_ville[i];
        }

        for (i = 0; i < 143; i++)
            for (j = 0; j < 143; j++)
                Grille[i][j] = G_Traitees[i][j];
    }
}

void pts_ville(struct tuile_s Grille[143][143], struct joueur_s *Joueurs, int x, int y)
{
    int i, j, max_pion = 1;
    struct tuile_s G_Traitees[143][143];
    int valide = 0;
    int pions_ville[5] = {0, 0, 0, 0, 0};

    // copie du tableau
    for (i = 0; i < 143; i++)
        for (j = 0; j < 143; j++)
            G_Traitees[i][j] = Grille[i][j];

    if (parcours_pts_ville(G_Traitees, x, y, &valide, pions_ville) != 0)
    {
        for (i = 0; i < 5; i++)
            if (pions_ville[i] >= max_pion)
                max_pion = pions_ville[i];

        for (i = 0; i < 5; i++)
        {
            if (pions_ville[i] == max_pion)
                Joueurs[i].points += valide;

            Joueurs[i].pionsPoses -= pions_ville[i];
        }

        for (i = 0; i < 143; i++)
            for (j = 0; j < 143; j++)
            {
                Grille[i][j] = G_Traitees[i][j];
                Grille[i][j].visitee = 0;
            }
    }
}

int pions_ville(struct tuile_s Grille[143][143], int x, int y, int position)
{
    int i, j, valide = 0, cnt = 0;
    struct tuile_s G_Traitees[143][143];

    // copie du tableau
    for (i = 0; i < 143; i++)
        for (j = 0; j < 143; j++)
            G_Traitees[i][j] = Grille[i][j];

    for (i = 0; i < 4; i++)
        if (Grille[x][y].cotes[i] == 'v' || Grille[x][y].cotes[i] == 'b')
            cnt++;

    // // Anciennce condition que je ne comprends pas
    // if (Grille[x][y].centre == 'v' || Grille[x][y].centre == 'b' || cnt == 0)
    if (cnt == 0)
        return 1;

    return verif_pions_ville(G_Traitees, x, y, &valide, position);
}

int parcours_pts_ville(struct tuile_s Grille[143][143], int x, int y, int *valide, int pions_ville[5])
{
    int i, double_ville = 0;

    // Conditions d'arrêts pour s'il n'y a pas de problème, et qu'on n'incrémente pas
    if ((x < 0 || x > 143 || y < 0 || y > 143) || Grille[x][y].visitee == 1)
        return 1;

    Grille[x][y].visitee = 1;

    // Si la tuile n'est pas posée
    if (Grille[x][y].posee == 0)
    {
        // printf("Non posée Grille[%d][%d]\n", x, y);
        return 0;
    }

    // Ajout des pions dans le tableau de pions
    for (i = 0; i < 4; i++)
        if ((Grille[x][y].cotes[i] == 'v' || Grille[x][y].cotes[i] == 'b') && Grille[x][y].pion.positionPion == i)
        {
            pions_ville[Grille[x][y].pion.idPion] += 1;
            Grille[x][y].pion.positionPion = -1;
            Grille[x][y].pion.idPion = -1;
        }
    if ((Grille[x][y].centre == 'v' || Grille[x][y].centre == 'b') && Grille[x][y].pion.positionPion == 4)
    {
        pions_ville[Grille[x][y].pion.idPion] += 1;
        Grille[x][y].pion.positionPion = -1;
        Grille[x][y].pion.idPion = -1;
    }

    int ville_fermee = 1;

    // sauvegarder si la première tuile du parcours est une division de villes
    if (*valide == 0 && Grille[x][y].centre != 'v' && Grille[x][y].centre != 'b')
    {
        for (i = 0; i < 4; i++)
        {
            if (Grille[x][y].cotes[i] == 'v')
                double_ville += 1;
        }
    }

    // incrémentation du score
    if (Grille[x][y].centre != 'b')
        *valide += 2;
    else
        *valide += 4;

    // Si c'est une fin de ville (mais pas la première du parcours)
    if (Grille[x][y].centre != 'v' && Grille[x][y].centre != 'b' && *valide > 2)
        return 1;

    // Appels des tuiles adjacentes
    // Haut
    if (x > 0 && (Grille[x - 1][y].cotes[2] == 'v' || Grille[x - 1][y].cotes[2] == 'b' || Grille[x - 1][y].posee == 0) && (Grille[x][y].cotes[0] == 'v' || Grille[x][y].cotes[0] == 'b'))
    {
        ville_fermee &= parcours_pts_ville(Grille, x - 1, y, valide, pions_ville);

        if (double_ville == 2 && *valide > 2)
        {
            Grille[x][y].visitee = 0; // pour pouvoir retraiter cette tuile plus tard
            return ville_fermee;
        }
    }

    // Droite
    if (y < 142 && (Grille[x][y + 1].cotes[3] == 'v' || Grille[x][y + 1].cotes[3] == 'b' || Grille[x][y + 1].posee == 0) && (Grille[x][y].cotes[1] == 'v' || Grille[x][y].cotes[1] == 'b'))
    {
        ville_fermee &= parcours_pts_ville(Grille, x, y + 1, valide, pions_ville);

        if (double_ville == 2 && *valide > 2)
        {
            Grille[x][y].visitee = 0;
            return ville_fermee;
        }
    }

    // Bas
    if (x < 142 && (Grille[x + 1][y].cotes[0] == 'v' || Grille[x + 1][y].cotes[0] == 'b' || Grille[x + 1][y].posee == 0) && (Grille[x][y].cotes[2] == 'v' || Grille[x][y].cotes[2] == 'b'))
    {
        ville_fermee &= parcours_pts_ville(Grille, x + 1, y, valide, pions_ville);

        if (double_ville == 2 && *valide > 2)
        {
            Grille[x][y].visitee = 0;
            return ville_fermee;
        }
    }

    // Gauche
    if (y > 0 && (Grille[x][y - 1].cotes[1] == 'v' || Grille[x][y - 1].cotes[1] == 'b' || Grille[x][y - 1].posee == 0) && (Grille[x][y].cotes[3] == 'v' || Grille[x][y].cotes[3] == 'b'))
    {
        ville_fermee &= parcours_pts_ville(Grille, x, y - 1, valide, pions_ville);

        if (double_ville == 2 && *valide > 2)
        {
            Grille[x][y].visitee = 0;
            return ville_fermee;
        }
    }

    return ville_fermee;
}

int parcours_pts_ville_FP(struct tuile_s Grille[143][143], int x, int y, int *valide, int pions_ville[5])
{
    int i, double_ville = 0;

    // Conditions d'arrêts pour s'il n'y a pas de problème, et qu'on n'incrémente pas
    if ((x < 0 || x > 143 || y < 0 || y > 143) || Grille[x][y].visitee == 1 || Grille[x][y].posee == 0)
        return 1;

    Grille[x][y].visitee = 1;

    // Ajout des pions dans le tableau de pions
    for (i = 0; i < 4; i++)
        if ((Grille[x][y].cotes[i] == 'v' || Grille[x][y].cotes[i] == 'b') && Grille[x][y].pion.positionPion == i)
            pions_ville[Grille[x][y].pion.idPion] += 1;

    if ((Grille[x][y].centre == 'v' || Grille[x][y].centre == 'b') && Grille[x][y].pion.positionPion == 4)
        pions_ville[Grille[x][y].pion.idPion] += 1;

    int ville_fermee = 1;

    // sauvegarder si la première tuile du parcours est une division de villes
    if (*valide == 0 && Grille[x][y].centre != 'v' && Grille[x][y].centre != 'b')
    {
        for (i = 0; i < 4; i++)
        {
            if (Grille[x][y].cotes[i] == 'v')
                double_ville += 1;
        }
    }

    // incrémentation du score
    if (Grille[x][y].centre != 'b')
        *valide += 1;
    else
        *valide += 2;

    // Si c'est une fin de ville (mais pas la première du parcours)
    if (Grille[x][y].centre != 'v' && Grille[x][y].centre != 'b' && *valide > 2)
        return 1;

    // Appels des tuiles adjacentes
    // Haut
    if (x > 0 && (Grille[x - 1][y].cotes[2] == 'v' || Grille[x - 1][y].cotes[2] == 'b' || Grille[x - 1][y].posee == 0) && (Grille[x][y].cotes[0] == 'v' || Grille[x][y].cotes[0] == 'b'))
    {
        ville_fermee |= parcours_pts_ville(Grille, x - 1, y, valide, pions_ville);

        if (double_ville == 2 && *valide > 2)
        {
            Grille[x][y].visitee = 0; // pour pouvoir retraiter cette tuile plus tard
            return ville_fermee;
        }
    }

    // Droite
    if (y < 142 && (Grille[x][y + 1].cotes[3] == 'v' || Grille[x][y + 1].cotes[3] == 'b' || Grille[x][y + 1].posee == 0) && (Grille[x][y].cotes[1] == 'v' || Grille[x][y].cotes[1] == 'b'))
    {
        ville_fermee |= parcours_pts_ville(Grille, x, y + 1, valide, pions_ville);

        if (double_ville == 2 && *valide > 2)
        {
            Grille[x][y].visitee = 0;
            return ville_fermee;
        }
    }

    // Bas
    if (x < 142 && (Grille[x + 1][y].cotes[0] == 'v' || Grille[x + 1][y].cotes[0] == 'b' || Grille[x + 1][y].posee == 0) && (Grille[x][y].cotes[2] == 'v' || Grille[x][y].cotes[2] == 'b'))
    {
        ville_fermee |= parcours_pts_ville(Grille, x + 1, y, valide, pions_ville);

        if (double_ville == 2 && *valide > 2)
        {
            Grille[x][y].visitee = 0;
            return ville_fermee;
        }
    }

    // Gauche
    if (y > 0 && (Grille[x][y - 1].cotes[1] == 'v' || Grille[x][y - 1].cotes[1] == 'b' || Grille[x][y - 1].posee == 0) && (Grille[x][y].cotes[3] == 'v' || Grille[x][y].cotes[3] == 'b'))
    {
        ville_fermee |= parcours_pts_ville(Grille, x, y - 1, valide, pions_ville);

        if (double_ville == 2 && *valide > 2)
        {
            Grille[x][y].visitee = 0;
            return ville_fermee;
        }
    }

    return ville_fermee;
}

int verif_pions_ville(struct tuile_s Grille[143][143], int x, int y, int *cnt, int initPion)
{
    struct position P;
    char double_ville = 0;
    int i;

    // Conditions d'arrêts pour s'il n'y a pas de problème, et qu'on n'incrémente pas
    if ((x < 0 || x > 143 || y < 0 || y > 143) || Grille[x][y].visitee == 1 || Grille[x][y].posee == 0)
        return 1;

    Grille[x][y].visitee = 1;

    // printf("Tuiles[%d][%d] : position pion = %d\n", x, y, Grille[x][y].pion.positionPion);
    if (Grille[x][y].pion.positionPion != -1)
    {
        return 0;
    }

    // Si c'est une fin de ville (mais pas la première du parcours)
    if (Grille[x][y].centre != 'v' && Grille[x][y].centre != 'b' && *cnt > 1)
        return 1;

    // incrémentation déplacement
    *cnt += 1;

    int posable = 1;

    for (i = 0; i < 4; i++)
        if (Grille[x][y].cotes[i] == 'v' || Grille[x][y].cotes[i] == 'v')
            double_ville += 1;

    // Appel forcé de la tuile adjacente si la première tuile est potentiellement une "double différente"
    if (*cnt == 1 && Grille[x][y].centre != 'v' && Grille[x][y].centre != 'b' && initPion != 4 && double_ville == 2)
    {

        printf("G[%d][%d] est une double ville", x, y);
        P = T_direction_route(initPion, x, y);
        posable &= verif_pions_ville(Grille, P.x, P.y, cnt, P.pere);
    }
    else if (Grille[x][y].centre == 'b' || Grille[x][y].centre == 'v' || double_ville != 2)
    {
        // Haut
        if (x > 0 && (Grille[x - 1][y].cotes[2] == 'v' || Grille[x - 1][y].cotes[2] == 'b' || Grille[x - 1][y].posee == 0) && (Grille[x][y].cotes[0] == 'v' || Grille[x][y].cotes[0] == 'b'))
            posable &= verif_pions_ville(Grille, x - 1, y, cnt, initPion);

        // Droite
        if (y < 142 && (Grille[x][y + 1].cotes[3] == 'v' || Grille[x][y + 1].cotes[3] == 'b' || Grille[x][y + 1].posee == 0) && (Grille[x][y].cotes[1] == 'v' || Grille[x][y].cotes[1] == 'b'))
            posable &= verif_pions_ville(Grille, x, y + 1, cnt, initPion);

        // Bas
        if (x < 142 && (Grille[x + 1][y].cotes[0] == 'v' || Grille[x + 1][y].cotes[0] == 'b' || Grille[x + 1][y].posee == 0) && (Grille[x][y].cotes[2] == 'v' || Grille[x][y].cotes[2] == 'b'))
            posable &= verif_pions_ville(Grille, x + 1, y, cnt, initPion);

        // Gauche
        if (y > 0 && (Grille[x][y - 1].cotes[1] == 'v' || Grille[x][y - 1].cotes[1] == 'b' || Grille[x][y - 1].posee == 0) && (Grille[x][y].cotes[3] == 'v' || Grille[x][y].cotes[3] == 'b'))
            posable &= verif_pions_ville(Grille, x, y - 1, cnt, initPion);
    }

    return posable;
}

void pts_abbaye(struct tuile_s Grille[143][143], int x, int y, struct joueur_s *Joueurs, int nb_tours, int nb_joueurs)
{ // uniqument en pleine partie
    if (Grille[x][y].centre == 'a' && Grille[x][y].pion.positionPion == 4)
    {
        if (Grille[x][y + 1].posee == 1 && Grille[x][y - 1].posee == 1 && Grille[x + 1][y].posee == 1 && Grille[x - 1][y].posee == 1 && Grille[x + 1][y + 1].posee == 1 && Grille[x - 1][y - 1].posee == 1 && Grille[x - 1][y + 1].posee == 1 && Grille[x + 1][y - 1].posee == 1)
        {
            Grille[x][y].traitee[4] = 1;
            Joueurs[Grille[x][y].pion.idPion].points += 9;
            Joueurs[Grille[x][y].pion.idPion].pionsPoses -= 1;
            Grille[x][y].pion.idPion = -1;
            Grille[x][y].pion.positionPion = -1;
        }
    }

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
                continue; // ça nous evite le cas ou  c'est zero psk sinon on verifierai que grille[x] et [y]

            if (Grille[x + i][y + j].centre == 'a' && Grille[x + i][y + j].pion.positionPion == 4 && (Grille[x + i][y + j].traitee[4] != 1 && Grille[x + i][y + j].pion.idPion != -1))
            {
                if (Grille[x + i][y + j + 1].posee == 1 && Grille[x + i][y + j - 1].posee == 1 && Grille[x + i + 1][y + j].posee == 1 && Grille[x + i - 1][y + j].posee == 1 && Grille[x + i + 1][y + j + 1].posee == 1 && Grille[x + i - 1][y + j - 1].posee == 1 && Grille[x + i - 1][y + j + 1].posee == 1 && Grille[x + i + 1][y + j - 1].posee == 1)
                {
                    Grille[x + i][y + j].traitee[4] = 1;
                    Joueurs[Grille[x + i][y + j].pion.idPion].points += 9;
                    Joueurs[Grille[x + i][y + j].pion.idPion].pionsPoses -= 1;
                    Grille[x + i][y + j].pion.idPion = -1;
                    Grille[x + i][y + j].pion.positionPion = -1;
                }
            }
        }
    }
}

void pts_abbaye_FP(struct tuile_s Grille[143][143], int x, int y, struct joueur_s *Joueurs)
{ // uniqument en fin de partie
    int i, j;

    if (Grille[x][y].centre == 'a' && Grille[x][y].pion.positionPion == 4)
    {
        for (i = -1; i <= 1; i++)
            for (j = -1; j <= 1; j++)
            {
                if (i == 0 && j == 0)
                    continue;
                if (Grille[x + i][y + j].posee == 1)
                {
                    Joueurs[Grille[x][y].pion.idPion].points += 1;
                }
            }
    }
}

void pts_FP(struct tuile_s Grille[143][143], struct joueur_s *Joueurs)
{
    int i, j, k;
    for (i = 0; i < 143; ++i)
        for (j = 0; j < 143; ++j)
        {
            if (Grille[i][j].centre == 'a' && Grille[i][j].pion.positionPion == 4)
            {
                pts_abbaye_FP(Grille, i, j, Joueurs);
            }
            if (((i > 0 && j > 0) && (i < 141 && j < 142)) && Grille[i][j].pion.positionPion != -1)
            {
                // pour les routes
                if (Grille[i][j].cotes[0] == 'r' || Grille[i][j].cotes[1] == 'r' || Grille[i][j].cotes[2] == 'r' || Grille[i][j].cotes[3] == 'r' || Grille[i][j].centre == 'r')
                {
                    if (Grille[i][j].centre != 'r')
                    {
                        for (k = 0; k < 4; k++)
                        {
                            if (Grille[i][j].cotes[k] == 'r' && Grille[i][j].traitee[k] == 0)
                                pts_route_FP(Grille, i, j, k, Joueurs);
                        }
                    }
                    else if (Grille[i][j].traitee[4] == 0)
                        pts_route_FP(Grille, i, j, 4, Joueurs);
                }
                // pour les villes
                if (Grille[i][j].cotes[0] == 'v' || Grille[i][j].cotes[1] == 'v' || Grille[i][j].cotes[2] == 'v' || Grille[i][j].cotes[3] == 'v' || Grille[i][j].centre == 'v' ||
                    Grille[i][j].centre == 'b')
                {
                    pts_ville_FP(Grille, Joueurs, i, j);
                }
            }
        }
}

void rotation(struct tuile_s *T) // 1 mars
{
    int i, tmp = T->cotes[3];

    for (i = 3; i > 0; i--)
        T->cotes[i] = T->cotes[i - 1];
    T->cotes[0] = tmp;
}

void interface_joueur(struct tuile_s Grille[143][143], struct tuile_s Pile[NB_TUILES], int *nb_tours, int nb_joueurs, struct joueur_s *Joueur, int h, int b, int g, int d)
{
    int choix = -1;

    printf("Indiquez le numéro de l'action que vous souhaitez effectuer.\n\n\t1) Rotation de 90° dans le sens horaire\n\t2) Poser une tuile\n\n");
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        rotation(&Pile[*nb_tours]);
        break;
    case 2:
        poser_tuile(Grille, Pile, nb_tours, nb_joueurs, Joueur, h, b, g, d);
        break;
    default:
        printf("Commande non reconnue.\n");
        break;
    }
}

void parseur_csv(char *fname, struct tuile_s *Pile)
{
    FILE *fic = fopen(fname, "r");
    char *ligne;
    int i, j;
    size_t len = 0; // pour le getline
    char *choixCentre;

    if (fic != NULL)
    { // on s'assure que la lecture de fichier s'est bien faite
        for (i = 0; i < NB_TUILES; i++)
        {
            getline(&ligne, &len, fic);
            Pile[i].cotes[0] = strtok(ligne, ",")[0]; // on fait explicitement le premier strtok
            for (j = 1; j < 4; j++)
            {
                Pile[i].cotes[j] = strtok(NULL, ",")[0];
            }

            choixCentre = strtok(NULL, "");
            if (choixCentre[0] == 'v' && choixCentre[4] == 'a')
            {
                Pile[i].centre = 'V'; // si c'est une village
            }
            else
                Pile[i].centre = choixCentre[0]; // si ça ne commence pas par v

            Pile[i].pion.idPion = -1;
            Pile[i].pion.positionPion = -1;
            Pile[i].posee = 0;
        }
    }

    else
        printf("Erreur d'ouverture du fichier.");

    fclose(fic);
}