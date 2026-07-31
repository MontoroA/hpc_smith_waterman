#include <stdbool.h>

#ifndef IO_H
#define IO_H

#define MODE_INVALID 0
#define MODE_DEFAULT 1
#define MODE_FROM_FILES 2
#define MODE_GENERATE_RANDOM 3
#define MODE_LIST_SEQUENCES 4
#define MODE_PRINT_SEQUENCE 5

int read_mode(int argc, char **argv, bool load_checkpoint);

#endif