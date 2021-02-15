#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define LINE 51

int shellSort(char array[], int size);
void getInfo(int *len, int *sequence, char *line, FILE *file);

int main(){
    FILE *inFile = NULL;
    char line[LINE];
    int dataSets = 0;

    // Opens the file
    inFile = fopen("inFile.txt", "r");
    if (!inFile){
        printf("\n> ERROR! File not found."); 
        
        return 2;
    }
    // Gets the number of datasets
    fgets(line, LINE, inFile); dataSets = atoi(line);
    for (int i = 0; i < dataSets; i++){
        int len = 0, sequences = 0;

        // Gets the number of sequences in the present dataset and the lenght of it
        getInfo(&len, &sequences, line, inFile);
        for (int j = 0; j < sequences; j++){
            // Gets a sequence
            fgets(line, LINE, inFile); line[len] = '\0';
            printf("%s\n", line);
        }
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




