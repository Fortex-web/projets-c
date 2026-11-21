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

void ajouter_tache(struct liste *l, char *titre) {
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

void menu (struct liste *l) {
    int quitter = 0;
    int choix = 0;
    while (quitter == 0) {
        afficher_taches(l);
        printf("\nQue veux-tu faire ?\n1. Ajouter une tâche\n2. Cocher une tâche\n3. Supprimer une tâche\n4. Quitter\n");
        scanf("%d", &choix);
        while (getchar() != '\n');
        if (choix == 1) {
            char texte[50];
            printf("Titre de la tâche : ");
            fgets(texte, sizeof(texte), stdin);
            texte[strcspn(texte, "\n")] = '\0';
            printf("\n");
            ajouter_tache(l, texte);
            printf("Tâche ajoutée !\n");
        } else if (choix == 2) {
            int numero;
            struct tache *d;
            int i = 0;
            printf("Désignez le numéro de tache que vous voulez cochez \n");
            scanf(" %d", &numero);
            d = l->tete;
            while( i < numero - 1 && numero > 0 && d->suivante != NULL) {
                d = d->suivante;
                i++;
            }
            if (numero < 1 || i != numero - 1 || d == NULL) {
                printf("Numero pas bon, veillez tapez un numero valide !\n");
            } else {
                d->etat = (d->etat - 1)*(d->etat - 1);
            }

        } else if (choix == 3) {

        } else if (choix == 4) {
            quitter = 1;
        } else {
            printf("Choix inconnu !\n");
        }
    }
}

int main(void) {
    struct liste l = {NULL, NULL};
    ajouter_tache(&l, "Réviser LO21");
    ajouter_tache(&l, "Aller à la salle");
    ajouter_tache(&l, "Rendre le TP");
    menu(&l);


    return 0;
}
