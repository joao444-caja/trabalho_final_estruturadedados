#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    float nota;
} Aluno;

typedef struct NoAluno {
    Aluno dados;
    struct NoAluno *prev;
    struct NoAluno *next;
} NoAluno;

typedef struct NoUndo {
    Aluno registro_excluido;
    struct NoUndo *next;
} NoUndo;

NoAluno *lista_head = NULL;
NoUndo *pilha_top = NULL;

int is_empty_pilha() {
    return (pilha_top == NULL);
}

Aluno top_pilha() {
    if (is_empty_pilha()) {
        Aluno vazio = {0, "Pilha Vazia", 0.0};
        return vazio;
    }
    return pilha_top->registro_excluido;
}

void push_operacao(Aluno aluno) {
    NoUndo *novo_no = (NoUndo *)malloc(sizeof(NoUndo));
    if (novo_no == NULL) {
        printf("ERRO: Falha na alocacao de memoria para o UNDO.\n");
        return;
    }
    novo_no->registro_excluido = aluno;
    novo_no->next = pilha_top;
    pilha_top = novo_no;
    printf("[UNDO] Operacao de exclusao registrada.\n");
}


Aluno pop_operacao() {
    if (is_empty_pilha()) {
        Aluno vazio = {0, "", 0.0};
        return vazio;
    }
    NoUndo *temp = pilha_top;
    Aluno aluno_undo = temp->registro_excluido;
    pilha_top = pilha_top->next;
    free(temp); 
    return aluno_undo;
}

Aluno ler_dados_aluno() {
    Aluno novo;
    printf("Digite o ID do aluno (inteiro): ");
    scanf("%d%*c", &novo.id); 
    printf("Digite o NOME do aluno: ");
    fgets(novo.nome, 50, stdin); 
    novo.nome[strcspn(novo.nome, "\n")] = 0;
    printf("Digite a NOTA do aluno: ");
    scanf("%f%*c", &novo.nota);
    return novo;
}

void inserir_aluno(Aluno novo_aluno) {
    NoAluno *novo_no = (NoAluno *)malloc(sizeof(NoAluno));
    if (novo_no == NULL) {
        printf("ERRO: Falha na alocacao de memoria para o aluno.\n");
        return;
    }
    novo_no->dados = novo_aluno;
    novo_no->next = NULL;

    if (lista_head == NULL) {
        novo_no->prev = NULL;
        lista_head = novo_no;
        printf("Aluno %s (ID %d) inserido como o primeiro.\n", novo_aluno.nome, novo_aluno.id);
        return;
    }

    NoAluno *atual = lista_head;
    while (atual->next != NULL) {
        atual = atual->next;
    }
    atual->next = novo_no;
    novo_no->prev = atual;
    printf("Aluno %s (ID %d) inserido no final da lista.\n", novo_aluno.nome, novo_aluno.id);
}


void remover_aluno(int id_busca) {
    NoAluno *atual = lista_head;
    while (atual != NULL && atual->dados.id != id_busca) {
        atual = atual->next;
    }

    if (atual != NULL) {
    
        push_operacao(atual->dados); 
        
        if (atual->prev != NULL) {
            atual->prev->next = atual->next;
        } else {
            lista_head = atual->next; 
        }
        if (atual->next != NULL) {
            atual->next->prev = atual->prev;
        }
        
        free(atual); 
        printf("Aluno ID %d removido com sucesso.\n", id_busca);
    } else {
        printf("ERRO: Aluno ID %d nao encontrado.\n", id_busca);
    }
}

void desfazer_exclusao() {
    Aluno aluno_recuperado = pop_operacao();
    
    if (aluno_recuperado.id == 0 && strcmp(aluno_recuperado.nome, "") == 0) {
        printf("Nao ha operacoes de exclusao para desfazer.\n");
        return;
    }

    NoAluno *novo_no = (NoAluno *)malloc(sizeof(NoAluno));
    if (novo_no == NULL) {
         printf("ERRO: Falha na alocacao de memoria ao desfazer.\n");
         return;
    }
    
    novo_no->dados = aluno_recuperado;
    novo_no->prev = NULL;
    novo_no->next = lista_head;

    if (lista_head != NULL) {
        lista_head->prev = novo_no;
    }
    lista_head = novo_no;
    
    printf("Exclusao do aluno ID %d (Nome: %s) desfeita. Registro reinserido.\n", aluno_recuperado.id, aluno_recuperado.nome);
}

