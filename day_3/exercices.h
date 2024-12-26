#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    TYPE_PERSON,
    TYPE_BOOK
} ObjectType;


typedef struct Person {
    int age;
} Person;


static inline int are_persons_equals(void *a, void *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }

    Person *p1 = (Person *)a;
    Person *p2 = (Person *)b;

    return p1->age == p2->age ? 1 : 0;
}

static inline int compare_persons(void *a, void *b) {
    Person *p1 = (Person *)a;
    Person *p2 = (Person *)b;
    return p1->age - p2->age;
}


typedef struct Book {
    int pages;
} Book;


static inline int are_books_equals(void *a, void *b) {
    if (a == NULL || b == NULL) {
        return 0; 
    }

    Book *b1 = (Book *)a;
    Book *b2 = (Book *)b;

    return b1->pages == b2->pages ? 1 : 0;
}

static inline int compare_books(void *a, void *b) {
    Book *b1 = (Book *)a;
    Book *b2 = (Book *)b;
    return b1->pages - b2->pages;
}

static inline int are_equals(void *obj1, void *obj2, int (*compare_fnc)(void *, void *)) {
    if (obj1 == NULL || obj2 == NULL || compare_fnc == NULL) {
        return 0; 
    }

    return compare_fnc(obj1, obj2) == 1;
};

static inline int is_greater(void *obj1, void *obj2, int (*compare_fnc)(void *, void *)) {
    if (obj1 == NULL || obj2 == NULL || compare_fnc == NULL) {
        fprintf(stderr, "Invalid parameters in is_greater.\n");
        return 0; 
    }

    return compare_fnc(obj1, obj2) > 0 ? 1 : 0;
};


static inline void swap(void *obj1, void *obj2, size_t size) {
    if (obj1 == NULL || obj2 == NULL || size == 0) {
        fprintf(stderr, "Invalid parameters in swap.\n");
        return;
    }

    char *temp = malloc(size);
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation error in swap.\n");
        exit(EXIT_FAILURE);
    }

    memcpy(temp, obj1, size);
    memcpy(obj1, obj2, size);
    memcpy(obj2, temp, size);

    free(temp);
};


static inline void sort(void *array, int nb_of_elems_in_array, size_t elem_size, int (*compare_fnc)(void *, void *)) {
    if (array == NULL || nb_of_elems_in_array <= 1) {
        fprintf(stderr, "Invalid parameters in sort.\n");
        return;
    }

    char *base = (char *)array;
    for (int i = 0; i < nb_of_elems_in_array - 1; i++) {
        for (int j = 0; j < nb_of_elems_in_array - i - 1; j++) {
            void *elem1 = base + j * elem_size;
            void *elem2 = base + (j + 1) * elem_size;

            if (is_greater(elem1, elem2, compare_fnc)) {
                swap(elem1, elem2, elem_size);
            }
        }
    }
};


static inline int is_in_array(void *obj_to_find, void *array, int nb_of_elems_in_array, size_t elem_size, int (*compare_fnc)(void *, void *)) {
    if (obj_to_find == NULL || array == NULL || nb_of_elems_in_array <= 0 || compare_fnc == NULL) {
        fprintf(stderr, "Invalid parameters in is_in_array.\n");
        return 0;
    }

    char *base = (char *)array;
    for (int i = 0; i < nb_of_elems_in_array; i++) {
        void *elem = base + i * elem_size;
        if (compare_fnc(obj_to_find, elem) == 0) {
            return 1;
        }
    }

    return 0;
};
