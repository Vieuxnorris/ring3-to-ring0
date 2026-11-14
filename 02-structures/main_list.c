#include "list.h"
#include <stdio.h>

enum {
    MAX_INDEX=3
};

const int pushes_reversed[] = {30,20,10};
const int pushes_ordered[] = {10,20,30};
const int test_delete_l_bis[] = {10,30};
const int test_delete[] = {10,30};
const int test_delete_m[] = {30,20};
const int test_delete_m_bis[] = {20,30};
const int test_delete_l[] = {30};
const int test_delete_k[] = {10,0,30};

// return 1 : if the value of p does not match expected[index]
// return 1 : if p has one index too many
// return 1 : if index is not equal to nb_expected
// return 1 : if the size of the list does not match
// return 0 : if all the tests pass
int check_list(struct List *l, const int *expected, size_t nb_expected) {
    struct Node *p = l->head;
    size_t index = 0;
    while (p != NULL && index != nb_expected) {
        if (expected[index] != p->value) {
            printf("ERROR p->value does not match index:%zu index_value:%d value_p:%d\n", index, expected[index],p->value);
            return 1;
        }
        index++;
        p = p->next;
    }

    if (p != NULL) {
        printf("ERROR one node too many after index %zu\n", index);
        return 1;
    }
    if (index != nb_expected) {
        printf("ERROR INDEX MAX - index_value:%zu max_index:%zu\n", index, nb_expected);
        return 1;
    }
    if (l->size != nb_expected) {
        printf("ERROR size: %zu expected %zu\n", l->size, nb_expected);
        return 1;
    }

    return 0;
}

// return 1 : if list_delete returns something other than expected_return
// return 1 : if check_list fails
// return 0 : if l == NULL or the tests pass
int test_deletion(struct List *l, int test_value, int expected_return, const int *expected, size_t nb_expected, size_t *nb_free) {
    int result_test = list_delete(l, test_value, nb_free);
    if (result_test != expected_return) {
        printf("expected_return:%d - test_value:%d - result_test:%d\n", expected_return, test_value, result_test);
        return 1;
    }
    if (l == NULL) {
        return 0;
    }
    if (check_list(l, expected, nb_expected) != 0) {
        return 1;
    }
    return 0;
}

