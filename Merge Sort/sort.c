#include <stdio.h> 

void merge(int arr[], int l, int m, int r) {
    // Create three counters
    int i = 0, j = 0, k = 0;

    // Create two new arrays for each half.
    int s1 = m - l + 1;
    int s2 = r - m;
    int leftArray[m + 1];
    int rightArray[s2];

    // Put elements from first half of original into new array.
    for (int i = 0; i < s1; i++) {
        leftArray[i] = arr[l + i];
    }

    // Put elements from second half of original into new array.
    for (int i = 0; i < s2; i++) {
        rightArray[i] = arr[m + i + 1];
    }


    i = j = 0;
    k = l;
    // while elements are not single
    while (i < s1 && j < s2) {
        if (leftArray[i] < rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
            k++;
        } else {
            arr[k] = rightArray[j];
            j++;
            k++;
        }
    }

    while (i < s1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < s2) {
        arr[k] = rightArray[j];
        k++;
        j++;
    }
}


// Merge helper function
void mergesort(int *array, int l, int r) {
    if (r > l) {
        int m = (l + r) / 2;
        mergesort(array, l, m);
        mergesort(array, m + 1, r);

        merge(array, l, m, r);
    }
}


// Provided below is a sort function. We have also
// provided a template for how to document functions
// to help organize your code.
// Name: sortIntegers
// Input(s):
//          (1) 'array' is a pointer to an integer address. 
//              This is the start of some 'contiguous block of memory' that we will sort.
//          (2) 'size' tells us how big the array of data is we are sorting.
// Output: No value is returned, but 'array' should be modified to store a sorted array of numbers.
void sortIntegers(int *array, unsigned int size) {
    mergesort(array, 0, size - 1);

}

// Input: A pointer to an array (i.e. the array itself points to the first index)
//        The size of the array (Because we do not know how big the array is automatically)
void printIntArray(int *array, unsigned int size) {
    unsigned int i; // Note: 'unsigned int' is a datatype for storing positive integers.
    for (i = 0; i < size; i = i + 1) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {

    // Some test data sets.
    int dataset1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int dataset2[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int dataset3[] = {0, 3, 2, 1, 4, 7, 6, 5, 8, 9, 10};
    int dataset4[] = {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int dataset5[] = {100, 201, 52, 3223, 24, 55, 623, 75, 8523, -9, 150};
    int dataset6[] = {-1, 1, 2, -3, 4, 5, -6, 7, 8, -9, 10};

    // Sort our integer array
    sortIntegers(dataset1, 11);
    sortIntegers(dataset2, 11);
    sortIntegers(dataset3, 11);
    sortIntegers(dataset4, 11);
    sortIntegers(dataset5, 11);
    sortIntegers(dataset6, 11);

    // Print out an array
    printIntArray(dataset1, 11);
    printIntArray(dataset2, 11);
    printIntArray(dataset3, 11);
    printIntArray(dataset4, 11);
    printIntArray(dataset5, 11);
    printIntArray(dataset6, 11);

    return 0;
}
