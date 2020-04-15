#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free
#include "my_dll.h"

int main() {
    dll_t *TestDLL1 = create_dll();

    // test to check if list is empty
    //printf("1 = Empty, 0 = Not Empty  RESULT: %d\n",dll_empty(TestDLL1));

    // test to check if push was successful
    dll_push_front(TestDLL1, 1);

    // test to check if list is empty
    //printf("1 = Empty, 0 = Not Empty  RESULT: %d\n",dll_empty(TestDLL1));

    dll_push_front(TestDLL1, 2);
    dll_push_front(TestDLL1, 3);
    dll_push_front(TestDLL1, 4);
    dll_push_front(TestDLL1, 5);
    dll_push_front(TestDLL1, 6);
    dll_push_front(TestDLL1, 7);
    dll_push_front(TestDLL1, 8);
    dll_push_front(TestDLL1, 9);
    dll_push_front(TestDLL1, 10);

//     test to insert new node
     dll_insert(TestDLL1,3,5);

//     test to pop front
     printf("%d\n",dll_pop_front(TestDLL1));

//     test to pop back
     printf("%d\n",dll_pop_back(TestDLL1));

    // test to get data
    printf("Data is %d\n", dll_get(TestDLL1, 6));

    // test to get count
    printf("Size: %d\n", dll_size(TestDLL1));

    // prints DLL
    printable(TestDLL1);

    // frees DLL
    free_dll(TestDLL1);

    // test to get data
    printf("Data is %d\n", dll_get(TestDLL1, 3));

    // test to remove a node
    printf("Remove code: %d\n",dll_remove(TestDLL1,3));

    // test to get data
    printf("Data is %d\n", dll_get(TestDLL1, 3));

    // test to get count
    printf("Size: %d\n", dll_size(TestDLL1));

    // prints DLL
    printable(TestDLL1);

    // test to get count
    printf("Size: %d\n", dll_size(TestDLL1));

    // frees DLL
    free_dll(TestDLL1);

    return 0;
}