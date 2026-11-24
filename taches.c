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

void sauvegarder(struct liste *l) {
    FILE *f = fopen("tache.txt", "w");
    struct tache *d;
    if (f == NULL) {
    printf("Impossible d'ouvrir le fichier\n");
    return ;
    }
    d = l->tete;
    while (d != NULL) {
        fprintf(f, "%d %s\n", d->etat, d->titre);
        d = d->suivante;
    }
    fclose(f);
}


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

void charger(struct liste *l) {
    FILE *f = fopen("tache.txt", "r");
    if (f == NULL) {
        printf("fichier inexistant !");
        return;
    }
    char ligne[100];
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        int etat;
        char tache[50];
        sscanf(ligne, "%d %49[^\n]", &etat, tache);  
        ajouter_tache(l, tache);
        if ( etat == 1) {
            l->queue->etat = 1;
        }
    }
    fclose(f);
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
            sauvegarder(l);
        } else if (choix == 2) {
            int numero;
            struct tache *d;
            int i = 0;
            printf("Désignez le numéro de tache que vous voulez cochez \n");
            scanf(" %d", &numero);
            d = l->tete;
            while( d != NULL && i < numero - 1 && numero > 0 && d->suivante != NULL) {
                d = d->suivante;
                i++;
            }
            if (numero < 1 || i != numero - 1 || d == NULL) {
                printf("Numero pas bon, veillez tapez un numero valide !\n");
            } else {
                d->etat = (d->etat - 1)*(d->etat - 1);
            }
            sauvegarder(l);
        } else if (choix == 3) {
            int numero;
            struct tache *d;   
            struct tache *b;   
            int i = 0;
            printf("Désignez le numéro de tache que vous voulez supprimez \n");
            scanf(" %d", &numero);

            if (l->tete == NULL || numero < 1) {
                printf("Numero pas bon, veillez tapez un numero valide !\n");
            } else if (numero == 1) {
                b = l->tete;
                l->tete = b->suivante;
                if (l->tete == NULL) {

                    l->queue = NULL;
                }
                free(b);
            } else {
                d = l->tete;
                while (i < numero - 2 && d->suivante != NULL) {
                    d = d->suivante;
                    i++;
                }
                b = d->suivante;   
                if (i != numero - 2 || b == NULL) {
                    printf("Numero pas bon, veillez tapez un numero valide !\n");
                } else {
                    d->suivante = b->suivante;   
                    if (b == l->queue) {
                        l->queue = d;
                    }
                    free(b);
                }
            }
            sauvegarder(l);
        } else if (choix == 4) {
            quitter = 1;
        } else {
            printf("Choix inconnu !\n");
        }
    }
}

int main(void) {
    struct liste l = {NULL, NULL};
    charger(&l); 
    menu(&l);


    return 0;
}