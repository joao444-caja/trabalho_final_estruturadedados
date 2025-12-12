#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno {
    int matricula;
    char nome[50];
    float nota;
    struct Aluno* next;
    struct Aluno* prev;
} Aluno;

typedef struct RegistroExclusao {
    int matricula;
    char nome[50];
    float nota;
    struct RegistroExclusao* next;
} RegistroExclusao;

Aluno* criarAluno(int matricula, char nome[], float nota) {
    Aluno* novo = malloc(sizeof(Aluno));
    if (!novo) return NULL;
    novo->matricula = matricula;
    strcpy(novo->nome, nome);
    novo->nota = nota;
    novo->next = NULL;
    novo->prev = NULL;
    return novo;
}

void inserirInicio(Aluno** head, int matricula, char nome[], float nota) {
    Aluno* novo = criarAluno(matricula, nome, nota);
    if (!novo) return;

    if (*head == NULL) {
        *head = novo;
        return;
    }

    novo->next = *head;
    (*head)->prev = novo;
    *head = novo;
}

void inserirFim(Aluno** head, int matricula, char nome[], float nota) {
    Aluno* novo = criarAluno(matricula, nome, nota);
    if (!novo) return;

    if (*head == NULL) {
        *head = novo;
        return;
    }

    Aluno* aux = *head;
    while (aux->next != NULL) aux = aux->next;

    aux->next = novo;
    novo->prev = aux;
}

void registrarExclusao(RegistroExclusao** topo, int matricula, char nome[], float nota) {
    RegistroExclusao* novo = malloc(sizeof(RegistroExclusao));
    if (!novo) return;

    novo->matricula = matricula;
    strcpy(novo->nome, nome);
    novo->nota = nota;
    novo->next = *topo;
    *topo = novo;
}

void imprimirListaInvertida(Aluno* head) {
    Aluno* aux = head;
    if (!aux) return;

    while (aux->next) aux = aux->next;

    printf("\nLISTA EM ORDEM INVERSA:\n\n");
    while (aux) {
        printf("Matrícula: %d\nNome: %s\nNota: %.2f\n\n",
               aux->matricula, aux->nome, aux->nota);
        aux = aux->prev;
    }
}

void remover(Aluno** head, RegistroExclusao** topo, int matricula) {
    if (*head == NULL) return;

    Aluno* aux = *head;

    if (aux->matricula == matricula) {
        *head = aux->next;
        if (*head != NULL) (*head)->prev = NULL;

        registrarExclusao(topo, aux->matricula, aux->nome, aux->nota);
        free(aux);
        return;
    }

    while (aux != NULL && aux->matricula != matricula)
        aux = aux->next;

    if (aux == NULL) return;

    if (aux->prev) aux->prev->next = aux->next;
    if (aux->next) aux->next->prev = aux->prev;

    registrarExclusao(topo, aux->matricula, aux->nome, aux->nota);
    free(aux);
}

void desfazerExclusao(Aluno** head, RegistroExclusao** topo) {
    if (*topo == NULL) {
        printf("\nNenhuma exclusão para desfazer.\n");
        return;
    }

    RegistroExclusao* excluido = *topo;
    inserirInicio(head, excluido->matricula, excluido->nome, excluido->nota);

    *topo = excluido->next;
    free(excluido);

    printf("\nExclusão desfeita com sucesso.\n");
}

void imprimirLista(Aluno* head) {
    if (head == NULL) {
        printf("\nA lista está vazia.\n");
        return;
    }

    Aluno* aux = head;
    printf("\nALUNOS CADASTRADOS:\n\n");

    while (aux != NULL) {
        printf("Matrícula: %d\nNome: %s\nNota: %.2f\n\n",
               aux->matricula, aux->nome, aux->nota);
        aux = aux->next;
    }
}

void buscarMatricula(Aluno* head, int matricula) {
    Aluno* aux = head;

    while (aux != NULL && aux->matricula != matricula)
        aux = aux->next;

    if (aux == NULL) {
        printf("\nAluno não encontrado.\n");
        return;
    }

    printf("\nAluno encontrado:\nMatrícula: %d\nNome: %s\nNota: %.2f\n",
           aux->matricula, aux->nome, aux->nota);
}

void ordenarLista(Aluno** head) {
    if (*head == NULL || (*head)->next == NULL) return;

    Aluno* atual = (*head)->next;

    while (atual != NULL) {
        Aluno* aux = atual->prev;

        while (aux != NULL && aux->matricula > atual->matricula)
            aux = aux->prev;

        Aluno* proximo = atual->next;

        if (atual->prev) atual->prev->next = atual->next;
        if (atual->next) atual->next->prev = atual->prev;

        if (aux == NULL) {
            atual->next = *head;
            atual->prev = NULL;
            (*head)->prev = atual;
            *head = atual;
        } else {
            atual->next = aux->next;
            atual->prev = aux;

            if (aux->next) aux->next->prev = atual;
            aux->next = atual;
        }

        atual = proximo;
    }

    printf("\nLista ordenada com sucesso.\n");
}

void liberarMemoria(Aluno* head) {
    Aluno* aux;
    while (head != NULL) {
        aux = head;
        head = head->next;
        free(aux);
    }
}

void liberarPilha(RegistroExclusao* topo) {
    RegistroExclusao* aux;
    while (topo != NULL) {
        aux = topo;
        topo = topo->next;
        free(aux);
    }
}

void exibirTopoPilha(RegistroExclusao* topo) {
    if (topo == NULL) {
        printf("\nA pilha de registros está vazia.\n");
        return;
    }

    printf("\nÚltimo aluno excluído:\nMatrícula: %d\nNome: %s\nNota: %.2f\n",
           topo->matricula, topo->nome, topo->nota);
}

int menu() {
    int op;
    printf("\n### MENU ###\n");
    printf("1 - Inserir no início\n");
    printf("2 - Inserir no fim\n");
    printf("3 - Remover\n");
    printf("4 - Listar\n");
    printf("5 - Buscar por matrícula\n");
    printf("6 - Ordenar lista\n");
    printf("7 - Desfazer exclusão\n");
    printf("8 - Exibir topo da pilha\n");
    printf("9 - Listar invertido\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &op);
    return op;
}

int main() {
    Aluno* head = NULL;
    RegistroExclusao* topo = NULL;

    int op, matricula;
    char nome[50];
    float nota;

    do {
        op = menu();

        switch (op) {
            case 1:
                printf("Matrícula: ");
                scanf("%d", &matricula);
                printf("Nome: ");
                scanf(" %[^\n]", nome);
                printf("Nota: ");
                scanf("%f", &nota);
                inserirInicio(&head, matricula, nome, nota);
                break;

            case 2:
                printf("Matrícula: ");
                scanf("%d", &matricula);
                printf("Nome: ");
                scanf(" %[^\n]", nome);
                printf("Nota: ");
                scanf("%f", &nota);
                inserirFim(&head, matricula, nome, nota);
                break;

            case 3:
                printf("Matrícula para remover: ");
                scanf("%d", &matricula);
                remover(&head, &topo, matricula);
                break;

            case 4:
                imprimirLista(head);
                break;

            case 5:
                printf("Matrícula para buscar: ");
                scanf("%d", &matricula);
                buscarMatricula(head, matricula);
                break;

            case 6:
                ordenarLista(&head);
                break;

            case 7:
                desfazerExclusao(&head, &topo);
                break;

            case 8:
                exibirTopoPilha(topo);
                break;

            case 9:
                imprimirListaInvertida(head);
                break;

            case 0:
                printf("\nSaindo...\
