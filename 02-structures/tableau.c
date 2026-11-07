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

int main() {
    const size_t nb_ajouts = 1000;
    struct Tableau *t = tableau_creer(0);
    if (t == NULL) {
        return 1;
    }

    int valid;
    for(size_t i=0; i<nb_ajouts; i++) {
        valid = tableau_ajouter(t, (int)i-500);
        if (valid != 0) {
            printf("ERROR ajout sur l'indice: %zu\n", i);
            tableau_liberer(t);
            return 1;
        }
    }

    if(t->taille != nb_ajouts) {
        printf("ERROR taille:%zu == attendu:%zu\n", t->taille, nb_ajouts);
        tableau_liberer(t);
        return 1;
    }
    printf("taille=%zu - capacite=%zu\n", t->taille, t->capacite);
    
    int v;
    for(size_t i=0; i<nb_ajouts;i++) {
        if(tableau_lire(t, i, &v) == 0) {
            if (v != (int)i-500) {
                printf("indice: %zu attendu: %d, lu: %d\n", i, (int)i-500, v);
                tableau_liberer(t);
                return 1;
            }
        } else {
            printf("ERROR\n");
            tableau_liberer(t);
            return 1;
        }
    }

    printf("OK : 1000 valeurs verifiees.\n");
    tableau_liberer(t);
    return 0;
}