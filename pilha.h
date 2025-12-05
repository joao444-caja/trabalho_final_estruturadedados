#ifndef pilha.h
#define pilha.h

typedef struct Operaçao {
    char descricao[50];
    struct Operaçao* prox;
}

typedef struct {
    struct Operaçao* topo;
} Pilha;

void inicializarPilha(Pilha* p);
void push(Pilha* p, char* desc);
void pop(Pilha* p);
void imprimirPilha(Pilha* p);

#endif


