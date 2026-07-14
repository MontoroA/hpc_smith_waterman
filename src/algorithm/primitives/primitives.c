#include <stdlib.h>

#include "algorithm/primitives/primitives.h"
#include "hpc/mpi_handler.h"
#include "utils/utils.h"


MatrixMap create_block_map(CharArray* seq1, CharArray* seq2)
{
    MatrixMap map;
    //Doesnt matter if the last blocks have a smaller size
    int height = (seq1->length + BLOCK_HEIGHT - 1) / BLOCK_HEIGHT;
    int width = (seq2->length + BLOCK_WIDTH - 1) / BLOCK_WIDTH;
    int length = height * width;

    bool* visited = malloc(length * sizeof(bool));
    for(int i = 0; i < length; i++){
        visited[i] = false;
    }
    map.visited = visited;
    map.current_level = 0;
    return map;
}

void print_block_map(MatrixMap map, CharArray* seq1, CharArray* seq2)
{
    int height = (seq1->length + BLOCK_HEIGHT - 1) / BLOCK_HEIGHT;
    int width = (seq2->length + BLOCK_WIDTH - 1) / BLOCK_WIDTH;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            printf("%d ", map.visited[i * width + j]);
        }
        printf("\n");
    }
    printf("\n");
}

MatrixIndex* get_unlocked_neighbors(MatrixIndex block, MatrixMap map)
{
    //map[block] = true; //marcar bloque como procesado
    //TODO
    //Mirar el bloque recibido: puede habilitar a los siguientes: abajo, derecha, siguiente en diagonal
    //Mirar map para eso, obtener
}