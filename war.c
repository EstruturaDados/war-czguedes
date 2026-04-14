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

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define NUM_TERRITORIOS 5

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.

// Funções de setup e gerenciamento de memória:
Territorio* alocarMapa(int qteMapas);
void liberarMemoria(Territorio* mapa);

// Funções de interface com o usuário:
void imprimirBorder(const char* texto);
void inicializarTerritorios(Territorio* allTerritorios, int qteMapas);
void exibirMapa(int qteMapas, const Territorio* allTerritorios);
int exibirMenuPrincipal();

// Funções de lógica principal do jogo:
void simularAtaque(Territorio*atk, Territorio*def);
void faseDeAtaque(Territorio* allTerritorios, int qteMapas);

// Função utilitária:
void limparBufferEntrada();

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    int qteMapas;
    int isRunning = 1;
    

    imprimirBorder("SETUP");
    printf("Qual a quantidade de territórios no mapa? (Máximo %d)\n", NUM_TERRITORIOS);
    scanf("%d", &qteMapas);

    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    Territorio* allTerritorios = alocarMapa(qteMapas);
    limparBufferEntrada();
    
    imprimirBorder("WAR ESTRUTURADO");
    printf("\nBem-vindo ao jogo War.\n\n");
    printf("Antes de iniciar, precisamos cadastrar territórios.\nPara cada um deles você deverá definir um nome, uma cor, e a quantidade de tropas que estarão neste.\n");
    printf("\nVamos prosseguir?\n");
    
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    inicializarTerritorios(allTerritorios, qteMapas);

    //IMPRIME AS CARACTERÍSTICAS DE CADA TERRITORIO
    exibirMapa(qteMapas, allTerritorios);
    

    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.
    do
    {
        int iterator = exibirMenuPrincipal();

        switch (iterator)
        {
        case 1:
            exibirMapa(qteMapas, allTerritorios);
            faseDeAtaque(allTerritorios, qteMapas);
            break;
        case 2:
            // Verificar Missão
            break;
        case 0:
            printf("Saindo do jogo...\n");
            isRunning = 0;
            break;
        
        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
        }

    } while (isRunning);
    
    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    liberarMemoria(allTerritorios);
    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.
Territorio* alocarMapa(int qteMapas){    
    Territorio* mapa = (Territorio*) calloc(qteMapas, sizeof(Territorio));

    if(mapa == NULL){
        printf("Erro ao alocar memória para o mapa.\n");
        exit(1);
    };

    return mapa;
};

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
void inicializarTerritorios(Territorio* allTerritorios, int qteMapas){
    for (size_t i = 0; i < qteMapas; i++)
    {
        printf("\n--- CADASTRANDO TERRITÓRIO %zu ---\n", i+1);
        //CADASTRAR NOME
        printf("Nome do Território:\t");
        fgets(allTerritorios[i].nome, sizeof(allTerritorios[i].nome), stdin);
        //CADASTRAR COR
        printf("Cor das Tropas:\t");
        fgets(allTerritorios[i].cor, sizeof(allTerritorios[i].cor), stdin);
        //CADASTRAR No. TROPAS
        printf("Quantidade de Tropas:\t");
        scanf("%d", &allTerritorios[i].tropas);
        printf("\n");

        limparBufferEntrada();        
    }
};


// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.
void liberarMemoria(Territorio* mapa){
    free(mapa);
};

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.
int exibirMenuPrincipal(){
    int iterator;

    imprimirBorder("--- MENU PRINCIPAL ---");
    printf("1. Atacar\n");
    printf("2. Verificar Missão\n");
    printf("0. Sair do Jogo\n");
    printf("Escolha uma opção:\n"); 
    scanf("%d", &iterator);

    return iterator;
};

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
void exibirMapa(int qteMapas, const Territorio* allTerritorios){
    imprimirBorder("MAPA ATUAL");

    for (size_t j = 0; j < qteMapas; j++)
    {
        printf("\n--- TERRITÓRIO %zu ---\n", j+1);     
        printf("Nome:\t %s", allTerritorios[j].nome);
        printf("Cor:\t %s", allTerritorios[j].cor);
        printf("Num. Tropas:\t %d", allTerritorios[j].tropas);
        printf("\n");
    }
};

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.
void faseDeAtaque(Territorio* allTerritorios, int qteMapas){
    int atk, def;

    printf("\nEscolha o número do território de origem (atacante):\n");
    scanf("%d", &atk);
    printf("Escolha o número do território de destino (defensor):\n");
    scanf("%d", &def);

    if(atk<1 || atk>qteMapas || def<1 || def>qteMapas){
        printf("Número de território inválido. Tente novamente.\n");
        getchar();
        return;
    }

    if(atk == def){
        printf("O território de origem e destino não podem ser o mesmo. Tente novamente.\n");
        getchar();
        return;
    }
    simularAtaque(&allTerritorios[atk-1], &allTerritorios[def-1]);
    limparBufferEntrada();
};

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.
void simularAtaque(Territorio*atk, Territorio*def){
    //validar se é possível atacar
    if(atk->tropas < 2){
        printf("Você precisa de pelo menos 2 tropas para atacar.\n");
        return;
    }

    //rolar os dados
    int dadoATk = (rand() % 6)+1;
    int dadoDef = (rand() % 6)+1;

    //Mostrar resultado
    printf("Dado do Atacante: %d\n", dadoATk);
    printf("Dado do Defensor: %d\n", dadoDef);

    //comparar resultados
    if(dadoATk > dadoDef){
        printf("Atacante vence a batalha!\n");
        def->tropas -= 1;
    } else {
        printf("Defensor vence a batalha!\n");
        atk->tropas -= 1;
    }
    //verificar posse do território
    if(def->tropas==0){
        printf("Território conquistado!\n");        
    }
    getchar();
};

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada(){
    int c;
    while ((c=getchar()) != '\n' && c != EOF);
    
}

//imprimirBorder():
//Função utilitária para imprimir uma borda decorativa no console, usada para separar seções do jogo e melhorar a estética da interface.
void imprimirBorder(const char* texto) {
    int largura = 50; // largura fixa do quadro
    int i;

    // linha superior
    printf("╔");
    for(i = 0; i < largura; i++) printf("═");
    printf("╗\n");

    // texto centralizado simples
    printf("║ %-48s ║\n", texto);

    // linha inferior
    printf("╚");
    for(i = 0; i < largura; i++) printf("═");
    printf("╝\n");
}