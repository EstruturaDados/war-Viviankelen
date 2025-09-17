#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para remover '\n' lido por fgets

void remover_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Cadastro dos territórios

void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);

        printf("Nome do territorio: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        remover_newline(mapa[i].nome);

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        remover_newline(mapa[i].cor);

        printf("Numero de tropas: ");
        while (scanf("%d", &mapa[i].tropas) != 1 || mapa[i].tropas < 0) {
            printf("Valor invalido. Digite um número >= 0: ");
            while (getchar() != '\n'); // limpa buffer
        }
        getchar(); // limpa '\n' do buffer
    }
}

// Exibição dos territórios
void exibirTerritorios(Territorio *mapa, int n) {
    printf("\n\n=== MAPA DO MUNDO - ESTADO ATUAL ===\n\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função de ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Não é permitido atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 0) {
        printf("O território atacante não tem tropas suficientes!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
	printf("\n=== RESULTADO DA BATALHA ===\n\n");
    printf("\nDados rolados -> Atacante rolou os dados e tirou: %d | Defensor rolou os dados e tirou: %d\n",
           dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nVITORIA DO ATACANTE!\n");
        strcpy(defensor->cor, atacante->cor);       // muda dono
        defensor->tropas = atacante->tropas / 2;   // metade das tropas do atacante
    } else {
        printf("\nDEFESA BEM-SUCEDIDA!\n");
        atacante->tropas--;  // atacante perde uma tropa
    }
}

// Liberação da memória
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main(void) {
    srand(time(NULL)); // inicializa aleatoriedade

    int numTerritorios;
    printf("Digite o numero de territorios a cadastrar: ");
    while (scanf("%d", &numTerritorios) != 1 || numTerritorios <= 0) {
        printf("Valor inválido. Digite um número positivo: ");
        while (getchar() != '\n'); // limpa buffer
    }
    getchar(); // limpa '\n' após scanf

    // Alocação dinâmica
    
    Territorio *mapa = (Territorio *)calloc(numTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("ERRO AO ALOCAR MEMORIA.\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, numTerritorios);
    exibirTerritorios(mapa, numTerritorios);

    // Loop de ataques
    int atacante, defensor;
    while (1) {
        printf("\n=== FASE DE ATAQUE ===\n\n");
        printf("Digite o indice do territorio atacante (-1 para sair): ");
        scanf("%d", &atacante);
        if (atacante == -1) break;

        printf("Digite o indice do territorio defensor: ");
        scanf("%d", &defensor);

        if (atacante >= 0 && atacante < numTerritorios &&
            defensor >= 0 && defensor < numTerritorios &&
            atacante != defensor) {
            atacar(&mapa[atacante], &mapa[defensor]);
        } else {
            printf("INDICES INVALIDOS.\n");
        }

        // Mostrar territórios após cada ataque
        exibirTerritorios(mapa, numTerritorios);
    }

    // Liberação da memória
    liberarMemoria(mapa);

    printf("\nFim do programa.\n");
    return 0;
}

