// =================== GRAPH =================
// - Implement each of the functions to create a working graph_t.
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <stdio.h>
#include <stdlib.h>


typedef struct DLL dll_t;

// Create a node data structure to store data within.
typedef struct node {
    int data;
    struct node *next;
    struct node *previous;
    dll_t *neighborsIN;
    dll_t *neighborsOUT;
    int visited;

} node_t;


// used in graph_nodes
typedef struct DLL {
    int count;        // count keeps track of how many items are in the DLL.
    node_t *head;        // head points to the first node in our DLL.
    node_t *tail; //tail points to the last node in our DLL.
} dll_t;


// Create a graph_t data structure
// Our graph_t keeps track of the number of graph_nodes, the number of edges and an array
// of all the graph_nodes in the graph_t, and the maximum number of graph_nodes we store in our graph_t.
typedef struct graph_t {
    int numNodes;
    int numEdges;
    dll_t *graph_nodes;
} graph_t;

typedef struct {
    int *array;
    size_t used;
    size_t size;
} Array;

// Creates a DLL : Returns a pointer to a newly created DLL.
dll_t *create_dll() {
    dll_t *myDLL = malloc(sizeof(dll_t));
    myDLL->head = NULL;
    myDLL->tail = NULL;
    myDLL->count = 0;
    return myDLL;
}

node_t *create_node() {
    node_t *mynode = malloc(sizeof(node_t));
    mynode->next = NULL;
    mynode->data = 0;
    mynode->neighborsIN = create_dll();
    mynode->neighborsOUT = create_dll();
    mynode->previous = NULL;
    mynode->visited = 0;
    return mynode;
}

// Creates a graph_t
// Returns a pointer to a newly created graph_t.
// The graph_t should be initialized with data on the heap.
// The graph_t fields should also be initialized to default values.
graph_t *create_graph() {
    graph_t *myGraph = malloc(sizeof(graph_t));
    myGraph->numNodes = 0;
    myGraph->numEdges = 0;
    myGraph->graph_nodes = create_dll();
    return myGraph;
}

void initArray(Array *a, size_t initialSize) {
    a->array = (int *) malloc(initialSize * sizeof(int));
    a->used = 0;
    a->size = initialSize;
}

void insertArray(Array *a, int element) {
    if (a->used == a->size) {
        a->size *= 2;
        a->array = (int *) realloc(a->array, a->size * sizeof(int));
    }
    a->array[a->used++] = element;
}

