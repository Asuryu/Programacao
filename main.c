// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

// GUARDAR A STRUCT NUM BINARY FILE
// GUARDAR A STRUCT NUM BINARY FILE
// GUARDAR A STRUCT NUM BINARY FILE

// FAZER UM JOGADOR AUTOMÁTICO
// FAZER UM JOGADOR AUTOMÁTICO
// FAZER UM JOGADOR AUTOMÁTICO

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "engine.h"
#include "files.h"

#include "utils.c"
#include "engine.c"
#include "files.c"



int main(){

    Jogador jogadorA;
    Jogador jogadorB;
    int jogada;

    int flag = 0;

    if(existeFicheiro()){
        
        mostrarASCII();
        char escolha;
        printf("Foi encontrado um ficheiro de jogo.\nPretende continuar o jogo anterior?\n\n");
        do {
            printf("Continuar? (S/N) ");
            scanf("\n%c", &escolha);

            if (escolha == 'N') break;
            else if (escolha == 'S') break;

        } while (escolha != 'S' || escolha != 'N');

        if (escolha == 'S') flag = 1;

    }

    initRandom();

    ptabuleiro lista = NULL;
    ptabuleiro aux;

    int randomDim;
    int computador;
    int linhasTotais, colunasTotais, turno = 0;
    char **tabuleiro;

    if(flag == 0){

        if(menu() == 0) computador = 0;
        else computador = 1;

        jogadorA.nome = 'A';
        jogadorA.pedras = 1;
        jogadorA.expandir = 2;

        jogadorB.nome = 'B';
        jogadorB.pedras = 1;
        jogadorB.expandir = 2;

        randomDim = intUniformRnd(3, 5);
        linhasTotais = randomDim;
        colunasTotais = randomDim;
        jogada = 1;

        tabuleiro = gerarTabuleiro(linhasTotais, colunasTotais);
        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, 0, NULL, computador, NULL, NULL, NULL);
    
    } else {

        lista = recuperaJogo(&jogadorA, &jogadorB);

        aux = lista;
        while(aux->prox != NULL){
            computador = aux->cpu;
            linhasTotais = aux->linhas;
            colunasTotais = aux->colunas;
            jogada = aux->cota;
            turno = aux->jogador;
            tabuleiro = aux->tab;
            aux = aux->prox;
        }

    }

    int linha, coluna, pedras, expandir, jogadaAleatoria, l, c, cr;
    char cor, escolha, habilidade, tipo;

    do{
        
        mostrarASCII();
        mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais);

        if(computador == 0){
            if(turno == 0) printf("\n[JOGADOR A]\n");
            else printf("\n[JOGADOR B]\n");
        } else if(computador == 1) {
            if(turno == 0) printf("\n[JOGADOR A]\n");
            else{
                int retorno = 0;
                do{
                    jogadaAleatoria = intUniformRnd(1, 3);
                    retorno = verificaJogadaCPU(tabuleiro, linhasTotais, colunasTotais, jogada, jogadaAleatoria, &jogadorB);

                } while(retorno == 0);
                

                mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais);
                printf("\n[COMPUTADOR]\n");
                if(jogadaAleatoria == 1){
                    printf("Usou uma peça");
                    
                    if(retorno == 1){
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, 22, turno, computador, 'G', 0, 0);
                    }
                    else if(retorno == 2){
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, 22, turno, computador, 'Y', 0, 0);
                    } 
                    else if(retorno == 3){
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, 22, turno, computador, 'R', 0, 0);
                    } 
                } 
                else if(jogadaAleatoria == 2){
                    printf("Usou uma pedra");
                    lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, 22, turno, computador, 'X', 0, 0);
                } 
                else if(jogadaAleatoria == 3){
                    printf("Usou uma expansão");
                    colunasTotais++;
                    lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, 22, turno, computador, 'E', 0, 0);
                } 

                mostra_info(lista);
                scanf("%d", &computador);

                jogada++;
                turno = 0;
            }
        }

        printf("Que jogada queres efetuar? (P - Peça / H - Habilidade / T - Tabuleiro / E - Sair): ");
        scanf("%c", &escolha);
        switch(escolha){
            case 'P':
                printf("Onde queres colocar a tua peça? (Linha Coluna Cor): ");
                scanf("%d %d %c", &linha, &coluna, &cor);

                if(colocarPeca(tabuleiro, cor, linha, coluna, linhasTotais, colunasTotais)){
                    if(jogadaVencedora(tabuleiro, cor, linha, coluna, linhasTotais, colunasTotais, turno)){
                        
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, cor, linha, coluna);

                        char exportar;
                        do {
                            printf("\nExportar ficheiro do jogo? (S/N) ");
                            fflush(stdin);
                            scanf("%c", &exportar);

                            if (exportar == 'N'){
                                free(tabuleiro);
                                exit(0);
                            }
                            else if (exportar == 'S') break;

                        } while (exportar != 'S' || exportar != 'N');

                        mostrarASCII();
                        char fname[30];
                        printf("\nIntroduza um nome para o ficheiro\n>> ");
                        fflush(stdin);
                        fgets(fname, 30, stdin);
                        exportarJogo(fname, lista);
                        free(tabuleiro);
                        exit(0);

                    }
                    else {
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, cor, linha, coluna);
                        jogada++;
                        if(turno == 0) turno = 1;
                        else turno = 0;
                    }
                }

                break;

            case 'H':
                if(turno == 0){
                    pedras = jogadorA.pedras;
                    expandir = jogadorA.expandir;
                }
                else{
                    pedras = jogadorB.pedras;
                    expandir = jogadorB.expandir;
                }

                printf("> Tens %d PEDRAS para jogares\n", pedras);
                printf("> Podes EXPANDIR mais %d vezes\n", expandir);

                printf("Que habilidade queres utilizar? (P - Pedra / E - Expandir): ");
                scanf("\n%c", &habilidade);
                
                if(habilidade == 'P' && pedras > 0){
                    printf("Onde queres colocar a tua pedra? (Linha Coluna): ");
                    scanf("%d %d", &linha, &coluna);
                    if(colocarPeca(tabuleiro, 'X', linha, coluna, linhasTotais, colunasTotais)){
                        if(turno == 0){
                            jogadorA.pedras = pedras - 1;
                            turno = 1;
                        }
                        else{
                            jogadorB.pedras = pedras - 1;
                            turno = 0;
                        }
                        
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, 'X', linha, coluna);
                        jogada++;
                    }
                }
                if(habilidade == 'E' && expandir > 0){
                    printf("Qual é o tipo de expansão que queres fazer? (L - Linha / C - Coluna): ");
                    scanf("\n%c", &tipo);
                    if(tipo == 'L') linhasTotais += 1;
                    else if(tipo == 'C') colunasTotais += 1;
                    else break;

                    tabuleiro = expandirTabuleiro(tabuleiro, linhasTotais, colunasTotais, tipo);

                    if(turno == 0){
                        jogadorA.expandir = expandir - 1;
                        turno = 1;
                    }
                    else{
                        jogadorB.expandir = expandir - 1;
                        turno = 0;
                    }
                    lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, 'E', NULL, NULL);
                    jogada++;
                }

                break;

            case 'T':
                mostrarASCII();
                int k;
                char continuar;
                do {
                    mostrarASCII();
                    if(jogada == 1) k = 0;
                    else if(jogada == 2) k = 1;
                    else{
                        printf("Qual o número de jogadas que quer recuar para visualizar? (1 - %d) ", nrElementos(lista));
                        scanf("%d", &k);
                        printf("\n");
                    }
                    
                    if(procura_cota(lista, nrElementos(lista) - k)){
                        
                        do {
                            printf("\nContinuar? (S/N) ");
                            scanf("\n\n%c", &continuar);
                            break;
                        } while (continuar != 'S' || continuar != 'N');
                        
                        if(continuar == 'S') break;
                    }

                } while ((k > nrElementos(lista) || k <= 0) || continuar == 'N');

                break;

            case 'E':
                mostrarASCII();
                printf("Antes de sair pretende guardar o jogo para retomar mais tarde?\n");
                printf("\nGuardar? (S/N) ");

                char guardar;
                do {
                    scanf("%c", &guardar);

                    if (guardar == 'S'){
                        guardaJogo(lista, &jogadorA, &jogadorB);
                        break;
                    }
                    else if (guardar == 'N') break;

                } while (guardar != 'S' || guardar != 'N');
                
                liberta_lista(lista);
                free(tabuleiro);
                exit(0);

            default:
                break;
        }

    } while (1);

    return 0;

}