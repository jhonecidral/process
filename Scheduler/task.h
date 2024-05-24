#ifndef TASK_H
#define TASK_H

#include "common.h"

typedef struct task {
    char name[SIZE];
    int priority;
    int burst;
    int deadline;
    struct task *next;
} Task;

void add_task(const char *name, int priority, int burst);
void add_task_edf(const char *name, int priority, int burst, int deadline);

// Funções para manipulação de filas
void add_task_to_queue(Task **queue, const char *name, int priority, int burst);
Task *remove_task_from_queue(Task **queue);

#endif // TASK_H
