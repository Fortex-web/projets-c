#include <stdlib.h>
#include <stdio.h>

struct maillon {
    int position_x;
    int position_y;
    struct maillon *precedent;
}; 

struct snake {
    struct maillon *tete;
    struct maillon *queue;
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
        }
    }
    grille[0][0] = '+';
    grille[11][11] = '+';
    grille[0][11] = '+';
    grille[11][0] = '+';
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



void avancer(char grille[12][12], struct snake *s, char direction) {
    int dx = 0;
    int dy = 0;
    if ((direction != 'z') && (direction != 's') && (direction != 'd') && (direction != 'q')) {
        printf("mauvaise touche, réessayez !\n\n");
    } else {
        if (direction == 'z') {
            dy = -1;
            dx = 0;
        } else if (direction == 's') {
            dy = 1;
            dx = 0;
        } else if (direction == 'd') {
            dx = 1;
            dy = 0;
        } else if (direction == 'q') {
            dx = -1;
            dy = 0;
        } 
        struct maillon *c = malloc(sizeof(struct maillon));
        struct maillon *a;
        c->position_y = s->tete->position_y + dy;
        c->position_x = s->tete->position_x + dx;
        c->precedent = NULL;
        grille[s->queue->position_y][s->queue->position_x] = '.';
        a = s->queue;
        s->queue = s->queue->precedent;
        s->tete->precedent = c;
        grille[s->tete->position_y][s->tete->position_x] = 'o';
        s->tete = c;
        grille[s->tete->position_y][s->tete->position_x]  = '@';
        free(a);
    }
    
}

int main (void) {

    char grille[12][12];
    char direction;
    int perdu = 0;

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

    
    struct snake s = {tete,queue};
    
    
    while(c->precedent != NULL) {
        grille[c->position_y][c->position_x] = 'o';
        c = c->precedent;
    }

    grille[tete->position_y][tete->position_x] = '@';

    afficher_grille(grille);

    while(perdu == 0 )  {
        scanf(" %c", &direction);
        printf("\n");
        avancer(grille, &s, direction);
        struct maillon *d = s.queue;
        while (d->precedent != NULL) {
            if ((s.tete->position_x == d->position_x) && (s.tete->position_y == d->position_y)) {
                perdu = 1;
                break;
            }
            d = d->precedent;
        }
        
        afficher_grille(grille);
        if ((s.tete->position_x == 11) || (s.tete->position_y == 11) || (s.tete->position_x == 0) || (s.tete->position_y == 0)) {
            perdu = 1;
        }
    }
    
    if (perdu == 1) {
        printf("GAME OVER\n");
    }

    
    
    return 0;
}
