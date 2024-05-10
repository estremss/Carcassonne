#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game_structures.h"
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

int deplacer_tuile_en_derniere_position(struct tuile_s *Pile, int nb_tours, struct tuile_s Grille[143][143], int h, int b, int g, int d)
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
        // deplacer_tuile_en_derniere_position(Pile, nb_tours, Grille, h, b, g, d);
    }

    return cnt_posable;
}

void melange(struct tuile_s *Pile)
{
    int i, n = 72;
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

void parametre_partie(struct tuile_s *Pile, struct tuile_s Grille[143][143], int *nb_joueurs, int *nb_ia)
{
    printf("\v\v\v\v\v\tNombre de joueurs : ");
    scanf("%d", nb_joueurs);
    printf("\n\n\tNombre d'IA : ");
    scanf("%d", nb_ia);
    printf("\n");
    if (*nb_joueurs + *nb_ia < 2 || *nb_joueurs + *nb_ia > 5)
    {
        printf("\tLe nombre de joueurs doit être compris entre 2 et 5.\n");
        parametre_partie(Pile, Grille, nb_joueurs, nb_ia);
    }
    Grille[NB_TUILES][NB_TUILES] = depiler(Pile, 0);
    melange(Pile); // pour le debug on le laisse en commentaire
}

int posable(struct tuile_s Grille[143][143], struct tuile_s T, int h, int b, int g, int d) // 1 mars
{                                                                                          // return le nb d'endroit où la tuile est posable                                                                                           // on n'a pas testé la fonction
    // à confirmer si pour 'jouable' on doit utiliser des pointeurs ou pas
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

void poser_tuile(struct tuile_s Grille[143][143], struct tuile_s Pile[72], int *nb_tours, int nb_joueurs, struct joueur_s *Joueur)
{
    int x, y, i;

    printf("Entrez le numéro de la colonne : ");
    scanf("%d", &y);
    printf("Entrez le numéro de la ligne : ");
    scanf("%d", &x);

    if (x > 2 * NB_TUILES - 2 || y > 2 * NB_TUILES - 2 || x < 0 || y < 0)
    {
        printf("Coordonnées inexistantes.");
        interface_joueur(Grille, Pile, nb_tours, nb_joueurs, Joueur);
    }

    if (Grille[x][y].jouable == 'O')
    { // MODIFIER POUR QUE L'utilistaeur NE PUISSE PAS POSER PIONS SUR PRE ET APPLIQUER LE CHANGEMENT DE COULEUR DU PION
        Grille[x][y] = depiler(Pile, *nb_tours);
        poser_pion(Grille, Joueur, *nb_tours, nb_joueurs, x, y);

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

        *nb_tours += 1;
    }
    else
    {
        printf("\nLa tuile n'est pas jouable ici.\n\n");
        interface_joueur(Grille, Pile, nb_tours, nb_joueurs, Joueur);
    }
}
void poser_pion(struct tuile_s Grille[143][143], struct joueur_s *Joueur, int nb_tours, int nb_joueurs, int x, int y)
{
    int choixPoserPion = -1;

    while (choixPoserPion != 0 && choixPoserPion != 1)
    {
        printf("\nVoulez-vous placer un pion sur la tuile ?\n(oui: 1 - non: 0) : ");
        scanf("%d", &choixPoserPion);
    }

    if (choixPoserPion == 1)
    {
        int position;

        printf("Choisissez le côté où poser le pion :\n\t-0 : Haut\n\t-1 : Droite\n\t-2 : Bas \n\t-3 : Gauche \n\t-4 : Centre\n\t-5 : Annuler\n");
        scanf("%d", &position);

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
               (position < 0 || position > 4))
        {
            // DEBUG
            // if ((Grille[x][y].centre == 'r' && position == 4 && verif_route_iteratif(Grille, x, y, position) != 0) ||
            //     (position < 4 && Grille[x][y].cotes[position] == 'r' && verif_route_iteratif(Grille, x, y, position) != 0))
            // {
            //     printf("erreur fonction verif route iteratif\n");
            // }

            printf("Le pion n'est pas posable ici.\n\n");
            printf("Choisissez le côté où poser le pion :\n\t-0 : Haut\n\t-1 : Droite\n\t-2 : Bas \n\t-3 : Gauche \n\t-4 : Centre\n\t-5 : Annuler\n");
            scanf("%d", &position);

            if (position == 5)
                return;
        }

        Grille[x][y].pion.idPion = (nb_tours - 1) % nb_joueurs;
        Grille[x][y].pion.positionPion = position;
        Joueur[(nb_tours - 1) % nb_joueurs].pionsPoses++;
    }
}

int verif_route(struct tuile_s Grille[143][143], int x, int y, int papa, int i, int j)
{ // return 0 si on peut poser le pion, -1 sinon
    // on peut mettre 4 dans "papa" par défaut

    // i et j sont la sauvegarde des premiers x et y, ils ne changent pas dans les appels, dans le premier appel ils doivent être égaux à x et y
    // papa est le coté de la tuile précédente qui est connecté à la route de la tuile actuelle
    // etat est la variable qui se transmet d'appel en appel qui indique si on est tombé sur un pion ou pas, 0 si on est pas tombé sur un pion, 1 dans l'autre cas
    printf("%d,%d", x, y);
    if (etat_verif_route == 0)
    {

        // Conditions d'arrêt 1 : si pion posé sur route
        if (Grille[x][y].pion.idPion != -1)
        {

            if (Grille[x][y].pion.positionPion <= 3 && Grille[x][y].cotes[Grille[x][y].pion.positionPion] == 'r')
            {
                etat_verif_route = 1;
                printf("erreur type pion coté");
                return -1;
            }
            else
            {
                if ((Grille[x][y].pion.positionPion == 4 && Grille[x][y].centre == 'r'))
                {
                    etat_verif_route = 1;
                    printf("erreur type pion centre");
                    return -1;
                }
            }
        }
        // Condition d'arrêt 2 : si fin de route OU tuile absente
        else if (Grille[x][y].centre != 'r')
            return 0;

        // Traitement : on regarde à quel endroit part la route en s'assurant que ce ne soit pas l'endroit d'où elle vient

        if (Grille[x][y].cotes[0] == 'r' && papa != 2)
        {
            papa = 0;
            if (etat_verif_route == 0)
                verif_route(Grille, x - 1, y, papa, i, j);
            else
            {
                printf("erreur type 1");
                return -1;
            }
        }
        if (Grille[x][y].cotes[1] == 'r' && papa != 3)
        {
            papa = 1;
            if (etat_verif_route == 0)
                verif_route(Grille, x, y + 1, papa, i, j);
            else
            {
                printf("erreur type 2");
                return -1;
            }
        }
        if (Grille[x][y].cotes[2] == 'r' && papa != 0)
        {
            papa = 2;
            if (etat_verif_route == 0)
                verif_route(Grille, x + 1, y, papa, i, j);
            else
            {
                printf("erreur type 3");
                return -1;
            }
        }
        if (Grille[x][y].cotes[3] == 'r' && papa != 1)
        {
            papa = 3;
            if (etat_verif_route == 0)
                verif_route(Grille, x, y - 1, papa, i, j);
            else
            {
                printf("erreur type 4");
                return -1;
            }
        }
    }

    else
    {
        printf("erreur type etat");
        return -1;
    }

    return 0;
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
{ // return 0 si c'est bon et -1 sinon
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

    if (P.y == x && P.y == y) // si on a fait une boucle
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

void pts_route(struct tuile_s Grille[143][143], int x, int y, int position_pion, struct joueur_s *Joueurs)
{ // return le nombre de points rapporté par la pose de la route dans le tour
    // reste à définir où est-ce que la fonction sera appelée

    int pions_route_actuelle[5];
    struct position P;
    struct tuile_s G_Traitees[143][143];
    int direction_route = 0, direction_route2 = -1;
    int i, j, cnt_pts = 1;

    for (i = 0; i < 143; i++)
        for (j = 0; j < 143; j++)
            G_Traitees[i][j] = Grille[i][j];

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

    printf("direction 1 : %d\ndirection 2: %d", direction_route, direction_route2);

    P = T_direction_route(direction_route, x, y);

    while (Grille[P.x][P.y].cotes[P.pere] == 'r' && (P.x != x || P.y != y))
    {
        cnt_pts += 1;
        // ajout du premier éventuel pion
        for (i = 0; i < 4; i++) // le cas si le pion est sur un coté
        {
            if (Grille[P.x][P.y].cotes[i] == 'r' && Grille[P.x][P.y].pion.positionPion == i)
            {
                G_Traitees[P.y][P.y].traitee[i] = 1;
                pions_route_actuelle[Grille[P.x][P.y].pion.idPion] += 1;
            } // on ajoute un pion au joueur correspondant dans le tableau de comptage des pions des joueurs
        }

        if (Grille[P.x][P.y].centre == 'r' && Grille[P.x][P.y].pion.positionPion == 4)
        {
            G_Traitees[P.x][P.y].traitee[4] = 1;
            pions_route_actuelle[Grille[P.x][P.y].pion.idPion] += 1;
        } // on ajoute un pion au joueur correspondant dans le tableau de comptage des pions des joueurs

        if (Grille[P.x][P.y].centre == 'r')
        {
            direction_route = (P.pere + 1) % 4;
            while (Grille[P.x][P.y].cotes[direction_route] != 'r')
                direction_route = (direction_route + 1) % 4;
            
            G_Traitees[P.x][P.y].traitee[direction_route] = 1;
        }
        else
            break; // on break car on est sur une fin de route

        P = T_direction_route(direction_route, P.x, P.y);
    }

    if (direction_route2 != -1 && P.x != x && P.y != y && Grille[P.x][P.y].posee == 1)
    {
        P = T_direction_route(direction_route2, x, y);

        while (Grille[P.x][P.y].cotes[P.pere] == 'r' && Grille[P.x][P.y].posee == 1 && (P.x != x || P.y != y))
        {
            cnt_pts += 1;
            // ajout du premier éventuel pion
            for (i = 0; i < 4; i++) // le cas si le pion est sur un coté
            {
                if (Grille[P.x][P.y].cotes[i] == 'r' && Grille[P.x][P.y].pion.positionPion == i)
                {
                    G_Traitees[P.x][P.y].traitee[i] = 1;
                    pions_route_actuelle[Grille[P.x][P.y].pion.idPion] += 1;
                } // on ajoute un pion au joueur correspondant dans le tableau de comptage des pions des joueurs
            }

            if (Grille[P.x][P.y].centre == 'r' && Grille[P.x][P.y].pion.positionPion == 4)
            {
                G_Traitees[P.x][P.y].traitee[i] = 1;
                pions_route_actuelle[Grille[P.x][P.y].pion.idPion] += 1;
            } // on ajoute un pion au joueur correspondant dans le tableau de comptage des pions des joueurs

            if (Grille[P.x][P.y].centre == 'r')
            {
                direction_route2 = (P.pere + 1) % 4;
                while (Grille[P.x][P.y].cotes[direction_route2] != 'r')
                    direction_route2 = (direction_route2 + 1) % 4;

                G_Traitees[P.x][P.y].traitee[i] = 1;
            }
            else
                break; // on break car on est sur une fin de route (il faudra surement mettre un if après)

            P = T_direction_route(direction_route2, P.x, P.y);
        }
    }

    if (Grille[P.x][P.y].posee == 1 || (P.x == x && P.y == y))
    {
        int max_tableau = 1;
        for (i = 0; i < 5; i++)
        {
            if (pions_route_actuelle[i] >= max_tableau)
                max_tableau = pions_route_actuelle[i];
        }
        for (i = 0; i < 5; i++)
        {
            if (pions_route_actuelle[i] == max_tableau)
                Joueurs[i].points += cnt_pts;
        }

        for (i = 0; i < 143; i++)
            for(j = 0; j < 143; j++)
                Grille[i][j] = G_Traitees[i][j];
    }
}

void rotation(struct tuile_s *T) // 1 mars
{
    int i, tmp = T->cotes[3];

    for (i = 3; i > 0; i--)
        T->cotes[i] = T->cotes[i - 1];
    T->cotes[0] = tmp;
}

void interface_joueur(struct tuile_s Grille[143][143], struct tuile_s Pile[72], int *nb_tours, int nb_joueurs, struct joueur_s *Joueur)
{
    int choix;

    printf("Indiquez le numéro de l'action que vous souhaitez effectuer.\n\n\t1) Rotation de 90° dans le sens horaire\n\t2) Poser une tuile\n\n");
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        rotation(&Pile[*nb_tours]);
        break;
    case 2:
        poser_tuile(Grille, Pile, nb_tours, nb_joueurs, Joueur);
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
        for (i = 0; i < 72; i++)
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
        }
    }

    else
        printf("Erreur d'ouverture du fichier.");

    fclose(fic);
}