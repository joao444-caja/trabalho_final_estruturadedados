#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "pilha.h"

void inicializarLista(Lista* l) {
    l->inicio = NULL;
}

void inserir(Lista* l, int valor, Pilha* p) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->prox = l->inicio;
    l->inicio = novoNo;

    push(p, "Inseriu elemento na lista");
}

void removerElemento(Lista* l, int valor, Pilha* p) {
    No* atual = l->inicio;
    No* anterior = NULL;

    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        push(p, "Elemento nao encontrado na lista");
        return;
    }

    if (anterior == NULL) {
        l->inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    push(p, "Removeu elemento da lista");
}

void imprimirLista(Lista* l) {
    No* atual = l->inicio;
    printf("Lista: ");
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->prox;
    }
    printf("NULL\n");
}