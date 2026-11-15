#include <stdlib.h>
#include <stdio.h>

struct maillon {
    int position_x;
    int position_y;
    struct maillon *precedent;
}; 

void cree_grille(char grille[12][12]) {
    for (int i =0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            grille[i][j] = '.';
            if(i == 0 || i == 11) {
                grille[i][j] = '-';
            }
            if(j == 0 || j == 11) {
                grille[i][j] = '|';
            }
            grille[0][0] = '+';
            grille[11][11] = '+';
            grille[0][11] = '+';
            grille[11][0] = '+';
        }
    }
}

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

    cree_grille(grille);

    struct maillon *queue = malloc(sizeof(struct maillon));
    struct maillon *a = malloc(sizeof(struct maillon));
    struct maillon *tete = malloc(sizeof(struct maillon));

    queue->position_x = 3;
    queue->position_y = 5;
    queue->precedent = a;

    a->position_x = 4;
    a->position_y = 5;
    a->precedent = tete;

    tete->position_x = 5;
    tete->position_y = 5;
    tete->precedent = NULL;

    struct maillon *c = queue;
    
    while(c->precedent != NULL) {
        grille[c->position_y][c->position_x] = 'o';
        c = c->precedent;
    }

    grille[tete->position_y][tete->position_x] = '@';

    afficher_grille(grille);


    free(queue);
    free(a);
    free(tete);
    
    return 0;
}
