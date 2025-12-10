#include <stdio.h>
#include <string.h>

// Estrutura que representa uma carta do Super Trunfo
typedef struct {
    char estado[3];           // Ex: "SP", "RJ"
    char codigo[4];           // Ex: "A01"
    char cidade[50];          // Nome da cidade
    int populacao;            // Número de habitantes
    float area;               // Área em km²
    float pib;                // PIB em bilhões
    int pontos_turisticos;    // Quantidade de pontos turísticos
} Carta;

// Função para calcular densidade populacional (hab/km²)
float densidade_populacional(Carta c) {
    return (c.area > 0) ? c.populacao / c.area : 0.0;
}

// Função para calcular PIB per capita
float pib_per_capita(Carta c) {
    return (c.populacao > 0) ? (c.pib * 1000000000) / c.populacao : 0.0;
}

// Função para obter o valor de um atributo específico de uma carta
float get_valor_atributo(Carta c, int attr) {
    switch (attr) {
        case 1: return c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return densidade_populacional(c);
        case 5: return pib_per_capita(c);
        default: return 0.0;
    }
}

// Função para obter o nome de um atributo
const char* get_nome_atributo(int attr) {
    switch (attr) {
        case 1: return "Populacao";
        case 2: return "Area";
        case 3: return "PIB";
        case 4: return "Densidade Populacional";
        case 5: return "PIB per capita";
        default: return "Desconhecido";
    }
}

// Função para exibir o menu de atributos, excluindo o já escolhido
void exibir_menu_atributos(int excluido) {
    printf("Escolha um atributo:\n");
    if (1 != excluido) printf("1 - Populacao\n");
    if (2 != excluido) printf("2 - Area\n");
    if (3 != excluido) printf("3 - PIB\n");
    if (4 != excluido) printf("4 - Densidade Populacional\n");
    if (5 != excluido) printf("5 - PIB per capita\n");
    printf("Sua escolha: ");
}

// Função para determinar o vencedor de um único atributo (usando ternário)
int determinar_vencedor_attr(float v1, float v2, int eh_densidade) {
    return eh_densidade ? (v1 < v2 ? 1 : 2) : (v1 > v2 ? 1 : 2);
}

