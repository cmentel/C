// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_bst.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main() {

    // creates BST
    bst_t *testBST = create_bst();

    // test to check if it's empty
    printf("Empty test: %d\n", bst_empty(testBST));

    // test to add elements to the tree
    printf("Add Test: %d\n", bst_add(testBST, 2));

    // test to check if it's empty
    printf("Empty test: %d\n", bst_empty(testBST));

    // test to add elements to the tree
    printf("Add Test: %d\n", bst_add(testBST, 4));
    // test to add elements to the tree
    printf("Add Test: %d\n", bst_add(testBST, 5));
    // test to add elements to the tree
    printf("Add Test: %d\n", bst_add(testBST, 9));
    // test to add elements to the tree
    printf("Add Test: %d\n", bst_add(testBST, 4));
    // test to add elements to the tree
    printf("Add Test: %d\n", bst_add(testBST, 54));
    // test to add elements to the tree
    printf("Add Test: %d\n", bst_add(testBST, 23));
    // test to add elements to the tree
    printf("Add Test: %d\n", bst_add(testBST, 13));


    // test to get sum
    printf("Here's the sum: %d\n", sum(testBST));

    // test to find if a number exists
    printf("Here's the find: %d\n", find(testBST, 5));
    printf("Here's the find: %d\n", find(testBST, 7));
    printf("Here's the find: %d\n", find(testBST, 53));

    // test to get the size
    printf("Here's the size: %d\n", bst_size(testBST));


    free_bst(testBST);
    return 0;
}