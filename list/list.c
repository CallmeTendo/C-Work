// list/list.c
//
// Singly Linked List Implementation
// Author: Nigel <Last Name>
// Provides basic linked list operations including insertion,
// removal, search, and string conversion.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define LIST_ERROR -1   // Returned for invalid operations

/* Allocate a new empty list */
list_t *list_alloc() {
    list_t *l = (list_t *) malloc(sizeof(list_t));
    l->head = NULL;
    return l;
}

/* Free all nodes and the list itself */
void list_free(list_t *l) {
    node_t *curr = l->head;
    while (curr != NULL) {
        node_t *next = curr->next;
        free(curr);
        curr = next;
    }
    free(l);
}

/* Print list contents */
void list_print(list_t *l) {
    node_t *curr = l->head;
    while (curr != NULL) {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
    printf("NULL\n");
}

/* Convert list to string (caller must free returned buffer) */
char *listToString(list_t *l) {
    char *buf = (char *) malloc(1024);   // reasonable buffer size
    buf[0] = '\0';

    node_t *curr = l->head;
    char temp[32];

    while (curr != NULL) {
        sprintf(temp, "%d->", curr->value);
        strcat(buf, temp);
        curr = curr->next;
    }

    strcat(buf, "NULL");
    return buf;
}

/* Return length of list */
int list_length(list_t *l) {
    int count = 0;
    node_t *curr = l->head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

/* Helper: allocate a new node */
node_t *getNode(elem value) {
    node_t *n = (node_t *) malloc(sizeof(node_t));
    n->value = value;
    n->next = NULL;
    return n;
}

/* Add element to back of list */
void list_add_to_back(list_t *l, elem value) {
    node_t *newNode = getNode(value);

    if (l->head == NULL) {
        l->head = newNode;
        return;
    }

    node_t *curr = l->head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode;
}

/* Add element to front of list */
void list_add_to_front(list_t *l, elem value) {
    node_t *newNode = getNode(value);
    newNode->next = l->head;
    l->head = newNode;
}

/* Add element at 1-based index */
void list_add_at_index(list_t *l, elem value, int index) {
    if (index <= 0) return;

    int len = list_length(l);

    if (index == 1) {
        list_add_to_front(l, value);
        return;
    }

    if (index == len + 1) {
        list_add_to_back(l, value);
        return;
    }

    if (index > len + 1) return;

    node_t *curr = l->head;
    for (int pos = 1; pos < index - 1; pos++) {
        curr = curr->next;
    }

    node_t *newNode = getNode(value);
    newNode->next = curr->next;
    curr->next = newNode;
}

/* Remove element from back */
elem list_remove_from_back(list_t *l) {
    if (l->head == NULL) return LIST_ERROR;

    node_t *curr = l->head;

    if (curr->next == NULL) {
        elem val = curr->value;
        free(curr);
        l->head = NULL;
        return val;
    }

    while (curr->next->next != NULL) {
        curr = curr->next;
    }

    elem val = curr->next->value;
    free(curr->next);
    curr->next = NULL;
    return val;
}

/* Remove element from front */
elem list_remove_from_front(list_t *l) {
    if (l->head == NULL) return LIST_ERROR;

    node_t *temp = l->head;
    elem val = temp->value;

    l->head = temp->next;
    free(temp);

    return val;
}

/* Remove element at 1-based index */
elem list_remove_at_index(list_t *l, int index) {
    if (index <= 0 || l->head == NULL) return LIST_ERROR;

    if (index == 1) {
        return list_remove_from_front(l);
    }

    node_t *curr = l->head;
    for (int pos = 1; pos < index - 1; pos++) {
        if (curr->next == NULL) return LIST_ERROR;
        curr = curr->next;
    }

    if (curr->next == NULL) return LIST_ERROR;

    node_t *temp = curr->next;
    elem val = temp->value;

    curr->next = temp->next;
    free(temp);

    return val;
}

/* Check if value exists in list */
bool list_is_in(list_t *l, elem value) {
    node_t *curr = l->head;
    while (curr != NULL) {
        if (curr->value == value) return true;
        curr = curr->next;
    }
    return false;
}

/* Get element at 1-based index */
elem list_get_elem_at(list_t *l, int index) {
    if (index <= 0) return LIST_ERROR;

    node_t *curr = l->head;
    int pos = 1;

    while (curr != NULL) {
        if (pos == index) return curr->value;
        curr = curr->next;
        pos++;
    }

    return LIST_ERROR;
}

/* Get index of element (1-based) */
int list_get_index_of(list_t *l, elem value) {
    node_t *curr = l->head;
    int index = 1;

    while (curr != NULL) {
        if (curr->value == value) return index;
        curr = curr->next;
        index++;
    }

    return LIST_ERROR;
}
