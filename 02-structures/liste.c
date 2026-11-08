#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

void liste_liberer(struct Liste *l) {
    if (l != NULL) {
        free(l);
    } else {
        printf("Liste NULL no free memory needed\n");
    }
}

struct Liste *liste_creer(void) {
    struct Liste *l = malloc(sizeof(struct Liste));
    if (l == NULL) {
        return NULL;
    }

    l->taille = 0;
    l->premier = NULL;
    return l;
}