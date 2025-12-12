# 🚀 Projeto Final - Estrutura de Dados: Sistema de Gerenciamento de Alunos

Este projeto consiste na implementação de um sistema de gerenciamento de cadastros, demonstrando o uso e integração de estruturas de dados dinâmicas fundamentais. Foi desenvolvido como requisito para a disciplina de Estrutura de Dados da UNOCHAPECÓ.

---

### 📋 Integrantes do Grupo

| Nome Completo | Função Principal |
| :--- | :--- |
| **João Ricardo Matielo** | Desenvolvedor Principal |
| **Augusto Merigo Battisti** | Desenvolvedor |
| **João Gabriel Kerckhoff dos Santos** | Desenvolvedor |
| **Erick Gabriel da Cruz** | Desenvolvedor |

---

### 💡 Visão Geral e Requisitos Atendidos

O sistema implementa o gerenciamento de registros de alunos utilizando a integração das seguintes estruturas de dados dinâmicas:

1.  **Estrutura Principal:** Lista Duplamente Encadeada (LDE).
    * **Vantagem:** Permite a travessia nos dois sentidos e facilita a remoção de elementos.
2.  **Estrutura Auxiliar:** Pilha (Stack).
    * **Uso:** Gerencia as operações de exclusão para permitir a funcionalidade de **`Undo` (Desfazer)**, seguindo a lógica LIFO (Last-In, First-Out).
3.  **Algoritmo de Ordenação:** Insertion Sort.
    * **Aplicação:** Implementado para reordenar a LDE diretamente, manipulando os ponteiros dos nós com base no ID do Aluno.

---

### ⚙️ Detalhamento das Funções

O código é estruturado em C e oferece as seguintes funcionalidades através de um menu interativo:

#### 1. Funções da Lista Duplamente Encadeada (LDE)
| Função | Descrição | Requisito (PDF) |
| :--- | :--- | :--- |
| `inserir_aluno()` | Adiciona um novo registro ao final da lista. | Inserção de elementos |
| `remover_aluno()` | Remove um registro por ID. O registro é enviado para a Pilha de `Undo`. | Remoção de elementos |
| `buscar_aluno()` | Localiza e exibe o registro de um aluno pelo seu ID. | Busca de elementos |
| `imprimir_lista()` | Percorre e exibe todos os elementos em ordem. | Impressão dos elementos |

#### 2. Funções da Pilha (Controle de Undo)
| Função | Descrição | Requisito (PDF) |
| :--- | :--- | :--- |
| `push_operacao()` | Insere o aluno removido no topo da pilha. | `push` |
| `pop_operacao()` |
