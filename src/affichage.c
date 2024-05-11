#include <stdio.h>
#include "affichage.h"

#define NB_TUILES 72

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

// Underline
#define UWHT "\e[4;37m"

void afficher_tuile_dbg(struct tuile_s t)
{
    printf("\t%c\t\n", t.cotes[0]);
    printf("%c\t%c\t%c\n", t.cotes[3], t.centre, t.cotes[1]);
    printf("\t%c\t\n\n", t.cotes[2]);
}

void affichage_accueil(void)
{
    char entree;
    system("clear");

    printf("\n\n\n\n\n\t\t\t      # ###\n");
    printf("\t\t\t    /  /###  /\n");
    printf("\t\t\t   /  /  ###/\n");
    printf("\t\t\t  /  ##   ##\n");
    printf("\t\t\t /  ###\n");
    printf("\t\t\t##   ##          /###   ###  /###     /###      /###     /###      /###   ###  /###   ###  /###     /##\n");
    printf("\t\t\t##   ##         / ###  / ###/ #### / / ###  /  / ###  /  / #### / / #### /  / ###  / ###/ #### / ###/ #### / / ###\n");
    printf("\t\t\t##   ##        /   ###/   ##   ###/ /   ###/  /   ###/  ##  ###/ ##  ###/  /   ###/   ##   ###/   ##   ###/ /   ###\n");
    printf("\t\t\t##   ##       ##    ##    ##       ##        ##    ##  ####     ####      ##    ##    ##    ##    ##    ## ##    ###\n");
    printf("\t\t\t##   ##       ##    ##    ##       ##        ##    ##    ###      ###     ##    ##    ##    ##    ##    ## ########\n");
    printf("\t\t\t ##  ##       ##    ##    ##       ##        ##    ##      ###      ###   ##    ##    ##    ##    ##    ## #######\n");
    printf("\t\t\t  ## #      / ##    ##    ##       ##        ##    ##        ###      ### ##    ##    ##    ##    ##    ## ##\n");
    printf("\t\t\t   ###     /  ##    /#    ##       ###     / ##    /#   /###  ## /###  ## ##    ##    ##    ##    ##    ## ####    /\n");
    printf("\t\t\t    ######/    ####/ ##   ###       ######/   ####/ ## / #### / / #### /   ######     ###   ###   ###   ### ######/\n");
    printf("\t\t\t      ###       ###   ##   ###       #####     ###   ##   ###/     ###/     ####       ###   ###   ###   ### #####\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tAppuyez sur Entrée pour commencer à jouer.");

    scanf("%c", &entree);
}

