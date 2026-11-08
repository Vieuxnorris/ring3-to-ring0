#include "liste.h"
#include <stdio.h>

int main(void) {
    liste_liberer(NULL);
    struct Liste *l = liste_creer();
    if (l == NULL) {
        printf("ERROR ALLOC List\n");
        liste_liberer(l);
        return 1;
    }
    printf("taille:%zu - adresse:0x%p\n", l->taille, l->premier);
    liste_liberer(l);
    return 0;
}