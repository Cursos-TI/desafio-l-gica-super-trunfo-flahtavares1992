#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio [cite: 702, 1401]
// Estrutura para agrupar dados heterogêneos do território
typedef struct {
    char nome[30];      // Nome do território
    char cor[10];       // Cor do exército (dono)
    int tropas;         // Quantidade de tropas
} Territorio;

// Definição da struct Jogador (para gerenciar a missão)
typedef struct {
    char cor[10];
    char* missao;       // A missão será alocada dinamicamente [cite: 1388]
    int territorios_conquistados;
} Jogador;

// Vetor de strings com as missões estratégicas [cite: 1386]
char* missoes_estrategicas[] = {
    "Missão 1: Conquistar 3 territórios seguidos.",
    "Missão 2: Eliminar todas as tropas da cor VERMELHA.",
    "Missão 3: Dominar 8 territórios com pelo menos 2 tropas.",
    "Missão 4: Alcançar 10 territórios.",
    "Missão 5: Destruir o exército da cor AZUL."
};
const int TOTAL_MISSOES = 5;

// --- PROTÓTIPOS DAS FUNÇÕES (MODULARIZAÇÃO) ---
Territorio* alocar_mapa(int *tamanho);
void cadastrar_territorios(Territorio *mapa, int tamanho);
void exibir_mapa(Territorio *mapa, int tamanho); 
void atribuir_missao(char* destino, char* missoes[], int totalMissoes); 
int verificar_missao(Jogador *jogador, Territorio *mapa, int tamanho); 
void atacar(Territorio *atacante, Territorio *defensor); 
void liberar_memoria(Territorio *mapa, Jogador *j); 

// >>> NOVO PROTÓTIPO ADICIONADO PARA CORRIGIR O ERRO:
void exibir_missao(char* missao); // Função para exibir a missão (Passagem por Valor)
// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------

int main() {
    // Inicializa gerador de números aleatórios [cite: 1065, 1409]
    srand(time(NULL)); 

    int tamanho_mapa = 0;
    
    // Aloca a memória para o mapa (Nível Aventureiro)
    Territorio *mapa = alocar_mapa(&tamanho_mapa);

    if (mapa == NULL || tamanho_mapa <= 0) {
        printf("Erro ao alocar o mapa ou tamanho inválido.\n");
        return 1;
    }

    // Cadastra os territórios (Nível Novato/Aventureiro)
    cadastrar_territorios(mapa, tamanho_mapa);
    
    // Configuração do Jogador para a Missão (Simplificado para um jogador)
    Jogador jogador;
    strcpy(jogador.cor, "AZUL");
    jogador.territorios_conquistados = 0;
    
    // Aloca memória para a string de missão (Nível Mestre) [cite: 1388]
    jogador.missao = (char*)malloc(100 * sizeof(char)); 
    if (jogador.missao == NULL) {
        printf("Erro ao alocar memória para a missão.\n");
        liberar_memoria(mapa, &jogador);
        return 1;
    }

    // Atribui a missão ao jogador
    atribuir_missao(jogador.missao, missoes_estrategicas, TOTAL_MISSOES);
    exibir_missao(jogador.missao); // Passagem por valor (cópia do endereço)

    // --- SIMULAÇÃO DE ATAQUE E VERIFICAÇÃO DE MISSÃO ---
    printf("\n--- INÍCIO DA SIMULAÇÃO ---\n");
    // Exemplo: Ataque do Território 1 (índice 0) no Território 2 (índice 1)
    
    // Ataque 1
    atacar(&mapa[0], &mapa[1]);
    exibir_mapa(mapa, tamanho_mapa);
    
    // Verificação de missão após a ação
    if (verificar_missao(&jogador, mapa, tamanho_mapa)) {
        printf("\n+++ JOGADOR VENCEU! Missão cumprida! +++\n");
    } else {
        printf("\nMissão ainda não cumprida. Jogo continua...\n");
    }

    // Liberação da memória alocada dinamicamente
    liberar_memoria(mapa, &jogador); // [cite: 1052, 1406]
    return 0;
}

// --------------------------- IMPLEMENTAÇÕES DE FUNÇÕES -----------------------------------