void freeArray(Array *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

// DLL Empty
// Check if the DLL is empty
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t *l) {
    if (l == NULL) {
        return 1;
    }
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
        node_t *pushy = create_node();
        pushy->data = item;
        if (dll_empty(l) == 1) {
            l->head = pushy;
            l->tail = pushy;
            l->count++;
            return 1;
        } else if (dll_empty(l) == 0) {
            node_t *itr = l->head;
            while (itr->next != NULL) {
                itr = itr->next;
            }
            itr->next = pushy;
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

// Graph Empty
// Check if the graph_t is empty
// Returns >= 0 if true (The graph_t is completely empty, i.e. numNodes == 0 )
// Returns -1 if false (the graph_t has at least one node)
int graph_empty(graph_t *g) {
    if (g == NULL || g->numNodes == 0) {
        return 0;
    }
    return -1;
}

//Returns >=0 if the node with value is in the graph_t, otherwise returns -1;
int contains_node(graph_t *g, int value) {
    if (g == NULL) {
        return -1;
    }
    if (g->graph_nodes->head == NULL || g->graph_nodes == NULL) {
        return -1;
    }
    node_t *itr = g->graph_nodes->head;
    while (itr != NULL) {
        if (itr->data == value) {
            return 1;
        }
        itr = itr->next;
    }
    return -1;

}

// Adds a new node with the corresponding item in the graph_t.
// Returns a -1 if the operation fails or has duplicate node. (otherwise returns >=0 on success)
// (i.e. the memory allocation for a new node failed).
int graph_add_node(graph_t *g, int item) {
    if (g == NULL) {
        return -1;
    }
    if (contains_node(g, item) == 1) {
        return -1;
    }
    if (g->graph_nodes->head == NULL) {
        dll_push_back(g->graph_nodes, item);
        g->numNodes++;
        return 2;
    }
    dll_push_back(g->graph_nodes, item);
    g->numNodes++;
    return 1;
}

// Removes the node from the graph_t and the corresponding edges connected
// to the node.
// Returns a -1 if the operation fails (otherwise returns >=0 on success).
int graph_remove_node(graph_t *g, int item) {
    if (g == NULL || g->numNodes == 0) {
        return -1;
    }
    if (contains_node(g, item) == -1) {
        return -1;
    }
    dll_remove(g->graph_nodes, item);
    g->numNodes--;
    return 1;
}

void graph_print_helper(graph_t *g) {
    printf("Graph print helper:\n");
    node_t *printer = g->graph_nodes->head;
    int i = 1;
    while (printer != NULL) {
        printf("Node: %d\n", printer->data);
        node_t *printerr = printer->neighborsIN->head;
        while (printerr != NULL) {
            printf("Node %d: IN Neighbors: %d\n", i, printerr->data);
            printerr = printerr->next;
        }
        node_t *printerrr = printer->neighborsOUT->head;
        while (printerrr != NULL) {
            printf("Node %d: OUT Neighbors: %d\n", i, printerrr->data);
            printerrr = printerrr->next;

        }
        printer = printer->next;
        i++;
    }

}

void edge_print_helper(graph_t *g) {
    node_t *printer = g->graph_nodes->head->neighborsOUT->head;
    while (printer != NULL) {
        printf("%d\n", printer->data);
        printer = printer->next;
    }
    node_t *printer2 = g->graph_nodes->head->neighborsIN->head;
    while (printer2 != NULL) {
        printf("%d\n", printer2->data);
        printer2 = printer2->next;
    }

}

//Returns >=0 if an edge from source to destination exists, -1 otherwise.
int contains_edge(graph_t *g, int source, int destination) {
    if (g == NULL) {
        return -1;
    }
    if (contains_node(g, source) == 1 && contains_node(g, destination) == 1) {
        node_t *itr = g->graph_nodes->head;
        while (itr->next != NULL) {
            if (itr->data == source) {
                node_t *itrr = itr->neighborsOUT->head;
                while (itrr != NULL) {
                    if (itrr->data == destination) {
                        return 1;
                    }
                    itrr = itrr->next;
                }
            }
            itr = itr->next;
        }
    }
    return -1;
}


//Adds an edge from source to destination.
//If source or destination is not found, or the edge already exists in the graph_t returns -1.
//Otherwise it returns >= 0
int graph_add_edge(graph_t *g, int source, int destination) {
    if (g == NULL) {
        return -1;
    }

    if (contains_edge(g, source, destination) == 1) {
        return -1;
    }

    if (contains_node(g, source) == 1 && contains_node(g, destination) == 1) {
        node_t *itr = g->graph_nodes->head;
        while (itr != NULL) {
            if (itr->data == source) {
                dll_push_back(itr->neighborsOUT, destination);
            }
            if (itr->data == destination) {
                dll_push_back(itr->neighborsIN, source);
            }
            itr = itr->next;
        }
        g->numEdges++;
        return 1;
    }
    return -1;
}

//Removes an edge from source to destination.
//If source or destination is not found in the graph_t returns -1.
//If no such edge exists also returns -1.
//Otherwise it returns >=0
int graph_remove_edge(graph_t *g, int source, int destination) {
    if (g == NULL) {
        return -1;
    }
    if (contains_node(g, source) == 1 && contains_node(g, destination) == 1) {
        node_t *itr = g->graph_nodes->head;
        while (itr->next != NULL) {
            if (itr->data == source) {
                dll_remove(itr->neighborsIN, source);
            }
            if (itr->data == destination) {
                dll_remove(itr->neighborsOUT, destination);
            }
            itr = itr->next;
        }
        g->numEdges--;
        return 1;
    }
    return -1;
}

// Returns the number of neighbors for value.
int numNeighbors(graph_t *g, int value) {
    if (g == NULL || contains_node(g, value) == -1) {
        return 0;
    }
    int i = 0;
    node_t *itr = g->graph_nodes->head;
    while (itr != NULL) {
        if (itr->data == value) {
            node_t *itrr = itr->neighborsIN->head;
            while (itrr != NULL) {
                i++;
                itrr = itrr->next;
            }
            node_t *itrrr = itr->neighborsOUT->head;
            while (itrrr != NULL) {
                i++;
                itrrr = itrrr->next;
            }
        }
        itr = itr->next;
    }
    return i;
}

node_t *findNode(graph_t *g, int data) {
    node_t *itr = g->graph_nodes->head;
    while (itr != NULL) {
        if (itr->data == data) {
            return itr;
        }
        itr = itr->next;
    }
    return NULL;
}

//Returns an int array of all the neighbors of the node with data=value.
int *getNeighbors(graph_t *g, int value) {
    int *a = malloc(sizeof(int) * numNeighbors(g, value));
    if (g == NULL || contains_node(g, value) == -1) {
        return a;
    }
    node_t *node = findNode(g, value);
    node_t *itr = node->neighborsOUT->head;

    int counter = 0;

    while (itr != NULL) {
        int nodeData = itr->data;
        a[counter] = nodeData;
        counter++;
        itr = itr->next;
    }
    return a;
}


struct queue {
    int back;       // TAIL The next free position in the queue
    // (i.e. the end or tail of the line)
    int front;       // HEAD Current 'head' of the queue
    // (i.e. the front or head of the line)
    int size;       // How many total elements we currently have enqueued.
    int capacity;  // Maximum number of items the queue can hold
    int *data;       // The 'integer' data our queue holds / the array
};
typedef struct queue queue_t;

queue_t *create_queue(int capacity) {
    queue_t *myQueue = NULL;
    if (capacity > 0) {
        queue_t *q = (queue_t *) malloc(sizeof(queue_t));
        q->data = (int *) malloc((sizeof(int)) * capacity);
        q->capacity = capacity;
        q->front = 0;
        q->back = 0;
        q->size = 0;
        return q;
    }
    return myQueue;
}

int queue_empty(queue_t *q) {
    if (q == NULL) {
        return -1;
    } else if (q->size > 0) {
        return 0;
    } else {
        return 1;
    }
}

int queue_full(queue_t *q) {
    if (q == NULL) {
        return -1;
    } else if (q->size == q->capacity) {
        return 1;
    } else {
        return 0;
    }
}

int queue_enqueue(queue_t *q, int item) {
    if (q == NULL) {
        return -1;
    } else if (queue_full(q) == 1) {
        return 0;
    } else {
        q->data[q->back] = item;
        q->size = q->size + 1;
        q->back = (q->back + 1) % (q->capacity + 1);
        return 1;
    }
}

int queue_dequeue(queue_t *q) {
    if (q == NULL) {
        return -1;
    } else if (q->size == 0) {
        return 0;
    } else {
        int returnItem = q->data[q->front];
        q->size = q->size - 1;
        q->front = q->data[(q->front) + 1] % (q->capacity + 1);
        return returnItem;
    }
}

typedef struct stack {
    int count;        // count keeps track of how many items are in the stack.
    unsigned int capacity;    // Stores the maximum size of our stack
    node_t *head;        // head points to a node on the top of our stack.
} stack_k;

// Creates a stack
// Returns a pointer to a newly created stack.
// The stack should be initialized with data on the heap.
stack_k *create_stack(unsigned int capacity) {
    stack_k *myStack = NULL;
    if (capacity > 0) {
        stack_k *s = (stack_k *) malloc(sizeof(stack_k));
        if (s == NULL) {
            return NULL;
        }
        s->capacity = capacity;
        s->head = NULL;
        s->count = 0;
        return s;
    }
    return myStack;
}

int stack_empty(stack_k *s) {
    if (s == NULL) {
        return -1;
    } else if (s->count > 0) {
        return 0;
    } else {
        return 1;
    }
}

// Stack Full
// Check if the stack is full
// Returns 1 if true (The Stack is completely full, i.e. equal to capacity)
// Returns 0 if false (the Stack has more space available to add items)
// Returns -1 if the stack is NULL.
int stack_full(stack_k *s) {
    if (s == NULL) {
        return -1;
    } else if (s->capacity == s->count) {
        return 1;
    } else {
        return 0;
    }
}

int stack_enqueue(stack_k *s, int item) {
    if (s == NULL) {
        return -1;
    } else if (stack_full(s) == 1) {
        return 0;
    } else {
        node_t *newNode;
        newNode = malloc(sizeof(node_t));
        if (newNode == NULL) {
            return -1;
        }
        newNode->data = item;
        newNode->next = NULL;

        if (stack_empty(s) == 1) {
            s->head = newNode;
        } else if (stack_empty(s) == 0) {
            node_t *tmp = s->head->next;
            while (tmp->next != NULL) {
                tmp = tmp->next;
            }
            tmp->next = newNode;
        }
        s->count = s->count + 1;
        return 1;
    }
}

// Dequeue an item
// Returns the item at the front of the stack and removes an item from the stack.
// Removing from an empty queue returns a 0. Assume all entries are going to be > 0.
// Returns -1 if the stack is NULL. Assumption there is not going to be negative numbers in the stack
int stack_dequeue(stack_k *s) {
    if (s == NULL) {
        return -1;
    } else if (stack_empty(s) == 1) {
        return 0;
    } else {
        node_t *item;
        item = s->head;
        while (item->next != NULL) {
            node_t *store = item->next;
            item = store;
        }
        int tourney = item->data;
        free(item);
        s->count = s->count - 1;
        return tourney;
    }
}

// Prints the the graph_t using BFS
// For NULL or empty graph_t it should print nothing.
void graph_print(graph_t *g) {
    if (g == NULL) {
        return;
    }

    queue_t *queue = create_queue(g->numNodes * 2);
    queue_enqueue(queue, g->graph_nodes->head->data);

    while (queue_empty(queue) == 0) {
        int nodeData = queue_dequeue(queue);
            node_t *elemNode = findNode(g, nodeData);
            if (elemNode->visited == 0) {
                elemNode->visited = 1;

                int *neighbors = getNeighbors(g, nodeData);
                int sizeNeighbors = numNeighbors(g, nodeData);
                int i = 0;
                while (i < sizeNeighbors) {
                    node_t *neighNode = findNode(g, neighbors[i]);
                    if (neighNode->visited == 0) {
                        queue_enqueue(queue, neighbors[i]);
                    }
                    i++;
                }
                printf("%d",neighbors[i]);
                free(neighbors);
            }
        }
}

// Graph Size
// Returns the number of graph_nodes in the graph_t
// Returns -1 on failure.
int graph_num_nodes(graph_t *g) {
    if (g == NULL) {
        return -1;
    }
    return g->numNodes;
}

// Graph Size
// Returns the number of edges in the graph_t,
// Returns -1 on failure.
int graph_num_edges(graph_t *g) {
    if (g == NULL) {
        return -1;
    }
    return g->numEdges;
}

// Free graph_t
// Removes a graph_t and ALL of its elements from memory.
// This should be called before the program terminates.
void free_graph(graph_t *g) {
    if (g == NULL) {
        return;
    }
    printf("Freeing Graph\n");
    while (g->graph_nodes->head) {
        node_t *next = g->graph_nodes->head->next;
        while (g->graph_nodes->head->neighborsIN->head) {
            node_t *nextt = g->graph_nodes->head->neighborsIN->head->next;
            free(g->graph_nodes->head->neighborsIN->head);
            g->graph_nodes->head->neighborsIN->head = nextt;
        }
        while (g->graph_nodes->head->neighborsOUT->head) {
            node_t *nexxtt = g->graph_nodes->head->neighborsOUT->head->next;
            free(g->graph_nodes->head->neighborsOUT->head);
            g->graph_nodes->head->neighborsOUT->head = nexxtt;
        }
        free(g->graph_nodes->head);
        g->graph_nodes->head = next;
    }
    free(g);

}


// Returns >0 if I can reach the destination from source, -1 otherwise (Using BFS)
int is_reachable(graph_t *g, int source, int dest) {
    if (g == NULL || contains_node(g, source) == -1 || contains_node(g, dest) == -1) {
        return -1;
    }
    if (contains_edge(g, source, dest) == 1) {
        return 0;
    }

    queue_t *queue = create_queue(g->numNodes * 2);
    queue_enqueue(queue, source);

    while (queue_empty(queue) == 0) {
        int nodeData = queue_dequeue(queue);
        if (nodeData == dest) {
            return 1;
        } else {
            node_t *elemNode = findNode(g, nodeData);
            if (elemNode->visited == 0) {
                elemNode->visited = 1;

                int *neighbors = getNeighbors(g, nodeData);
                int sizeNeighbors = numNeighbors(g, nodeData);
                int i = 0;
                while (i < sizeNeighbors) {
                    node_t *neighNode = findNode(g, neighbors[i]);
                    if (neighNode->visited == 0) {
                        queue_enqueue(queue, neighbors[i]);
                    }
                    i++;
                }
                free(neighbors);
            }
        }
    }
    return -1;
}

// Returns 0 if there is a cycle in the graph, -1 otherwise (using BFS or DFS)
int has_cycle(graph_t *g) {
    if (g == NULL) {
        return -1;
    }
    queue_t *queue = create_queue(g->numNodes * 5);
    node_t *itr = g->graph_nodes->head;
    while (itr != NULL) {
        if (itr->neighborsIN == NULL) {
            queue_enqueue(queue, itr->data);
        }
        itr = itr->next;
    }
    while (queue_empty(queue) == 0) {
        int nodeData = queue_dequeue(queue);
        node_t *elemNode = findNode(g, nodeData);
        if (elemNode->visited == 0) {
            elemNode->visited = 1;

            int *neighbors = getNeighbors(g, nodeData);
            int sizeNeighbors = numNeighbors(g, nodeData);
            int i = 0;
            while (i < sizeNeighbors) {
                node_t *neighNode = findNode(g, neighbors[i]);
                if (neighNode->visited == 0) {
                    queue_enqueue(queue, neighbors[i]);
                }
                i++;
            }
            free(neighbors);
        } else {
            return 1;
        }
    }
    return -1;

}

void print_graph(graph_t *g) {
    if (g == NULL) {
        return;
    }

    queue_t *queue = create_queue(g->numNodes * 2);
    node_t *itr = g->graph_nodes->head;
    while (itr != NULL) {
        if (itr->neighborsIN == NULL) {
            queue_enqueue(queue, itr->data);
        }
        itr = itr->next;
    }

    while (queue_empty(queue) == 0) {
        int nodeData = queue_dequeue(queue);
        node_t *elemNode = findNode(g, nodeData);
        if (elemNode->visited == 0) {
            elemNode->visited = 1;
            printf("%d\n", elemNode->data);
            int *neighbors = getNeighbors(g, nodeData);
            int sizeNeighbors = numNeighbors(g, nodeData);
            int i = 0;
            while (i < sizeNeighbors) {
                node_t *neighNode = findNode(g, neighbors[i]);
                if (neighNode->visited == 0) {
                    queue_enqueue(queue, neighbors[i]);
                }
                i++;
            }
            free(neighbors);
        }
    }
}

// Prints any path from source to destination if there exists one
// (Choose either BFS or DFS, typically DFS is much simpler)
void print_path(graph_t *g, int source, int dest) {
    if (g == NULL || is_reachable(g, source, dest) == -1) {
        return;
    }
    int j = 0;
    queue_t *queue = create_queue(g->numNodes * 2);
    node_t *itr = g->graph_nodes->head;
    while (itr != NULL) {
        if (itr->neighborsIN == NULL) {
            queue_enqueue(queue, itr->data);
        }
        itr = itr->next;
    }
    while (queue_empty(queue) == 0) {
        int nodeData = queue_dequeue(queue);
        node_t *elemNode = findNode(g, nodeData);
        if (elemNode->visited == 0) {
            elemNode->visited = 1;

            int *neighbors = getNeighbors(g, nodeData);
            int sizeNeighbors = numNeighbors(g, nodeData);
            int i = 0;
            while (i < sizeNeighbors) {
                node_t *neighNode = findNode(g, neighbors[i]);
                if (neighNode->visited == 0) {
                    queue_enqueue(queue, neighbors[i]);
                    j++;
                }
                i++;
            }
        } else {
            return;
        }
    }
    for (int k =0; k < j; k++){
        printf("%d ",queue_dequeue(queue));
    }
}

#endif