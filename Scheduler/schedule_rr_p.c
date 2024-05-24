#include "schedule_rr_p.h"
#include <stdio.h>
#include <stdlib.h>

extern Task *task_list;

#define MAX_PRIORITY 5
Task *priority_queues[MAX_PRIORITY];

void schedule_rr_p() {
    // Inicializa as filas de prioridade
    for (int i = 0; i < MAX_PRIORITY; i++) {
        priority_queues[i] = NULL;
    }

    // Distribui as tarefas nas filas de prioridade
    Task *current = task_list;
    while (current != NULL) {
        add_task_to_queue(&priority_queues[current->priority - 1], current->name, current->priority, current->burst);
        current = current->next;
    }

    int slice = 10; // Definindo um slice de tempo arbitrário para o RR
    int time = 0;
    int all_empty = 0;

    // Loop de execução das tarefas
    while (!all_empty) {
        all_empty = 1;
        for (int i = 0; i < MAX_PRIORITY; i++) {
            if (priority_queues[i] != NULL) {
                all_empty = 0;
                Task *task = remove_task_from_queue(&priority_queues[i]);
                if (task->burst > slice) {
                    printf("Executando tarefa: %s, Prioridade: %d, Burst: %d, Tempo: %d\n", task->name, task->priority, slice, time);
                    task->burst -= slice;
                    add_task_to_queue(&priority_queues[i], task->name, task->priority, task->burst);
                } else {
                    printf("Executando tarefa: %s, Prioridade: %d, Burst: %d, Tempo: %d\n", task->name, task->priority, task->burst, time);
                    free(task);
                }
                time += slice;
            }
        }
    }
}
