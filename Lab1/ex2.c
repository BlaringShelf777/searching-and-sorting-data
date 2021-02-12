#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TST1 100        // Array' size
#define TST2 1000       //  ||
#define TST3 10000      //  ||
#define TST4 100000     //  ||
#define CIURASIZE 9     // Ciura' sequence size
#define MAX 5           // Random numbers
#define MIN 1           //  ||

// Deque
typedef struct node_t{
    struct node_t *prev;
    struct node_t *next;
    int num;
}node_t;

// Descriptor 
typedef struct desc_t{
    node_t *start;
    node_t *end;
}desc_t;

// Data structures
void initializeNode(node_t **node);
void initializeDesc(desc_t **descriptor);
void insertNode(node_t **root, desc_t **descriptor, int num);
void destroyDeque(node_t **root);
void destroyDesc(desc_t **descriptor);
// Array
void printArray(int array[], int size);
int *makeArray(int size);
// Sorting
void shellSort(int array[], int size, desc_t *descriptor);


int main(){
    // Data structures
    node_t *root = NULL;
    desc_t *descriptor = NULL;
    // Array
    int *array1 = NULL, *array2 = NULL, *array3 = NULL, *array4 = NULL;
    // Sequence
    int ciuraSeq[] = {1, 4, 10, 23, 57, 132, 301, 701, 1750}, i = 0;

    // Creates the Ciura' sequence
    initializeDesc(&descriptor);
    while(!descriptor->start || descriptor->end->num <= TST4 / 2 + 1){
        if (i < CIURASIZE)
            insertNode(&root, &descriptor, ciuraSeq[i++]);
        else
            insertNode(&root, &descriptor, (int) floor(2.55*descriptor->end->num));
    }
    // Creates the arrays
    array1 = makeArray(TST1);
    array2 = makeArray(TST2);
    array3 = makeArray(TST3);
    array4 = makeArray(TST4);
    // Calls the Shellsort with Ciuras' sequence for the arrays
    shellSort(array1, TST1, descriptor);
    shellSort(array2, TST2, descriptor);
    shellSort(array3, TST3, descriptor);
    shellSort(array4, TST4, descriptor);
    // deallocates the data structs used to store the Ciura' sequence
    destroyDeque(&root);
    destroyDesc(&descriptor);
    // deallocates the arrays
    free(array1); free(array2); free(array3); free(array4);

    return 0;
}

// Shellsort Algorithm using Ciura' sequence
void shellSort(int array[], int size, desc_t *descriptor){
    node_t *segment = descriptor->start;
    clock_t start_t, end_t;

    start_t = clock();
    // Find the best starting segment
    if (segment->prev->num > size / 2 + 1)
        do{
            segment = segment->prev;
        }while(segment->num > size / 2 + 1);
    // Adjusts the segment
    segment = segment->next;
    do{
        // updates the segment
        segment = segment->prev;
        for (int i = 0; i < size; i++)
            for (int j = segment->num + i; j < size; j += segment->num){
                int k = j - segment->num, aux = array[j];

                while (k >= 0 && aux < array[k]){
                    array[k + segment->num] = array[k];
                    k -= segment->num;
                }
                array[k + segment->num] = aux;
            }
    }while(segment != descriptor->start);
    end_t = clock();
    printf("\n> Array of size [%d] sorted.\n> Time taken: %lfs\n\n", size, (double)(end_t - start_t) / CLOCKS_PER_SEC);
} 

// initializes a node
void initializeNode(node_t **node){
    *node = (node_t *) malloc(sizeof(node_t));
    (*node)->prev = (*node)->next = NULL;
}

// Initializes a descriptor
void initializeDesc(desc_t **descriptor){
    *descriptor = (desc_t *) malloc(sizeof(desc_t));
    (*descriptor)->start = (*descriptor)->end = NULL;
}

// Insert a node at the end of a Deque
void insertNode(node_t **root, desc_t **descriptor, int num){
    if (!(*root)){
        initializeNode(root);
        (*root)->num = num;
        (*root)->prev = (*root)->next = NULL;
        (*descriptor)->end = (*descriptor)->start = *root;

        return;
    }
    node_t *aux = NULL;

    initializeNode(&aux);
    aux->num = num;
    aux->prev = (*descriptor)->end;
    aux->next = (*descriptor)->start;
    aux->prev->next = aux;
    aux->next->prev = aux;
    (*descriptor)->end = aux;
}

// Destroys a Deque
void destroyDeque(node_t **root){
    if (*root){
        while((*root)->next){
            *root = (*root)->next;
            (*root)->prev->next = NULL;
            free((*root)->prev);
        }
        free(*root);
    }

    return NULL;
}

// Destroys a descriptor
void destroyDesc(desc_t **descriptor){
    if (!(*descriptor))
        return;
    free(*descriptor);
}

// Creates an array of integers of "int size" size
int *makeArray(int size){
    int *array = (int *) malloc(sizeof(int) * size);

    srand(time(NULL));
    for (int i = 0; i < size; i++)
        array[i] = rand() % (int) pow(10, MIN + rand() % (MAX - MIN + 1));
    
    return array;
}

// Prints an array of integers of "int size" size
void printArray(int array[], int size){
    for (int i = 0; i < size; i++)
        printf(" %d", array[i]);
    printf("\n");
}