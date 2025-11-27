#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
struct Territorio {
    char nome[50];      // Nome do território (até 49 caracteres + \0)
    char cor[20];       // Cor do exército dominante (até 19 caracteres + \0)
    int tropas;         // Número de tropas
};

int main() {
    // Vetor estático de 5 territórios
    struct Territorio territorios[5];
    
    // Leitura dos dados para cada território
    for (int i = 0; i < 5; i++) {
        printf("Digite os dados do território %d:\n", i + 1);
        
        // Leitura do nome usando fgets (permite espaços)
        printf("Nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        // Remover o '\n' deixado pelo fgets
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        
        // Leitura da cor usando fgets (permite espaços)
        printf("Cor do exército dominante: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        // Remover o '\n' deixado pelo fgets
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        
        // Leitura do número de tropas usando scanf
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        // Consumir o '\n' deixado pelo scanf para evitar problemas na próxima iteração
        getchar();  // Ou usar while(getchar() != '\n'); mas getchar() é suficiente aqui
    }
    
    // Exibição organizada do estado atual do mapa
    printf("\nEstado atual do mapa:\n");
    printf("=====================================\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Número de Tropas: %d\n", territorios[i].tropas);
        printf("-------------------------------------\n");
    }
    
    return 0;
}