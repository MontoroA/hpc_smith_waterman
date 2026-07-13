#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "utils/io.h"
#include "utils/sequences.h"

#define BUFFER_SIZE 8192

static char* path = "data/"; 
static char* path_small = "data/small/"; 
static char* path_medium = "data/medium/"; 
static char* path_large = "data/large/"; 
static char* default_seq1 = "data/small/default_seq1";
static char* default_seq2 = "data/small/default_seq2";

char* decide_folder_based_on_size(int length) {
    if (length < 1000) 
        return path_small;
    if (length < 10000) 
        return path_medium;
    return path_large;
}

CharArray* load_sequence_in_folders(const char* filename){
    FILE *filePointer;
    filePointer = fopen(filename, "rb");

    printf("Loading sequence from file: %s\n", filename);
    if(filePointer == NULL){
        printf("Could not open file\n");
        return NULL;
    }

    fseek(filePointer, 0, SEEK_END);
    long length = ftell(filePointer);
    fseek(filePointer, 0, SEEK_SET);

    CharArray* seq = malloc(sizeof(CharArray));
    seq->data = malloc(length + 2);
    char* temp = seq->data + 1;
    int read = fread(temp, 1, length, filePointer);
    if(read != length){
        printf("Error reading file: expected %ld bytes, read %d bytes\n", length, read);
        free(seq->data);
        free(seq);
        fclose(filePointer);
        return NULL;
    }
    temp[length] = '\0';
    seq->length = length;

    fclose(filePointer);
    return seq;
}


CharArray* generate_sequence(int exp) {
    srand(time(NULL));
    char bases[] = {'A', 'C', 'G', 'T'};
    unsigned int size = pow(10, exp);
    char* result = malloc(sizeof(char) * (size + 1));
    for(unsigned int i = 0; i < size; i++) {
        result[i] = bases[rand() % 4];
    }
    result[size] = '\0';
    for(unsigned int i = 0; i < size; i++) {
        printf("%c", result[i]);
    }
    printf("\n");
    CharArray* seq = malloc(sizeof(CharArray));
    seq->data = result;
    seq->length = size;
    return seq;
}

int count_files(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror(path);
        return -1;
    }
    int count = 0;
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[4096];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == 0 && S_ISREG(st.st_mode))
            count++;
    }

    closedir(dir);
    return count;
}

int save_sequence(const char* folder, CharArray* seq) {
    char filename[PATH_MAX];
    int file_count = count_files(folder);

    snprintf(filename, sizeof(filename), "%s/%d", folder, file_count + 1);
    FILE *filePointer = fopen(filename, "wb");
    if(filePointer == NULL){
        printf("Could not open file for writing: %s\n", filename);
        return -1;
    }
    int written = fwrite(seq->data, 1, seq->length, filePointer);
    fclose(filePointer);
    if(written != seq->length){
        return -1;
    }
    return 0;
}


void list_files(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("Could not open directory: %s\n", path);
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (
            strcmp(entry->d_name, ".") == 0 || 
            strcmp(entry->d_name, "..") == 0 ||
            strcmp(entry->d_name, "README") == 0
        ) continue;

        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        struct stat st;
        if (stat(fullpath, &st) == -1)
            continue;

        unsigned short mode = st.st_mode;
        if (S_ISDIR(mode)) {
            list_files(fullpath);
        } else if (S_ISREG(mode)) {
            printf("%s\n", fullpath);
        }
    }
    closedir(dir);
}

int print_sequence(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        return 1;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    if (ferror(file)) {
        fclose(file);
        return 1;
    }
    fclose(file);
    printf("\n");
    return 0;
}

/*
    Precondiciones:
        - mode debe ser un valor válido (1-7)
        - params debe contener los argumentos necesarios para el modo seleccionado
    Estas condiciones si cumplen si previamente se llamo a io.c::read_mode(args, argv), 
    que verifica que el modo sea válido y que la cantidad de argumentos sea correcta.
*/
CharArray** execute_mode(int mode, char** params){
    CharArray** seqs = NULL;
    int err;
    switch(mode){
        case MODE_DEFAULT:
            seqs = malloc(2*sizeof(CharArray*));
            seqs[0] = load_sequence_in_folders(default_seq1);
            seqs[1] = load_sequence_in_folders(default_seq2);
            break;
            
        case MODE_FROM_FILES:
            seqs = malloc(2*sizeof(CharArray*));
            seqs[0] = load_sequence_in_folders(params[0]);
            seqs[1] = load_sequence_in_folders(params[1]);
            break;
            
        case MODE_FROM_STRINGS:
            seqs = malloc(2*sizeof(CharArray*));
            CharArray* seq1 = malloc(sizeof(CharArray));
            CharArray* seq2 = malloc(sizeof(CharArray));
            seq1->length = strlen(params[0]);
            seq2->length = strlen(params[1]);
            seq1->data = malloc(seq1->length + 1);
            seq2->data = malloc(seq2->length + 1);
            strcpy(seq1->data, params[0]);
            strcpy(seq2->data, params[1]);
            seq1->data[seq1->length] = '\0';
            seq2->data[seq2->length] = '\0';
            seqs[0] = seq1;
            seqs[1] = seq2;
            break;
            
        case MODE_GENERATE_RANDOM:
            int exponent = atoi(params[0]);
            CharArray* generated_seq = generate_sequence(exponent);
            char* folder =  decide_folder_based_on_size(generated_seq->length);
            err = save_sequence(folder, generated_seq);
            if(err != 0){
                printf("Error saving generated sequence\n");
            }
            break;
            
        case MODE_LIST_SEQUENCES:
            char* dir;
            if(params[0] != NULL){
                dir = params[0];
            } else{
                dir = path;
            }
            list_files(dir);
            break;
            
        case MODE_PRINT_SEQUENCE:
            char *print_path = params[0];
            err = print_sequence(print_path);
            if (err != 0) {
                printf("Error printing sequence from %s\n", print_path);
            }
            break;

        case MODE_DELETE_SEQUENCE:
            // char *delete_path = params[0];
            printf("Delete sequence mode is not implemented yet.\n");
            break;
    }
    return seqs;
}