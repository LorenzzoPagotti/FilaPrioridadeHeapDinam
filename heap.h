#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COR_VERMELHA  "\x1b[31m" // Prioridade 1 (Crítico)
#define COR_AMARELA   "\x1b[33m" // Prioridade 2 e 3
#define COR_VERDE     "\x1b[32m" // Prioridade 4 e 5
#define COR_RESET     "\x1b[0m"  // Normal

typedef struct Paciente { // struct paciente
    char nome[50];
    int codigo_triagem;
    int prioridade; // 1 a 5
} Paciente;

typedef struct Heap {
    Paciente* pacientes; // array de pacientes
    int tamanho;
    int capacidade;
} Heap;

Heap* criarHeap(int capacidade_inicial);
void destruirHeap(Heap* h);

void inserirPaciente(Heap* h, Paciente p);
Paciente atenderPaciente(Heap* h);
void alterarPrioridade(Heap* h, int codigo_triagem, int nova_prioridade);

void imprimirFila(Heap* h); 
void imprimirArvoreASCII(Heap* h);

void heapifyUp(Heap* h, int indice);
void heapifyDown(Heap* h, int indice);
void trocar(Paciente* a, Paciente* b);

#endif