int main() {
    // === CADASTRO DAS DUAS CARTAS (pré-definidas) ===
    Carta carta1 = {"SP", "A01", "São Paulo", 12325281, 1521.0, 699.2, 42};
    Carta carta2 = {"RJ", "B02", "Rio de Janeiro", 6775561, 1182.3, 350.0, 58};

    // === EXIBIÇÃO INICIAL DAS CARTAS ===
    printf("========================================\n");
    printf("       SUPER TRUNFO - DESAFIO FINAL\n");
    printf("========================================\n\n");

    printf("Carta 1: %s (%s) - %s\n", carta1.cidade, carta1.estado, carta1.codigo);
    printf("  Populacao: %d | Area: %.1f km² | PIB: %.1f bi | Pontos turisticos: %d\n\n", 
           carta1.populacao, carta1.area, carta1.pib, carta1.pontos_turisticos);

    printf("Carta 2: %s (%s) - %s\n", carta2.cidade, carta2.estado, carta2.codigo);
    printf("  Populacao: %d | Area: %.1f km² | PIB: %.1f bi | Pontos turisticos: %d\n\n", 
           carta2.populacao, carta2.area, carta2.pib, carta2.pontos_turisticos);

    // === MENU INTERATIVO PARA PRIMEIRO ATRIBUTO ===
    int attr1 = 0;
    while (attr1 < 1 || attr1 > 5) {
        exibir_menu_atributos(0);  // Nenhum excluído ainda
        scanf("%d", &attr1);
        switch (attr1) {
            case 1: case 2: case 3: case 4: case 5: break;  // Válidos
            default: printf("Opcao invalida! Tente novamente.\n\n"); break;
        }
    }

    // === MENU DINÂMICO PARA SEGUNDO ATRIBUTO (exclui o primeiro) ===
    int attr2 = 0;
    while (attr2 < 1 || attr2 > 5 || attr2 == attr1) {
        exibir_menu_atributos(attr1);  // Exclui o attr1
        scanf("%d", &attr2);
        switch (attr2) {
            case 1: case 2: case 3: case 4: case 5:
                if (attr2 == attr1) {
                    printf("Voce ja escolheu esse atributo! Escolha outro.\n\n");
                    attr2 = 0;
                }
                break;
            default: printf("Opcao invalida! Tente novamente.\n\n"); attr2 = 0; break;
        }
    }

    // === OBTÉM VALORES DOS ATRIBUTOS ===
    float val1_attr1 = get_valor_atributo(carta1, attr1);
    float val2_attr1 = get_valor_atributo(carta2, attr1);
    float val1_attr2 = get_valor_atributo(carta1, attr2);
    float val2_attr2 = get_valor_atributo(carta2, attr2);

    // === CALCULA SOMAS ===
    float soma1 = val1_attr1 + val1_attr2;
    float soma2 = val2_attr1 + val2_attr2;

    // === EXIBE COMPARAÇÃO INDIVIDUAL ===
    printf("\n----------------------------------------\n");
    printf("COMPARACAO INDIVIDUAL\n");
    printf("----------------------------------------\n");

    // Atributo 1
    int eh_densidade1 = (attr1 == 4);
    int vencedor_attr1 = (val1_attr1 == val2_attr1) ? 0 : determinar_vencedor_attr(val1_attr1, val2_attr1, eh_densidade1);
    printf("Atributo 1: %s\n", get_nome_atributo(attr1));
    printf("Carta 1 - %s (%s): %.2f\n", carta1.cidade, carta1.estado, val1_attr1);
    printf("Carta 2 - %s (%s): %.2f\n", carta2.cidade, carta2.estado, val2_attr1);
    if (vencedor_attr1 == 0) printf("Resultado: Empate!\n\n");
    else printf("Resultado: Carta %d (%s) venceu esse atributo!\n\n", vencedor_attr1, vencedor_attr1 == 1 ? carta1.cidade : carta2.cidade);

    // Atributo 2
    int eh_densidade2 = (attr2 == 4);
    int vencedor_attr2 = (val1_attr2 == val2_attr2) ? 0 : determinar_vencedor_attr(val1_attr2, val2_attr2, eh_densidade2);
    printf("Atributo 2: %s\n", get_nome_atributo(attr2));
    printf("Carta 1 - %s (%s): %.2f\n", carta1.cidade, carta1.estado, val1_attr2);
    printf("Carta 2 - %s (%s): %.2f\n", carta2.cidade, carta2.estado, val2_attr2);
    if (vencedor_attr2 == 0) printf("Resultado: Empate!\n\n");
    else printf("Resultado: Carta %d (%s) venceu esse atributo!\n\n", vencedor_attr2, vencedor_attr2 == 1 ? carta1.cidade : carta2.cidade);

    // === EXIBE RESULTADO FINAL PELA SOMA ===
    printf("----------------------------------------\n");
    printf("RESULTADO FINAL (SOMA DOS ATRIBUTOS)\n");
    printf("----------------------------------------\n");
    printf("Soma Carta 1 (%s): %.2f\n", carta1.cidade, soma1);
    printf("Soma Carta 2 (%s): %.2f\n\n", carta2.cidade, soma2);

    if (soma1 == soma2) {
        printf("Resultado: EMPATE! As somas sao iguais.\n");
    } else if (soma1 > soma2) {
        printf("Resultado: Carta 1 (%s) venceu a rodada!\n", carta1.cidade);
    } else {
        printf("Resultado: Carta 2 (%s) venceu a rodada!\n", carta2.cidade);
    }

    printf("========================================\n");
    return 0;
}
