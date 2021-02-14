#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define LEN 4
#define MAX 25

char *makeSequence(int size);
int shellSort(char array[], int size);

int main(){
    char *sequence = makeSequence(LEN);
    char *aux =  (char *) malloc(sizeof(char) * LEN + 1);
    int counter;

    strncpy(aux, sequence, LEN + 1);
    counter = shellSort(aux, LEN);
    printf(">%s.\n>%s.\n>%d\n\n", sequence, aux, counter);

    return 0;
}

char *makeSequence(int size){
    char *sequence = (char *) malloc(sizeof(char) * size + 1);

    srand(time(NULL));
    for (int i = 0; i < size; i++)
        sequence[i] = 'A' + rand() % (MAX + 1);
    sequence[size] = '\0';

    return sequence;
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