#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tache {
    char titre[50];
    int etat;
    struct tache *suivante;
};

struct liste {
    struct tache *tete;   
    struct tache *queue;  
};

void ajouter_tache(struct liste *l, char titre[50]) {
    struct tache *t = malloc(sizeof(struct tache));
    t->etat = 0;
    strcpy(t->titre, titre);
    t->suivante = NULL;
    if ( l->tete == NULL ) {
        l->tete = t;
        l->queue = t;
    } else {
        l->queue->suivante = t;
        l->queue = t;
    }
}

void afficher_taches(struct liste *l) {
    struct tache *d;
    d = l->tete;
    int numero = 1;
    while (d != NULL) {
        if (d->etat == 0) {
            printf("%d. [ ] %s\n", numero, d->titre);
        } else {
            printf("%d. [X] %s\n", numero, d->titre);
        }
        d = d->suivante;
        numero = numero + 1;
    }
}



int main(void) {
    struct liste l = {NULL, NULL};
    ajouter_tache(&l, "Réviser LO21");
    ajouter_tache(&l, "Aller à la salle");
    ajouter_tache(&l, "Rendre le TP");
    afficher_taches(&l);
    return 0;
}
