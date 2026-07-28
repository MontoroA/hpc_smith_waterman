#ifndef LIST_H
#define LIST_H


typedef struct List{
    char value;
    struct List* next;
} List;

void init(List* list, char value);
void push(List** list, char value);
int length(List* list);
char* print_list(List* list);

#endif