// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================


/*
  territorios.c
  Programa simples para cadastrar 5 territórios (estrutura Territorio)
  - Cada Territorio possui: nome (até 29 chars), cor (até 9 chars) e tropas (int)
  - Após o cadastro dos 5 territórios, o programa exibe todos os dados.
  - Comentários explicam criação da struct, leitura e exibição.
*/

#include <stdio.h>
#include <string.h>

#define NUM_TERRITORIOS 5

// --- Definição da struct Território:

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Função buffer
void limpar_buffer_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* descarta */ }
}
// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

int main(void) {
    Territorio lista[NUM_TERRITORIOS];

    printf("=== Cadastro de %d Territórios ===\n\n", NUM_TERRITORIOS);

    /* Laço de entrada: pede nome, cor e tropas para cada território */
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);

        /* Lê o nome (permite espaços). O formato " %29[^\n]" ignora
           espaços em branco iniciais e lê até o '\n' (máx 29 chars). */
        printf("  Nome (até 29 caracteres, pode conter espacos): ");
        if (scanf(" %29[^\n]", lista[i].nome) != 1) {
            /* Caso improvável: garantir string vazia */
            lista[i].nome[0] = '\0';
        }

        /* Lê a cor do exército (uma palavra sem espaços é suficiente) */
        printf("  Cor do exército (ex: vermelho, azul): ");
        if (scanf(" %9s", lista[i].cor) != 1) {
            lista[i].cor[0] = '\0';
        }

        /* Lê o número de tropas, validando entrada inteira >= 0 */
        printf("  Numero de tropas (inteiro >= 0): ");
        while (1) {
            if (scanf("%d", &lista[i].tropas) == 1 && lista[i].tropas >= 0) {
                /* entrada válida */
                break;
            } else {
                /* entrada inválida: limpa buffer e pede novamente */
                printf("    Entrada invalida. Digite um numero inteiro >= 0: ");
                limpar_buffer_stdin();
            }
        }

        printf("\n");
        
    }
/* Exibição dos dados cadastrados: percorre o vetor e imprime com formatação clara */
    printf("=== Territórios cadastrados ===\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Territorio %d\n", i + 1);
        printf("  Nome : %s\n", lista[i].nome);
        printf("  Cor  : %s\n", lista[i].cor);
        printf("  Tropas: %d\n", lista[i].tropas);
        printf("---------------------------\n");
    }

    printf("Fim do programa.\n");
    return 0;
}

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
