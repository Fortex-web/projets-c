#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void afficher_grille(char grille[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", grille[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int a_gagne(char grille[3][3], char joueur) {
    for (int i = 0; i < 3; i++) {
        
        if (grille[i][0] == joueur && grille[i][1] == joueur && grille[i][2] == joueur) {
            return 1;
        }
        
        if (grille[0][i] == joueur && grille[1][i] == joueur && grille[2][i] == joueur) {
            return 1;
        }
    }
   
    if (grille[0][0] == joueur && grille[1][1] == joueur && grille[2][2] == joueur) {
        return 1;
    }
    if (grille[0][2] == joueur && grille[1][1] == joueur && grille[2][0] == joueur) {
        return 1;
    }
    return 0; 
}

int coup_gagnant(char grille[3][3], char symbole) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grille[i][j] == '.') {
                grille[i][j] = symbole;
                if (a_gagne(grille, symbole) == 1) {
                    grille[i][j] = '.';
                    return (i*3 + j);
                }
                grille[i][j] = '.';
            }

        }

    }
    return -1;
}

int grille_pleine(char grille[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grille[i][j] == '.') {
                return 0;
            }
        }

    }
    return 1;
}

int minimax(char grille[3][3], char joueur) {
    char joueur_pro;
    int meuilleur_score;
    if (joueur == 'O') {
        joueur_pro = 'X';
        meuilleur_score = -2;
    } else {
        joueur_pro = 'O';
        meuilleur_score = 2;
    }

    if (a_gagne(grille, 'X') == 1) {
        return -1;
    } else if (a_gagne(grille, 'O') == 1) {
        return 1;
    } else if (grille_pleine(grille) == 1) {
        return 0;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grille[i][j] == '.') {
                grille[i][j] = joueur;
                int score = minimax(grille, joueur_pro);
                if (joueur =='O') {
                    if (score > meuilleur_score) {
                        meuilleur_score = score;
                    }
                } else {
                    if (score < meuilleur_score) {
                        meuilleur_score = score;
                    }
                }
                grille[i][j] = '.';

            }
        }

    }
    return meuilleur_score;
}

int meilleur_coup(char grille[3][3]) {
    int meilleur = -2;
    int ligne;
    int colonne;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grille[i][j] == '.') {
                grille[i][j] = 'O';
                int score = minimax(grille, 'X');
            if (score > meilleur) {
                meilleur = score;
                ligne = i;
                colonne = j;
            }
            grille[i][j] = '.';
}
        }
    }
    return ((ligne*3)+colonne);
}


int main(void) {
    srand(time(NULL));
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
        int win_x = coup_gagnant(grille, 'X');
        int win_o = coup_gagnant(grille, 'O');

        if (joueur == 'O') {
            ligne = (meilleur_coup(grille)/3)+1;
            colonne = (meilleur_coup(grille)%3)+1;
        } else {
            printf("Joueur %c, donnez la ligne et la colonne :\n", joueur);
            scanf("%d %d", &ligne, &colonne);
        }

        if (ligne > 3 || ligne < 1 || colonne > 3 || colonne < 1) {
            printf("La ligne et la colonne doivent etre entre 1 et 3\n");
        } else if (grille[ligne-1][colonne-1] != '.' ) {
            if (joueur == 'X') {
            printf("Case deja prise\n");
            }
        } else {
            nb_tours++;
            grille[ligne-1][colonne-1] = joueur;
            if (joueur == 'O') {
                printf("L'ordi joue en %d %d\n", ligne, colonne);
            }
            afficher_grille(grille);

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
    }

    if (gagnant == 0) {
        printf("Match nul !\n");
    }

    return 0;
}