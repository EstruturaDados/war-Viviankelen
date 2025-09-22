#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//--- Estruturas do Jogo ---

// Estrutura para representar um territorio
typedef struct {
    char nome[30];
    char cor_jogador[10]; // Cor do jogador que controla o territorio
    int tropas;
} Territorio;

//--- Prototipos das Funcoes ---
void exibirMenu();
void inicializarMapa(Territorio* mapa, const int tamanho);
void liberarMemoria(Territorio* mapa, char** missoes_jogadores, int num_jogadores);
void exibirMapa(const Territorio* mapa, const int tamanho);
void exibirMissao(const char* missao);
void atribuirMissao(char* destino, char* missoes[], const int totalMissoes);
int verificarMissao(const char* missao, const Territorio* mapa, const int tamanho, const char* cor_jogador);
void atacar(Territorio* atacante, Territorio* defensor);

//--- Funcoes do Jogo ---

// Exibe as opcoes do menu para o jogador.

void exibirMenu() {
    printf("\n--- Menu do Jogador ---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair do Jogo\n");
    printf("------------------------\n");
    printf("Escolha uma opcao: ");
}

/*
 * Inicializa o mapa com territorios e tropas padroes.
 */
void inicializarMapa(Territorio* mapa, const int tamanho) {
    // Inicializacao dos territorios com os dados fornecidos
    strcpy(mapa[0].nome, "America");
    strcpy(mapa[0].cor_jogador, "Verde");
    mapa[0].tropas = 5;

    strcpy(mapa[1].nome, "Europa");
    strcpy(mapa[1].cor_jogador, "Azul");
    mapa[1].tropas = 3;

    strcpy(mapa[2].nome, "Asia");
    strcpy(mapa[2].cor_jogador, "Vermelho");
    mapa[2].tropas = 2;

    strcpy(mapa[3].nome, "Africa");
    strcpy(mapa[3].cor_jogador, "Amarelo");
    mapa[3].tropas = 4;

    strcpy(mapa[4].nome, "Oceania");
    strcpy(mapa[4].cor_jogador, "Branco");
    mapa[4].tropas = 1;
}

//Funcao para liberar toda a memoria alocada dinamicamente.
 
void liberarMemoria(Territorio* mapa, char** missoes_jogadores, int num_jogadores) {
    printf("\nLiberando memoria...\n");
    for (int i = 0; i < num_jogadores; i++) {
        free(missoes_jogadores[i]);
    }
    free(missoes_jogadores);
    free(mapa);
    printf("Memoria liberada com sucesso.\n");
}

//Exibe o estado atual de cada territorio no mapa.

void exibirMapa(const Territorio* mapa, const int tamanho) {
    printf("\n--- Estado Atual do Mapa ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Territorio: %-20s | Dono: %-10s | Tropas: %d\n", 
               mapa[i].nome, mapa[i].cor_jogador, mapa[i].tropas);
    }
    printf("---------------------------\n");
}

//Exibe a missao de um jogador.

void exibirMissao(const char* missao) {
    printf("\nSua missao estrategica e: %s\n", missao);
}

//Sorteia e atribui uma missao a um jogador.

void atribuirMissao(char* destino, char* missoes[], const int totalMissoes) {
    int indice_sorteado = rand() % totalMissoes;
    strcpy(destino, missoes[indice_sorteado]);
}

//Verifica se a missao de um jogador foi cumprida.

int verificarMissao(const char* missao, const Territorio* mapa, const int tamanho, const char* cor_jogador) {
    // Logica para a missao "Destruir o exercito Verde"
    if (strstr(missao, "Destruir o exercito Verde")) {
        int exercito_restante = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor_jogador, "Verde") == 0) {
                exercito_restante += mapa[i].tropas;
            }
        }
        return exercito_restante == 0;
    }
    
    // Logica para a missao "Conquistar 3 territorios"
    if (strstr(missao, "Conquistar 3 territorios")) {
        int count_conquistados = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor_jogador, cor_jogador) == 0) {
                count_conquistados++;
            }
        }
        return count_conquistados >= 3;
    }

    return 0; 
}

