#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------------------------------------------
// Struct Sala
// Representa cada cômodo da mansão. Cada sala pode ter um caminho
// à esquerda e outro à direita.
// -------------------------------------------------------------
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// -------------------------------------------------------------
// criarSala()
// Cria dinamicamente uma sala, define o nome e inicializa
// os ponteiros como NULL.
// -------------------------------------------------------------
Sala* criarSala(char nome[]) {
    Sala *nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// -------------------------------------------------------------
// explorarSalas()
// Permite o jogador caminhar pela mansão, escolhendo entre
// esquerda (e), direita (d) ou sair (s).
// -------------------------------------------------------------
void explorarSalas(Sala *atual) {

    char opcao;

    // enquanto a sala não for nula
    while (atual != NULL) {
        printf("\nVocê está na sala: **%s**\n", atual->nome);
        printf("Para onde deseja ir?\n");
        printf(" (e) Esquerda\n");
        printf(" (d) Direita\n");
        printf(" (s) Sair da exploração\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 's' || opcao == 'S') {
            printf("\nExploração encerrada.\n");
            return;
        }
        else if (opcao == 'e' || opcao == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Não há caminho à esquerda!\n");
            }
        }
        else if (opcao == 'd' || opcao == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Não há caminho à direita!\n");
            }
        }
        else {
            printf("Opção inválida! Tente novamente.\n");
        }

        // Se chegou em um nó folha, avisar e encerrar
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\nVocê chegou ao fim do caminho, última sala: %s\n", atual->nome);
            return;
        }
    }
}

// -------------------------------------------------------------
// main()
// Monta o mapa completo da mansão (a árvore binária) e
// inicia a exploração.
// -------------------------------------------------------------
int main() {

    // Criando as salas (nós da árvore)
    Sala *hall = criarSala("Hall de Entrada");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *cozinha = criarSala("Cozinha");
    Sala *salaJantar = criarSala("Sala de Jantar");
    Sala *sotao = criarSala("Sótão");
    Sala *jardim = criarSala("Jardim");

    // Montando o mapa manualmente (sem inserção dinâmica)
    //                 Hall
    //               /     \
    //        Biblioteca   Cozinha
    //         /               \
    //   Sala Jantar          Sótão
    //                          \
    //                         Jardim

    hall->esquerda = biblioteca;
    hall->direita = cozinha;

    biblioteca->esquerda = salaJantar;
    
    cozinha->direita = sotao;
    
    sotao->direita = jardim;

    printf("===== Detective Quest – Exploração da Mansão =====\n");
    printf("Você começará no Hall de Entrada!\n");

    explorarSalas(hall);

    return 0;
}
