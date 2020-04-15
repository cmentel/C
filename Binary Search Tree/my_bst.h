// =================== Support Code =================
// Binary Search Tree ( BST ).
// - Implement each of the functions to create a working BST.
// - Do not change any of the function declarations
//   - (i.e. bst_t* create_bst() should not have additional arguments)
// - You should not have any 'printf' statements in your BST functions.
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================
#ifndef MYBST_H
#define MYBST_H

#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Create a node data structure to store data within
// our BST. In our case, we will stores 'integers'

typedef struct node {
    int data;
    struct node *rightChild;
    struct node *leftChild;
} node_t;


// Create a BST data structure
// Our BST holds a pointer to the root node in our BST called root.
typedef struct BST {
    int count;        // count keeps track of how many items are in the BST.
    node_t *root;        // root points to the root node in our BST.
} bst_t;

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values.
bst_t *create_bst() {
    bst_t *myBST = malloc(sizeof(bst_t));
    if (myBST == NULL) {
        return 0;
    } else {
        myBST->count = 0;
        myBST->root = NULL;
        return myBST;
    }
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element enqueued)
int bst_empty(bst_t *t) {
    if (t == NULL || t->root == NULL || t->count == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Helper function to add / check nodes.
int addHelper(node_t *currentNode, node_t *newNode) {
    if (newNode == NULL) {
        return 0;
    }
    if (newNode->data < currentNode->data) {
        if (currentNode->leftChild == NULL) {
            currentNode->leftChild = newNode;
            return 0;

        } else { addHelper(currentNode->leftChild, newNode); }
    } else {
        if (currentNode->rightChild == NULL) {
            currentNode->rightChild = newNode;
            return 0;
        } else { addHelper(currentNode->rightChild, newNode); }
    }
}


// Adds a new node containing item in the correct place of the BST.
// If the data is less then the current node we go right, otherwise we go left.
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// It should run in O(log(n)) time.
int bst_add(bst_t *t, int item) {
    if (t == NULL) {
        return -1;
    }
    node_t *newNode = malloc(sizeof(node_t));
    newNode->data = item;
    if (t->root == NULL || bst_empty(t) == 1) {
        t->root = newNode;
        t->count++;
        return 0;
    } else {
        t->count++;
        return addHelper(t->root, newNode);
    }
}

// Node Print Helper
void descendingHelper(node_t *NodeToBePrinter, int order) {
    if (NodeToBePrinter == NULL) {
        return;
    } else {
        descendingHelper(NodeToBePrinter->rightChild, order);
        printf("%d\n", NodeToBePrinter->data);
        descendingHelper(NodeToBePrinter->leftChild, order);
    }
}

// Node Print Helper
void ascendingHelper(node_t *NodeToBePrinter, int order) {
    if (NodeToBePrinter == NULL) {
        return;
    } else {
        ascendingHelper(NodeToBePrinter->leftChild, order);
        printf("%d\n", NodeToBePrinter->data);
        ascendingHelper(NodeToBePrinter->rightChild, order);
    }
}

// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// For NULL tree it should print nothing.
// It should run in O(n) time.
void bst_print(bst_t *t, int order) {
    if (t == NULL) {
        return;
    } else {
        // Ascending order
        if (order == 0) {
            ascendingHelper(t->root, order);
            return;
        }
            // Descending order
        else {
            descendingHelper(t->root, order);
            return;
        }
    }
}

// Node Sum Helper
int sumHelper(node_t *root) {
    if (root == NULL) {
        return 0;
    } else {
        return (root->data + sumHelper(root->leftChild) + sumHelper(root->rightChild));
    }
}

// Returns the sum of all the nodes in the tree.
// exits the program for a NULL tree.
// It should run in O(n) time.
int sum(bst_t *t) {
    if (t->root == NULL) {
        return 0;

    } else {
        return sumHelper(t->root);
    }
}

// Node Find Helper
int findHelper(node_t *root, int value) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == value) {
        return 1;
    }
    if (root->data > value) {
        return findHelper(root->leftChild, value);
    }
    return findHelper(root->rightChild, value);
}

// Returns 1 if value is found in the tree, 0 otherwise.
// For NULL tree it exists the program.
// It should run in O(log(n)) time.
int find(bst_t *t, int value) {
    if (t == NULL || t->root == NULL) {
        return 0;
    } else {
        return (findHelper(t->root, value));
    }
}

// Node size Helper
int sizeHelper(node_t *root) {
    if (root == NULL) {
        return 0;
    } else {
        return (1 + sizeHelper(root->leftChild) + sizeHelper(root->rightChild));
    }
}

// BST Size
// Queries the current size of the BST
// A BST that has not been previously created will crash the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t *t) {
    if (t == NULL || t->root == 0) {
        return 0;
    } else {
        return sizeHelper(t->root);
    }
}

// Helper function to free BST
void freeHelper(node_t *root) {
    if (root == NULL) {
        return;
    }
    freeHelper(root->leftChild);
    freeHelper(root->rightChild);
    free(root);
}


// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the program terminates.
void free_bst(bst_t *t) {
    freeHelper(t->root);
    free(t);
}

#endif