//Simula um ataque entre dois territorios.

void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor_jogador, defensor->cor_jogador) == 0) {
        printf("Voce nao pode atacar seu proprio territorio!\n");
        return;
    }

    printf("\n%s ataca %s!\n", atacante->nome, defensor->nome);
    
    int dado_ataque = rand() % 6 + 1;
    int dado_defesa = rand() % 6 + 1;
    
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dado_ataque, dado_defesa);
    
    if (dado_ataque > dado_defesa) {
        printf("Ataque bem-sucedido! %s conquistou %s.\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor_jogador, atacante->cor_jogador);
        int tropas_transferidas = atacante->tropas / 2;
        defensor->tropas = tropas_transferidas;
        atacante->tropas -= tropas_transferidas;
    } else {
        printf("Ataque falhou! %s perdeu uma tropa.\n", atacante->nome);
        atacante->tropas--;
        if (atacante->tropas <= 0) {
            printf("%s perdeu todas as suas tropas e foi eliminado do jogo!\n", atacante->nome);
        }
    }
}

//--- Funcao Principal ---

int main() {
    srand(time(NULL));

    const int num_territorios = 5;
    const int num_jogadores = 5; 
    char* cores_jogadores[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Branco"};

    char* missoes_possiveis[] = {
        "Destruir o exercito Verde",
        "Conquistar 3 territorios",
        "Destruir o exercito Azul",
        "Conquistar 3 territorios",
        "Destruir o exercito Vermelho"
    };
    const int total_missoes = 5;

    Territorio* mapa = (Territorio*)calloc(num_territorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro na alocacao de memoria para o mapa.\n");
        return 1;
    }

    char** missoes_jogadores = (char**)malloc(num_jogadores * sizeof(char*));
    for (int i = 0; i < num_jogadores; i++) {
        missoes_jogadores[i] = (char*)malloc(100 * sizeof(char));
    }

    inicializarMapa(mapa, num_territorios);

    for (int i = 0; i < num_jogadores; i++) {
        atribuirMissao(missoes_jogadores[i], missoes_possiveis, total_missoes);
    }
    
    int jogador_atual = 0; 
    int jogo_ativo = 1;
    int opcao;

    while (jogo_ativo) {
        printf("\n--- Turno do Jogador %d (%s) ---\n", jogador_atual + 1, cores_jogadores[jogador_atual]);
        exibirMapa(mapa, num_territorios);
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int atacante_idx, defensor_idx;
                printf("Digite o indice do seu territorio para atacar (0 a %d): ", num_territorios - 1);
                scanf("%d", &atacante_idx);
                
                if (strcmp(mapa[atacante_idx].cor_jogador, cores_jogadores[jogador_atual]) != 0) {
                    printf("Voce nao controla este territorio. Tente novamente.\n");
                    continue;
                }

                printf("Digite o indice do territorio inimigo para atacar (0 a %d): ", num_territorios - 1);
                scanf("%d", &defensor_idx);
                
                if (atacante_idx >= 0 && atacante_idx < num_territorios && defensor_idx >= 0 && defensor_idx < num_territorios) {
                    atacar(&mapa[atacante_idx], &mapa[defensor_idx]);
                } else {
                    printf("Indices invalidos. O turno e perdido.\n");
                }
                break;
            }
            case 2:
                exibirMissao(missoes_jogadores[jogador_atual]);
                break;
            case 0:
                jogo_ativo = 0;
                printf("Jogo encerrado.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

        if (jogo_ativo && verificarMissao(missoes_jogadores[jogador_atual], mapa, num_territorios, cores_jogadores[jogador_atual])) {
            printf("\n--- FIM DE JOGO ---\n");
            printf("PARABENS! O jogador %d (%s) cumpriu sua missao e venceu o jogo!\n", jogador_atual + 1, cores_jogadores[jogador_atual]);
            jogo_ativo = 0;
        }

        if (opcao == 1) {
            jogador_atual = (jogador_atual + 1) % num_jogadores;
        }
    }

    liberarMemoria(mapa, missoes_jogadores, num_jogadores);

    return 0;
}
