#include <stdio.h>
#include <stdlib.h>

#include "utils/io.h"

int read_mode(int argc, char** argv){
    if (argc < 2) {
        fprintf(stderr, "Modo no especificado.\n");
        return MODE_INVALID;
    }
    int cant = argc - 2;
    //TODO: verificar tipados
    // char** params = argv + 2;
    int mode = atoi(argv[1]);

    switch (mode) {
        case MODE_DEFAULT:
            if (cant != 0) {
                fprintf(stderr, "Modo 1 no recibe parametros.\n");
                return MODE_INVALID;
            }
            break;
            
            case MODE_FROM_FILES:
            if (cant != 2) {
                fprintf(stderr, "Modo 2 requiere: <archivo1> <archivo2>\n");
                return MODE_INVALID;
            }
            // char *file1 = params[0];
            // char *file2 = params[1];
            break;
            
            case MODE_FROM_STRINGS:
            if (cant != 2) {
                fprintf(stderr, "Modo 3 requiere: <seq1> <seq2>\n");
                return MODE_INVALID;
            }
            // char *seq1 = params[0];
            // char *seq2 = params[1];
            break;
            
            case MODE_GENERATE_RANDOM:
            if (cant != 1) {
                fprintf(stderr, "Modo 4 requiere: <exponente>\n");
                return MODE_INVALID;
            }
            // int exponent = atoi(params[0]);
            break;
            
            case MODE_LIST_SEQUENCES:
            if (cant == 0) {
                //nada
            }
            else if (cant == 1) {
                // char *subdir = params[0];
            }
            else {
                fprintf(stderr, "Modo 5 recibe cero o un parametro.\n");
                return MODE_INVALID;
            }
            break;
            
            case MODE_PRINT_SEQUENCE:
            if (cant != 1) {
                fprintf(stderr, "Modo 6 requiere: <path>\n");
                return MODE_INVALID;
            }
            // char *print_path = params[0];
            break;

            case MODE_DELETE_SEQUENCE:
            if (cant != 1) {
                fprintf(stderr, "Modo 7 requiere: <path>\n");
                return MODE_INVALID;
            }
            // char *delete_path = params[0];
            break;

        default:
            printf("Modo invalido: %d\n", mode);
            printf("Modos validos:\n");
            printf("1: Cargar secuencias por defecto. No recibe parametros.\n");
            printf("2: Cargar secuencias desde archivos. Recibe dos parametros: <archivo1> <archivo2>\n");
            printf("3: Cargar secuencias desde cadenas de caracteres. Recibe dos parametros: <seq1> <seq2>\n");
            printf("4: Generar secuencia aleatoria. Recibe un parametro: <exponente>\n");
            printf("5: Listar secuencias en un directorio. Recibe cero o un parametro: [<subdirectorio>]\n");
            printf("6: Imprimir secuencia desde un archivo. Recibe un parametro: <path>\n");
            printf("7: Eliminar secuencia desde un archivo. Recibe un parametro: <path>\n");
            return MODE_INVALID;
    }

    return mode;
}

int reports(double start, double end){
    double tiempo = end - start;
    printf("Tiempo de ejecución: %f segundos\n", tiempo);
    return 0;
}

