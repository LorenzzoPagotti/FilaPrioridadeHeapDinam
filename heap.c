#include "heap.h"

Heap* criarHeap(int capacidade_inicial) 
{
    Heap* h = (Heap*) malloc(sizeof(Heap));
    h->tamanho = 0;
    h->capacidade = capacidade_inicial;
    h->pacientes = (Paciente*) malloc(capacidade_inicial * sizeof(Paciente));
    return h;
}

void destruirHeap(Heap* h) 
{
    if (h == NULL) return;

    free(h->pacientes);
    free(h);
}

void trocar(Paciente* a, Paciente* b) 
{
    Paciente temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(Heap* h, int indice) 
{
    int pai = (indice - 1) / 2;

    while (indice > 0 && h->pacientes[indice].prioridade < h->pacientes[pai].prioridade) 
    {
        trocar(&h->pacientes[indice], &h->pacientes[pai]);
        indice = pai;
        pai = (indice - 1) / 2;
    }
}

void heapifyDown(Heap* h, int indice) 
{
    int menor = indice;
    int filho_esq = (2 * indice) + 1;
    int filho_dir = (2 * indice) + 2;

    if (filho_esq < h->tamanho && h->pacientes[filho_esq].prioridade < h->pacientes[menor].prioridade) 
    {
        menor = filho_esq;
    }

    if (filho_dir < h->tamanho && h->pacientes[filho_dir].prioridade < h->pacientes[menor].prioridade) 
    {
        menor = filho_dir;
    }

    if (menor != indice) 
    {
        trocar(&h->pacientes[indice], &h->pacientes[menor]);
        heapifyDown(h, menor);
    }
}

void inserirPaciente(Heap* h, Paciente p) 
{
    if (h->tamanho == h->capacidade) 
    {
        h->capacidade *= 2;
        h->pacientes = (Paciente*) realloc(h->pacientes, h->capacidade * sizeof(Paciente));
        printf("\nCapacidade aumentada para %d.\n", h->capacidade);
    }

    h->pacientes[h->tamanho] = p;
    h->tamanho++;

    heapifyUp(h, h->tamanho - 1);
}

Paciente atenderPaciente(Heap* h) 
{
    if (h->tamanho == 0) 
    {
        Paciente vazio;
        vazio.codigo_triagem = -1;
        return vazio;
    }

    Paciente paciente_atendido = h->pacientes[0];

    h->pacientes[0] = h->pacientes[h->tamanho - 1];
    h->tamanho--;

    heapifyDown(h, 0);

    return paciente_atendido;
}

void alterarPrioridade(Heap* h, int codigo_triagem, int nova_prioridade) 
{
    int indice = -1;

    for (int i = 0; i < h->tamanho; i++) 
    {
        if (h->pacientes[i].codigo_triagem == codigo_triagem) 
        {
            indice = i;
            break;
        }
    }

    if (indice == -1) 
    {
        printf("Paciente com codigo %d nao encontrado.\n", codigo_triagem);
        return;
    }

    int prioridade_antiga = h->pacientes[indice].prioridade;
    h->pacientes[indice].prioridade = nova_prioridade;

    if (nova_prioridade < prioridade_antiga) 
    {
        heapifyUp(h, indice);
    } 
    else if (nova_prioridade > prioridade_antiga) 
    {
        heapifyDown(h, indice);
    }
    printf("Fila reoordenada.\n");
}

void imprimirFila(Heap* h) {
    printf("\n--- FILA DE ESPERA (Ordem do Array) ---\n");
    for (int i = 0; i < h->tamanho; i++) {
        printf("Prioridade %d | Triagem: %d | Nome: %s\n", 
               h->pacientes[i].prioridade, h->pacientes[i].codigo_triagem, h->pacientes[i].nome);
    }
}

// Ajudante recursiva que desenha os galhos conectando os nós
void imprimirArvoreRecursivo(Heap* h, int indice, int tracos[], int nivel, int isFilhoDireito) {
    if (indice >= h->tamanho) return;

    // 1. Vai pro filho da direita primeiro (parte de cima da tela)
    if (2 * indice + 2 < h->tamanho) {
        tracos[nivel] = isFilhoDireito ? 0 : 1; // Decide se precisa descer uma linha reta '|'
        imprimirArvoreRecursivo(h, 2 * indice + 2, tracos, nivel + 1, 1);
    }

    // 2. Desenha a estrutura de galhos antes do nó
    for (int i = 0; i < nivel - 1; i++) {
        printf(tracos[i] ? "│   " : "    ");
    }
    if (nivel > 0) {
        printf(isFilhoDireito ? "┌── " : "└── ");
    } else {
        printf("➤ "); // Indicador visual para a Raiz
    }

    // 3. Imprime o paciente com as cores da gravidade
    Paciente p = h->pacientes[indice];
    if (p.prioridade == 1) {
        printf(COR_VERMELHA);
    } else if (p.prioridade <= 3) {
        printf(COR_AMARELA);
    } else {
        printf(COR_VERDE);
    }
    printf("[P%d] %d (%s)" COR_RESET "\n", p.prioridade, p.codigo_triagem, p.nome);

    // 4. Vai pro filho da esquerda (parte de baixo da tela)
    if (2 * indice + 1 < h->tamanho) {
        tracos[nivel] = isFilhoDireito ? 1 : 0;
        imprimirArvoreRecursivo(h, 2 * indice + 1, tracos, nivel + 1, 0);
    }
}

// Função principal que o main chama
void imprimirArvoreASCII(Heap* h) {
    int tracos[100] = {0}; // Array que aguenta árvores gigantes (100 níveis de profundidade)
    imprimirArvoreRecursivo(h, 0, tracos, 0, 0);
}