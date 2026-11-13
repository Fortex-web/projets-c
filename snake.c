#include <stdlib.h>
#include <stdio.h>

struct maillon {
    int position_x;
    int position_y;
    struct maillon *suivant;
}; 

void afficher_grille(char grille[12][12]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            printf("%c ", grille[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main (void) {
    char grille[12][12];
    for (int i =0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            grille[i][j] = '.';
            if(i == 0 || i == 11) {
                grille[i][j] = '-';
            }
            if(j == 0 || j == 11) {
                grille[i][j] = '|';
            }
            
        }
    }

    afficher_grille(grille);

    return 0;
}
