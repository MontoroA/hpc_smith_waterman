#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void init(List* list, char value){
    list->value = value;
    list->next = NULL;
}

void push(List** list, char value){
    if(*list == NULL){
        *list = malloc(sizeof(List));
        init(*list, value);
        return;
    }
    List* new_node = malloc(sizeof(List));
    new_node->value = value;
    new_node->next = *list;
    *list = new_node;
}

int length(List* list){
    if(list == NULL)
        return 0;
    List* current = list;
    int size = 1;
    while(current->next != NULL){
        current = current->next;
        size++;
    }
    return size;
}

char* print(List* list){
    int len = length(list);
    char* res = malloc(sizeof(char)*len); 
    int i = 0;
    while(list != NULL){
        res[i] = list->value;
        list = list->next;
        i++;
    }
    printf("%s\n", res);
    return res;
}