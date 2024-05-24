#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Task *task_list = NULL;
Task *edf_task_list = NULL;

void add_task(const char *name, int priority, int burst) {
    add_task_to_queue(&task_list, name, priority, burst);
}

void add_task_edf(const char *name, int priority, int burst, int deadline) {
    Task *new_task = (Task *)malloc(sizeof(Task));
    if (!new_task) {
        printf("Erro ao alocar memória para nova tarefa.\n");
        return;
    }
    strncpy(new_task->name, name, SIZE);
    new_task->priority = priority;
    new_task->burst = burst;
    new_task->deadline = deadline;
    new_task->next = edf_task_list;
    edf_task_list = new_task;

    printf("EDF Task added: %s, Priority: %d, Burst: %d, Deadline: %d\n", name, priority, burst, deadline);
}

void add_task_to_queue(Task **queue, const char *name, int priority, int burst) {
    Task *new_task = (Task *)malloc(sizeof(Task));
    if (!new_task) {
        printf("Erro ao alocar memória para nova tarefa.\n");
        return;
    }
    strncpy(new_task->name, name, SIZE);
    new_task->priority = priority;
    new_task->burst = burst;
    new_task->deadline = 0;
    new_task->next = *queue;
    *queue = new_task;

    printf("Task added: %s, Priority: %d, Burst: %d\n", name, priority, burst);
}

Task *remove_task_from_queue(Task **queue) {
    if (*queue == NULL) return NULL;

    Task *task_to_remove = *queue;
    *queue = task_to_remove->next;
    return task_to_remove;
}
