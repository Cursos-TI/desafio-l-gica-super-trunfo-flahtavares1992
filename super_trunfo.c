#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da capacidade máxima da mochila (lista estática)
#define MAX_ITENS 10

// 1. Criação da struct Item 
// Estrutura de dados heterogênea para representar um item no inventário.
typedef struct {
    char nome[30];      // Ex: Arma, Munição, Kit Médico
    char tipo[20];      // Ex: Fuzil, Granada, Cura
    int quantidade;     // Número de unidades do item
} Item;

// Variável global (ou ponteiro passado) para rastrear quantos itens estão na mochila.
int contador = 0;

// --- PROTÓTIPOS DAS FUNÇÕES OBRIGATÓRIAS [cite: 537] ---
void inserirItem(Item mochila[], int *contador);
void removerItem(Item mochila[], int *contador);
void listarItens(Item mochila[], int contador);
int buscarItem(Item mochila[], int contador, const char *nomeBusca);


// =================================================================
// MAIN FUNCTION - FLUXO DE EXECUÇÃO
// =================================================================
int main() {
    // 2. Criação do vetor de structs (Lista Estática) 
    Item mochila[MAX_ITENS];
    int opcao;
    
    printf("--- Sistema de Inventário (Nível Novato) ---\n");
    printf("Capacidade máxima: %d itens.\n", MAX_ITENS);

    do {
        printf("\n-----------------------------------------\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item por Nome\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &contador);
                break;
            case 2:
                removerItem(mochila, &contador);
                break;
            case 3:
                listarItens(mochila, contador);
                break;
            case 4: {
                char nomeBusca[30];
                printf("Digite o nome do item a buscar: ");
                scanf("%s", nomeBusca);
                
                int indice = buscarItem(mochila, contador, nomeBusca);
                if (indice != -1) {
                    printf("\n[RESULTADO DA BUSCA SEQUENCIAL]\n");
                    printf("Item encontrado no índice %d (Posição %d):\n", indice, indice + 1);
                    printf("Nome: %s | Tipo: %s | Qtd: %d\n", 
                        mochila[indice].nome, mochila[indice].tipo, mochila[indice].quantidade);
                } else {
                    printf("Item '%s' não encontrado no inventário.\n", nomeBusca);
                }
                break;
            }
            case 0:
                printf("Saindo do sistema de inventário. Boa sorte na ilha!\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}


// =================================================================
// IMPLEMENTAÇÕES DAS FUNÇÕES
// =================================================================

// FUNÇÃO 1: Inserir Item [cite: 497, 504]
void inserirItem(Item mochila[], int *contador) {
    if (*contador >= MAX_ITENS) {
        printf("\nMochila Cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    
    printf("\n[CADASTRANDO NOVO ITEM]\n");
    
    printf("Nome do Item: ");
    scanf("%s", mochila[*contador].nome);
    
    printf("Tipo (arma/cura/ferramenta): ");
    scanf("%s", mochila[*contador].tipo);
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*contador].quantidade);
    
    (*contador)++; // Incrementa o número de itens na mochila
    printf("Item inserido com sucesso na posição %d.\n", *contador);
}

// FUNÇÃO 2: Remover Item [cite: 498, 505]
void removerItem(Item mochila[], int *contador) {
    if (*contador == 0) {
        printf("\nMochila vazia! Nada para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeRemover);

    // 1. Busca o item a ser removido (usando busca sequencial)
    int indiceRemover = buscarItem(mochila, *contador, nomeRemover);

    if (indiceRemover != -1) {
        // 2. Se encontrado, remove o item [cite: 336]
        // Desloca todos os elementos seguintes uma posição para trás para "tapar" o espaço [cite: 340]
        for (int i = indiceRemover; i < *contador - 1; i++) {
            mochila[i] = mochila[i + 1]; // Move o próximo item para a posição atual
        }
        
        (*contador)--; // Decrementa o número de itens
        printf("Item '%s' removido com sucesso.\n", nomeRemover);
    } else {
        printf("Item '%s' não encontrado na mochila.\n", nomeRemover);
    }
}

// FUNÇÃO 3: Listar Itens [cite: 499, 506]
void listarItens(Item mochila[], int contador) {
    printf("\n--- INVENTÁRIO ATUAL (Total: %d itens) ---\n", contador);
    if (contador == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < contador; i++) {
        // Percorrendo o vetor e exibindo os dados [cite: 539]
        printf("%d. [Nome: %s | Tipo: %s | Qtd: %d]\n", 
            i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// FUNÇÃO 4: Buscar Item (Busca Sequencial/Linear) [cite: 507, 525, 398]
// Retorna o índice do item ou -1 se não encontrado.
int buscarItem(Item mochila[], int contador, const char *nomeBusca) {
    // A busca linear examina, um por um, todos os elementos da estrutura [cite: 399]
    for (int i = 0; i < contador; i++) {
        // Compara a string do nome do item com o nome buscado
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i; // Item encontrado
        }
    }
    return -1; // Item não encontrado
}
