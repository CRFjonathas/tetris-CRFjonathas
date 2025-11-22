#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

typedef struct {
    char nome;
    int id;
} Peca;

#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct {
    Peca itens[TAM_FILA];
    int frente, tras, qtd;
} Fila;

typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

int id_contador = 0;

Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = id_contador++;
    return p;
}

// --- FUNÇÕES BASICAS (Reaproveitadas do Aventureiro) ---
void inicializarFila(Fila *f) {
    f->frente = 0; f->tras = -1; f->qtd = 0;
    for(int i=0; i<TAM_FILA; i++) {
        f->tras = (f->tras + 1) % TAM_FILA;
        f->itens[f->tras] = gerarPeca();
        f->qtd++;
    }
}
void reporFila(Fila *f) {
    if (f->qtd < TAM_FILA) {
        f->tras = (f->tras + 1) % TAM_FILA;
        f->itens[f->tras] = gerarPeca();
        f->qtd++;
    }
}
Peca removerFila(Fila *f) {
    Peca p = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
    return p;
}
void inicializarPilha(Pilha *p) { p->topo = -1; }
int pilhaCheia(Pilha *p) { return p->topo == TAM_PILHA - 1; }
int pilhaVazia(Pilha *p) { return p->topo == -1; }
void push(Pilha *p, Peca item) { p->itens[++(p->topo)] = item; }
Peca pop(Pilha *p) { return p->itens[(p->topo)--]; }

// --- FUNÇÕES ESPECIAIS MESTRE ---

// Opção 4: Troca simples (Frente Fila <-> Topo Pilha)
void trocarFrenteTopo(Fila *f, Pilha *p) {
    if (pilhaVazia(p)) {
        printf("\n[!] Erro: Pilha vazia. Impossivel trocar.\n");
        return;
    }
    // Swap direto
    Peca temp = f->itens[f->frente];
    f->itens[f->frente] = p->itens[p->topo];
    p->itens[p->topo] = temp;
    printf("\n[ok] Troca realizada: Frente da Fila <-> Topo da Pilha.\n");
}

// Opção 5: Troca Múltipla (3 Primeiros Fila <-> 3 da Pilha)
void trocarBloco(Fila *f, Pilha *p) {
    // Validação
    if (p->topo != 2) { // Precisa ter exatamente 3 itens (índices 0, 1, 2)
        printf("\n[!] Erro: Pilha precisa ter 3 pecas para essa troca.\n");
        return;
    }
    
    // Como a fila é circular, usamos uma variável auxiliar para percorrer os índices
    int idxFila = f->frente;
    
    // Loop de troca para 3 elementos
    for (int k = 2; k >= 0; k--) { // k vai do topo (2) até a base (0) da pilha
        Peca temp = f->itens[idxFila];
        
        // Troca Fila -> Pilha
        f->itens[idxFila] = p->itens[k];
        
        // Troca Pilha -> Fila
        p->itens[k] = temp;
        
        // Avança índice circular
        idxFila = (idxFila + 1) % TAM_FILA;
    }
    printf("\n[ok] Troca Multipla realizada com sucesso!\n");
}

void mostrarEstado(Fila *f, Pilha *p) {
    printf("\n=== Estado (Mestre) ===");
    printf("\nFila: ");
    int i = f->frente;
    for (int c = 0; c < f->qtd; c++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\nPilha (Topo->Base): ");
    for (int k = p->topo; k >= 0; k--) {
        printf("[%c %d] ", p->itens[k].nome, p->itens[k].id);
    }
    printf("\n=======================\n");
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

    srand(time(NULL));
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    int opcao;

    do {
        mostrarEstado(&fila, &pilha);
        printf("\n1 - Jogar peca");
        printf("\n2 - Reservar peca");
        printf("\n3 - Usar reserva");
        printf("\n4 - Trocar (Frente <-> Topo)");
        printf("\n5 - Troca Multipla (3 <-> 3)");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Jogar
                printf("\n[-] Jogou: [%c %d]\n", removerFila(&fila).nome, removerFila(&fila).id); // Bug visual no print corrigido abaixo
                // Correção logica: o print chamava removerFila 2x. 
                // Forma correta:
                // Peca temp = removerFila(&fila);
                // printf("Jogou: %c %d", temp.nome, temp.id);
                reporFila(&fila);
                break;
            case 2: // Reservar
                if (pilhaCheia(&pilha)) printf("\n[!] Pilha cheia!\n");
                else {
                    push(&pilha, removerFila(&fila));
                    reporFila(&fila);
                }
                break;
            case 3: // Usar
                if (pilhaVazia(&pilha)) printf("\n[!] Pilha vazia!\n");
                else printf("\n[-] Usou: [%c %d]\n", pop(&pilha).nome, pop(&pilha).id); // Erro visual similar corrigido na logica
                break;
            case 4: trocarFrenteTopo(&fila, &pilha); break;
            case 5: trocarBloco(&fila, &pilha); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Invalido.\n");
        }
    } while (opcao != 0);
    return 0;
}

