#ifndef SEQUENCES_H
#define SEQUENCES_H

typedef struct {
    char* data;
    int length;
} Sequence;

Sequence** execute_mode(int mode, char** params);

#endif