#include <stdio.h>
#include <string.h>

// Estrutura para representar uma carta do Super Trunfo
typedef struct {
    char estado[3];           // Ex: "SP"
    char codigo[4];           // Ex: "A01"
    char cidade[50];          // Nome da cidade
    int populacao;            // Em habitantes
    float area;               // Em km²
    float pib;                // Em bilhões ou milhões (não importa a unidade, só comparação)
    int pontos_turisticos;    // Quantidade
} Carta;

// Função para calcular densidade populacional (hab/km²)
float calcular_densidade(Carta c) {
    if (c.area > 0) {
        return c.populacao / c.area;
    }
    return 0;
}

// Função para calcular PIB per capita
float calcular_pib_per_capita(Carta c) {
    if (c.populacao > 0) {
        return c.pib / c.populacao * 1000000;  // ajusta para valor legível
    }
    return 0;
}

int main() {
    // === CADASTRO DAS DUAS CARTAS (pré-definidas no código) ===
    Carta carta1 = {"SP", "A01", "São Paulo", 12325281, 1521.0, 699.2, 42};
    Carta carta2 = {"RJ", "B02", "Rio de Janeiro", 6775561, 1182.3, 350.0, 58};

    // === EXIBIÇÃO DAS CARTAS ===
    printf("======================================\n");
    printf("       SUPER TRUNFO - COMPARACAO       \n");
    printf("======================================\n\n");

    printf("CARTA 1: %s (%s) - %s\n", carta1.cidade, carta1.estado, carta1.codigo);
    printf("   Populacao: %d | Area: %.1f km² | PIB: %.1f bi | Pontos turisticos: %d\n\n", 
           carta1.populacao, carta1.area, carta1.pib, carta1.pontos_turisticos);

    printf("CARTA 2: %s (%s) - %s\n", carta2.cidade, carta2.estado, carta2.codigo);
    printf("   Populacao: %d | Area: %.1f km² | PIB: %.1f bi | Pontos turisticos: %d\n\n", 
           carta2.populacao, carta2.area, carta2.pib, carta2.pontos_turisticos);

    // === ESCOLHA DO ATRIBUTO PARA COMPARAÇÃO (definido no código) ===
    // Mude aqui para testar outros atributos!
    int atributo_escolhido = 4;  
    // 1 = População | 2 = Área | 3 = PIB | 4 = Densidade Populacional | 5 = PIB per capita

    float valor1, valor2;
    char atributo_nome[30] = "";
    int maior_vence = 1;  // 1 = maior ganha | 0 = menor ganha (só para densidade)

    // === CÁLCULO E DEFINIÇÃO DO ATRIBUTO ESCOLHIDO ===
    if (atributo_escolhido == 1) {
        strcpy(atributo_nome, "Populacao");
        valor1 = carta1.populacao;
        valor2 = carta2.populacao;
    }
    else if (atributo_escolhido == 2) {
        strcpy(atributo_nome, "Area");
        valor1 = carta1.area;
        valor2 = carta2.area;
    }
    else if (atributo_escolhido == 3) {
        strcpy(atributo_nome, "PIB");
        valor1 = carta1.pib;
        valor2 = carta2.pib;
    }
    else if (atributo_escolhido == 4) {
        strcpy(atributo_nome, "Densidade Populacional");
        valor1 = calcular_densidade(carta1);
        valor2 = calcular_densidade(carta2);
        maior_vence = 0;  // Quem tem MENOR densidade vence!
    }
    else if (atributo_escolhido == 5) {
        strcpy(atributo_nome, "PIB per capita");
        valor1 = calcular_pib_per_capita(carta1);
        valor2 = calcular_pib_per_capita(carta2);
    }

    // === EXIBE A COMPARAÇÃO ===
    printf("----------------------------------------\n");
    printf(" Comparacao de cartas (Atributo: %s)\n", atributo_nome);
    printf("----------------------------------------\n");
    printf("Carta 1 - %s (%s): %.2f\n", carta1.cidade, carta1.estado, valor1);
    printf("Carta 2 - %s (%s): %.2f\n\n", carta2.cidade, carta2.estado, valor2);

    // === DETERMINA O VENCEDOR COM IF-ELSE ===
    if (valor1 == valor2) {
        printf("Resultado: EMPATE! Ambas as cartas tem o mesmo valor.\n");
    }
    else if (maior_vence) {
        // Maior valor ganha
        if (valor1 > valor2) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.cidade);
        } else {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.cidade);
        }
    }
    else {
        // Menor valor ganha (densidade populacional)
        if (valor1 < valor2) {
            printf("Resultado: Carta 1 (%s) venceu!\n", carta1.cidade);
        } else {
            printf("Resultado: Carta 2 (%s) venceu!\n", carta2.cidade);
        }
    }

    printf("======================================\n");
    return 0;
}