void imprimir_lista() {
    if (lista_head == NULL) {
        printf("A lista de alunos esta vazia.\n");
        return;
    }
    printf("\n--- LISTA DE ALUNOS ---\n");
    NoAluno *atual = lista_head;
    int i = 1;
    while (atual != NULL) {
        printf("%d. ID: %d | Nome: %s | Nota: %.2f\n", i++, atual->dados.id, atual->dados.nome, atual->dados.nota);
        atual = atual->next;
    }
    printf("-------------------------\n");
}

void buscar_aluno(int id_busca) {
    NoAluno *atual = lista_head;
    while (atual != NULL) {
        if (atual->dados.id == id_busca) {
            printf("\n--- ALUNO ENCONTRADO ---\n");
            printf("ID: %d | Nome: %s | Nota: %.2f\n", atual->dados.id, atual->dados.nome, atual->dados.nota);
            printf("------------------------\n");
            return;
        }
        atual = atual->next;
    }
    printf("Aluno ID %d nao encontrado na lista.\n", id_busca);
}

void insertion_sort() {
    if (lista_head == NULL || lista_head->next == NULL) {
        printf("Lista ja esta ordenada ou vazia.\n");
        return;
    }

    NoAluno *sorted = NULL; 
    NoAluno *current = lista_head; 

    while (current != NULL) {
        NoAluno *next = current->next;
        
        
        if (current->prev != NULL) {
            current->prev->next = current->next;
        }
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
        current->prev = NULL;
        current->next = NULL;

        
        if (sorted == NULL || current->dados.id < sorted->dados.id) {
            
            current->next = sorted;
            if (sorted != NULL) {
                sorted->prev = current;
            }
            sorted = current;
        } else {
            
            NoAluno *temp = sorted;
            while (temp->next != NULL && temp->next->dados.id < current->dados.id) {
                temp = temp->next;
            }
            
            current->next = temp->next;
            if (temp->next != NULL) {
                temp->next->prev = current;
            }
            temp->next = current;
            current->prev = temp;
        }

        current = next; 
    }
    lista_head = sorted; 
    printf("Lista ordenada por ID com sucesso (Insertion Sort).\n");
}

void free_lista() {
    NoAluno *current = lista_head;
    NoAluno *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    lista_head = NULL;
}


void free_pilha() {
    NoUndo *current = pilha_top;
    NoUndo *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    pilha_top = NULL;
}

int main() {
    int opcao;
    int id_busca;

    do {
        printf("\n--- MENU DE CADASTRO DE ALUNOS (ED) ---\n");
        printf("1. Inserir Novo Aluno\n");
        printf("2. Remover Aluno (Com Undo)\n");
        printf("3. Buscar Aluno por ID\n");
        printf("4. Imprimir Lista de Alunos\n");
        printf("5. Ordenar Lista (Insertion Sort)\n");
        printf("6. Desfazer Ultima Exclusao (Undo)\n");
        printf("7. Checar Topo da Pilha (DEBUG)\n"); 
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d%*c", &opcao) != 1) { 
             printf("Entrada invalida. Digite um numero de 0 a 7.\n");
             opcao = -1;
             int c;
             while ((c = getchar()) != '\n' && c != EOF); 
        }

        switch(opcao) {
            case 1: 
                inserir_aluno(ler_dados_aluno());
                break;
            case 2:
                printf("Digite o ID do aluno a ser removido: ");
                scanf("%d%*c", &id_busca);
                remover_aluno(id_busca);
                break;
            case 3:
                printf("Digite o ID do aluno para busca: ");
                scanf("%d%*c", &id_busca);
                buscar_aluno(id_busca);
                break;
            case 4:
                imprimir_lista();
                break;
            case 5:
                insertion_sort();
                break;
            case 6: 
                desfazer_exclusao();
                break;
            case 7: 
                if(!is_empty_pilha()) {
                    Aluno topo = top_pilha();
                    printf("[TOPO DA PILHA] Ultimo aluno excluido: %s (ID %d).\n", topo.nome, topo.id);
                } else {
                    printf("[TOPO DA PILHA] A pilha de UNDO esta vazia.\n");
                }
                break;
            case 0:
                printf("Liberando memoria e encerrando o programa...\n");
                free_lista();
                free_pilha();
                break;
            default:
                if(opcao != -1) {
                    printf("Opcao invalida. Tente novamente.\n");
                }
                break;
        }
    } while (opcao != 0);
    
    return 0;
}