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
    if (c.area > 0) {
        return c.populacao / c.area;
    }
    return 0.0;
}

// Função para calcular PIB per capita
float pib_per_capita(Carta c) {
    if (c.populacao > 0) {
        return (c.pib * 1000000000) / c.populacao;  // Converte PIB para reais e divide
    }
    return 0.0;
}

int main() {
    // === CADASTRO DAS DUAS CARTAS (pré-definidas no código) ===
    Carta carta1 = {"SP", "A01", "São Paulo", 12325281, 1521.0, 699.2, 42};
    Carta carta2 = {"RJ", "B02", "Rio de Janeiro", 6775561, 1182.3, 350.0, 58};

    // === EXIBIÇÃO DAS INFORMAÇÕES DAS CARTAS ===
    printf("========================================\n");
    printf("       SUPER TRUNFO - COMPARACAO\n");
    printf("========================================\n\n");

    printf("Carta 1: %s (%s) - %s\n", carta1.cidade, carta1.estado, carta1.codigo);
    printf("  Populacao: %d habitantes\n", carta1.populacao);
    printf("  Area: %.1f km²\n", carta1.area);
    printf("  PIB: R$ %.1f bilhões\n", carta1.pib);
    printf("  Pontos turisticos: %d\n", carta1.pontos_turisticos);
    printf("  Densidade populacional: %.2f hab/km²\n", densidade_populacional(carta1));
    printf("  PIB per capita: R$ %.2f\n\n", pib_per_capita(carta1));

    printf("Carta 2: %s (%s) - %s\n", carta2.cidade, carta2.estado, carta2.codigo);
    printf("  Populacao: %d habitantes\n", carta2.populacao);
    printf("  Area: %.1f km²\n", carta2.area);
    printf("  PIB: R$ %.1f bilhões\n", carta2.pib);
    printf("  Pontos turisticos: %d\n", carta2.pontos_turisticos);
    printf("  Densidade populacional: %.2f hab/km²\n", densidade_populacional(carta2));
    printf("  PIB per capita: R$ %.2f\n\n", pib_per_capita(carta2));

    // === ATRIBUTO ESCOLHIDO PARA COMPARAÇÃO (mude aqui se quiser testar outro) ===
    int atributo = 4;  
    // 1 = População | 2 = Área | 3 = PIB | 4 = Densidade Populacional | 5 = PIB per capita

    float valor1, valor2;
    char nome_atributo[30] = "";
    int menor_vence = 0;  // 1 se o menor valor ganha (só densidade)

    // === DEFINIÇÃO DO ATRIBUTO E CÁLCULO DOS VALORES ===
    if (atributo == 1) {
        strcpy(nome_atributo, "Populacao");
        valor1 = carta1.populacao;
        valor2 = carta2.populacao;
    }
    else if (atributo == 2) {
        strcpy(nome_atributo, "Area");
        valor1 = carta1.area;
        valor2 = carta2.area;
    }
    else if (atributo == 3) {
        strcpy(nome_atributo, "PIB");
        valor1 = carta1.pib;
        valor2 = carta2.pib;
    }
    else if (atributo == 4) {
        strcpy(nome_atributo, "Densidade Populacional");
        valor1 = densidade_populacional(carta1);
        valor2 = densidade_populacional(carta2);
        menor_vence = 1;  // Quem tem MENOR densidade vence!
    }
    else if (atributo == 5) {
        strcpy(nome_atributo, "PIB per capita");
        valor1 = pib_per_capita(carta1);
        valor2 = pib_per_capita(carta2);
    }

    // === EXIBE A COMPARAÇÃO ===
    printf("----------------------------------------\n");
    printf("COMPARACAO DE CARTAS (Atributo: %s)\n", nome_atributo);
    printf("----------------------------------------\n");
    printf("Carta 1 - %s (%s): %.2f\n", carta1.cidade, carta1.estado, valor1);
    printf("Carta 2 - %s (%s): %.2f\n\n", carta2.cidade, carta2.estado, valor2);

    // === DETERMINA O VENCEDOR ===
    if (valor1 == valor2) {
        printf("Resultado: EMPATE! As duas cartas tem o mesmo valor.\n");
    }
    else if (menor_vence) {
        // Densidade populacional: menor ganha
        if (valor1 < valor2) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.cidade);
        } else {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.cidade);
        }
    }
    else {
        // Todos os outros: maior ganha
        if (valor1 > valor2) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.cidade);
        } else {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.cidade);
        }
    }

    printf("========================================\n");
    return 0;
}
