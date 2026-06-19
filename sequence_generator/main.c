#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Ingrese el exponente e (10^e))\n./sequence_generator <exponente> > out.txt (si queres que quede en un txt)\n");
        return 1;
    }

    srand(time(NULL));

    char bases[] = {'A', 'C', 'G', 'T'};
    int exp = atoi(argv[1]);
    unsigned int size = pow(10, exp);
    char* result = malloc(sizeof(char) * (size + 1)); // +1 por el \0
    for(unsigned int i = 0; i < size; i++) {
        result[i] = bases[rand() % 4];
    }
    result[size] = '\0';
    for(unsigned int i = 0; i < size; i++) {
        printf("%c", result[i]);
    }
    free(result);
    return 0;
}