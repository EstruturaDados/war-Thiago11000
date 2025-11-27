#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
struct Territorio {
    char nome[50];
    char cor[20];
    int tropas;
};

// Constantes
const int NUM_TERRITORIOS = 5;
const int MAX_DADOS_ATAQUE = 3;
const int MAX_DADOS_DEFESA = 2;

// Protótipos das funções
void inicializarTerritorios(struct Territorio** territorios);
void exibirMapa(const struct Territorio* territorios);
void simularAtaque(struct Territorio* territorios);
int verificarMissoes(const struct Territorio* territorios);
void menuPrincipal(struct Territorio* territorios);

int main() {
    // Alocação dinâmica com calloc
    struct Territorio* territorios = (struct Territorio*) calloc(NUM_TERRITORIOS, sizeof(struct Territorio));
    if (territorios == NULL) {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    // Inicializar srand para números aleatórios
    srand(time(NULL));

    // Inicializar territórios automaticamente
    inicializarTerritorios(&territorios);

    // Menu principal
    menuPrincipal(territorios);

    // Liberar memória
    free(territorios);
    return 0;
}

// Função para inicializar territórios automaticamente
void inicializarTerritorios(struct Territorio** territorios) {
    // Dados iniciais fixos (exemplo)
    strcpy((*territorios)[0].nome, "Europa");
    strcpy((*territorios)[0].cor, "Azul");
    (*territorios)[0].tropas = 5;

    strcpy((*territorios)[1].nome, "Ásia");
    strcpy((*territorios)[1].cor, "Verde");
    (*territorios)[1].tropas = 4;

    strcpy((*territorios)[2].nome, "América");
    strcpy((*territorios)[2].cor, "Vermelho");
    (*territorios)[2].tropas = 3;

    strcpy((*territorios)[3].nome, "África");
    strcpy((*territorios)[3].cor, "Amarelo");
    (*territorios)[3].tropas = 2;

    strcpy((*territorios)[4].nome, "Oceania");
    strcpy((*territorios)[4].cor, "Roxo");
    (*territorios)[4].tropas = 1;
}

// Função para exibir o mapa
void exibirMapa(const struct Territorio* territorios) {
    printf("\nEstado atual do mapa:\n");
    printf("=====================================\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território %d: %s\n", i + 1, territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Número de Tropas: %d\n", territorios[i].tropas);
        printf("-------------------------------------\n");
    }
}

// Função para simular ataque
void simularAtaque(struct Territorio* territorios) {
    int atacante, defensor;
    printf("Escolha o território atacante (1-5): ");
    scanf("%d", &atacante);
    atacante--;  // Ajustar para índice 0-based
    if (atacante < 0 || atacante >= NUM_TERRITORIOS || territorios[atacante].tropas < 2) {
        printf("Território inválido ou sem tropas suficientes para atacar.\n");
        return;
    }

    printf("Escolha o território defensor (1-5, diferente do atacante): ");
    scanf("%d", &defensor);
    defensor--;  // Ajustar para índice 0-based
    if (defensor < 0 || defensor >= NUM_TERRITORIOS || defensor == atacante) {
        printf("Território inválido.\n");
        return;
    }

    // Rolar dados
    int dadosAtaque[MAX_DADOS_ATAQUE];
    int numDadosAtaque = (territorios[atacante].tropas > MAX_DADOS_ATAQUE) ? MAX_DADOS_ATAQUE : territorios[atacante].tropas - 1;
    for (int i = 0; i < numDadosAtaque; i++) {
        dadosAtaque[i] = rand() % 6 + 1;
    }

    int dadosDefesa[MAX_DADOS_DEFESA];
    int numDadosDefesa = (territorios[defensor].tropas >= MAX_DADOS_DEFESA) ? MAX_DADOS_DEFESA : territorios[defensor].tropas;
    for (int i = 0; i < numDadosDefesa; i++) {
        dadosDefesa[i] = rand() % 6 + 1;
    }

    // Ordenar dados (maior para menor) - simples bubble sort
    for (int i = 0; i < numDadosAtaque - 1; i++) {
        for (int j = 0; j < numDadosAtaque - i - 1; j++) {
            if (dadosAtaque[j] < dadosAtaque[j + 1]) {
                int temp = dadosAtaque[j];
                dadosAtaque[j] = dadosAtaque[j + 1];
                dadosAtaque[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < numDadosDefesa - 1; i++) {
        for (int j = 0; j < numDadosDefesa - i - 1; j++) {
            if (dadosDefesa[j] < dadosDefesa[j + 1]) {
                int temp = dadosDefesa[j];
                dadosDefesa[j] = dadosDefesa[j + 1];
                dadosDefesa[j + 1] = temp;
            }
        }
    }

    // Comparar dados
    int vitoriasAtacante = 0;
    int comparacoes = (numDadosAtaque < numDadosDefesa) ? numDadosAtaque : numDadosDefesa;
    for (int i = 0; i < comparacoes; i++) {
        if (dadosAtaque[i] > dadosDefesa[i]) {
            vitoriasAtacante++;
        }
    }

    // Exibir resultados
    printf("Dados do atacante (%s): ", territorios[atacante].nome);
    for (int i = 0; i < numDadosAtaque; i++) printf("%d ", dadosAtaque[i]);
    printf("\nDados do defensor (%s): ", territorios[defensor].nome);
    for (int i = 0; i < numDadosDefesa; i++) printf("%d ", dadosDefesa[i]);
    printf("\n");

    // Aplicar lógica
    if (vitoriasAtacante > comparacoes / 2) {  // Mais vitórias que derrotas
        territorios[defensor].tropas--;
        printf("Atacante venceu! Defensor perdeu 1 tropa.\n");
        if (territorios[defensor].tropas == 0) {
            strcpy(territorios[defensor].cor, territorios[atacante].cor);
            printf("Território conquistado! Cor mudou para %s.\n", territorios[atacante].cor);
        }
    } else {
        printf("Empate ou defesa venceu. Nenhuma mudança.\n");
    }
}

// Função para verificar missões
int verificarMissoes(const struct Territorio* territorios) {
    // Missão 1: Destruir exército Verde (todas as tropas verdes = 0)
    int tropasVerdes = 0;
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (strcmp(territorios[i].cor, "Verde") == 0) {
            tropasVerdes += territorios[i].tropas;
        }
    }
    int missao1 = (tropasVerdes == 0);

    // Missão 2: Conquistar 3 territórios (assumindo jogador controla cor do território 1)
    int conquistados = 0;
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (strcmp(territorios[i].cor, territorios[0].cor) == 0) {
            conquistados++;
        }
    }
    int missao2 = (conquistados >= 3);

    printf("\nVerificação de Missões:\n");
    printf("1. Destruir exército Verde: %s\n", missao1 ? "COMPLETA" : "PENDENTE");
    printf("2. Conquistar 3 territórios: %s (%d conquistados)\n", missao2 ? "COMPLETA" : "PENDENTE", conquistados);

    if (missao1 && missao2) {
        printf("PARABÉNS! Todas as missões foram completadas. Vitória!\n");
        return 1;  // Vitória
    }
    return 0;  // Não venceu ainda
}

// Função do menu principal
void menuPrincipal(struct Territorio* territorios) {
    int opcao;
    do {
        printf("\nMenu Principal:\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missões\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                simularAtaque(territorios);
                break;
            case 2:
                exibirMapa(territorios);
                verificarMissoes(territorios);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}