void affichage_menu(void)
{
    system("clear");
    printf("\n                                                                              |--__\n");
    printf("                                                                              |\n");
    printf("                                                                              X\n");
    printf("                                                                     |-___   / \\       |--__\n");
    printf("                                                                     |      =====      |\n");
    printf("                                                                     X      | .:|      X\n");
    printf("                                                                    / \\     | O |     / \\\n");
    printf("                                                                   =====   |:  . |   =====\n");
    printf("    [ o ]-------------[ o ]------------[ o ]                       |.: |__| .   : |__| :.|                            [ o ]-------------[ o ]-------------[ o ]\n");
    printf("    [   ]     ___     [   ]            [   ]                       |  :|. :  ...   : |.  |                            [   ]             [   ]     ___     [   ]\n");
    printf("    [   ]    /   \\    [   ]            [   ]               __   __W| .    .  ||| .      :|W__  --                     [   ]             [   ]    /   \\    [   ]\n");
    printf("    [   ]   |     |   [   ]   o        [   ]             -- __  W  WWWW______\"\"\"______WWWW   W -----  --              [   ]             [   ]   |     |   [   ]\n");
    printf("    [   ]   |     |   [   ]~\\_|_       [   ]        -  -     ___  ---    ____     ____----       --__  -              [   ]             [   ]   |     |   [   ]\n");
    printf("    [___]___|_____|___[___]___|________[___]--_ -- _ -- _ -- _            --__    --    --__     -___        __-   _  [___]_____________[___]___|_____|___[___]\n");

    printf("\v\v\t\t\t\t\t\t\tProjet de programmation du jeu Carcassonne en langage C.\n\t\t\t\tCette version de Carcassonne se joue uniquement avec les villes, les villages, les abbayes et les routes.\n\n\t\t\t\t\t\t\tProjet réalisé par Assalas ARAB et Evan ESTREMS.\n\n\n");
    printf("    ___________________________________________________________________________________________________________________________________________________________\n");

    printf(WHT);
    printf("\n");
    printf("__________________________________________________________________*************************************_________________________________________________________");
    printf("\n\t\t\t\t\t\t\t\t  |    __  __  _____  _   _  _   _    |\n");
    printf("\t\t\t\t\t\t\t\t  |   |  \\/  || ____|| \\ | || | | |   |\n");
    printf("\t\t\t\t\t\t\t\t  |   | |\\/| ||  _|  |  \\| || | | |   |\n");
    printf("\t\t\t\t\t\t\t\t  |   | |  | || |___ | |\\  || |_| |   |\n");
    printf("\t\t\t\t\t\t\t\t  |   |_|  |_||_____||_| \\_| \\___/    |\n");
    printf("\t\t\t\t\t\t\t\t  |                                   |\n");
    printf("__________________________________________________________________*************************************_________________________________________________________\n");
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

void afficher_ligne_couleur(struct tuile_s Grille[143][143], int l, int g, int d)
{ // changer couleur en couleur pion
    char *couleur;
    int i;
    // haut des tuiles
    printf("    |");
    for (i = g; i <= d; i++)
    {

        switch (Grille[l][i].pion.idPion)
        {
        case 0:
            couleur = BLK;
            break;
        case 1:
            couleur = GRN;
            break;
        case 2:
            couleur = BLU;
            break;
        case 3:
            couleur = MAG;
            break;
        case 4:
            couleur = CYN;
            break;
        default:
            break;
        }
        if (Grille[l][i].posee == 1)
        {
            if (Grille[l][i].pion.positionPion == 0)
            {
                switch (Grille[l][i].cotes[0])
                {
                case 'r':
                    printf(GRNB "  " YELB "%s♟ " GRNB "  " RESET, couleur);
                    break;

                case 'v':
                case 'b':
                    if ((Grille[l][i].cotes[3] == 'v' && Grille[l][i].centre == 'v') || (Grille[l][i].cotes[3] == 'b' && Grille[l][i].centre == 'b'))
                        printf(REDB "  " RESET);
                    else
                        printf(GRNB "  " RESET);

                    printf(REDB "%s♟ " RESET, couleur);

                    if ((Grille[l][i].cotes[1] == 'v' && Grille[l][i].centre == 'v') || (Grille[l][i].cotes[1] == 'b' && Grille[l][i].centre == 'b'))
                        printf(REDB "  " RESET);

                    else
                        printf(GRNB "  " RESET);

                    break;

                default:
                    break;
                }
            }
            else
            {
                switch (Grille[l][i].cotes[0])
                {
                case 'r':
                    printf(GRNB "  " YELB "  " GRNB "  " RESET);
                    break;

                case 'v':
                case 'b':
                    if ((Grille[l][i].cotes[3] == 'v' && Grille[l][i].centre == 'v') || (Grille[l][i].cotes[3] == 'b' && Grille[l][i].centre == 'b'))
                        printf(REDB "  " RESET);
                    else
                        printf(GRNB "  " RESET);

                    printf(REDB "  " RESET);

                    if ((Grille[l][i].cotes[1] == 'v' && Grille[l][i].centre == 'v') || (Grille[l][i].cotes[1] == 'b' && Grille[l][i].centre == 'b'))
                        printf(REDB "  " RESET);

                    else
                        printf(GRNB "  " RESET);

                    break;

                case 'p':
                    printf(GRNB "      " RESET);
                    break;

                default:
                    break;
                }
            }
        }
        else
        {
            if (Grille[l][i].jouable == 'X')
            {
                printf("      ");
            }
            else
            {
                printf(WHTBL "      " RESET);
            }
        }
    }
    printf("|\n");
    printf("%3d |", l);
    // tuiles du milieu
    for (i = g; i <= d; i++)
    {
        switch (Grille[l][i].pion.idPion)
        {
        case 0:
            couleur = BLK;
            break;
        case 1:
            couleur = GRN;
            break;
        case 2:
            couleur = BLU;
            break;
        case 3:
            couleur = MAG;
            break;
        case 4:
            couleur = CYN;
            break;
        default:
            break;
        }
        if (Grille[l][i].posee == 1)
        // Grille[l][i].cotes[3]
        {
            if (Grille[l][i].pion.positionPion == 3)
            {
                switch (Grille[l][i].cotes[3])
                {
                case 'r':
                    printf(YELB "%s♟ " RESET, couleur);
                    break;
                case 'v':
                    printf(REDB "%s♟ " RESET, couleur);
                    break;

                case 'b':
                    printf(REDB "%s♟ " RESET, couleur);
                    break;

                default:
                    break;
                }
            }
            else
            {
                switch (Grille[l][i].cotes[3])
                {
                case 'r':
                    printf(YELB "  " RESET);
                    break;

                case 'p':
                    printf(GRNB "  " RESET);
                    break;

                case 'v':
                    printf(REDB "  " RESET);
                    break;

                case 'b':
                    printf(REDB "  " RESET);
                    break;

                default:
                    break;
                }
            }
            // Grille[l][i].centre
            if (Grille[l][i].pion.positionPion == 4)
            {
                switch (Grille[l][i].centre)
                {
                case 'r':
                    printf(YELB "%s♟ " RESET, couleur);
                    break;
                case 'v':
                    printf(REDB "%s♟ " RESET, couleur);
                    break;
                case 'b':
                    printf(REDB WHT "🛡 " RESET "%s♟" RESET, couleur);
                    break;
                case 'a':
                    printf(WHTB "%s♟ " RESET, couleur);
                    break;

                default:
                    break;
                }
            }
            else
            {
                switch (Grille[l][i].centre)
                {
                case 'r':
                    printf(YELB "  " RESET);
                    break;

                case 'p':
                    printf(GRNB "  " RESET);
                    break;

                case 'v':
                    printf(REDB "  " RESET);
                    break;
                case 'b':
                    printf(REDB WHT "🛡 " RESET);
                    break;
                case 'V':
                    printf(BLKHB "  " RESET);
                    break;
                case 'a':
                    printf(WHTB "  " RESET);
                    break;

                default:
                    break;
                }
            }
            // Grille[l][i].cotes[1]
            if (Grille[l][i].pion.positionPion == 1)
            {
                switch (Grille[l][i].cotes[1])
                {
                case 'r':
                    printf(YELB "%s♟ " RESET, couleur);
                    break;
                case 'v':
                case 'b':
                    printf(REDB "%s♟ " RESET, couleur);
                    break;
                default:
                    break;
                }
            }
            else
            {
                switch (Grille[l][i].cotes[1])
                {
                case 'r':
                    printf(YELB "  " RESET);
                    break;

                case 'p':
                    printf(GRNB "  " RESET);
                    break;

                case 'v':
                case 'b':
                    printf(REDB "  " RESET);
                    break;

                default:
                    break;
                }
            }
        }
        else
        {
            if (Grille[l][i].jouable == 'X')
            {
                printf("      ");
            }
            else
            {
                printf(WHTBL "      " RESET);
            }
        }
    }
    printf("| %d\n", l);
    printf("    |");
    // Grille[l][i].cotes[2]
    for (i = g; i <= d; i++)
    {
        switch (Grille[l][i].pion.idPion)
        {
        case 0:
            couleur = BLK;
            break;
        case 1:
            couleur = GRN;
            break;
        case 2:
            couleur = BLU;
            break;
        case 3:
            couleur = MAG;
            break;
        case 4:
            couleur = CYN;
            break;
        default:
            break;
        }
        if (Grille[l][i].posee == 1)
        {
            if (Grille[l][i].pion.positionPion == 2)
            {
                switch (Grille[l][i].cotes[2])
                {
                case 'r':
                    printf(GRNB "  " YELB "%s♟ " GRNB "  " RESET, couleur);
                    break;

                case 'v':
                case 'b':
                    if ((Grille[l][i].cotes[3] == 'v' && Grille[l][i].centre == 'v') || (Grille[l][i].cotes[3] == 'b' && Grille[l][i].centre == 'b'))
                        printf(REDB "  " RESET);
                    else
                        printf(GRNB "  " RESET);

                    printf(REDB "%s♟ " RESET, couleur);

                    if ((Grille[l][i].cotes[1] == 'v' && Grille[l][i].centre == 'v') || (Grille[l][i].cotes[1] == 'b' && Grille[l][i].centre == 'b'))
                        printf(REDB "  " RESET);
                    else
                        printf(GRNB "  " RESET);
                    break;
                default:
                    break;
                }
            }
            else
            {
                switch (Grille[l][i].cotes[2])
                {
                case 'r':
                    printf(GRNB "  " YELB "  " GRNB "  " RESET);
                    break;

                case 'v':
                case 'b':
                    if ((Grille[l][i].cotes[3] == 'v' && Grille[l][i].centre == 'v') || (Grille[l][i].cotes[3] == 'b' && Grille[l][i].centre == 'b'))
                        printf(REDB "  " RESET);
                    else
                        printf(GRNB "  " RESET);

                    printf(REDB "  " RESET);

                    if ((Grille[l][i].cotes[1] == 'v' && Grille[l][i].centre == 'v') || (Grille[l][i].cotes[1] == 'b' && Grille[l][i].centre == 'b'))
                        printf(REDB "  " RESET);
                    else
                        printf(GRNB "  " RESET);
                    break;

                case 'p':
                    printf(GRNB "      " RESET);
                    break;

                default:
                    break;
                }
            }
        }
        else
        {
            if (Grille[l][i].jouable == 'X')
            {
                printf("      ");
            }
            else
            {
                printf(WHTBL "      " RESET);
            }
        }
    }
    printf("|\n");
}

void afficher_tuile_en_cours_couleur(struct tuile_s T)
{
    printf("_______________________________________________________________________________________________________________________________________\n\n");
    printf(REDB "\t  " RESET " Villes    " BLKHB "  " RESET " Villages    " GRNB "  " RESET " Prés    " WHTB "  " RESET " Abbayes    " YELB "  " RESET " Routes    " WHT "♟" RESET " Pions    " WHT "🛡 " RESET " Blason"
                "\n\n");
    printf(RESET UWHT "Tuile en cours :\n\n" RESET);
    // T.cotes[0]
    printf("\t");
    switch (T.cotes[0])
    {
    case 'r':
        printf(GRNB "  " YELB "  " GRNB "  " RESET);
        break;

    case 'v':
    case 'b':
        if ((T.cotes[3] == 'v' && T.centre == 'v') || (T.cotes[3] == 'b' && T.centre == 'b'))
            printf(REDB "  " RESET);
        else
            printf(GRNB "  " RESET);

        printf(REDB "  " RESET);

        if ((T.cotes[1] == 'v' && T.centre == 'v') || (T.cotes[1] == 'b' && T.centre == 'b'))
            printf(REDB "  " RESET);

        else
            printf(GRNB "  " RESET);

        break;

    case 'p':
        printf(GRNB "      " RESET);
        break;

    default:
        break;
    }
    printf("\n\t");
    // T.cotes[3]
    switch (T.cotes[3])
    {
    case 'r':
        printf(YELB "  " RESET);
        break;

    case 'p':
        printf(GRNB "  " RESET);
        break;

    case 'v':
        printf(REDB "  " RESET);
        break;

    case 'b':
        printf(REDB "  " RESET);
        break;

    default:
        break;
    }
    // T.centre
    switch (T.centre)
    {
    case 'r':
        printf(YELB "  " RESET);
        break;

    case 'p':
        printf(GRNB "  " RESET);
        break;

    case 'v':
        printf(REDB "  " RESET);
        break;
    case 'b':
        printf(REDB WHT "🛡 " RESET);
        break;
    case 'V':
        printf(BLKHB "  " RESET);
        break;
    case 'a':
        printf(WHTB "  " RESET);
        break;

    default:
        break;
    }
    // T.cotes[1]
    switch (T.cotes[1])
    {
    case 'r':
        printf(YELB "  " RESET);
        break;

    case 'p':
        printf(GRNB "  " RESET);
        break;

    case 'v':
    case 'b':
        printf(REDB "  " RESET);
        break;

    default:
        break;
    }
    printf("\n\t");
    // T.cotes[2]
    switch (T.cotes[2])
    {
    case 'r':
        printf(GRNB "  " YELB "  " GRNB "  " RESET);
        break;

    case 'v':
    case 'b':
        if ((T.cotes[3] == 'v' && T.centre == 'v') || (T.cotes[3] == 'b' && T.centre == 'b'))
            printf(REDB "  " RESET);
        else
            printf(GRNB "  " RESET);

        printf(REDB "  " RESET);

        if ((T.cotes[1] == 'v' && T.centre == 'v') || (T.cotes[1] == 'b' && T.centre == 'b'))
            printf(REDB "  " RESET);
        else
            printf(GRNB "  " RESET);
        break;

    case 'p':
        printf(GRNB "      " RESET);
        break;

    default:
        break;
    }
    printf("\n\n");
}

void afficher_joueurs(int nb_joueurs, int nb_tours, struct joueur_s *Joueur)
{
    int i;
    char *couleur;
    // Affichage 1ere ligne
    for (i = 0; i < nb_joueurs; i++)
    {
        if (i != (nb_tours - 1) % nb_joueurs)
        {
            printf(MAG);
            printf("Joueur %d           \t", i + 1);
            printf(RESET);
        }
        else
            printf(WHT "Joueur %d           \t" RESET, i + 1);
    }
    printf("\n");

    // Affichage 2e ligne
    for (i = 0; i < nb_joueurs; i++)
    {
        switch (i)
        {
        case 0:
            couleur = BLK;
            break;
        case 1:
            couleur = GRN;
            break;
        case 2:
            couleur = BLU;
            break;
        case 3:
            couleur = MAG;
            break;
        case 4:
            couleur = CYN;
            break;
        default:
            break;
        }
        if (i != (nb_tours - 1) % nb_joueurs)
            printf("%s♟" MAG " : %d/6           \t" RESET, couleur, (6 - Joueur[i].pionsPoses));
        else
            printf("%s♟" WHT " : %d/6           \t" RESET, couleur, (6 - Joueur[i].pionsPoses));
    }
    printf("\n");

    // Affichage 3e ligne
    for (i = 0; i < nb_joueurs; i++)
    {
        if (i != (nb_tours - 1) % nb_joueurs)
        {
            printf(MAG);
            printf("🪙%3d                   ", Joueur[i].points);
            printf(RESET);
        }
        else
            printf(WHT "🪙%3d                   " RESET, Joueur[i].points);
    }
    printf("\n");
}

void affichage(struct tuile_s Grille[143][143], struct tuile_s Pile[72], int nb_tours, int nb_joueurs, struct joueur_s *Joueur, int *h, int *b, int *g, int *d)
{
    int i, j;
    int coord_max = NB_TUILES + nb_tours, coord_min = NB_TUILES - nb_tours; // pour ne pas recalculer à chaque itération

    system("clear");
    afficher_joueurs(nb_joueurs, nb_tours, Joueur);
    afficher_tuile_en_cours(Pile[nb_tours]);
    afficher_tuile_en_cours_couleur(Pile[nb_tours]);

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

    // deplacer_tuile_en_derniere_position(Pile, nb_tours, Grille, &Pile[nb_tours], *h, *b, *g, *d);

    posable(Grille, Pile[nb_tours], *h, *b, *g, *d);

    // Affichage (on laisse une marge de 1 dans les coins)

    // Affichage coord abcisses
    printf("    ");
    for (i = *g - 1; i <= *d + 1; i++)
    {
        printf("  %3d ", i);
    }
    printf("\n    ");

    // Affichage ligne de tirets
    for (i = 0; i < 6 * (*d - *g + 3) + 2; i++)
    {
        printf("-");
    }
    printf("\n");

    // Affichage de la grille
    for (i = *h - 1; i <= *b + 1; i++)
    {
        afficher_ligne_couleur(Grille, i, *g - 1, *d + 1);
    }

    // Affichage ligne de tirets
    printf("    ");
    for (i = 0; i < 6 * (*d - *g + 3) + 2; i++)
    {
        printf("-");
    }
    printf("\n");

    // Affichage ordonnées du bas
    printf("    ");
    for (i = *g - 1; i <= *d + 1; i++)
    {
        printf("  %3d ", i);
    }
    printf("\n\n");
}
void Affichage_fin(struct joueur_s *Joueurs,int nb_joueurs ){
    int i=2;
    struct joueur_s classement[5];
    int max;
printf("╔══════════════════════════════════╦═════════╦════════════════════════╗\n");
printf("║               Joueurs            ║   Pts   ║       classement       ║\n");
printf("╠══════════════════════════════════╬═════════╬════════════════════════╣\n");
for (i=0;i<nb_joueurs;i++){
    if(Joueurs[i].points>max);

    printf("║ player %d                        ║    %d   ║           %d            ║\n",i,Joueurs[i].points,classement);
    printf("╠══════════════════════════════════╬═════════╬════════════════════════╣\n");
}

printf("╚══════════════════════════════════╩═════════╩════════════════════════╝\n");




}