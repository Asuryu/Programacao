// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "engine.h"
#include "files.h"
#include "utils.c"
#include "engine.c"
#include "files.c"


int mainAAA(){

    initRandom();

    plivro lista = NULL;
    char **tabuleiro;
    int randomDim;
    int linhasTotais, colunasTotais;

    randomDim = intUniformRnd(3, 5);
    linhasTotais = randomDim;
    colunasTotais = randomDim;
    
    tabuleiro = gerarTabuleiro(linhasTotais, colunasTotais);
    lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, 0);

    tabuleiro[0][0] = 'C';
    lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, 1);

    tabuleiro[1][1] = 'P';
    lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, 2);


    //mostra_info(lista);
    printf("\n\n\n\n\n");
    //procura_cota(lista, 2);
    printf("%d", nrElementos(lista));
    liberta_lista(lista);

    return 0;
}

int main(){

    int flag = 0;

    if(existeFicheiro()){
        
        mostrarASCII();
        char escolha;
        printf("Foi encontrado um ficheiro de jogo.\nPretende continuar o jogo anterior?\n");
        printf("\nContinuar? (S/N) ");
        do {
            scanf("%c", &escolha);

            if (escolha == 'N') break;
            else if (escolha == 'S') break;

        } while (escolha != 'S' || escolha != 'N');

        if (escolha == 'S') flag = 1;

    }

    initRandom();
    plivro lista = NULL;

    Jogador jogadorA;
    Jogador jogadorB;

    int randomDim;
    int linhasTotais, colunasTotais, turno;
    char **tabuleiro;

    if(flag == 0){
        menu();

        jogadorA.nome = 'A';
        jogadorA.pedras = 1;
        jogadorA.expandir = 2;

        jogadorB.nome = 'B';
        jogadorB.pedras = 1;
        jogadorB.expandir = 2;

        randomDim = intUniformRnd(3, 5);
        linhasTotais = randomDim;
        colunasTotais = randomDim;

        tabuleiro = gerarTabuleiro(linhasTotais, colunasTotais);
        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, 0);
    
    } else {
        // LER DO FICHEIRO DO JOGO ANTERIOR

        // Carregar:
        // 1. Tabela
        // 2. LINHAS E COLUNAS
        // 3. TURNO
        // 4. JOGADORES

        tabuleiro = recuperaJogo(tabuleiro, &linhasTotais, &colunasTotais, &turno, &jogadorA, &jogadorB);
        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, 0);
        scanf("%d", randomDim);
    }

    int linha, coluna, pedras, expandir;
    char cor, escolha, habilidade, tipo;
    int jogada = 1;

    do{
        mostrarASCII();
        mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais);

        if(turno == 0) printf("\n[JOGADOR A]\n");
        else printf("\n[JOGADOR B]\n");

        printf("Que jogada queres efetuar? (P - Peça / H - Habilidade / T - Tabuleiro / E - Sair): ");
        scanf("%c", &escolha);
        switch(escolha){
            case 'P':
                printf("Onde queres colocar a tua peça? (Linha Coluna Cor): ");
                scanf("%d %d %c", &linha, &coluna, &cor);

                if(colocarPeca(tabuleiro, cor, linha, coluna, linhasTotais, colunasTotais)){
                    if(jogadaVencedora(tabuleiro, cor, linha, coluna, linhasTotais, colunasTotais, turno)){
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
                        exportarJogo(fname);
                        free(tabuleiro);
                        exit(0);

                    }
                    else {
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada);
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
                        
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada);
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
                    lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada);
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
                
                printf("\n\n");
                //mostra_info(lista);
                procura_cota(lista, 0);
                liberta_lista(lista);

                char guardar;
                do {
                    scanf("%c", &guardar);

                    if (guardar == 'S'){
                        guardaJogo(tabuleiro, linhasTotais, colunasTotais, turno, &jogadorA, &jogadorB);
                        break;
                    }
                    else if (guardar == 'N') break;

                } while (guardar != 'S' || guardar != 'N');
                free(tabuleiro);
                exit(0);

            default:
                break;
        }

    } while (1);

    return 0;

}