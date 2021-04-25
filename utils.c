// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}

int existeFicheiro(){
    FILE *f;

    f = fopen("jogo.bin", "rb");
    if(f == NULL) return 0;
    return 1;
}

void mostrarASCII(){

    system("clear");
    printf("   _____                      ____                     \n");
    printf("  / ___/___  ____ ___  ____ _/ __/___  _________  _____\n");
    printf("  |__ \\/ _ \\/ __ `__ \\/ __ `/ /_/ __ \\/ ___/ __ \\/ ___/\n");
    printf(" ___/ /  __/ / / / / / /_/ / __/ /_/ / /  / /_/ (__  ) \n");
    printf("/____/\\___/_/ /_/ /_/\\__,_/_/  \\____/_/   \\____/____/  \n");
    printf("                                                       \n");
    printf("Jogo dos Semáforos - Trabalho Prático de Programação\n\n\n");

}

void howToPlay(){
    mostrarASCII();
    printf("");
    printf("");
}

void menu(){

    printf("\e[1;1H\e[2J");
    mostrarASCII();
    int escolha;
    printf("1 - Começar um jogo\n");
    printf("2 - Instruções de como jogar\n");
    printf("0 - Sair do jogo\n\n");

    printf("Opção: ");
    scanf("%d", &escolha);
    
    switch (escolha){
        case 1:
            break;
        case 2:
            howToPlay();
        case 0:
            exit(0);
        default:
            menu();
    }

}

char **gerarTabuleiro(int dim){

    char **tabuleiro;
 
    tabuleiro = (char **)malloc(sizeof(char *)*dim);

    for(int i = 0; i < dim; i++){
        tabuleiro[i] = (char *)malloc(sizeof(char)*dim);
    }

    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            tabuleiro[i][j] = '_';
        }
    }

    return tabuleiro;

}

void mostrarTabuleiro(char **tabuleiro, int dim){

    mostrarASCII();
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }

}

int colocarPeca(char **tabuleiro, char cor, int l, int c){

    switch(cor){
        case 'G':
            if(tabuleiro[l][c] == '_'){
                tabuleiro[l][c] = 'G';
                return 1;
            }
            printf("Não podes colocar a peça VERDE nessa posição\n");
            return 0;

        case 'Y':
            if(tabuleiro[l][c] == 'G'){
                tabuleiro[l][c] = 'Y';
                return 1;
            }
            printf("Não podes colocar a peça AMARELA nessa posição\n");
            return 0;

        case 'R':
            if(tabuleiro[l][c] == 'Y'){
                tabuleiro[l][c] = 'R';
                return 1;
            }
            printf("Não podes colocar a peça VERMELHA nessa posição\n");
            return 0;

        default:
            printf("Escolhe uma cor válida para jogares\n");
            return 0;
    }
        

    if(tabuleiro[l][c] == '_'){
        tabuleiro[l][c] = 'V';
    }

}