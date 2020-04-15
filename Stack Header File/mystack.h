// =================== Support Code =================
// Stack
// - Implement each of the functions to create a working stack.
// - Do not change any of the function declarations
// - (i.e. stack_t* create_stack() should not have additional arguments)
// - You should not have any 'printf' statements in your stack functions.
// - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================
#ifndef MYSTACK_H
#define MYSTACK_H

// Stores the maximum 'depth' of our stack.
// Our implementation enforces a maximum depth of our stack.
// (i.e. capacity cannot exceed MAX_DEPTH for any stack)


# define MAX_DEPTH 32


// Create a node data structure to store data within
// our stack. In our case, we will stores 'integers'
typedef struct node {
    int data;
    struct node *next;
} node_t;

// Create a stack data structure
// Our stack holds a single pointer to a node, which
// is a linked list of nodes.
typedef struct stack {
    int count;        // count keeps track of how many items are in the stack.
    unsigned int capacity;    // Stores the maximum size of our stack
    node_t *head;        // head points to a node on the top of our stack.
} stack_t;

// Creates a stack
// Returns a pointer to a newly created stack.
// The stack should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The stacks fields should also be initialized to default values.
// Returns NULL if we couldn't allocate memory.
stack_t *create_stack(unsigned int capacity) {
    stack_t *myStack = NULL;
    if (capacity > 0) {
        stack_t *s = (stack_t *) malloc(sizeof(stack_t));
        s->capacity = capacity;
        s->head = NULL;
        s->count = 0;
        return s;
    }
    return myStack;
}

// Stack Empty
// Check if the stack is empty
// Returns 1 if true (The stack is completely empty)
// Returns 0 if false (the stack has at least one element)
// Returns -1 if the stack is NULL.
int stack_empty(stack_t *s) {
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
int stack_full(stack_t *s) {
    if (s == NULL) {
        return -1;
    } else if (s->capacity == s->count) {
        return 1;
    } else {
        return 0;
    }
}

// Push a new item
// i.e. push a new item into our data structure
// Returns a 0 if the operation fails
// Returns a 1 if the operation succeeds
// Returns -1 if the stack is NULL.
// (i.e. if the stack is full that is an error).
int stack_enqueue(stack_t *s, int item) {
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
int stack_dequeue(stack_t *s) {
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
        s->count = s-> count - 1;
        return tourney;
    }
}

// Stack Size
// Queries the current size of a stack
// Returns -1 if the stack is NULL.
unsigned int stack_size(stack_t *s) {
    if (s == NULL) {
        return -1;
    } else {
        return s->count;
    }
}

// Free stack
// Removes a stack and ALL of its elements from memory.
// This should be called before the program terminates.
void free_stack(stack_t *s) {
    if (s == NULL) {
    } else {
        node_t *tmp = s->head;
        while (tmp->next != NULL) {
            node_t *store = tmp->next;
            free(tmp);
            tmp = store;
        }
    }
    free(s);
}

#endif