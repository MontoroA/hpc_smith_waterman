#include <stdbool.h>

#ifndef IO_H
#define IO_H

static const int MODE_INVALID = 0;
static const int MODE_DEFAULT = 1;
static const int MODE_FROM_FILES = 2;
static const int MODE_FROM_STRINGS = 3;
static const int MODE_GENERATE_RANDOM = 4;
static const int MODE_LIST_SEQUENCES = 5;
static const int MODE_PRINT_SEQUENCE = 6;
static const int MODE_DELETE_SEQUENCE = 7;

int read_mode(int argc, char **argv, bool load_checkpoint);

#endif