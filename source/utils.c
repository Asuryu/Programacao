// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
// Tomás Gomes Silva - 2020143845

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/utils.h"

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
    fclose(f);
    return 1;
}

void mostrarASCII(){

    system("@cls||clear");
    printf("   _____                      ____                     \n");
    printf("  / ___/___  ____ ___  ____ _/ __/___  _________  _____\n");
    printf("  |__ \\/ _ \\/ __ `__ \\/ __ `/ /_/ __ \\/ ___/ __ \\/ ___/\n");
    printf(" ___/ /  __/ / / / / / /_/ / __/ /_/ / /  / /_/ (__  ) \n");
    printf("/____/\\___/_/ /_/ /_/\\__,_/_/  \\____/_/   \\____/____/  \n");
    printf("                                                       \n");
    printf("Jogo dos Sem\u00E1foros - Trabalho Pr\u00E1tico de Programa\u00E7\u00E3o\n\n\n");

}

void howToPlay();

int menu(){

    mostrarASCII();
    int escolha = - 1;
    printf("1 - Jogador vs Jogador\n");
    printf("2 - Jogador vs Computador\n");
    printf("3 - Instru\u00E7ões de como jogar\n");
    printf("0 - Sair do jogo\n\n");

    printf("Op\u00E7\u00E3o: ");
    fflush(stdin);
    scanf("%d", &escolha);

    if(escolha == 1) return 0;
    else if(escolha == 2) return 1;
    else if(escolha == 3) howToPlay();
    else if(escolha == 0) exit(0);
    else menu();
}

void howToPlay(){
    mostrarASCII();
    printf("");
    printf("> O jogo do Sem\u00E1foro \u00E9 um jogo de tabuleiro entre 2 pessoas que efetuam jogadas alternadas ");
    printf("at\u00E9 que uma delas ven\u00E7a ou que se verifique um empate.\n\n");
    printf("> \u00C9 gerado um tabuleiro quadrado com dimens\u00E3o aleat\u00F3ria (entre 3 e 5 linhas) e cada jogador ");
    printf("pode escolher jogar uma pe\u00E7a ou utilizar uma habilidade especial.\n\n");
    char continuar;
    printf("\nPressione a tecla ENTER para continuar");
    fflush(stdin);
    getchar();

    mostrarASCII();
    printf("> Alternadamente, os jogadores v\u00E3o colocando pe\u00E7as de cor\nVERDE (G), AMARELA (Y) ou VERMELHA (R)\n\n");
    printf("> Ganha o jogador que coloque uma pe\u00E7a que permita formar uma linha, coluna ou diagonal completa com pe\u00E7as da mesma cor\n\n");
    printf("\nPressione a tecla ENTER para continuar");
    fflush(stdin);
    getchar();

    mostrarASCII();
    printf("> As jogadas v\u00E1lidas relativas a colocar uma pe\u00E7a s\u00E3o as seguintes:\n\n");
    printf("1. Colocar uma pe\u00E7a VERDE numa c\u00E9lula vazia\n");
    printf("2. Trocar uma pe\u00E7a VERDE por uma pe\u00E7a AMARELA\n");
    printf("3. Trocar uma pe\u00E7a AMARELA por uma pe\u00E7a VERMELHA\n\n");
    printf("\nPressione a tecla ENTER para continuar");
    fflush(stdin);
    getchar();


    mostrarASCII();
    printf("> Para além de jogarem pe\u00E7as, os jogadores podem tamb\u00E9m utilizar habilidades especiais:\n\n");
    printf("1. Colocar uma pedra numa c\u00E9lula vazia (limitada a 1 por jogo)\n");
    printf("2. Adicionar uma nova linha ou coluna ao final do tabuleiro (limitada a 2 por jogo)\n\n");
    printf("\nPressione a tecla ENTER para continuar");
    fflush(stdin);
    getchar();

    return;

}