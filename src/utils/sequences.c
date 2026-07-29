#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "utils/cli.h"
#include "utils/sequences.h"
#include "utils/reports.h"

#define min(a,b) (((a)<(b)) ? (a) : (b))

#define BUFFER_SIZE 8192

static char* path = "data"; 
static char* path_small = "data/small/"; 
static char* path_medium = "data/medium/"; 
static char* path_large = "data/large/"; 
// static char* path_test = "data/test/"; 
// static char* path_temp = "data/temp/"; 
static char* default_seq1 = "data/small/default_seq1";
static char* default_seq2 = "data/small/default_seq2";


// SequenceBuffer* sequence1_buffer = NULL;
// SequenceBuffer* sequence2_buffer = NULL;


char* decide_folder_based_on_size(int length) {
    if (length < 1000) 
        return path_small;
    if (length < 10000) 
        return path_medium;
    return path_large;
}

SequenceBuffer* load_Sequence(const char* filename, const uint32_t start){
    FILE *filePointer;
    filePointer = fopen(filename, "rb");

    logging(0, "Loading sequence from file: %s\n", filename);
    if(filePointer == NULL){
        logging(0, "Could not open file\n");
        return NULL;
    }

    fseek(filePointer, 0, SEEK_END);
    long length = ftell(filePointer);
    uint32_t read_length = min((uint32_t)length, MAX_BUFFER_SIZE);
    fseek(filePointer, start, SEEK_SET);

    CharArray* seq = malloc(sizeof(CharArray));
    seq->data = malloc(read_length);
    seq->length = read_length;
    uint32_t read = fread(seq->data, 1, read_length, filePointer);
    if(read != read_length){
        logging(0, "Error reading file: expected %ld bytes, read %d bytes\n", read_length, read);
        free(seq->data);
        free(seq);
        fclose(filePointer);
        return NULL;
    }
    // seq->data[read_length] = '\0';
    seq->length = read_length;
    fclose(filePointer);

    SequenceBuffer* buffer = malloc(sizeof(SequenceBuffer));
    buffer->data = seq;
    buffer->start = 0;
    buffer->total_length = length;

    return buffer;
}


uint32_t count_files(const char *path) {
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
    return (uint32_t)count;
}

char* save_sequence(const char* folder, CharArray* seq, const char* name) {
    char path[PATH_MAX];
    char* newName = NULL;
    if(name != NULL){
        snprintf(path, sizeof(path), "%s/%s", folder, name);
        newName = (char*)malloc(strlen(name) + 1);
        strcpy(newName, name);
    } else{
        uint32_t file_count = count_files(folder);
        snprintf(path, sizeof(path), "%s/%d", folder, file_count + 1);
        newName = (char*)malloc(4);
        snprintf(newName, 4, "%d", file_count + 1);
    }

    FILE *filePointer = fopen(path, "ab");
    if(filePointer == NULL){
        logging(0, "Could not open file for writing: %s\n", path);
        free(newName);
        return NULL;
    }


    int written = fwrite(seq->data, 1, seq->length, filePointer);
    fclose(filePointer);
    
    if(written != seq->length){
        free(newName);
        free(seq->data);
        free(seq);
        return NULL;
    }

    return newName;
}

// ojo: tienen largo 1 de mas
// TODO resolver el NULL al final. Va?
int generate_and_save_sequence(int exp) {
    srand(time(NULL));
    char bases[] = {'A', 'C', 'G', 'T'};
    uint32_t total_size = pow(10, exp);
    uint32_t size = min(total_size, MAX_BUFFER_SIZE);
    
    char* folder = decide_folder_based_on_size(total_size);
    uint32_t saved_size = 0;
    char* name = NULL;
    while(saved_size < total_size){
        uint32_t chunk_size = min(size, total_size - saved_size);
        char* chunk = malloc((chunk_size + 1));
        
        for(unsigned int i = 0; i < chunk_size; i++) {
            chunk[i] = bases[rand() % 4];
            // printf("%c", chunk[i]);
        }
        printf("\n");
        chunk[chunk_size] = '\0';
        
        CharArray* seq = malloc(sizeof(CharArray));
        seq->data = chunk;
        seq->length = chunk_size;

        name = save_sequence(folder, seq, name);
        printf("Saved bytes %d to %d of %d in %s%s\n", saved_size, saved_size + chunk_size, total_size, folder, name);
        free(chunk);
        free(seq);
        if(name == NULL){
            logging(0, "Error saving sequence\n");
            return -1;
        }
        saved_size += chunk_size;
    }
    return 0;
}


void list_files(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        logging(0, "Could not open directory: %s\n", path);
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
            logging_wo_header("%s\n", fullpath);
        }
    }
    closedir(dir);
}

int print_sequence(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        return 1;
    }
    logging(0, "Printing sequence from %s", filepath);

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
        - mode debe ser un valor válido (1-5)
        - params debe contener los argumentos necesarios para el modo seleccionado
    Estas condiciones si cumplen si previamente se llamo a cli.c::read_mode(args, argv), 
    que verifica que el modo sea válido y que la cantidad de argumentos sea correcta.
*/
SequenceBuffer** execute_mode(int mode, char** params){
    SequenceBuffer** seqs = NULL;
    int err = 0;

    switch(mode){

        case MODE_DEFAULT:
            seqs = malloc(2*sizeof(SequenceBuffer*));
            seqs[0] = load_Sequence(default_seq1, 0);
            seqs[1] = load_Sequence(default_seq2, 0);
            if (seqs[0] == NULL || seqs[1] == NULL) {
                free(seqs[0]);
                free(seqs[1]);
                free(seqs);
                return NULL;
            }
            break;
            
        case MODE_FROM_FILES:
            seqs = malloc(2*sizeof(SequenceBuffer*));
            seqs[0] = load_Sequence(params[0], 0);
            printf("Sequence1: %s\n", params[0]);
            seqs[1] = load_Sequence(params[1], 0);
            if (seqs[0] == NULL || seqs[1] == NULL) {
                free(seqs[0]);
                free(seqs[1]);
                free(seqs);
                err = 1;
            }
            break;
            
        case MODE_GENERATE_RANDOM:
            int exponent = atoi(params[0]);
            err = generate_and_save_sequence(exponent);
            break;
            
        case MODE_LIST_SEQUENCES:
            char* dir;
            if(params[0] != NULL){
                dir = params[0];
            } else{
                dir = path;
            }
            logging(0, "Listing files in directory: %s\n", dir);
            list_files(dir);
            break;
            
        case MODE_PRINT_SEQUENCE:
            char *print_path = params[0];
            err = print_sequence(print_path);
            if (err != 0) {
                logging(0, "Error printing sequence from %s\n", print_path);
            }
            break;
        default:
            err = 1;
    }
    if(err != 0){
        logging(0, "Error ejecutando modo: no se pudieron cargar las secuencias\n");
        free(seqs);
        return NULL;
    }
    return seqs;
}

bool buffer_contains(SequenceBuffer* buffer, uint32_t start, uint32_t length){
    if(buffer == NULL){
        return false;
    }
    if(start < buffer->start){
        return false;
    }
    if((start + length) > (buffer->start + buffer->data->length)){
        return false;
    }
    return true;
}

void free_SequenceBuffer(SequenceBuffer* buffer){
    if(buffer == NULL){
        return;
    }
    if(buffer->data != NULL){
        free(buffer->data->data);
        free(buffer->data);
    }
    free(buffer->path);
    free(buffer);
}