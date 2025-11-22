#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- ESTRUTURAS E DEFINIÇÕES ---

typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
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

// Variável global para IDs únicos
int id_contador = 0;

// --- FUNÇÕES AUXILIARES ---

Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = id_contador++;
    return p;
}

// --- GERENCIAMENTO DE FILA ---

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
    // Preenche a fila inicialmente
    for (int i = 0; i < TAM_FILA; i++) {
        f->tras = (f->tras + 1) % TAM_FILA;
        f->itens[f->tras] = gerarPeca();
        f->qtd++;
    }
}

// Garante que a fila esteja sempre cheia (Regra dos níveis avançados)
void reporFila(Fila *f) {
    while (f->qtd < TAM_FILA) {
        f->tras = (f->tras + 1) % TAM_FILA;
        f->itens[f->tras] = gerarPeca();
        f->qtd++;
    }
}

Peca removerFila(Fila *f) {
    // Nota: Como a fila é reposta automaticamente, não verificamos underflow aqui
    Peca p = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
    return p;
}

// --- GERENCIAMENTO DE PILHA ---

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
    }
}

Peca pop(Pilha *p) {
    if (!pilhaVazia(p)) {
        return p->itens[(p->topo)--];
    }
    Peca vazia = {'?', -1};
    return vazia;
}

// --- FUNÇÕES ESTRATÉGICAS (NÍVEL MESTRE) ---

// Opção 4: Troca a peça da frente da fila com a do topo da pilha
void trocarFrenteTopo(Fila *f, Pilha *p) {
    if (pilhaVazia(p)) {
        printf("\n[!] Erro: A pilha esta vazia. Nao ha o que trocar.\n");
        return;
    }
    
    // Realiza a troca direta
    Peca temp = f->itens[f->frente];
    f->itens[f->frente] = p->itens[p->topo];
    p->itens[p->topo] = temp;
    
    printf("\n[OK] Troca realizada: [Frente Fila] <-> [Topo Pilha].\n");
}

// Opção 5: Troca os 3 primeiros da fila com as 3 peças da pilha
void trocarBloco(Fila *f, Pilha *p) {
    // Validação: A pilha precisa estar cheia (3 itens) para trocar 3x3
    if (p->topo != 2) { 
        printf("\n[!] Erro: A pilha precisa ter exatamente 3 pecas para esta manobra.\n");
        return;
    }
    
    int idxFila = f->frente;
    
    // Percorre os 3 elementos da pilha (do topo 2 até a base 0)
    for (int k = 2; k >= 0; k--) {
        Peca temp = f->itens[idxFila];
        
        // Fila recebe da Pilha
        f->itens[idxFila] = p->itens[k];
        
        // Pilha recebe da Fila
        p->itens[k] = temp;
        
        // Avança o índice da fila circularmente
        idxFila = (idxFila + 1) % TAM_FILA;
    }
    printf("\n[OK] Troca Multipla (3x3) realizada com sucesso!\n");
}

// --- VISUALIZAÇÃO ---

void mostrarEstado(Fila *f, Pilha *p) {
    printf("\n========================================");
    printf("\n FILA (Proximas):  ");
    int i = f->frente;
    for (int count = 0; count < f->qtd; count++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % TAM_FILA;
    }
    
    printf("\n PILHA (Reserva):  ");
    if (pilhaVazia(p)) {
        printf("[ Vazia ]");
    } else {
        // Mostra do Topo para a Base (Padrão Pilha)
        for (int k = p->topo; k >= 0; k--) {
            printf("[%c %d] ", p->itens[k].nome, p->itens[k].id);
        }
    }
    printf("\n========================================\n");
}

// --- MAIN ---

int main() {
    srand(time(NULL)); // Semente para aleatoriedade
    
    Fila fila;
    Pilha pilha;
    int opcao;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    printf("\n--- TETRIS STACK: GERENCIADOR DE PECAS ---\n");

    do {
        mostrarEstado(&fila, &pilha);
        
        printf("1 - Jogar peca (Dequeue)\n");
        printf("2 - Reservar peca (Fila -> Pilha)\n");
        printf("3 - Usar peca reservada (Pop Pilha)\n");
        printf("4 - Trocar (Frente Fila <-> Topo Pilha)\n");
        printf("5 - Troca Multipla (3 da Fila <-> 3 da Pilha)\n");
        printf("0 - Sair\n");
        printf(">> Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Jogar
                Peca p = removerFila(&fila);
                printf("\n[-] Voce jogou a peca: [%c %d]\n", p.nome, p.id);
                reporFila(&fila); // Mantém fila cheia
                break;
            }
            case 2: { // Reservar
                if (pilhaCheia(&pilha)) {
                    printf("\n[!] A pilha de reserva esta cheia!\n");
                } else {
                    Peca p = removerFila(&fila);
                    push(&pilha, p);
                    printf("\n[+] Peca reservada: [%c %d]\n", p.nome, p.id);
                    reporFila(&fila);
                }
                break;
            }
            case 3: { // Usar reserva
                if (pilhaVazia(&pilha)) {
                    printf("\n[!] A pilha de reserva esta vazia!\n");
                } else {
                    Peca p = pop(&pilha);
                    printf("\n[-] Usando peca da reserva: [%c %d]\n", p.nome, p.id);
                }
                break;
            }
            case 4:
                trocarFrenteTopo(&fila, &pilha);
                break;
            case 5:
                trocarBloco(&fila, &pilha);
                break;
            case 0:
                printf("\nEncerrando sistema...\n");
                break;
            default:
                printf("\n[!] Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}