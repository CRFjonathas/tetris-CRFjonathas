#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

// Definição da Peça
typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
    int id;
} Peca;

// Estrutura da Fila Circular
#define TAM_FILA 5
typedef struct {
    Peca itens[TAM_FILA];
    int frente;
    int tras;
    int qtd;
} Fila;

// Variável global para gerar IDs sequenciais
int id_contador = 0;

// Função para gerar uma nova peça aleatória
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = id_contador++;
    return p;
}

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
    // Preenche a fila inicialmente (opcional, mas recomendado pelo enunciado)
    for (int i = 0; i < TAM_FILA; i++) {
        f->tras = (f->tras + 1) % TAM_FILA;
        f->itens[f->tras] = gerarPeca();
        f->qtd++;
    }
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return (f->qtd == 0);
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return (f->qtd == TAM_FILA);
}

// Insere elemento no final (Enqueue)
void enqueue(Fila *f) {
    if (filaCheia(f)) {
        printf("\n[!] Fila cheia! Jogue uma peca antes de inserir.\n");
        return;
    }
    Peca p = gerarPeca();
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = p;
    f->qtd++;
    printf("\n[+] Peca inserida: [%c %d]\n", p.nome, p.id);
}

// Remove elemento da frente (Dequeue)
void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("\n[!] Fila vazia! Insira novas pecas.\n");
        return;
    }
    Peca p = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
    printf("\n[-] Voce jogou a peca: [%c %d]\n", p.nome, p.id);
}

// Exibe o estado atual da fila
void mostrarFila(Fila *f) {
    printf("\n=== Estado Atual ===\nFila de pecas: ");
    if (filaVazia(f)) {
        printf("Vazia");
    } else {
        int i = f->frente;
        for (int count = 0; count < f->qtd; count++) {
            printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
            i = (i + 1) % TAM_FILA;
        }
    }
    printf("\n====================\n");
}

int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

    srand(time(NULL));
    Fila fila;
    inicializarFila(&fila);
    int opcao;

    do {
        mostrarFila(&fila);
        printf("\n1 - Jogar peca (Dequeue)");
        printf("\n2 - Inserir nova peca (Enqueue)");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: dequeue(&fila); break;
            case 2: enqueue(&fila); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}

