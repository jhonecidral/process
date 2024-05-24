// list.h

#ifndef LIST_H
#define LIST_H

#include "task.h"

// Nó da lista ligada
struct node {
    Task *task;
    struct node *next;
};

// Variável global externa head
extern struct node *head;

// Funções para manipulação da lista
void insert(struct node **head, Task *newTask);
void delete(struct node **head, Task *task);
void traverse(struct node *head);

#endif /* LIST_H */
