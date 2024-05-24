// list.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

// Variável global head
struct node *head = NULL;

// Função para adicionar uma nova tarefa à lista de tarefas
void insert(struct node **head, Task *newTask) {
    // Aloca memória para um novo nó
    struct node *newNode = malloc(sizeof(struct node));
    if (!newNode) {
        printf("Erro ao alocar memória para novo nó.\n");
        return;
    }

    // Preenche o novo nó com a tarefa fornecida
    newNode->task = newTask;
    newNode->next = NULL;

    // Se a lista estiver vazia, o novo nó se torna a cabeça da lista
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Percorre a lista até o último nó
    struct node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Insere o novo nó no final da lista
    temp->next = newNode;
}

// Função para excluir uma tarefa da lista de tarefas
void delete(struct node **head, Task *task) {
    struct node *temp = *head;
    struct node *prev = NULL;

    // Percorre a lista até encontrar a tarefa a ser excluída
    while (temp != NULL && temp->task != task) {
        prev = temp;
        temp = temp->next;
    }

    // Se a tarefa não foi encontrada na lista
    if (temp == NULL) {
        printf("Tarefa não encontrada na lista.\n");
        return;
    }

    // Se a tarefa a ser excluída é a cabeça da lista
    if (temp == *head) {
        *head = temp->next;
    } else {
        // Se a tarefa está no meio ou no final da lista
        prev->next = temp->next;
    }

    // Libera a memória alocada para a tarefa e para o nó
    free(temp->task->name);
    free(temp->task);
    free(temp);
}

// Função para percorrer e imprimir os elementos da lista de tarefas
void traverse(struct node *head) {
    struct node *temp = head;

    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n", temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}
