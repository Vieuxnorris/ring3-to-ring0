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
    for(size_t i=0; i<t->taille;i++) {
        printf("%d ", t->donnees[i]);
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

int main() {
    struct Tableau *t = tableau_creer(2);
    struct Tableau *j = tableau_creer(0);
    if (t == NULL || j == NULL) {
        return 1;
    }

    int last_result;

    // test 5 ajouts
    tableau_ajouter(t, 10);
    tableau_ajouter(t, 20);
    tableau_ajouter(t, 30);
    tableau_ajouter(t, 40);
    last_result = tableau_ajouter(t, 50);
    printf("taille=%zu capacite=%zu last_result=%d\n", t->taille,t->capacite, last_result);
    afficher_valeur(t);

    // test 3 ajouts
    tableau_ajouter(j, 10);
    tableau_ajouter(j, 20);
    tableau_ajouter(j, 30);
    last_result = tableau_ajouter(j, -1);
    printf("taille=%zu capacite=%zu last_result=%d\n", j->taille,j->capacite, last_result);
    afficher_valeur(j);

    // free
    tableau_liberer(t);
    tableau_liberer(j);
    return 0;
}