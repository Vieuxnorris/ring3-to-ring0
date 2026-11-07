#include "tableau.h"
#include <stdio.h>
#include <stdlib.h>


void tableau_liberer(struct Tableau *t) {
    if (t != NULL) {
        free(t->donnees);
    }
    free(t);
}

int tableau_lire(struct Tableau *t, size_t indice, int *buffer) {
    if (indice < t->taille) {
        *buffer = t->donnees[indice];
        return 0;
    }
    return 1;
}

int tableau_ajouter(struct Tableau *t, int valeur) {
    if (t->taille >= t->capacite) {
        size_t new_capacite;
        if (t->capacite == 0) {
            new_capacite = 1;
        } else {
            new_capacite = t->capacite * 2;
        }
        int *tmp = realloc(t->donnees, new_capacite * sizeof(int));

        if (tmp != NULL) {
            t->donnees = tmp;
            t->capacite = new_capacite;
        } else {
            return 1;
        }
    }

    t->donnees[t->taille] = valeur;
    t->taille++;
    return 0;
}

void afficher_valeur(struct Tableau *t) {
    int v;
    for(size_t i=0; i<t->taille;i++) {
        if (tableau_lire(t, i, &v) == 0) {
            printf("%d ", v);
        } else {
            printf("Indice invalide\n");
        }
    }
    printf("\n");
}

struct Tableau *tableau_creer(size_t capacite) {
    struct Tableau *t = malloc(sizeof(struct Tableau));
    if (t == NULL) {
        printf("ERROR MALLOC TABLEAU\n");
        return NULL;
    }

    t->donnees = malloc(sizeof(int) * capacite);
    if (t->donnees == NULL) {
        printf("ERROR MALLOC t->donnees\n");
        free(t);
        return NULL;
    }
    t->taille = 0;
    t->capacite = capacite;
    return t;
}