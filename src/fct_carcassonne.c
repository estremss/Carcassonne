#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game_structures.h"
#include "fct_carcassonne.h"

#define NB_TUILES 72

void afficher_tuile_dbg(struct tuile_s t)
{
    printf("\t%c\t\n", t.cotes[0]);
    printf("%c\t%c\t%c\n", t.cotes[3], t.centre, t.cotes[1]);
    printf("\t%c\t\n\n", t.cotes[2]);
}

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

    while (n > 1)
    {
        i = rand() % n; // il faudra faire avec time.h par la suite
        n--;
        save = Pile[n];
        Pile[n] = Pile[i];
        Pile[i] = save;
    }
}

void initialiser_partie(struct tuile_s *Pile, struct tuile_s Grille[143][143], int *nb_joueurs, int *nb_ia)
{
    printf("Nombre de joueurs : ");
    scanf("%d", nb_joueurs);
    printf("\nNombre d'IA : ");
    scanf("%d", nb_ia);
    printf("\n");
    Grille[NB_TUILES][NB_TUILES] = depiler(Pile, 0);
    melange(Pile);
}

void afficher_ligne(struct tuile_s Grille[143][143], int l, int g, int d)
{
    int i;
    // haut des tuiles
    printf("    | ");
    for (i = g; i <= d; i++)
    {
        if (Grille[l][i].posee == 1)
        {
            printf("   %c    | ", Grille[l][i].cotes[0]);
        }
        else
        {
            printf("        | ");
        }
    }
    printf("\n");
    printf("%3d | ", l);
    // centre des tuiles
    for (i = g; i <= d; i++)
    {
        if (Grille[l][i].posee == 1)
        {
            printf("%c  %c  %c | ", Grille[l][i].cotes[3], Grille[l][i].centre, Grille[l][i].cotes[1]);
        }
        else
        {
            if (Grille[l][i].jouable == 'X')
            {
                printf("        | ");
            }
            else
            {
                printf("   %c    | ", Grille[l][i].jouable);
            }
        }
    }
    printf("%d", l);
    printf("\n");
    printf("    | ");
    // bas des tuiles
    for (i = g; i <= d; i++)
    {
        if (Grille[l][i].posee == 1)
        {
            printf("   %c    | ", Grille[l][i].cotes[2]);
        }
        else
        {
            printf("        | ");
        }
    }
    // bidouillages pour avoir un affichage correct
    printf("\n    ");
    for (i = 0; i < 10 * (d - g + 1) + 1; i++)
    {
        printf("-");
    }
    printf("\n");
}

void afficher_tuile_en_cours(struct tuile_s T)
{ // 1 mars
    printf("-----------\n");
    printf("|    %c    |\n", T.cotes[0]);
    printf("| %c  %c  %c |\n", T.cotes[3], T.centre, T.cotes[1]);
    printf("|    %c    |\n", T.cotes[2]);
    printf("-----------\n\n");
}

void affichage(struct tuile_s Grille[143][143], struct tuile_s Pile[72], int nb_tours, int nb_joueurs, struct joueur_s *Joueur, int *h, int *b, int *g, int *d)
{
    int joueur = (((nb_tours - 1) % nb_joueurs) + 1); // relation maths pour afficher le bon joueur
    int i, j;
    int coord_max = NB_TUILES + nb_tours, coord_min = NB_TUILES - nb_tours; // pour ne pas recalculer à chaque itération

    system("clear");

    printf("Joueur %d\n", joueur);
    printf("Pions en main : %d/6\n", (6 - Joueur[joueur].pionsPoses));
    printf("Points : %d\n\n", Joueur[joueur].points);
    printf("Tuiles restantes : %d/72\n\n", NB_TUILES - nb_tours);
    afficher_tuile_en_cours(Pile[nb_tours]);
    // Trouver les max

    for (i = coord_min; i <= coord_max; i++)
    {
        for (j = coord_min; j <= coord_max; j++)
        {
            if (Grille[i][j].posee == 1)
            {
                if (i < *h) // si tuile posée et i < h (donc i plus haut que hauteur_max actuelle)
                    *h = i;
                if (i > *b)
                    *b = i;
                if (j < *g)
                    *g = j;
                if (j > *d)
                    *d = j;
            }
        }
    }

    posable(Grille, Pile[nb_tours], *h, *b, *g, *d);

    // Affichage (on laisse une marge de 1 dans les coins)

    // Affichage coord abcisses
    printf("    ");
    for (i = *g - 1; i <= *d + 1; i++)
    {
        printf("   %3d    ", i);
    }
    printf("\n    ");

    // Affichage ligne de tirets
    for (i = 0; i < 10 * (*d - *g + 3) + 1; i++)
    {
        printf("-");
    }
    printf("\n");

    // Affichage de la grille
    for (i = *h - 1; i <= *b + 1; i++)
    {
        afficher_ligne(Grille, i, *g - 1, *d + 1);
    }

    // Affichage ordonnées du bas
    printf("    ");
    for (i = *g - 1; i <= *d + 1; i++)
    {
        printf("   %3d    ", i);
    }
    printf("\n\n");
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
                    if ((T.cotes[0] == Grille[i - 1][j].cotes[2] || Grille[i - 1][j].posee == 0) && (T.cotes[1] == Grille[i][j + 1].cotes[3] || Grille[i][j + 1].posee == 0) && (T.cotes[2] == Grille[i + 1][j].cotes[0] || Grille[i + 1][j].posee == 0) && (T.cotes[3] == Grille[i][j - 1].cotes[1] || Grille[i][j - 1].posee == 0))
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

void poser_tuile(struct tuile_s Grille[143][143], struct tuile_s Pile[72], int *nb_tours)
{
    int x, y;

    printf("Entrez le numéro de la ligne : ");
    scanf("%d", &x);
    printf("Entrez le numéro de la colonne : ");
    scanf("%d", &y);

    if (x > NB_TUILES || y > NB_TUILES || x < 0 || y < 0)
    {
        printf("Coordonnées inexistantes.");
        poser_tuile(Grille, Pile, nb_tours);
    }

    if (Grille[x][y].jouable == 'O')
    {
        Grille[x][y] = depiler(Pile, *nb_tours);
        *nb_tours += 1;
    }
    else
    {
        printf("La tuile n'est pas jouable ici.\n\n");
        poser_tuile(Grille, Pile, nb_tours);
    }
}

void rotation(struct tuile_s *T) // 1 mars
{
    int i, tmp = T->cotes[3];

    for (i = 3; i > 0; i--)
        T->cotes[i] = T->cotes[i - 1];
    T->cotes[0] = tmp;
}

void interface_joueur(struct tuile_s Grille[143][143], struct tuile_s Pile[72], int *nb_tours, int nb_joueurs, struct joueur_s *Joueur, int *h, int *b, int *g, int *d)
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
        poser_tuile(Grille, Pile, nb_tours);
        break;
    default:
        printf("Commande non reconnue.");
        interface_joueur(Grille, Pile, nb_tours, nb_joueurs, Joueur, h, b, g, d);
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