int main(void) {
    size_t nb_free = 0;
    size_t nb_free_compare = 0;

    list_free(NULL, NULL);
    struct List *l = list_create();
    nb_free_compare++;
    struct Node *n;
    if (l == NULL) {
        printf("ERROR ALLOC List\n");
        list_free(l, NULL);
        return 1;
    }
    printf("size:%zu - address:0x%p\n", l->size, l->head);

    // Check push + size
    for (size_t i=0; i<MAX_INDEX;i++) {
        n = list_push_front(l,pushes_reversed[i]);
        if (n == NULL) {
            printf("ERROR ALLOC Node 1\n");
            list_free(l, &nb_free);
            return 1;
        }
        printf("size:%zu - address:0x%p\n", l->size, l->head);
        nb_free_compare++;
    }
    if (check_list(l, pushes_ordered, MAX_INDEX) != 0) {
        list_free(l, &nb_free);
        return 1;
    }

    list_print(l);

    for (size_t i=0; i<3;i++) {
        int buffer = 777;
        if(list_get(l, i, &buffer) == 0) {
            if(buffer == pushes_ordered[i]) {
                printf("test 1 -- buffer:%d - pushed_value:%d\n", buffer, pushes_ordered[i]);
            } else {
                printf("ERROR test 1 -- buffer:%d - pushed_value:%d\n", buffer, pushes_ordered[i]);
                list_free(l, &nb_free);
                return 1;
            }
        }
        else {
            printf("ERROR test 1 : index %zu rejected\n", i);
            list_free(l, &nb_free);
            return 1;
        }
    }
    int buffer = 777;
    if (list_get(l, 3, &buffer) == 0) {
        printf("ERROR test 2 -- index 3 accepted\n");
        list_free(l, &nb_free);
        return 1;
    } else {
        if (buffer != 777) {
            printf("ERROR test 2 -- buffer:%d\n", buffer);
            list_free(l, &nb_free);
            return 1;
        }
        printf("test 2 -- buffer:%d\n", buffer);
    }
    if (test_deletion(l, 20, 0, test_delete_l_bis, 2, &nb_free) != 0) {
        printf("ERROR - FAIL DELETE RECORD\n");
        list_free(l, &nb_free);
        return 1;
    }
    if (check_list(l, test_delete, 2) != 0) {
        list_free(l, &nb_free);
        return 1;
    }
    list_print(l);

    struct List *m = list_create();
    nb_free_compare++;
    if (m == NULL) {
        printf("ERROR ALLOC List\n");
        list_free(l, &nb_free);
        list_free(m, NULL);
        return 1;
    }
    if (list_get(m, 0, &buffer) == 0) {
        printf("ERROR test 3 : empty list accepted\n");
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        return 1;
    } else {
        if (buffer != 777) {
            printf("ERROR test 3 -- buffer:%d\n", buffer);
            list_free(l, &nb_free);
            list_free(m, &nb_free);
            return 1;
        }
        printf("test 3 -- buffer:%d\n", buffer);
    }

    for(size_t i=0; i<MAX_INDEX;i++) {
        n = list_push_back(m, pushes_reversed[i]);
        if (n == NULL) {
            printf("ERROR malloc\n");
            list_free(l, &nb_free);
            list_free(m, &nb_free);
            return 1;
        }
        printf("value n:%d ", n->value);
        nb_free_compare++;
    }
    printf("\n");

    struct Node *tmp = m->head;
    list_fail_malloc = 1;
    n = list_push_back(m, 50);
    list_fail_malloc = 0;
    if (n != NULL) {
        printf("n is not NULL\n");
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        return 1;
    }
    if (m->head != tmp) {
        printf("ERROR list differs from the temporary save (address)\n");
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        return 1;
    }
    if (check_list(m, pushes_reversed, MAX_INDEX) != 0) {
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        return 1;
    }

    printf("INIT TEST\n");
    list_print(l);
    list_print(m);
    if (test_deletion(l, 10, 0, test_delete_l, 1, &nb_free) != 0) {
        printf("ERROR - CASE B head\n");
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        return 1;
    }
    printf("OK CASE B\n");
    list_print(l);
    list_print(m);
    if (test_deletion(m, 10, 0, test_delete_m, 2, &nb_free) != 0) {
        printf("ERROR - CASE C last\n");
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        return 1;
    }
    printf("OK CASE C\n");
    list_print(l);
    list_print(m);
    if (test_deletion(l, 10, 1, test_delete_l, 1, &nb_free) != 0) {
        printf("ERROR - CASE D missing\n");
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        return 1;
    }
    printf("OK CASE D\n");
    list_print(l);
    list_print(m);
    if (test_deletion(l, 30, 0, NULL, 0, &nb_free) != 0) {
        printf("ERROR - CASE E1 emptying\n");
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        return 1;
    }
    printf("OK CASE E1\n");
    list_print(l);
    list_print(m);
    if (test_deletion(l, 10, 1, NULL, 0, &nb_free) != 0) {
        printf("ERROR - CASE E2 empty\n");
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        return 1;
    }
    printf("OK CASE E2\n");
    list_print(l);
    list_print(m);
    if (test_deletion(NULL, 10, 1, NULL, 0, &nb_free) != 0) {
        printf("ERROR - CASE F NULL\n");
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        return 1;
    }
    printf("OK CASE F\n");
    list_print(l);
    list_print(m);
    struct Node *test = list_push_back(m, 30);
    if (test != NULL) {
        nb_free_compare++;
        if (test_deletion(m, 30, 0, test_delete_m_bis, 2, &nb_free) != 0) {
            printf("ERROR - CASE G duplicate\n");
            list_free(l, &nb_free);
            list_free(m, &nb_free);
            return 1;
        }
    } else {
        printf("ERROR - CASE G ERROR MALLOC\n");
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        return 1;
    }
    printf("OK CASE G\n");
    list_print(l);
    list_print(m);

    struct List *k = list_create();
    nb_free_compare++;
    if (k == NULL) {
        printf("ERROR ALLOC List\n");
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        list_free(k, &nb_free);
        return 1;
    }
    printf("size:%zu - address:0x%p\n", k->size, k->head);
    for (size_t i=0; i<MAX_INDEX;i++) {
        n = list_push_back(k,test_delete_k[i]);
        if (n == NULL) {
            printf("ERROR ALLOC Node 1\n");
            list_free(l, &nb_free);
            list_free(m, &nb_free);
            list_free(k, &nb_free);
            return 1;
        }
        printf("size:%zu - address:0x%p\n", k->size, k->head);
        nb_free_compare++;
    }
    if (check_list(k, test_delete_k, MAX_INDEX) != 0) {
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        list_free(k, &nb_free);
        return 1;
    }
    list_print(k);
    if (test_deletion(k, 0, 0, test_delete, 2, &nb_free) != 0) {
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        list_free(k, &nb_free);
        return 1;
    }
    if (test_deletion(k, 10, 0, test_delete_l, 1, NULL) != 0) {
        list_free(l, &nb_free);
        list_free(m, &nb_free);
        list_free(k, &nb_free);
        return 1;
    }
    nb_free_compare--; // warning : free not eval


    list_free(l, &nb_free);
    list_free(m, &nb_free);
    list_free(k, &nb_free);
    printf("Number of free nb_free: %zu nb_free_compare:%zu\n", nb_free, nb_free_compare);
    if (nb_free != nb_free_compare) {
        printf("free compare it's WRONG!\n");
        return 1;
    }
    else {
        printf("free compare it's OK!\n");
        return 0;
    }
}