// NÍVEL AVENTUREIRO: Alocação Dinâmica do Mapa
Territorio* alocar_mapa(int *tamanho) {
    int n;
    printf("Quantos territórios no mapa? ");
    scanf("%d", &n);
    
    if (n <= 0) return NULL;

    // Calloc: aloca e inicializa com 0 (limpa) [cite: 1045]
    Territorio* mapa = (Territorio*)calloc(n, sizeof(Territorio));
    
    if (mapa != NULL) {
        *tamanho = n; // Atualiza o tamanho através do ponteiro
    }
    return mapa;
}

// NÍVEL NOVATO/AVENTUREIRO: Cadastro
void cadastrar_territorios(Territorio *mapa, int tamanho) {
    printf("\n--- Cadastro de %d Territórios ---\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        printf("\nTerritório %d:\n", i + 1);
        
        // Acesso aos campos via ponteiro (*mapa + i) ou mapa[i].campo
        printf("Nome: ");
        scanf("%s", (mapa + i)->nome); 
        
        printf("Cor do Exército: ");
        scanf("%s", (mapa + i)->cor);

        printf("Número de Tropas: ");
        scanf("%d", &(mapa + i)->tropas);
    }
}

// NÍVEL NOVATO/AVENTUREIRO: Exibição
void exibir_mapa(Territorio *mapa, int tamanho) {
    printf("\n--- RELATÓRIO PÓS-AÇÃO ---\n");
    for (int i = 0; i < tamanho; i++) {
        // Exibição dos dados através do ponteiro
        printf("[%s] Dono: %s, Tropas: %d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// NÍVEL MESTRE: Atribuição de Missão
void atribuir_missao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    // Copia a string da missão sorteada para o destino alocado [cite: 1387]
    strcpy(destino, missoes[sorteio]); 
}

// NÍVEL MESTRE: Exibição de Missão (Passagem por Valor para exibição)
void exibir_missao(char* missao) {
    // Recebe uma cópia do endereço (char*) apenas para leitura [cite: 1396]
    printf("\n--- SUA MISSÃO É: %s ---\n", missao); 
}

// NÍVEL AVENTUREIRO/MESTRE: Lógica de Ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    // Uso de rand() para simular o dado (1 a 6) [cite: 1403]
    int dado_ataque = (rand() % 6) + 1;
    int dado_defesa = (rand() % 6) + 1;

    // Validação básica (Nível Mestre): evita ataque a próprio território [cite: 1410]
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Ataque inválido! Você não pode atacar seu próprio território (%s).\n", defensor->nome);
        return;
    }

    printf("\n=== SIMULAÇÃO DE BATALHA ===\n");
    printf("Atacante %s (%s) dado: %d\n", atacante->nome, atacante->cor, dado_ataque);
    printf("Defensor %s (%s) dado: %d\n", defensor->nome, defensor->cor, dado_defesa);

    if (dado_ataque > dado_defesa) {
        printf("-> %s VENCEU o ataque!\n", atacante->nome);
        
        // Atualização de dados via ponteiro [cite: 1047]
        strcpy(defensor->cor, atacante->cor);
        
        // Transfere metade das tropas [cite: 1060]
        int tropas_transferidas = atacante->tropas / 2;
        defensor->tropas = tropas_transferidas;
        atacante->tropas -= tropas_transferidas;

    } else {
        printf("-> %s PERDEU o ataque. O defensor manteve a posição.\n", atacante->nome);
        // Atacante perde uma tropa [cite: 1061]
        atacante->tropas--;
    }
}

// NÍVEL MESTRE: Verificação de Missão (Lógica simples inicial) [cite: 1389]
// A missão é passada por referência (ponteiros) para acessar os dados.
int verificar_missao(Jogador *jogador, Territorio *mapa, int tamanho) {
    // Lógica SIMPLES: Verifica se o jogador tem mais da metade dos territórios
    int contagem_territorios = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, jogador->cor) == 0) {
            contagem_territorios++;
        }
    }
    
    // Se conquistar mais que 50% dos territórios, considera missão cumprida
    if (contagem_territorios > (tamanho / 2)) {
        return 1; 
    }
    return 0; 
}

// NÍVEL AVENTUREIRO/MESTRE: Liberação de Memória
void liberar_memoria(Territorio *mapa, Jogador *j) {
    // Libera a memória alocada para a missão (Nível Mestre)
    if (j != NULL && j->missao != NULL) {
        free(j->missao);
        j->missao = NULL;
    }
    
    // Libera a memória do mapa (Nível Aventureiro) [cite: 1052]
    if (mapa != NULL) {
        free(mapa);
    }
    printf("\nRecursos de memória liberados com sucesso.\n");
}
