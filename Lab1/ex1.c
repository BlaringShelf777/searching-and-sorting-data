#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void printArray(int array[], int size);
void shellSort(int array[], int size);

int main(){
    // Test array
    int tstArray[] = {54, 26, 93, 17, 77, 31, 44, 55, 20};
    // Exercice one array
    int array1[] = {733, 77, 611, 51, 496, 990, 61, 175, 127, 794, 794, 76, 197, 141, 863};
    // Exercisee two array
    int array2[] = {872, 424, 729, 573, 877, 696, 321, 758, 949, 217, 767, 238, 562, 175, 999, 12, 380, 406, 225, 995};

    //-- TEST
    printf("\n-------INPUT TEST ARRAY-------\n");
    printArray(tstArray, 9);
    printf("\n------------SORTING------------\n");
    shellSort(tstArray, 9);
    printf("\n");
    //-- EX1
    printf("\n---------INPUT ARRAY 1-----------\n");
    printArray(array1, 15);
    printf("\n------------SORTING------------\n");
    shellSort(array1, 15);
    printf("\n");
    //-- EX2
    printf("\n---------INPUT ARRAY 2-----------\n");
    printArray(array2, 20);
    printf("\n------------SORTING------------\n");
    shellSort(array2, 20);
    printf("\n");

    return 0;
}

// Prints an array of integers of 'int size' length
void printArray(int array[], int size){
    for (int i = 0; i < size; i++)
        printf(" %d", array[i]);
    printf("\n");
}

// Shellsort implementation
void shellSort(int array[], int size){
    int segment = 0, pot = 1;
    clock_t start_t, end_t;

    start_t = clock();
    while((int) floor(size / pow(2, pot))){
        segment = (int) floor(size / pow(2, pot++));
        for (int i = 0; i < size; i++)
            for (int j = segment + i; j < size; j += segment){
                int k = j - segment, aux = array[j];

                while (k >= 0 && aux < array[k]){
                    array[k + segment] = array[k];
                    k -= segment;
                }
                array[k + segment] = aux;
            }
        printf("After increments of size %d the list is: ", segment);
        printArray(array, size);
    }
    end_t = clock();
    printf("\n> Array of size [%d] sorted.\n> Time taken: %lfs\n\n", size, (double)(end_t - start_t) / CLOCKS_PER_SEC);
}  