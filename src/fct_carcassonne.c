#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game_structures.h"
#include "fct_carcassonne.h"

#define NB_TUILES 72

struct tuile_s depiler(struct tuile_s *Pile, int nb_tours)
// Cette fonction met la carte du tour courant en "posee = 1"
{
    Pile[nb_tours].posee = 1;
    Pile[nb_tours].jouable = 'X';

    return Pile[nb_tours];
}

void deplacer_tuile_en_derniere_position(struct tuile_s *Pile, int nb_tours)
{
    int i = 0;
    struct tuile_s save = Pile[nb_tours];

    for (i = nb_tours; i < NB_TUILES - 1; i++) // - 1 car avec le i+1 on ferait un core dumped sinon
    {
        Pile[i] = Pile[i + 1];
    }
    Pile[nb_tours] = save;
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
    Grille[NB_TUILES][NB_TUILES] = depiler(Pile, 0);
    melange(Pile);
}

void posable(struct tuile_s Grille[143][143], struct tuile_s T, int h, int b, int g, int d) // 1 mars
{                                                                                           // on n'a pas testé la fonction
    // à confirmer si pour 'jouable' on doit utiliser des pointeurs ou pas
    int i, j;
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
                        Grille[i][j].jouable = 'O';
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
}

void poser_tuile(struct tuile_s Grille[143][143], struct tuile_s Pile[72], int *nb_tours, int nb_joueurs, struct joueur_s *Joueur)
{
    int x, y, choixPoserPion;

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
        printf("\nVoulez-vous placer un pion sur la tuile ?\n(oui: 1 - non: 0) : ");
        scanf("%d", &choixPoserPion);

        if (choixPoserPion == 1)
        {
            char position;
            int nettoyeur;

            printf("Choisissez le côté où poser le pion :\n\t-N : en haut\n\t-E : à droite\n\t-S : à gauche\n\t-W : en bas\n\t-C : au centre\n");
            scanf("%d", &nettoyeur);
            scanf("%c", &position);

            while ((position == 'N' && Grille[x][y].cotes[0] == 'p') ||
                   (position == 'S' && Grille[x][y].cotes[2] == 'p') ||
                   (position == 'E' && Grille[x][y].cotes[1] == 'p') ||
                   (position == 'W' && Grille[x][y].cotes[3] == 'p') ||
                   (position == 'C' && Grille[x][y].centre == 'p') ||
                   (position == 'C' && Grille[x][y].centre == 'V'))
            {
                printf("Le pion n'est pas posable sur les Villages et les prés.\n\n");
                printf("Choisissez le côté où poser le pion :\n\t-N : en haut\n\t-E : à droite\n\t-S : à gauche\n\t-W : en bas\n\t-C : au centre\n");
                scanf("%d", &nettoyeur);
                scanf("%c", &position);
            }

            Grille[x][y].pion.idPion = (*nb_tours - 1) % nb_joueurs;
            Grille[x][y].pion.positionPion = position;
            Joueur[(*nb_tours - 1) % nb_joueurs].pionsPoses++;
        }
        *nb_tours += 1;
    }
    else
    {
        printf("La tuile n'est pas jouable ici.\n\n");
        interface_joueur(Grille, Pile, nb_tours, nb_joueurs, Joueur);
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
        }
    }

    else
        printf("Erreur d'ouverture du fichier.");

    fclose(fic);
}