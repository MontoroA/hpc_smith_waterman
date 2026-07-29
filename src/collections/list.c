#include <stdio.h>
#include <stdlib.h>

#include "collections/list.h"

void init_list(List *list, char value)
{
    list->value = value;
    list->next = NULL;
}

void push(List **list, char value)
{
    if (*list == NULL)
    {
        *list = malloc(sizeof(List));
        init_list(*list, value);
        return;
    }
    List *new_node = malloc(sizeof(List));
    new_node->value = value;
    new_node->next = *list;
    *list = new_node;
}

int length(List *list)
{
    if (list == NULL)
        return 0;
    List *current = list;
    int size = 1;
    while (current->next != NULL)
    {
        current = current->next;
        size++;
    }
    return size;
}

char *print_list(List *list)
{
    int len = length(list);
    char *res = malloc(len + 1);
    int i = 0;
    while (list != NULL)
    {
        res[i] = list->value;
        list = list->next;
        i++;
    }
    res[i] = '\0';
    printf("%s\n", res);
    return res;
}

void save_list(List *list, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("fopen");
        return;
    }

    while (list != NULL)
    {
        fputc(list->value, file);
        list = list->next;
    }

    fclose(file);
}

void free_list(List *list)
{
    while (list != NULL)
    {
        List *next = list->next;
        free(list);
        list = next;
    }
}