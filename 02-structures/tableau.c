#include <stdio.h>
#include <stdlib.h>

struct Tableau {
    int *donnees;
    size_t taille;
    size_t capacite;
};

void tableau_liberer(struct Tableau *t) {
    if (t != NULL) {
        free(t->donnees);
    }
    free(t);
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

int main() {
    struct Tableau *t = tableau_creer(10);
    if (t == NULL) {
        return 1;
    }
    printf("taille=%zu capacite=%zu\n", t->taille,t->capacite);
    tableau_liberer(t);
    return 0;
}