#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void assertEquals(char *expected, char *actual, char *msg) {
    if (strcmp(expected, actual) != 0) {
        printf("%s : FAILED\n", msg);
    } else {
        printf("%s : PASSED\n", msg);
    }
}

int main() {
    list_t *mylist = list_alloc();

    printf("=== Testing list_add_to_front ===\n");
    int values[] = {10,20,30,40,50,60,70,80,90,100};
    for (int i = 0; i < 10; i++) {
        list_add_to_front(mylist, values[i]);
    }

    char *s1 = listToString(mylist);
    assertEquals("100->90->80->70->60->50->40->30->20->10->NULL", s1, "list_add_to_front");
    free(s1);

    printf("=== Testing list_remove_at_index ===\n");
    list_remove_at_index(mylist, 3);   // remove 80
    list_remove_at_index(mylist, 20);  // out of bounds
    list_remove_at_index(mylist, 1);   // remove 100
    list_remove_at_index(mylist, 6);   // remove 40

    char *s2 = listToString(mylist);
    assertEquals("90->70->60->50->40->20->10->NULL", s2, "list_remove_at_index");
    free(s2);

    printf("=== Testing list_get_elem_at ===\n");
    printf("Elem at 3: %d\n", list_get_elem_at(mylist, 3));
    printf("Elem at 5: %d\n", list_get_elem_at(mylist, 5));
    printf("Elem at 0: %d\n", list_get_elem_at(mylist, 0));
    printf("Elem at -2: %d\n", list_get_elem_at(mylist, -2));
    printf("Elem at 12: %d\n", list_get_elem_at(mylist, 12));
    printf("Elem at 7: %d\n", list_get_elem_at(mylist, 7));

    printf("=== Testing list_get_index_of ===\n");
    printf("Index of 70: %d\n", list_get_index_of(mylist, 70));
    printf("Index of 20: %d\n", list_get_index_of(mylist, 20));
    printf("Index of 0: %d\n", list_get_index_of(mylist, 0));
    printf("Index of 10: %d\n", list_get_index_of(mylist, 10));
    printf("Index of 90: %d\n", list_get_index_of(mylist, 90));

    list_free(mylist);
    return 0;
}
