// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "utils.c"
#include "engine.h"
#include "engine.c"

typedef struct {
    char nome;
    int pedras;
    int expandir;
} Jogador;

int mainAAA(){
    initRandom();
    int randomDim = 3;
    int linhasTotais = randomDim;
    int colunasTotais = randomDim;

    char **tabuleiro = gerarTabuleiro(randomDim);
    linhasTotais += 2;
    tabuleiro = expandirTabuleiro(tabuleiro, linhasTotais, colunasTotais, 'L');
    mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais);
}

int main(){

    if(existeFicheiro()){
        
        mostrarASCII();
        char escolha;
        printf("Foi encontrado um ficheiro de jogo.\nPretende continuar o jogo anterior? (S/N)\n");
        do {
            scanf("%c", &escolha);

            if (escolha == 'N') break;
            else if (escolha == 'S') break;

        } while (escolha != 'S' || escolha != 'N');

        if (escolha == 'S') printf("Escolheu a opção SIM\n");
        else printf("Escolheu a opção NÃO\n");
    }

    else {
        menu();
        initRandom();

        Jogador jogadorA;
        Jogador jogadorB;

        jogadorA.nome = 'A';
        jogadorA.pedras = 1;
        jogadorA.expandir = 2;

        jogadorB.nome = 'B';
        jogadorB.pedras = 1;
        jogadorB.expandir = 2;

        int randomDim = intUniformRnd(3, 5);
        int linhasTotais = randomDim;
        int colunasTotais = randomDim;

        char **tabuleiro = gerarTabuleiro(randomDim);
        mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais);


        int linha, coluna, pedras, expandir, turno = 0;
        char cor, escolha, habilidade, tipo;

        do{
            if(turno == 0) printf("\n[JOGADOR A]\n");
            else printf("\n[JOGADOR B]\n");

            printf("Que jogada queres efetuar? (P - Peça / H - Habilidade / E - Sair): ");
            scanf("%c", &escolha);
            switch(escolha){
                case 'P':
                    printf("Onde queres colocar a tua peça? (Linha Coluna Cor): ");
                    scanf("%d %d %c", &linha, &coluna, &cor);

                    if(colocarPeca(tabuleiro, cor, linha, coluna)){
                        if(turno == 0) turno = 1;
                        else turno = 0;
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
                        if(colocarPeca(tabuleiro, 'X', linha, coluna)){
                            if(turno == 0){
                                jogadorA.pedras = pedras - 1;
                                turno = 1;
                            }
                            else{
                                jogadorB.pedras = pedras - 1;
                                turno = 0;
                            }
                        }
                    }
                    if(habilidade == 'E' && expandir > 0){
                        printf("Qual é o tipo de expansão que queres fazer? (L - Linha / C - Coluna): ");
                        scanf("\n%c", &tipo);
                        printf("%d", linhasTotais);
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
                    }

                    break;

                case 'E':
                    exit(0);

                default:
                    break;
            }

            mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais);

        } while (1);

    }

    return 0;

}