#include "heap.h"
#include <time.h>

void limparBuffer() 
{
    while (getchar() != '\n');
}

int main() 
{

    srand(time(NULL));

    Heap* hospital = criarHeap(10);
    int opcao;
    int contador_pacientes_gerados = 1;

    do {
        printf("\n");
        printf("==================================================\n");
        printf("SISTEMA DE FILA DE PRIORIDADE)\n");
        printf("==================================================\n");
        printf("1. Cadastrar Paciente (Triagem)\n");
        printf("2. Chamar Proximo Paciente (Atender)\n");
        printf("3. Alterar Prioridade (Agravamento/Melhora)\n");
        printf("4. Exibir Fila de Espera (Lista)\n");
        printf("5. Visualizar Arvore de Prioridades (ASCII)\n");
        printf("6. Encerrar Expediente (Sair)\n");
        printf("7. Gerar Pacientes Aleatorios (Simulacao)\n");
        printf("==================================================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) 
        {
            limparBuffer();
            opcao = 0;
        }

        switch (opcao) 
        {
            case 1: 
            {
                Paciente p;
                printf("\nCADASTRAR PACIENTE\n");
                
                printf("Nome do paciente: ");
                scanf(" %[^\n]", p.nome);
                
                printf("Codigo de triagem (numero inteiro): ");
                while (scanf("%d", &p.codigo_triagem) != 1) 
                {
                    limparBuffer();
                    printf("Invalido! Digite um inteiro: ");
                }

                printf("Nivel de prioridade (1=Critico a 5=Nao-urgente): ");
                while (scanf("%d", &p.prioridade) != 1 || p.prioridade < 1 || p.prioridade > 5) 
                {
                    limparBuffer();
                    printf("Invalido! Digite uma prioridade de 1 a 5: ");
                }

                inserirPaciente(hospital, p);
                printf("Paciente %s cadastrado com sucesso\n", p.nome);
                break;
            }

            case 2: 
            {
                printf("\nCHAMADA DE ATENDIMENTO\n");
                Paciente atendido = atenderPaciente(hospital);
                
                if (atendido.codigo_triagem == -1) 
                {
                    printf("Nenhum paciente na fila!\n");
                } 
                else 
                {
                    printf("Chamando paciente %s (Codigo: %d)...\n", atendido.nome, atendido.codigo_triagem);
                    printf("Motivo da prioridade: Nivel %d\n", atendido.prioridade);
                }
                break;
            }

            case 3: 
            {
                int codigo, nova_prio;
                printf("\n--- ALTERAR PRIORIDADE ---\n");
                
                if (hospital->tamanho == 0) 
                {
                    printf("A fila esta vazia.\n");
                    break;
                }

                printf("Digite o Codigo de Triagem do paciente: ");
                if (scanf("%d", &codigo) != 1) 
                { 
                    limparBuffer(); 
                    break; 
                }

                printf("Digite a NOVA prioridade (1 a 5): ");
                if (scanf("%d", &nova_prio) != 1 || nova_prio < 1 || nova_prio > 5) 
                {
                    limparBuffer();
                    printf("Prioridade invalida.\n");
                    break;
                }

                alterarPrioridade(hospital, codigo, nova_prio);
                break;
            }

            case 4:
                if (hospital->tamanho == 0) 
                {
                    printf("\nA fila esta vazia.\n");
                } 
                else 
                {
                    imprimirFila(hospital);
                }
                break;

            case 5:
                if (hospital->tamanho == 0) {
                    printf("\nNao ha pacientes para gerar a arvore.\n");
                } 
                else 
                {
                    printf("\nESTRUTURA DO HEAP:\n");
                    printf("(Topo da tela = Galhos da Direita | Fundo da tela = Galhos da Esquerda)\n\n");
                    imprimirArvoreASCII(hospital);
                    printf("\n========================================\n");
                }
                break;

            case 6:
                printf("\nEncerrando o sistema e liberando a memoria...\n");
                destruirHeap(hospital);
                break;

            case 7: 
            {
                int qtd;
                printf("\n--- GERADOR DE SIMULACAO ---\n");
                printf("Quantos pacientes aleatorios deseja gerar? ");
                
                if (scanf("%d", &qtd) != 1 || qtd <= 0) 
                {
                    limparBuffer();
                    printf("Digite um numero valido e maior que zero.\n");
                    break;
                }

                for (int i = 0; i < qtd; i++) 
                {
                    Paciente p;
                    p.codigo_triagem = (rand() % 9000) + 1000; // Gera codigo de 4 digitos (ex: 4521)
                    p.prioridade = (rand() % 5) + 1;           // Gera prioridade de 1 a 5
                    
                    // Cria com nome generico (ex: "Paciente 1", "Paciente 2")
                    sprintf(p.nome, "Paciente %d", contador_pacientes_gerados);
                    contador_pacientes_gerados++;

                    inserirPaciente(hospital, p);
                    printf("-> %s (Triagem: %d) chegou na emergencia com Prioridade %d\n", p.nome, p.codigo_triagem, p.prioridade);
                }
                
                printf("\n%d pacientes foram gerados e o Heap reordenou todos com sucesso!\n", qtd);
                break;
            }

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 6);

    return 0;
}