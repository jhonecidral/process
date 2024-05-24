#include "schedule_edf.h"
#include "task.h"
#include <stdio.h>

extern Task *edf_task_list;

void schedule_edf() {
    Task *current = edf_task_list;
    while (current != NULL) {
        printf("Executando tarefa: %s, Prioridade: %d, Burst: %d, Deadline: %d\n", current->name, current->priority, current->burst, current->deadline);
        current = current->next;
    }
}
