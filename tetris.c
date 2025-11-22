#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

// --- ESTRUTURAS ---
#define TAM_FILA 5
typedef struct {
    Peca itens[TAM_FILA];
    int frente, tras, qtd;
} Fila;

#define TAM_PILHA 3
typedef struct {
    Peca itens[TAM_PILHA];
    int topo; // Índice do topo
} Pilha;

int id_contador = 0;

Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = id_contador++;
    return p;
}

// --- FUNÇÕES DE FILA ---
void inicializarFila(Fila *f) {
    f->frente = 0; f->tras = -1; f->qtd = 0;
    // Enche a fila inicialmente
    for(int i=0; i<TAM_FILA; i++) {
        f->tras = (f->tras + 1) % TAM_FILA;
        f->itens[f->tras] = gerarPeca();
        f->qtd++;
    }
}

// Função auxiliar para repor a fila automaticamente (requisito do nível Aventureiro)
void reporFila(Fila *f) {
    if (f->qtd < TAM_FILA) {
        Peca p = gerarPeca();
        f->tras = (f->tras + 1) % TAM_FILA;
        f->itens[f->tras] = p;
        f->qtd++;
    }
}

Peca removerFila(Fila *f) {
    // Assume que a fila nunca fica vazia neste nível devido à reposição
    Peca p = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
    return p;
}

// --- FUNÇÕES DE PILHA ---
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return (p->topo == TAM_PILHA - 1);
}

int pilhaVazia(Pilha *p) {
    return (p->topo == -1);
}

void push(Pilha *p, Peca item) {
    if (!pilhaCheia(p)) {
        p->itens[++(p->topo)] = item;
        printf("\n[+] Peca reservada: [%c %d]\n", item.nome, item.id);
    }
}

Peca pop(Pilha *p) {
    if (!pilhaVazia(p)) {
        return p->itens[(p->topo)--];
    }
    Peca vazia = {' ', -1}; // Erro
    return vazia;
}

// --- EXIBIÇÃO ---
void mostrarEstado(Fila *f, Pilha *p) {
    printf("\n=== Estado Atual ===");
    // Fila
    printf("\nFila: ");
    int i = f->frente;
    for (int c = 0; c < f->qtd; c++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % TAM_FILA;
    }
    // Pilha
    printf("\nPilha (Topo->Base): ");
    for (int k = p->topo; k >= 0; k--) {
        printf("[%c %d] ", p->itens[k].nome, p->itens[k].id);
    }
    if (pilhaVazia(p)) printf("Vazia");
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

        srand(time(NULL));
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    int opcao;

    do {
        mostrarEstado(&fila, &pilha);
        printf("\n1 - Jogar peca (Dequeue)");
        printf("\n2 - Reservar peca (Fila -> Pilha)");
        printf("\n3 - Usar peca reservada (Pop Pilha)");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Jogar
                Peca p = removerFila(&fila);
                printf("\n[-] Voce jogou: [%c %d]\n", p.nome, p.id);
                reporFila(&fila);
                break;
            }
            case 2: { // Reservar
                if (pilhaCheia(&pilha)) {
                    printf("\n[!] Pilha cheia! Nao e possivel reservar.\n");
                } else {
                    Peca p = removerFila(&fila);
                    push(&pilha, p);
                    reporFila(&fila);
                }
                break;
            }
            case 3: { // Usar Reserva
                if (pilhaVazia(&pilha)) {
                    printf("\n[!] Pilha vazia!\n");
                } else {
                    Peca p = pop(&pilha);
                    printf("\n[-] Usou reserva: [%c %d]\n", p.nome, p.id);
                }
                break;
            }
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

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

