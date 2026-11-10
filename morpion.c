#include <stdio.h>

void afficher_grille(char grille[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", grille[i][j]);
        }
        printf("\n");
    }
}

int a_gagne(char grille[3][3], char joueur) {
    for (int i = 0; i < 3; i++) {
        // ligne i
        if (grille[i][0] == joueur && grille[i][1] == joueur && grille[i][2] == joueur) {
            return 1;
        }
        // colonne i
        if (grille[0][i] == joueur && grille[1][i] == joueur && grille[2][i] == joueur) {
            return 1;
        }
    }
    // diagonales
    if (grille[0][0] == joueur && grille[1][1] == joueur && grille[2][2] == joueur) {
        return 1;
    }
    if (grille[0][2] == joueur && grille[1][1] == joueur && grille[2][0] == joueur) {
        return 1;
    }
    return 0;
}

int main(void) {
    char grille[3][3];
    int ligne, colonne;
    char joueur = 'X';
    int nb_tours = 0;
    int gagnant = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grille[i][j] = '.';
        }
    }

    afficher_grille(grille);

    while (nb_tours < 9) {
        printf("Joueur %c, donnez la ligne et la colonne :\n", joueur);
        scanf("%d %d", &ligne, &colonne);

        if (ligne > 3 || ligne < 1 || colonne > 3 || colonne < 1) {
            printf("La ligne et la colonne doivent etre entre 1 et 3\n");
        } else if (grille[ligne-1][colonne-1] != '.') {
            printf("Case deja prise\n");
        } else {
            nb_tours++;
            grille[ligne-1][colonne-1] = joueur;

            if (a_gagne(grille, joueur) == 1) {
                afficher_grille(grille);
                printf("Joueur %c a gagne !\n", joueur);
                gagnant = 1;
                break;
            }

            if (joueur == 'X') {
                joueur = 'O';
            } else {
                joueur = 'X';
            }
        }

        afficher_grille(grille);
    }

    if (gagnant == 0) {
        printf("Match nul !\n");
    }

    return 0;
}
