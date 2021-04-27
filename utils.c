// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"


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

void howToPlay();

void menu(){

    mostrarASCII();
    int escolha;
    printf("1 - Jogador vs Jogador\n");
    printf("2 - Jogador vs Computador\n");
    printf("3 - Instruções de como jogar\n");
    printf("0 - Sair do jogo\n\n");

    printf("Opção: ");
    scanf("%d", &escolha);
    
    switch (escolha){
        case 1:
            break;
        case 2:
            break;
        case 3:
            howToPlay();
        case 0:
            exit(0);
        default:
            menu();
    }

}

void howToPlay(){
    mostrarASCII();
    printf("");
    printf("> O jogo do Semáforo é um jogo de tabuleiro entre 2 pessoas que efetuam jogadas alternadas ");
    printf("até que uma delas vença ou que se verifique um empate\n\n");
    printf("> É gerado um tabuleiro quadrado com dimensão aleatória (entre 3 e 5 linhas) e cada jogador ");
    printf("pode escolher jogar uma peça ou utilizar uma habilidade espcial.\n");
    printf("\nContinuar? (S/N) ");
    char continuar, continuar1;
    do {
        scanf("%c", &continuar);

        if (continuar == 'N') menu();
        else if (continuar == 'S') break;

    } while (continuar != 'S' || continuar != 'N');

    mostrarASCII();
    printf("> Alternadamente os jogadores vão colocando peças de cor\nVERDE (G), AMARELA (Y) e VERMELHA (R)\n\n");
    printf("> Ganha o jogador que coloque uma peça que permita formar uma linha, coluna ou diagonal completa com peças da mesma cor\n");
    printf("\nContinuar? (S/N) ");
    do {
        scanf("%c", &continuar1);

        if (continuar1 == 'N') menu();
        else if (continuar1 == 'S') break;

    } while (continuar1 != 'S' || continuar1 != 'N');

    mostrarASCII();
    printf("> As jogadas válidas relativas a colocar uma peça são as seguintes:\n\n");
    printf("1. Colocar uma peça VERDE numa célula vazia\n");
    printf("2. Trocar uma peça VERDE por uma peça AMARELA\n");
    printf("3. Trocar uma peça AMARELA por uma peça VERMELHA\n");
    printf("\nContinuar? (S/N) ");
    do {
        scanf("\n%c", &continuar);

        if (continuar == 'N') menu();
        else if (continuar == 'S') break;

    } while (continuar != 'S' || continuar != 'N');

    mostrarASCII();
    printf("> Para além de jogarem peças, os jogadores podem também utilizar habilidades espciais:\n\n");
    printf("1. Colocar uma pedra numa célula vazia (limitada a 1 por jogo)\n");
    printf("2. Adicionar uma nova linha ou coluna ao final do tabuleiro (limitada a 2 por jogo)\n");
    printf("\nContinuar? (S/N) ");
    do {
        scanf("%c", &continuar);

        if (continuar == 'N') menu();
        else if (continuar == 'S') menu();

    } while (continuar != 'S' || continuar != 'N');

}