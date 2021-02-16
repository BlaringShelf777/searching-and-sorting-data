#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define LINE 51

typedef struct data_t{
    int sort;
    char *sequence;
}data_t;

int shellSort(char array[], int size);
void getInfo(int *len, int *sequence, char *line, FILE *file);

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
        printf("\n> DATASET %d:\n", i + 1);
        for (int j = 0; j < sequences; j++){
            char *aux = (char *) malloc(sizeof(char) * len + 1);
            // Gets a sequence 
            fgets(line, LINE, inFile); line[len] = '\0';
           // data[j].sequence = (char *) malloc(sizeof(char) * len + 1);
            data[j].sequence = strdup(line); aux = strdup(line);
            data[j].sort = shellSort(aux, len); 
            free(aux);
        }
        for (int j = 0; j < sequences; j++)
            printf("\n> SEQ_CPY: %s.\n> SORT: %d.\n",data[j].sequence, data[j].sort);
        printf("\n");
    }
    fclose(inFile);

    return 0;
}

void getInfo(int *len, int *sequence, char *line, FILE *file){
    char *tokens = "\n ";
    char *str;

    fgets(line, LINE, file); fgets(line, LINE, file);
    str = strtok(line, tokens); *len = atoi(str);
    str = strtok(NULL, tokens); *sequence = atoi(str);
}

int shellSort(char array[], int size){
    int segment = 0, pot = 1, counter = 0;

    while((int) floor(size / pow(2, pot))){
        segment = (int) floor(size / pow(2, pot++));
        for (int i = 0; i < size; i++)
            for (int j = segment + i; j < size; j += segment){
                int k = j - segment, aux = array[j];

                while (k >= 0 && aux < array[k]){
                    array[k + segment] = array[k];
                    k -= segment;
                    counter++;
                }
                array[k + segment] = aux;
            }
    }

    return counter;
}  



