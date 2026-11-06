#include <stdio.h>
#include <string.h>

int main(void) {
    char mot[] = "maison";
    char mot_cache[sizeof(mot)];
    char lettre;
    int erreur = 0;
    int trouver;
    int lettre_deja_tape[26];

    for(int i = 0; i < strlen(mot); i++) {
        mot_cache[i] = '_';
    }

    mot_cache[strlen(mot)] = '\0';
    int n_lettres = 0;

    while (erreur < 7 && strcmp(mot, mot_cache) != 0) {
        printf("donnez une lettre\n");
        scanf(" %c", &lettre);
        printf("\n");
        trouver = 0;

        for (int j = 0; j < n_lettres; j++) {
            if (lettre==lettre_deja_tape[j]) {
                printf("Déjà proposée !\n");
                trouver = 1;
            }
        }

        for(int i = 0; i < strlen(mot); i++) {
            if (lettre == mot[i]) {
                    mot_cache[i] = lettre;
                    trouver = 1;
            } 
        }

        if (trouver == 0) {
            erreur++;
            lettre_deja_tape[n_lettres] = lettre;
            n_lettres = n_lettres+1;
        }

        for(int i = 0; i < strlen(mot); i++) {
            printf("%c ", mot_cache[i]);
        }


        printf("il vous reste %d essais\n", 7-erreur);
    }

    if (strcmp(mot, mot_cache) == 0) {
        printf("victoire !\n");
    } else {
        printf("défaite !\n");
    }

    return 0;
}