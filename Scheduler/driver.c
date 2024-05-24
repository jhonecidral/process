#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "schedule_rr_p.h"
#include "schedule_edf.h"
#include "common.h"

void load_tasks_rr(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo de tarefas para RR.\n");
        return;
    }

    char task[SIZE];
    char *name;
    int priority;
    int burst;

    while (fgets(task, SIZE, file) != NULL) {
        char *temp = strdup(task);
        if (temp == NULL) {
            printf("Erro ao duplicar a string.\n");
            fclose(file);
            return;
        }

        name = strtok(temp, ",");
        char *priority_str = strtok(NULL, ",");
        char *burst_str = strtok(NULL, ",");

        if (name == NULL || priority_str == NULL || burst_str == NULL) {
            printf("Erro ao ler os detalhes da tarefa.\n");
            free(temp);
            continue;
        }

        priority = atoi(priority_str);
        burst = atoi(burst_str);

        // Adiciona a tarefa à lista de RR
        printf("Adicionando tarefa RR: %s, Prioridade: %d, Burst: %d\n", name, priority, burst);
        add_task(name, priority, burst);

        free(temp);
    }

    fclose(file);
}

void load_tasks_edf(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo de tarefas para EDF.\n");
        return;
    }

    char task[SIZE];
    char *name;
    int priority;
    int burst;
    int deadline;

    while (fgets(task, SIZE, file) != NULL) {
        char *temp = strdup(task);
        if (temp == NULL) {
            printf("Erro ao duplicar a string.\n");
            fclose(file);
            return;
        }

        name = strtok(temp, ",");
        char *priority_str = strtok(NULL, ",");
        char *burst_str = strtok(NULL, ",");
        char *deadline_str = strtok(NULL, ",");

        if (name == NULL || priority_str == NULL || burst_str == NULL || deadline_str == NULL) {
            printf("Erro ao ler os detalhes da tarefa.\n");
            free(temp);
            continue;
        }

        priority = atoi(priority_str);
        burst = atoi(burst_str);
        deadline = atoi(deadline_str);

        // Adiciona a tarefa à lista de EDF
        printf("Adicionando tarefa EDF: %s, Prioridade: %d, Burst: %d, Deadline: %d\n", name, priority, burst, deadline);
        add_task_edf(name, priority, burst, deadline);

        free(temp);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    load_tasks_rr("rr-schedule_pri.txt");
    load_tasks_edf("edf-schedule_pri.txt");

    // Chama o escalonador apropriado
    printf("Executando escalonamento Round Robin:\n");
    schedule_rr_p();
    printf("\n");

    printf("Executando escalonamento EDF:\n");
    schedule_edf();

    return 0;
}
