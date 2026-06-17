#include <stdio.h>
#include <stdlib.h>

int load_sequence(const char* filename,char** seq, int* len){
    FILE *filePointer;
    filePointer = fopen(filename, "rb");

    if(filePointer == NULL){
        printf("Could not open file\n");
        return 1;
    }

    fseek(filePointer, 0, SEEK_END);
    long length = ftell(filePointer);
    fseek(filePointer, 0, SEEK_SET);

    
    *seq = malloc(length + 2);
    char* temp = *seq + 1;
    fread(temp, 1, length, filePointer);
    temp[length] = '\0';

    fclose(filePointer);
    *len = length;
    return 0;
}