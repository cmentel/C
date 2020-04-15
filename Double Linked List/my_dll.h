#ifndef MYDLL_H
#define MYDLL_H

#include <stdio.h>
#include <stdlib.h>

// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node {
    int data;
    struct node *next;
    struct node *previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
    int count;        // count keeps track of how many items are in the DLL.
    node_t *head;        // head points to the first node in our DLL.
    node_t *tail;          //tail points to the last node in our DLL.
} dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
dll_t *create_dll() {
    dll_t *myDLL = malloc(sizeof(dll_t));
    return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t *l) {
    if (l->count == 0) {
        return 1;
    } else {
        return 0;
    }
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns a -1 if the operation fails ( and if the DLL is NULL), otherwise returns 1 on success.
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t *l, int item) {

    if (l == NULL) {
        return -1;
    } else {
        node_t *pushy = malloc(sizeof(node_t));
        pushy->data = item;

        if (dll_empty(l) == 1) {
            l->head = pushy;
            l->tail = pushy;
            l->count++;
            return 1;
        } else if (dll_empty(l) == 0) {
            l->head->previous = pushy;
            pushy->next = l->head;
            l->head = pushy;
            l->count++;
            return 1;
        } else {
            return -1;
        }
    }
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns a -1 if the operation fails (and if the DLL is NULL), otherwise returns 1 on success.
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t *l, int item) {
    if (l == NULL) {
        return -1;
    } else {
        node_t *pushy = malloc(sizeof(node_t));
        pushy->data = item;
        if (dll_empty(l) == 1) {
            l->head = pushy;
            l->tail = pushy;
            l->count++;
            return 1;
        } else if (dll_empty(l) == 0) {
            l->tail->next = pushy;
            pushy->previous = l->tail;
            l->tail = pushy;
            l->count++;
            return 1;
        } else {
            return -1;
        }
    }
}

// Returns the front / head item in the DLL and also removes it from the list.
// Returns a -1 if the operation fails (and if the DLL is NULL).
// Assume no negative numbers in the list.
int dll_pop_front(dll_t *t) {
    if (t == NULL || dll_empty(t) == 1) {
        return -1;
    } else if (dll_empty(t) == 0) {
        node_t *keeper;
        keeper = t->head;
        int store = keeper->data;
        t->head = t->head->next;
        if (t->count != 1) {
            t->head->previous = NULL;
        } else {
            t->tail = NULL;
        }
        t->count--;
        free(t->head);
        return store;
    } else {
        return -1;
    }
}

// Returns the last item in the DLL, and also removes it from the list.
// Returns a -1 if the operation fails (and if the DLL is NULL).
// Assume no negative numbers in the list.
int dll_pop_back(dll_t *t) {
    if (t == NULL || dll_empty(t) == 1) {
        return -1;
    } else if (dll_empty(t) == 0) {
        node_t *keeper;
        keeper = t->tail;
        int store = keeper->data;
        t->tail = t->tail->previous;
        if (t->count != 1) {
            t->tail->next = NULL;
        } else {
            t->head = NULL;;
        }
        t->count--;
        free(t->tail);
        return store;
    } else {
        return -1;
    }
}

// Inserts a new node before the node at the specified position.
// Returns a -1 if the operation fails (and if the DLL is NULL), otherwise returns 1 on success.
// (i.e. the memory allocation for a new node failed or trying to insert at a negative position or at
//  a position past the size of the DLL ). Think test cases here.
int dll_insert(dll_t *l, int pos, int item) {
    int i;
    struct node *testytest, *temp;
    if (l == NULL || l->head == NULL) {
        return -1;
    } else if (pos < 0) {
        return -1;
    } else {
        temp = l->head;
        i = 1;
        while (i < pos - 1 && temp != NULL) {
            temp = temp->next;
            i++;
        }
        if (pos == 0) {
            dll_push_front(l, item);
        } else if (temp == l->tail) {
            dll_push_back(l, item);
        } else if (temp != NULL) {
            testytest = (struct node *) malloc(sizeof(struct node));
            testytest->data = item;
            testytest->next = temp->next;
            testytest->previous = temp;
            if (temp->next != NULL) {
                temp->next->previous = testytest;
            }
            temp->next = testytest;
            l->count++;
            return 1;
        } else {
            return -1;
        }
    }
    return -1;
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Returns a -1 if the operation fails (and if the DLL is NULL).
// Assume no negative numbers are in the list.
// (i.e. trying to get at a negative position or at a position past the size of the DLL ).
// Think test cases here.
int dll_get(dll_t *l, int pos) {
    if (l == NULL) {
        return -1;
    } else if (dll_empty(l) == 1) {
        return -1;
    } else if (pos > l->count || pos < 0) {
        return -1;
    } else if (pos >= 0 || pos < l->count) {
        node_t *temp;
        temp = l->head;
        int i = 0;
        while (temp != NULL) {
            if (i == pos) {
                return temp->data;
            } else {
                temp = temp->next;
                i++;
            }
        }
        return -1;
    }
}


// Removes the item at position pos starting at 0 ( 0 being the first item )
// Returns a -1 if the operation fails (and if the DLL is NULL).
// (i.e. trying to remove at a negative position or at a position past the size of the DLL ).
// Think test cases here.
int dll_remove(dll_t *l, int pos) {
    if (l == NULL || l->count == 0 || dll_empty(l) == 1 || pos > l->count || pos < 0) {
        return -1;
    } else if (pos == 0) {
        dll_pop_front(l);
    } else if (l->count == pos) {
        dll_pop_back(l);
    } else {
        int i = 0;
        node_t *tobedeleted = l->head;
        while (tobedeleted->next != NULL && i < pos) {
            tobedeleted = tobedeleted->next;
            i++;
        }
        tobedeleted->previous->next = tobedeleted->next;
        if (tobedeleted->next != NULL) {
            tobedeleted->next->previous = tobedeleted->previous;
        } else {
            dll_pop_back(l);
        }
        l->count--;
    }
}

// DLL Size
// Queries the current size of a DLL
// A DLL that has not been previously created will crash the program.
// Returns -1 if the DLL is NULL.
unsigned int dll_size(dll_t *t) {
    if (t == NULL) {
        return -1;
    } else {
        node_t *temp;
        temp = t->head;
        int i = 0;
        while (temp != NULL) {
            temp = temp->next;
            i++;
        }
        return i;
    }
}

// Free DLL
// Removes a DLL and ALL of its elements from memory.
// This should be called before the program terminates.
void free_dll(dll_t *t) {
    if (t == NULL) {
        return;
    } else {
        while (t->head) {
            node_t *next = t->head->next;
            free(t->head);
            t->head = next;
        }
        free(t);
    }
}

// Print function
void printable(dll_t *tobeprinted) {
    if (tobeprinted == NULL) {
        return;
    } else {
        node_t *temp;
        temp = tobeprinted->head;
        int i = 0;
        while (temp != NULL) {
            printf("Node %d is at position %d\n", temp->data, i);
            temp = temp->next;
            i++;
        }
    }
}
#endif