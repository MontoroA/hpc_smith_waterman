#ifndef LIST_H
#define LIST_H

#include <stdint.h>

typedef struct List
{
    char value;
    struct List *next;
} List;

// void init_list(List* list, char value);
void push(List **list, char value);
uint32_t length(List *list);
char *print_list(List *list);

void save_list(List *list, const char *filename);
void free_list(List *list);

#endif