#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>

#define LINE 51

// Stores the sequences
typedef struct data_t{
    int sort;
    char *sequence;
}data_t;

int inversions(char array[], int size);
void getInfo(int *len, int *sequence, char *line, FILE *file);
// HeapSort
void buildHeap(data_t array[], int size);
void heapify(data_t array[], int size, int index);
void heapSort(data_t array[], int size);

int main(){
    FILE *inFile = NULL, *outFile = NULL;
    char line[LINE];
    int dataSets = 0;

    // Opens the in file
    inFile = fopen("inFile.txt", "r");
    if (!inFile){
        printf("\n> ERROR! File not found.\n\n"); 
        
        return 2;
    }

    // Creates the out file
    outFile = fopen("outFile.txt", "w");
    if (!outFile){
        printf("\n> ERROR! Could not create file.\n\n");

        return 3;
    }
    
    // Gets the number of datasets
    fgets(line, LINE, inFile); dataSets = atoi(line);
    for (int i = 0; i < dataSets; i++){
        int len = 0, sequences = 0;
        data_t *data = (data_t *) malloc(sizeof(data_t) * sequences);

        // Gets the number of sequences in the present dataset and the lenght of it
        getInfo(&len, &sequences, line, inFile);
        printf("\n> Processing dataset %d...\n", i + 1);
        for (int j = 0; j < sequences; j++){
            char *aux = (char *) malloc(sizeof(char) * len + 1);
            // Gets a sequence 
            fgets(line, LINE, inFile); line[len] = '\0';
            // Creates a struct to store data
            data[j].sequence = (char *) malloc(sizeof(char) * len + 2);
            data[j].sequence = strdup(line); aux = strdup(line);
            data[j].sequence[len] = '\n'; data[j].sequence[len + 1] = '\0';
            data[j].sort = inversions(aux, len);
            free(aux);
        }
        heapSort(data, sequences);
        for (int j = 0; j < sequences; j++)
            printf("\n> SEQ: %s> %d.", data[j].sequence, data[j].sort);
        for (int j = 0; j < sequences; j++)
            fputs(data[j].sequence, outFile);
        if (i + 1 < dataSets)
            fputc('\n', outFile);
    }
    fclose(inFile); fclose(outFile);
    printf("\n> Your file <%s> is ready.\n", "outFile.txt");

    return 0;
}

void getInfo(int *len, int *sequence, char *line, FILE *file){
    char *tokens = "\n ";
    char *str;

    fgets(line, LINE, file); fgets(line, LINE, file);
    str = strtok(line, tokens); *len = atoi(str);
    str = strtok(NULL, tokens); *sequence = atoi(str);
}

int inversions(char array[], int size){
    int counter = 0;
    
    for (int i = 0, sizeAux = size; i < size; i++, sizeAux--)
        for(int j = 1; j < sizeAux; j++){
            if (array[j - 1] > array[j]){
                int aux = array[j - 1];
                
                array[j - 1] = array[j];
                array[j] = aux;
                counter++;
            }
        }
    
    return counter;
}  

void heapSort(data_t array[], int size){
    buildHeap(array, size);
    for (int i = 0, heapSize = size - 1; i < size; i++){
        data_t aux = array[0];

        array[0] = array[heapSize]; array[heapSize] = aux;
        heapify(array, heapSize--, 0);
    }
}

// Creates a Heap
void buildHeap(data_t array[], int size){
    for (int i = size - 1; i > 0; i--)
        heapify(array, size, i/2);
}

// Adjusts the Heap
void heapify(data_t array[], int size, int index){
    data_t aux = array[index];
    
    if ((index + 1) * 2 < size && array[(index + 1) * 2].sort > array[index].sort){
        if (array[(index + 1) * 2].sort > array[(index + 1) * 2 - 1].sort){
            array[index] = array[(index + 1) * 2];
            array[(index + 1) * 2] = aux;
            heapify(array, size, (index + 1) * 2);
        }else{
            array[index] = array[(index + 1) * 2 - 1];
            array[(index + 1) * 2 - 1] = aux;
            heapify(array, size, (index + 1) * 2 - 1);
        }
    }else if((index + 1) * 2 - 1 < size && array[(index + 1) * 2 - 1].sort > array[index].sort){
        array[index] = array[(index + 1) * 2 - 1];
        array[(index + 1) * 2 - 1] = aux;
        heapify(array, size, (index + 1) * 2 - 1);
    }
}

