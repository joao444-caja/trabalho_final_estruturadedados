
#ifndef lista_h
#define lista_h


typedef struct No {
    int valor;
    struct No* prox;
} No;

typedef struct {
    No* inicio;
} Lista;

#include "pilha.h" 

void inicializarLista(Lista* l);
void inserir(Lista* l, int valor, Pilha* p);
void removerElemento(Lista* l, int valor, Pilha* p);
void imprimirLista(Lista* l);

#endif