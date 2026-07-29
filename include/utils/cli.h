#ifndef IO_H
#define IO_H

static const int MODE_INVALID          = 0;
static const int MODE_DEFAULT          = 1;
static const int MODE_FROM_FILES       = 2;
static const int MODE_GENERATE_RANDOM  = 3;
static const int MODE_LIST_SEQUENCES   = 4;
static const int MODE_PRINT_SEQUENCE   = 5;

int read_mode(int argc, char** argv);

#endif